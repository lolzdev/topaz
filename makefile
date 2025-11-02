# SPDX-License-Identifier: BSD-3-Clause

include config.mk

SRC:=\
     topaz.c\
     linear.c\
     core/arena.c\
     core/vector.c

ifeq (${BACKEND},gl)
	SRC += gl/gl.c\
	       gl/platform.c
endif
ifeq (${BACKEND},vk)
	SRC += vk/platform.c\
	       vk/renderer.c\
	       vk/instance.c
endif

OBJ:=${SRC:.c=.o}

all: ${OBJ}
	${CC} ${LIBS} ${OBJ} -o topaz

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean
clean:
	@rm -rfv ${OBJ} topaz
