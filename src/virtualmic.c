#include "virtualmic.h"
#include "ambi.h"
#include <math.h>

static const double sqrt2 = 1.4142135623730951;

void vmic_decode(
		VirtualMic *vmic, 
		unsigned short *srcBuffer, 
		unsigned short *dstBuffer, 
		unsigned int nFrames
) {
	int i;
	double v,w,x,y,z;
	FrameB *s = (FrameB *)srcBuffer;
	double d = (double)((short)-1);
	unsigned short a = -1;
	d /= 2;
	for (i = 0; i < nFrames; i++) {
		w = (s[i].w / d) - 0.5;
		x = (s[i].x / d) - 0.5;
		y = (s[i].y / d) - 0.5;
		z = (s[i].z / d) - 0.5;
		v = vmic->p * sqrt2 * w + 
			(1 - vmic->p) * (
				cos(vmic->el) * cos(vmic->az) * x +
				sin(vmic->el) * cos(vmic->az) * y +
				sin(vmic->el) * z
			);
				
		dstBuffer[i] = (v + 0.5) * d;
	}
}
