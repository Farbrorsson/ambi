#include <stdio.h>
#include "audio.h"

int main(int argc, char** argv) {
	Audio a;
	a.device = argv[1];
	start(&a);
	return 0;
}
