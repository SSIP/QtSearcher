#include "helpers.h"
#include <iostream>
void toQimage(image *sourceImage, config *cfg, QImage *curQimg)
{
	curQimg->fill(QColor(Qt::white).rgb());

	for (int x = 0; x < cfg->imageResX; ++x) {
		for (int y = 0; y < cfg->imageResY; ++y) {
			uint8_t val = sourceImage->rawBitmap[y * 400 + x];
			curQimg->setPixel(x, y, qRgb(val, val, val));
		}
	}
}

void  setStdConf(config* cfg) {
	// TEMP
	cfg->imageResX = 400;
	cfg->imageResY = 400;
	// END TEMP

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
