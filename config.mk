# SPDX-License-Identifier: BSD-3-Clause

CC := cc
CFLAGS := -Wall -Wextra -std=c99 -pedantic -ggdb -fsanitize=address -DDEBUG
LIBS := -lm
# can be gl or vk
BACKEND := vk

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
	LIBS += -framework Cocoa -framework CoreVideo -framework Metal -framework IOKit
else ifeq (${PLATFORM},Linux)
	CFLAGS += -DPLATFORM_LINUX
endif
