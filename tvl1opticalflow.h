#ifndef TVL1OPTICALFLOW_H_
#define TVL1OPTICALFLOW_H_


#include "ImageIO.h"
#include "gaussianpyramid.h"

struct Params
{
	double theta;
	double lamda;
	int inneriter;
	int outeriter;
	int maxwarp;
	int level;
	double scale;
	int n;
	double gamma;
};

class TVL1OpticalFlow
{
public:
	TVL1OpticalFlow(const char *image0path, const char *image1path, Params param);
private:
	//structure-texture decomposition
	void STDecomposition(DoubleImage& image, DoubleImage& structure, DoubleImage& texture);
	void ResampleRho(DoubleImage& I0, DoubleImage& I1, DoubleImage& u);
	void DualROF(DoubleImage& u, DoubleImage& v, DoubleImage& p);
	void SolveV(DoubleImage& v, DoubleImage& u, DoubleImage& I1, DoubleImage& rho);  //rho is ¦Ñ
	void SolveU(DoubleImage& v, DoubleImage& p); //p is the vector p=[p1, p2]
	void Divergence(DoubleImage& p, DoubleImage& div);
	GaussianPyramid image0pyramid;
	GaussianPyramid image1pyramid;
	double theta; //¦È
	double lamda;
	char * image0path;
	char * image1path;
	Params param;
};

#endif