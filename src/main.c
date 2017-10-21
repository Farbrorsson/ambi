#include "audio_out.h"
#include "audio_in.h"
#include "loop.h"

static char* device = "plughw:2,0";

int main(int argc, char** argv) {
	AudioOut out;
	audioOut_init(&out, device);
	AudioIn in;
	audioIn_init(&in, "plughw:2,0");
	in.bufferSize = 256;
	out.bufferSize = 256;
	loop(&out, &in);
	return 0;
}
