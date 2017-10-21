#include "audio_in.h"

int audioIn_init(AudioIn *a, char *device) {
	int err;
	
	err = snd_pcm_open(&a->pcm, device, SND_PCM_STREAM_CAPTURE, 0);
	if (err < 0) return err;
	err = snd_pcm_set_params(a->pcm, SND_PCM_FORMAT_U16, 
		SND_PCM_ACCESS_RW_INTERLEAVED, 4, 48000, 1, 32000);
	if (err < 0) return err;
}

int audioIn_capture(AudioIn *a) {
	int status;
	status = snd_pcm_readi(a->pcm, a->buffer, a->bufferSize);
	if (status < 0) {
		status = snd_pcm_recover(a->pcm, status, 0);
		if (status < 0) {
			return status;
		}
	}
	return 0;
}

void audioIn_destroy(AudioIn *a) {
	snd_pcm_close(a->pcm);
}
