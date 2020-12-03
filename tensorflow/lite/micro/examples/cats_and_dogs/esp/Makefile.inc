# Copyright 2020 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(TARGET), esp)

# Adding some esp specific files in the main CMakeLists.txt
ESP_CATS_AND_DOGS_SRCS := \
tensorflow/lite/micro/examples/cats_and_dogs/esp/app_camera_esp.c \
tensorflow/lite/micro/examples/cats_and_dogs/esp/esp_audio_mem.c \
tensorflow/lite/micro/examples/cats_and_dogs/esp/esp_cli.c

ESP_CATS_AND_DOGS_HDRS := \
tensorflow/lite/micro/examples/cats_and_dogs/esp/app_camera_esp.h \
tensorflow/lite/micro/examples/cats_and_dogs/esp/esp_cli.h \
tensorflow/lite/micro/examples/cats_and_dogs/esp/esp_audio_mem.h

cats_and_dogs_SRCS += $(ESP_CATS_AND_DOGS_SRCS)
cats_and_dogs_HDRS += $(ESP_CATS_AND_DOGS_HDRS)
MAIN_SRCS += $(ESP_CATS_AND_DOGS_SRCS)

# ESP specific flags and files
CCFLAGS += -Wno-nonnull
CXXFLAGS += -Wno-return-type -Wno-strict-aliasing
cats_and_dogs_ESP_PROJECT_FILES := \
  sdkconfig.defaults \
  main/Kconfig.projbuild \
  partitions.csv \
  README_ESP.md \
  partitions.csv \
  components/static_images/sample_images/image0 \
  components/static_images/sample_images/image1 \
  components/static_images/sample_images/image2 \
  components/static_images/sample_images/image3 \
  components/static_images/CMakeLists.txt \
  components/static_images/component.mk \

# Remap downloaded model files as if they were in tensorflow/lite/micro/examples/..
MODEL_DOWNLOADS_DIR := tensorflow/lite/micro/tools/make/downloads/person_model_grayscale
MODEL_EXAMPLES_DIR := tensorflow/lite/micro/examples/cats_and_dogs/person_model_grayscale
cats_and_dogs_SRCS := $(patsubst $(MODEL_DOWNLOADS_DIR)/%,$(MODEL_EXAMPLES_DIR)/%,$(cats_and_dogs_SRCS))

# Custom rule to transform downloaded model files
$(PRJDIR)cats_and_dogs/esp-idf/main/person_model_grayscale/%: $(MODEL_DOWNLOADS_DIR)/%
	@mkdir -p $(dir $@)
	@python tensorflow/lite/micro/tools/make/transform_source.py \
        --platform=esp \
        --is_example_source \
        --source_path="$(patsubst $(MODEL_DOWNLOADS_DIR)/%,$(MODEL_EXAMPLES_DIR)/%,$<)" \
        < $< > $@

endif
