#include "helpers.h"
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
void  modifyConfig(config* cfg) {
	cfg->srcPath = QDir::homePath().toStdString();
	cfg->dstPath = QDir::homePath().toStdString();
}
