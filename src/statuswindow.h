#include "qtsearcher.h"
#include "helpers.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <sstream>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	config *cfg;
private slots:
	void startSearch();
	void selectSource();
	void selectDestination();
	void keepAll();
	void keepInteresting();
	void keepCandidate();
	void keepNone();
	void about();
	void updateMessages();
    void getAverage();
    void getCenter();
    void getPresort();
    void getCheck();
private:
	QThread* thread1;
	QThread* thread2;
	QThread* thread3;
	QThread* thread4;
	QThread* msgThread;
	void createLayout();
	void createActions();
	void createMenus();
	QWidget *widget;
	QLabel *imgCenter;
	QLabel *imgAverage;
	QLabel *imgPresort;
	QLabel *imgCheck;
	QTextEdit *logArea;
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
