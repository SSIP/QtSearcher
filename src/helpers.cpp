#include "helpers.h"

QImage *toQimage(image *sourceImage, config *cfg)
{
	QImage *result = new QImage(sourceImage->rawBitmap,
	                            static_cast<int>(cfg->imageResX),
                                static_cast<int>(cfg->imageResY),
								static_cast<int>(cfg->imageResX),
                                QImage::Format_Indexed8
	                           );
	return result;
}