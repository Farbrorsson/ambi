#include "ambi.h"

void ambi_aToB(unsigned short *srcBuffer, unsigned short *dstBuffer, unsigned int nFrames) {
	int i;
	int w,x,y,z;
	int lf, lb, rf, rb;
	FrameA a;
	FrameB *b;
	unsigned short d = (-1);
	d /= 2;
	
	for (i = 0; i < nFrames; i++) {
		lf = srcBuffer[i * 4 + 0];
		lb = srcBuffer[i * 4 + 1];
		rf = srcBuffer[i * 4 + 2];
		rb = srcBuffer[i * 4 + 3];
		lf -= d;
		lb -= d;
		rf -= d;
		rb -= d;
		//a = ((FrameA *)(srcBuffer))[i]; // copy a-format from buffer;
		//b = &((FrameB *)(dstBuffer))[i]; // write b-format back to buffer
		w = 0.5 * (lf + lb + rf + rb);
		x = 0.5 * ((lf - lb) + (rf - rb));
		y = 0.5 * ((lf - rb) - (rf - lb));
		z = 0.5 * ((lf - lb) + (rb - rf));
		dstBuffer[i * 4 + 0] = (w) + d;
		dstBuffer[i * 4 + 0] = (x) + d;
		dstBuffer[i * 4 + 0] = (y) + d;
		dstBuffer[i * 4 + 0] = (z) + d;
	}
}
