# SPDX-License-Identifier: BSD-3-Clause

include config.mk
ifeq (${DEBUG_BUILD},1)
	CFLAGS += -ggdb -fsanitize=address,undefined -DDEBUG
endif

SRC:=\
     topaz.c\
     linear.c\
     core/arena.c\
     core/vector.c\

ifeq (${GRAPHICS_BACKEND},gl)
	SRC +=	gl/gl.c\
		gl/platform.c\
		gl/renderer.c
endif
ifeq (${GRAPHICS_BACKEND},vk)
	SRC += vk/platform.c\
	       vk/renderer.c\
	       vk/instance.c\
	       vk/physical_device.c\
	       vk/device.c
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
