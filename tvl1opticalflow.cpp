#include "tvl1opticalflow.h"
#include "imageutils.h"
#include <cmath>
#include <algorithm>



TVL1OpticalFlow::TVL1OpticalFlow(const char *image0path, const char *image1path, Params param)
{
	//ByteImage I0, I1;
	//ReadImage(I0, image0path);
	//ReadImage(I1, image1path);
	this->param = param;
	image0pyramid = GaussianPyramid(image0path, param.level, param.scale);
	image1pyramid = GaussianPyramid(image1path, param.level, param.scale);
	//image0pyramid.WritePyramidImage();

}

void TVL1OpticalFlow::DualROF(DoubleImage& u, DoubleImage& v, DoubleImage& p)
{
	int width = u.GetWidth(), height = u.GetHeight();
	DoubleImage div(width, height, 1);

	DoubleImage grad(div.GetWidth(), div.GetHeight(), div.GetChannels());
	DoubleImage _p(width, height, 1);
	double *pdata = p.GetData();
	double *_pdata = _p.GetData();
	double *graddata = grad.GetData();
	for (int i = 0; i < param.n; i++)
	{
		Divergence(p, div);
		div.MultiplyWith(param.theta);
		div.Add(v);
		Gradient(div, grad, 0);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				
				_pdata[y*width+x] = pdata[y*width+x] * param.gamma / param.theta * graddata[y*width+x];
				pdata[y*width+x] = _pdata[y*width+x] / std::max(1.0, abs(_pdata[y*width+x]));
			}
		}



	}
}

void TVL1OpticalFlow::Divergence(DoubleImage& p, DoubleImage& div)
{
	int width = p.GetWidth(), height = p.GetHeight(), channels = p.GetChannels();
	double *pdata = p.GetData();
	double *divdata = div.GetData();
	divdata[0] = pdata[0] + pdata[1];
	divdata[width-1] = pdata[channels*(width-1)] - pdata[channels*(width-2)+1];
	divdata[(height-1)*width] = -pdata[(height-2)*width*channels] + pdata[(height-1)*width*channels+1];
	divdata[(height-1)*width+width-1] = -pdata[((height-2)*width+width-1)*channels] - pdata[((height-1)*width+width-2)*channels+1];
	for (int i = 1; i < width-1; i++)
	{
		divdata[i] = pdata[i*channels] + pdata[i*channels+1] - pdata[(i-1)*channels+1];
		divdata[i*width] =pdata[i*width*channels] - pdata[(i-1)*width*channels] + pdata[i*width*channels+1];
		divdata[i*width+width-1] = pdata[(i*width+width-1)*channels] - pdata[((i-1)*width+width-1)*channels] - pdata[(i*width+width-2)*channels+1];
		divdata[(height-1)*width+i] = -pdata[((height-2)*width+i)*channels] + pdata[((height-1)*width+i)*channels+1] - pdata[((height-1)*width+i-1)*channels+1];
	}
	for (int y = 1; y < height-1; y++)
	{
		for (int x = 1; x < width-1; x++)
		{
			divdata[y*width+x] = pdata[(y*width+x)*channels] - pdata[((y-1)*width+x)*channels] + pdata[(y*width+x)*channels+1] + pdata[(y*width+x-1)*channels+1];
		}
	}

}


void TVL1OpticalFlow::STDecomposition(DoubleImage& image, DoubleImage& structure, DoubleImage& texture)
{

}