#include "qtsearcher.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

QImage toQimage(image *sourceImage);