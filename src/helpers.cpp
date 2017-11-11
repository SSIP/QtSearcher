#include "helpers.h"

void toQimage(image *sourceImage, config *cfg, QImage *curImg)
{
	curImg = new QImage(sourceImage->rawBitmap,
						static_cast<int>(cfg->imageResX),
						static_cast<int>(cfg->imageResY),
						static_cast<int>(cfg->imageResX),
						QImage::Format_Indexed8
						);
}

void  setStdConf(config* cfg) {
	//cfg->imageResX = cfg->imageResY = 480;
	cfg->srcPath = QDir::homePath().toStdString();
	cfg->dstPath = QDir::homePath().toStdString();;
	cfg->keepFrames = KEEP_ALL;
	//cfg->archiveType = ARCHIVE_PNG; //todo: test bmp and png values
	cfg->centerSkipPixels = 5;
	cfg->centerAlgo = CENTER_OF_MASS;
	cfg->centerThreshold = 50;
	cfg->averageLength = 10;
	//cfg->averageFilterSize = 0.125;
	cfg->avgCrit = 1.5;
	cfg->devCrit = 1.5;
	cfg->checkSNR = 5.0;
	cfg->checkRadius = 1.0;
	cfg->verbosity = 2;
	cfg->rayBrightnessThreshold = 0.3;
}