MCU=	atmega128
F_CPU=	1000000UL
BAUD=	9600UL

CC=	avr-gcc
AR=	avr-ar

TARGET=	libmax7219.a

SRCS=	max7219.c
OBJS=	$(SRCS:.c=.o)

CFLAGS=	-DF_CPU=${F_CPU} -DBAUD=${BAUD} -Os -mmcu=${MCU}

all: build clean

build:
	${CC} ${CFLAGS} -c ${SRCS} ${LDFLAGS}
	${AR} rcs ${TARGET} ${OBJS}

clean:
	rm -rf ${OBJS}

cleandir: clean
	rm -rf ${TARGET}
