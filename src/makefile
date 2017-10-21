all: main.o
	gcc -lasound -lm -o ../ambi main.o loop.o audio_in.o audio_out.o ambi.o virtualmic.o

main.o: main.c loop.o audio_in.o audio_out.o
	gcc -c main.c loop.o audio_in.o audio_out.o
	
loop.o: loop.c loop.h audio_in.o audio_out.o virtualmic.o
	gcc -c loop.c audio_in.o audio_out.o virtualmic.o
	
audio_in.o: audio_in.c audio_in.h
	gcc -lasound -c audio_in.c
	
audio_out.o: audio_out.c audio_out.h
	gcc -lasound -c audio_out.c

virtualmic.o: virtualmic.c virtualmic.h ambi.o
	gcc -lm -c virtualmic.c
	
ambi.o: ambi.c ambi.h
	gcc -c ambi.c

clean:
	rm ../ambi main.o
