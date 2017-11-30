#include "helpers.h"
#include <iostream>
void toQimage8Bit(uint8_t *sourceImage, config *cfg, QImage *curQimg)
{
	curQimg->fill(QColor(Qt::white).rgb());
	for (int x = 0; x < cfg->imageResX; ++x) {
		for (int y = 0; y < cfg->imageResY; ++y) {
			uint8_t val = (uint8_t)sourceImage[(uint32_t)(y * 400 + x)];
			curQimg->setPixel(x, y, qRgb(val, val, val));
		}
	}
}

void toQimage16Bit(int16_t *sourceImage, config *cfg, QImage *curQimg)
{
	uint16_t val;
	int16_t tmp;
	curQimg->fill(QColor(Qt::white).rgb());
	for (int x = 0; x < cfg->imageResX; ++x) {
		for (int y = 0; y < cfg->imageResY; ++y) {
			tmp = sourceImage[(uint32_t)(y * 400 + x)] + 128;
			uint16_t val = (uint16_t)tmp;
			if(y == 200 && x == 200)
				cout << "Center value: " << val << endl;
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
	cfg->verbosity = 3;
	cfg->rayBrightnessThreshold = 0.3;
	cfg->maxDiameter = 0.8;
	cfg->leadingAverageLength = 5;
	cfg->trailingAverageLength = 15;
	cfg->framebufferLength = 20;
	cfg->leadingAverage = new averageImage(cfg->imageResX, cfg->imageResY, cfg->leadingAverageLength);
	cfg->trailingAverage = new averageImage(cfg->imageResX, cfg->imageResY, cfg->trailingAverageLength);
}
