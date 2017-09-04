#include <alsa/asoundlib.h>

typedef struct Audio {
	snd_pcm_t *pcm;
	char* device;
	char* buffer;
	size_t bufferSize;
} Audio;

void start(Audio*);
