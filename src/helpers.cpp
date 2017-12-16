#include "helpers.h"
/* Convert 8 bit integer to QImage
 *
 * Param *sourceImage is the image that will be converted
 * Param *cfg is the global configuration containing the image resolution
 * Param *curQimg is the reference to the target of the conversion
 */
void toQimage8Bit(uint8_t *sourceImage, config *cfg, QImage *curQimg)
{
	curQimg->fill(QColor(Qt::white).rgb());
	for (int x = 0; x < cfg->imageResX; ++x) {
		for (int y = 0; y < cfg->imageResY; ++y) {
			uint8_t val = (uint8_t)sourceImage[(uint32_t)(y * cfg->imageResX + x)];
			curQimg->setPixel(x, y, qRgb(val, val, val));
		}
	}
}

/* Convert 16 bit integer to QImage
 * We only use this function to display the diff image which is a 16 bit signed integer.
 * The diff image contains values arouond 0. To convert it to 8 bit unsigned int, we add
 * 128 and expect that no values are too large.
 *
 * Param *sourceImage is the image that will be coneverted
 * Param *cfg is the global configuration containing the image resolution
 * Param *curQimg is the reference to the target of the conversion
 */
void toQimage16Bit(int16_t *sourceImage, config *cfg, QImage *curQimg)
{
	uint16_t val;
	int16_t tmp;
	curQimg->fill(QColor(Qt::white).rgb());
	for (int x = 0; x < cfg->imageResX; ++x) {
		for (int y = 0; y < cfg->imageResY; ++y) {
			tmp = sourceImage[(uint32_t)(y * cfg->imageResX + x)] + 128;
			uint16_t val = (uint16_t)tmp;
			curQimg->setPixel(x, y, qRgb(val, val, val));
		}
	}
}


/* Set a standard configuration
 *
 * Param *cfg is the reference to the configuration struct
 */
void  setStdConf(config* cfg) {
	// MUST BE SET TO ZERO <0> !!!
	cfg->imageResX = 0;
	cfg->imageResY = 0;
	// END TEMP

	cfg->srcPath = QDir::homePath().toStdString();
	cfg->dstPath = QDir::homePath().toStdString();;
	cfg->keepFrames = KEEP_ALL;
	cfg->centerSkipPixels = 5;
	cfg->centerAlgo = CENTER_OF_MASS;
	cfg->centerThreshold = 50;
	cfg->averageLength = 10;
	cfg->checkSNR = 5.0;
	cfg->checkRadius = 1.0;
	cfg->verbosity = 1;
	cfg->rayBrightnessThreshold = 0.3;
	cfg->maxDiameter = 0.8;
	cfg->leadingAverageLength = 5;
	cfg->trailingAverageLength = 20;
	cfg->framebufferLength = 20;
}
