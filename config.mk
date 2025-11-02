# SPDX-License-Identifier: BSD-3-Clause

CC := cc
CFLAGS := -Wall -Wextra -std=c99 -pedantic -ggdb -O2
LIBS := -lm
# can be gl or vk
BACKEND := gl

PLATFORM := $(shell uname)

ifeq (${BACKEND},gl)
	CFLAGS += -DBACKEND_GL
ifeq (${PLATFORM},Darwin)
	LIBS += -framework OpenGL
else
	LIBS += -lGL
endif
else
	LIBS += -lvulkan
	CFLAGS += -DBACKEND_VK
endif

ifeq (${PLATFORM},Darwin)
	CFLAGS += -DPLATFORM_MACOS
	LIBS += -framework Cocoa -framework CoreVideo -framework IOKit
else ifeq (${PLATFORM},Linux)
	CFLAGS += -DPLATFORM_LINUX
endif
