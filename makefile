include config.mk

SRC:=topaz.c

ifeq (${BACKEND},gl)
	SRC += opengl/gl.c opengl/platform.c
endif

OBJ:=${SRC:.c=.o}

all: ${OBJ}
	${CC} ${LIBS} ${OBJ} -o topaz

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean
clean:
	@rm -rfv ${OBJ} topaz
