#include "audio_out.h"
#include <stdio.h>

int audioOut_init(AudioOut *a, char *device) {
	int err;
	
	err = snd_pcm_open(&a->pcm, device, SND_PCM_STREAM_PLAYBACK, 0);
	if (err < 0) return err;
	err = snd_pcm_set_params(a->pcm, SND_PCM_FORMAT_U16, 
		SND_PCM_ACCESS_RW_INTERLEAVED, 1, 48000, 1, 32000);
	if (err < 0) return err;
}

int audioOut_playback(AudioOut *a) {
	int status;
	status = snd_pcm_writei(a->pcm, a->buffer, a->bufferSize);
	if (status < 0) {
		status = snd_pcm_recover(a->pcm, status, 0);
		if (status < 0) {
			printf("o\n");
			return status;
		}
	}
	return 0;
}

void audioOut_destroy(AudioOut *a) {
	snd_pcm_close(a->pcm);
}
