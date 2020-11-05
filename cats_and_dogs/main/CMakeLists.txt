
#
# Main component of TF Micro project 'cats_dogs'
#

idf_component_register(
    SRCS detection_responder.cc esp/image_provider.cc esp/main.cc
         main_functions.cc model_settings.cc model_data.cc
         esp/app_camera_esp.c esp_audio_mem.c esp_cli.c
    INCLUDE_DIRS "")
