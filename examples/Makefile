MCU=	atmega128
F_CPU=	1000000UL
BAUD=	9600UL

CC=	avr-gcc
AR=	avr-ar

TARGET=	hello

SRCS=	hello.c
OBJS=	$(SRCS:.c=.o)

CFLAGS=	-DF_CPU=${F_CPU} -DBAUD=${BAUD} -I../libmax7219/ -Os -mmcu=${MCU}
LDFLAGS=	-L../libmax7219/ -lmax7219

all: build clean

build:
	${CC} ${CFLAGS} ${SRCS} -o ${TARGET} ${LDFLAGS}

clean:
	rm -rf ${OBJS}

cleandir: clean
	rm -rf ${TARGET}
