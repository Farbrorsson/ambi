#ifndef AUDIO_OUT
#define AUDIO_OUT

#include <alsa/asoundlib.h>

typedef struct AudioOut {
	snd_pcm_t *pcm;
	unsigned short buffer[256];
	size_t bufferSize;
} AudioOut;

int audioOut_init(AudioOut *, char *);
int audioOut_playback(AudioOut *);
void audioOut_destroy(AudioOut *);

#endif
