#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

void open(Audio *a) {
	int err = snd_pcm_open(a->pcm, a->device, SND_PCM_STREAM_PLAYBACK, 0);
	if (err < 0) {
		fprintf(stderr, "Cannot open audio device %s (%s)\n",
			a->device,
			snd_strerror(err)
		);
		exit(1);
	}
}

void allocHWParams(Audio *a) {
	int err = snd_pcm_hw_params_malloc(a->hwParams);
	if (err < 0) {
		fprintf(stderr, "Cannot allocate hardware parameter structure(%s)\n",
			snd_strerror(err)
		);
		exit(1);
}

void initHWParams(Audio *a) {
	int err = snd_pcm_hw_params_any(a->pcm, a->hwParams);
	if (err < 0) {
		fprintf(stderr, "cannot initialize hardware structure (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

void setHWAccess(Audio *a) {
	int err = snd_pcm_hw_params_set_access(a->pcm, a->hwParams, SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
		fprintf(stderr, "cannot set access type (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

void setSampleFormat(Audio *a) {
	int err = snd_pcm_hw_params_set_format(a->pcm, a->hwParams, SND_PCM_FORMAT_S16_LE) {
	if (err < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

void setSampleRate(Audio *a, int rate) {
	int err = snd_pcm_hw_params_set_rate_near(a->pcm, a->hwParams, &rate, 0);
	if (err < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

void setChannelCount(Audio *a, int n) {
	int err = snd_pcm_hw_params_set_channels(a->pcm, a->hwParams, n);
	if (err < 0) {
		fprintf(stderr, "Cannot set channel count (%s)\n",
			snd_strerror(err));
		exit(1);
	}
}

void setParameters(Audio *a) {
	int err  = snd_pcm_hw_params(a->pcm, a->hwParams);
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
	short buf[128];

	open(a);
	allocateHWParams(a);
	initHWParams(a);
	setHWAccess(a);
	setSampleFormat(a);
	setSampleRate(a, f);
	setChannelCount(a, nChannels);
	setParameters(a)

	snd_pcm_hw_params_free(a->hwParams);

	prerpareInterface(a);
	

	for (i = 0; i < 10; ++i) {
		if ((err = snd_pcm_writei(a->pcm, buf, 128)) != 128) {
			fprintf(stderr, "write to audio interface failed (%s)\n",
				snd_strerror(err));
			exit(1);
		}
	}

	printf("success\n");

	snd_pcm_close(a->pcm);
	exit(0);
}
