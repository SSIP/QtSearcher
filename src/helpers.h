#include "qtsearcher.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

void toQimage8Bit(uint8_t *sourceImage, config *cfg, QImage *curImg);
void toQimage16Bit(int16_t *sourceImage, config *cfg, QImage *curImg);
void setStdConf(config* cfg);
