#ifndef VIRTUALMIC
#define VIRTUALMIC

typedef struct VirtualMic {
	double az;
	double el;
	double stereo;
	double p; // shape
} VirtualMic;

void vmic_decode(
		VirtualMic *vmic, 
		unsigned short *srcBuffer, 
		unsigned short *dstBuffer, 
		unsigned int nFrames);
		
#endif
