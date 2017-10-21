#include "audio_out.h"
#include "audio_in.h"
#include "virtualmic.h"
#include "ambi.h"
/*
// Grab the b-format signal
Ambi *captureAudio(AudioBuffer *b) {
	audioIn_capture(b);
	return ambi_aToB(b);
}

/*
// Perform dft;
// Since a huffman window is used, we window two packets into
// 3 overlapping windows per channel.
*//*
void transform(char* backBuffer, char* frontBuffer) {
	
}

// Find all sources within the soundfield signal frame
void analyze(Ambi *a) {

}

// Filters out non-source-data from the signal
void filter(AmbiBuffer *a, nFrames) {
	
}
*/
void loop(AudioOut *out, AudioIn *in) {
	VirtualMic vmic = {0, 0, 0, 0.5};
	//a = captureAudio(b);
	//transform(a);
	//analyze(a);
	//filter(a);
	//synthesize(a);
	//iTransform(a);
	//playbackAudio(a);
	
	
	int i;
	int val;
	unsigned short a = -1;
	while(1) {
		audioIn_capture(in);
		vmic.az += 0.01;
		vmic.az = vmic.az > 6.28 ? 0 : vmic.az;
		ambi_aToB(in->buffer, in->buffer, in->bufferSize);
		vmic_decode(&vmic, in->buffer, out->buffer, in->bufferSize);
		/*for (i = 0; i < in->bufferSize; i++) {
			val = in->buffer[i*4+1];
			out->buffer[i] = val;
				//(in->buffer[(i*4) + 0] / 4) + 
				//(in->buffer[(i*4) + 1] / 4) + 
				//(in->buffer[(i*4) + 2] / 4) + 
				(in->buffer[(i*4) + 3]);
		}*/
		audioOut_playback(out);
	}
}
