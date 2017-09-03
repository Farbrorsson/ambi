#include <alsa/asoundlib.h>

typedef struct Audio {
	snd_pcm_t *pcm;
	snd_pcm_hw_params_t *hwParams;
	char* device;
} Audio;

void start(Audio*);
