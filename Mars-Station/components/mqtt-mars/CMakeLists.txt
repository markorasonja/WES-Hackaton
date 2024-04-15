set(COMPONENT_SRCS "mqtt-mars.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_ADD_INCLUDEDIRS "../led")
set(COMPONENT_REQUIRES driver mqtt json esp_wifi esp_event )

register_component()
