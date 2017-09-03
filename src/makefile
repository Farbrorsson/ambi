all: main.o audio.o
	gcc -lasound -o ../ambi main.o audio.o

main.o: main.c
	gcc -c main.c

audio.o: audio.c audio.h
	gcc -lasound -c audio.c

clean:
	rm ../ambi main.o audio.o
