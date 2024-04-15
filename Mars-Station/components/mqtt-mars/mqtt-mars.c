#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "mqtt_client.h"
#include "cJSON.h"
#include "mqtt-mars.h"
#include "math.h"
#include "led.h"

#define MQTT_BROKER "mqtt://4gpc.l.time4vps.cloud"
#define MQTT_PORT 1883
#define MQTT_TOPIC "WES/Mars/sensors"

#define DELAY_TIME_MS (5000U)


static const char *TAG = "MQTT station";


static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    // ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            // log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            // log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            // log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static esp_mqtt_client_handle_t mqtt_client_init(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER,
        .broker.address.port = MQTT_PORT,
        };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);

    return client;
};


int send_temp_hum_data(float temp, float hum)
{
    esp_mqtt_client_handle_t client = mqtt_client_init();
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "temp", round(temp * 100) / 100);
    cJSON_AddNumberToObject(root, "hum", round(hum * 100) / 100);
    cJSON *acc = cJSON_CreateObject();
    cJSON_AddNumberToObject(acc, "x", 0);
    cJSON_AddNumberToObject(acc, "y", 0);
    cJSON_AddNumberToObject(acc, "z", 0);
    cJSON_AddItemToObject(root, "acc", acc);
    char *json_str = cJSON_Print(root);

    printf("jsonn: %s", json_str);

    // Publish message
    int msg_id = esp_mqtt_client_publish(client, MQTT_TOPIC, json_str, strlen(json_str), 1, 0);

    // Clean up
    cJSON_Delete(root);
    free(json_str);
    ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

    led_pattern_show(LED_BLUE);

    esp_mqtt_client_stop(client);
    return msg_id;
}
