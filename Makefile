INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm

all: scroll

scroll: main.o display.o input.o
	cc -o scroll main.o display.o input.o $(LDFLAGS)

main.o: main.c scroll.h
	cc -c main.c $(INCLUDE)

display.o: display.c scroll.h
	cc -c display.c $(INCLUDE)

input.o: input.c scroll.h
	cc -c input.c $(INCLUDE)

clean:
	rm -f *.o scroll

run: scroll
	./scroll
