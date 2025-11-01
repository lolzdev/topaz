# SPDX-License-Identifier: BSD-3-Clause

CC := cc
CFLAGS := -Wall -Wextra -std=c99 -pedantic -ggdb -O2
LIBS := -lm
# if this is set to gl, it will use OpenGL, otherwise it will use Vulkan
BACKEND := gl

PLATFORM := $(shell uname)

ifeq (${BACKEND},gl)
	CFLAGS += -DBACKEND_GL
ifeq (${PLATFORM},Darwin)
	LIBS += -framework Cocoa -framework CoreVideo -framework OpenGL -framework IOKit
else
	LIBS += -lGL
endif
else
	CFLAGS := -DBACKEND_VK
endif

ifeq (${PLATFORM},Darwin)
	CFLAGS += -DPLATFORM_MACOS
endif
