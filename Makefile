TARGET=pval-test
CPPFLAGS=
CFLAGS=-O3 -g -Wall -D_GNU_SOURCE
LDLIBS=-lm -lgsl
LDFLAGS=-static
LDFLAGS=
CC=gcc

SOURCES=main.c \
    dieharder/dieharder-kstest.c \
    nist-sts/nist-sts-cephes.c nist-sts/nist-sts-assess.c \
    testu01/fbar.c testu01/fdist.c testu01/util.c \
    testu01/num.c testu01/num2.c testu01/fmass.c \
    testu01/tables.c testu01/mystr.c testu01/bitset.c \
    testu01/gofs.c testu01/gofw.c  testu01/wdist.c testu01/testu01.c

OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDLIBS) $(LDFLAGS)

clean:
	rm -f *.o dieharder/*.o nist-sts/*.o testu01/*.o *~ core $(TARGET)

.PHONY: clean
