set(COMPONENT_SRCDIRS .)
set(COMPONENT_ADD_INCLUDEDIRS . ../i2cdev)

set(COMPONENT_REQUIRES i2cdev log esp_idf_lib_helpers)


register_component()
