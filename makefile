# SPDX-License-Identifier: BSD-3-Clause

include config.mk
ifeq (${DEBUG_BUILD},1)
	CFLAGS += -ggdb -fsanitize=address,undefined -DDEBUG
endif

SRC:=\
     topaz.c\
     core/linear.c\
     core/vector.c\
     core/arena.c

ifeq (${GRAPHICS_BACKEND},gl)
	SRC +=	rendering/gl/gl.c\
			rendering/gl/platform.c\
			rendering/gl/renderer.c
endif
ifeq (${GRAPHICS_BACKEND},vk)
	SRC += rendering/vk/platform.c\
	       rendering/vk/renderer.c\
	       rendering/vk/instance.c\
	       rendering/vk/physical_device.c\
	       rendering/vk/device.c\
	       rendering/vk/surface.c

ifeq (${PLATFORM},Darwin)
	SRC += rendering/vk/macos_platform.c
endif
endif


OBJ:=${SRC:.c=.o}

all: ${OBJ}
	${CC} ${LIBS} ${CFLAGS} ${OBJ} -o topaz

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean
clean:
	@rm -rfv ${OBJ} topaz

INDENTABLE := $(shell find . -name "*.c" -o -name "*.h")
INDENTABLE := $(filter-out ./gl/gl.h,$(INDENTABLE))
INDENTABLE := $(filter-out ./rgfw.h,$(INDENTABLE))
indent: $(INDENTABLE:%=%.indent)

%.indent: %
	indent $<
	@rm $(notdir $<.BAK)
