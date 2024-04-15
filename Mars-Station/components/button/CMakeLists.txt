set(COMPONENT_SRCS "button.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_ADD_INCLUDEDIRS "../led")
set(COMPONENT_REQUIRES driver esp_event)

register_component()
