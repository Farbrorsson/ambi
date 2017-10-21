#ifndef AUDIO_IN
#define AUDIO_IN

#include <alsa/asoundlib.h>

typedef struct AudioIn {
	snd_pcm_t *pcm;
	unsigned short buffer[2048];
	size_t bufferSize;
} AudioIn;

int audioIn_init(AudioIn *, char *);
int audioIn_capture(AudioIn *);
void audioIn_destroy(AudioIn *);

#endif
