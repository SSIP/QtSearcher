#include "qtsearcher.h"
#include "helpers.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	config *cfg;

public:
	MainWindow();
private slots:
	void setStdConf(config* cfg);
	void startSearch();
	void selectSource();
	void selectDestination();
	void keepAll();
	void keepInteresting();
	void keepCandidate();
	void keepNone();
	void about();

private:
	void createLayout();
	void createActions();
	void createMenus();
	QWidget *widget;
	QLabel *imgCenter;
	QLabel *imgAverage;
	QLabel *imgPresort;
	QLabel *imgCheck;
	QGridLayout *layout;
	QMenu *searchMenu;
	QMenu *configMenu;
	QMenu *keepFrameMenu;
	QMenu *helpMenu;
	QActionGroup *keepFrameGroup;
	QAction *searchAct;
	QAction *exitAct;
	QAction *srcAct;
	QAction *dstAct;
	QAction *bla;
	QAction *keepAllAct;
	QAction *keepInterestingAct;
	QAction *keepCandidateAct;
	QAction *keepNoneAct;
	QAction *aboutAct;
	QLabel *infoLabel;
	QThread *thread;
};

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(config *cfg);
    ~Worker();
public slots:
    void process();
signals:
    void finished();
private:
    config *cfg;
};