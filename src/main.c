#include <stdio.h>
#include "audio.h"

int main(int argc, char** argv) {
	unsigned char buf[256];
	Audio a;
	a.device = argv[1];
	a.buffer = buf;
	a.bufferSize = 256;
	start(&a);
	return 0;
}
