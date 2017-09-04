#include <stdio.h>
#include "audio.h"

static char* device = "plughw:1,0";

int main(int argc, char** argv) {
	unsigned char buf[16*1024];
	Audio a;
	a.device = device;
	a.buffer = buf;
	a.bufferSize = 16*1024;
	start(&a);
	return 0;
}
