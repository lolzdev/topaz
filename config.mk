# SPDX-License-Identifier: BSD-3-Clause

CC := cc
CFLAGS := -Wall -Wextra -std=c99 -pedantic 
LIBS := -lm
# Can be gl or vk
GRAPHICS_BACKEND := vk
DEBUG_BUILD=1
PLATFORM := $(shell uname)

ifeq (${GRAPHICS_BACKEND},gl)
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
# Check for windowing platforms if it's linux
	LINUX_WINDOW_PLATFORM := $(shell echo $$DISPLAY) 
	# If LINUX_WINDOW_PLATFORM is "", it is Wayland, otherwise it's Xorg
ifeq ($(LINUX_WINDOW_PLATFORM),)
	LIBS += -lwayland-client
else	
	LIBS += -lX11 -lXrandr
endif
endif
