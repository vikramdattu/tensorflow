$(eval $(call add_third_party_download,$(PERSON_MODEL_URL),$(PERSON_MODEL_MD5),person_model_grayscale,))
$(eval $(call add_third_party_download,$(RUY_URL),$(RUY_MD5),ruy,))

cats_and_dogs_MODEL_SRCS := \
tensorflow/lite/micro/examples/cats_and_dogs/model_settings.cc \
tensorflow/lite/micro/examples/cats_and_dogs/model_data.cc

cats_and_dogs_MODEL_HDRS := \
tensorflow/lite/micro/examples/cats_and_dogs/model_settings.h \
tensorflow/lite/micro/examples/cats_and_dogs/model_data.h

cats_and_dogs_SRCS := \
tensorflow/lite/micro/examples/cats_and_dogs/detection_responder.cc \
tensorflow/lite/micro/examples/cats_and_dogs/image_provider.cc \
tensorflow/lite/micro/examples/cats_and_dogs/main.cc \
tensorflow/lite/micro/examples/cats_and_dogs/main_functions.cc \
$(cats_and_dogs_MODEL_SRCS)

cats_and_dogs_HDRS := \
tensorflow/lite/micro/examples/cats_and_dogs/detection_responder.h \
tensorflow/lite/micro/examples/cats_and_dogs/image_provider.h \
tensorflow/lite/micro/examples/cats_and_dogs/main_functions.h \
$(cats_and_dogs_MODEL_HDRS)

#Find any platform - specific rules for this example.
include $(wildcard tensorflow/lite/micro/examples/cats_and_dogs/*/Makefile.inc)

# Tests loading and running a vision model.
$(eval $(call microlite_test,cats_and_dogs_test,\
$(cats_and_dogs_TEST_SRCS),$(cats_and_dogs_TEST_HDRS)))

# Tests the image provider module.
$(eval $(call microlite_test,image_provider_test,\
$(IMAGE_PROVIDER_TEST_SRCS),$(IMAGE_PROVIDER_TEST_HDRS)))

# Tests the detection responder module.
$(eval $(call microlite_test,detection_responder_test,\
$(DETECTION_RESPONDER_TEST_SRCS),$(DETECTION_RESPONDER_TEST_HDRS)))

# Builds a standalone object recognition binary.
$(eval $(call microlite_test,cats_and_dogs,\
$(cats_and_dogs_SRCS),$(cats_and_dogs_HDRS)))
