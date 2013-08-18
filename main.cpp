#include "ImageIO.h"
#include "ctmf.h"
#include "imageutils.h"
#include "tvl1opticalflow.h"
int main()
{
/*
	ByteImage bsrc,bdst;
	ReadImage(bsrc, "E:\\dataset\\other-color-allframes\\other-data\\Beanbags\\frame10.png");
	bdst.Allocate(bsrc.GetWidth(), bsrc.GetHeight(), bsrc.GetChannels());
	uchar *srcdata = bsrc.GetData();
	uchar *dstdata = bdst.GetData();
	int srcstep = bsrc.GetWidth() * bsrc.GetChannels();
	int dststep = bdst.GetWidth() * bdst.GetChannels();
/ *
	for (int i = 0; i < 3; i++)
	{
		ctmf(srcdata+i, dstdata+i, bsrc.GetWidth(), bsrc.GetHeight(), srcstep, dststep, 2, bsrc.GetChannels(), 512*1024);
	}* /
	

	DoubleImage src(bsrc.GetWidth(), bsrc.GetHeight(), bsrc.GetChannels());
	DoubleImage dst(bsrc.GetWidth(), bsrc.GetHeight(), bsrc.GetChannels());
	
	Byte2DoubleImage(bsrc, src);
	MedianFilter(src, 2);
	Double2ByteImage(src, bdst);

	WriteImage(bdst, "E:\\dataset\\other-color-allframes\\other-data\\Beanbags\\frame10_median.png");*/
	char *im0path = "E:\\dataset\\other-color-allframes\\other-data\\Beanbags\\frame10.png";
	char *im1path = "E:\\dataset\\other-color-allframes\\other-data\\Beanbags\\frame11.png";
	Params param;
	param.level = 2;
	param.scale = 0.5;
	
	TVL1OpticalFlow tvl1(im0path, im1path, param);
	
}