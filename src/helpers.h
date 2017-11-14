#include "qtsearcher.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

void toQimage(image *sourceImage, config *cfg, QImage *curImg);
void setStdConf(config* cfg);
