CFLAGS = -Wall -g -std=c99

objs = myht.o libHash.o


all: myht


myht: $(objs) -lm

myht.o:   myht.c libHash.h
libHash.o: libHash.c libHash.h

clean:
	-rm -f $(objs) *~

purge: clean
	-rm -f myht
