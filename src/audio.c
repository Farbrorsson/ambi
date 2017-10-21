#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

void audio_capture(Audio *a) {
	
}

void audio_open(Audio *a) {
	int err = snd_pcm_open(&(a->pcm), a->device, SND_PCM_STREAM_PLAYBACK, 0);
	if (err < 0) {
		fprintf(stderr, "Cannot open audio device %s (%s)\n",
			a->device,
			snd_strerror(err)
		);
		exit(1);
	}
}


void setParameters(Audio *a) {
	int err  = snd_pcm_set_params(
		a->pcm,
		SND_PCM_FORMAT_U8,
		SND_PCM_ACCESS_RW_INTERLEAVED,
		1,
		48000,
		1,
		500000
	);
	if (err < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
			snd_strerror (err));
		exit (1);
	}
}

void prepareInterface(Audio *a) {
	int err = snd_pcm_prepare(a->pcm);
	if (err < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

//snd_output_t *output = NULL;
//unsigned char buffer[16*1024];        

void start(Audio *a) {
	int i;
	int err;
	
	 snd_pcm_sframes_t frames;
	
	for (i = 0; i < 16*1024; i++) {
		a->buffer[i] = (i % 256) > 128 ? 0x7a : 0x86;
	}

	audio_open(a);
	setParameters(a);

	prepareInterface(a);
	
	for (i = 0; i < 16; i++) {
        frames = snd_pcm_writei(a->pcm, a->buffer, a->bufferSize);
        if (frames < 0) {
        	printf("snd_pcm_recover\n");
            frames = snd_pcm_recover(a->pcm, frames, 0);
        }
        if (frames < 0) {
            printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
            break;
        }
        if (frames > 0 && frames < (long)(a->bufferSize))
            printf("Short write (expected %li, wrote %li)\n", (long)(a->bufferSize), frames);
    }
    snd_pcm_close(a->pcm);

	printf("success\n");

	snd_pcm_close(a->pcm);
	exit(0);
}
