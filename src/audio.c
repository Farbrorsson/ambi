#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

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

void start(Audio *a) {
	int nChannels = 2;
	int f = 44100;
	int i;
	int err;
	unsigned char buf[256];
	
	for (i = 0; i < 256; i++) {
		buf[i] = i > 128 ? 0x66 : 0x99;
	}
	

	audio_open(a);
	setParameters(a);

	prepareInterface(a);
	

	for (i = 0; i < 10; ++i) {
		if ((err = snd_pcm_writei(a->pcm, buf, 256)) != 128) {
			fprintf(stderr, "write to audio interface failed (%s)\n",
				snd_strerror(err));
			exit(1);
		}
	}

	printf("success\n");

	snd_pcm_close(a->pcm);
	exit(0);
}
