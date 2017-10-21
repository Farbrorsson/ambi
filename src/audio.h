typedef struct AudioBuffer {
	unsigned char* buffer;
	size_t nFrames;
	int channels;
	int rate;
} AudioBuffer;
