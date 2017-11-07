#include "qtsearcher.h"
#include <QMainWindow>
#include <mutex>
#include <thread>
#include <unistd.h>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
private slots:
	void startSearch();
	void selectSource();
	void selectDestination();
	void keepAll();
	void keepInteresting();
	void keepCandidate();
	void keepNone();
	void about();

private:
	void createActions();
	void createMenus();

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
	config *cfg;
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
    void error(QString err);
private:
    config *cfg;
};