#include "helpers.h"
/* Convert 8 bit integer to QImage
 *
 @sourceImage:    image that will be converted
 @cfg:            global configuration containing the image resolution
 @curQimg:        reference to the target of the conversion
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
 * @sourceImage:    image that will be coneverted
 * @cfg:            global configuration containing the image resolution
 * @curQimg:        reference to the target of the conversion
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
 @cfg:            the reference to the configuration struct
 */
void  modifyConfig(config* cfg) {
	cfg->srcPath = QDir::homePath().toStdString();
	cfg->dstPath = QDir::homePath().toStdString();
}
