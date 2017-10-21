#ifndef AMBI
#define AMBI

typedef struct FrameA {
	unsigned short lf;
	unsigned short lb;
	unsigned short rf;
	unsigned short rb;
} FrameA;

typedef struct FrameB {
	unsigned short w;
	unsigned short x;
	unsigned short y;
	unsigned short z;
} FrameB;

void ambi_aToB(unsigned short *, unsigned short *, unsigned int);

#endif
