#include "statuswindow.h"

MainWindow::MainWindow()
{
	createLayout();
	createActions();
	createMenus();

	setWindowTitle(tr("Menus"));
	setMinimumSize(1280, 960);
	resize(1280, 960);

	config cfg;
	setStdConf(&cfg);

	QThread* thread1 = new QThread;
	QThread* thread2 = new QThread;
	QThread* thread3 = new QThread;
	QThread* thread4 = new QThread;
	Worker* worker1 = new Worker(&cfg, imgCenter, 1);
	Worker* worker2 = new Worker(&cfg, imgAverage, 2);
	Worker* worker3 = new Worker(&cfg, imgPresort, 3);
	Worker* worker4 = new Worker(&cfg, imgCheck, 4);
	worker1->moveToThread(thread1);
	worker2->moveToThread(thread2);
	worker3->moveToThread(thread3);
	worker4->moveToThread(thread4);
	thread1->start();
	thread2->start();
	thread3->start();
	thread4->start();
}

void MainWindow::createLayout() {
    QImage myImage;
    myImage.load("test.bmp");
	QWidget *widget = new QWidget;
	setCentralWidget(widget);
	QLabel *capCenter = new QLabel("Center");
	capCenter->setAlignment(Qt::AlignRight);
	QLabel *capAverage = new QLabel("Average");
	capAverage->setAlignment(Qt::AlignLeft);
	QLabel *capPresort = new QLabel("Presort");
	capPresort->setAlignment(Qt::AlignRight);
	QLabel *capCheck = new QLabel("Check");
	capCheck->setAlignment(Qt::AlignLeft);
	QLabel *imgCenter = new QLabel();
	QLabel *imgAverage = new QLabel();
	QLabel *imgPresort = new QLabel();
	QLabel *imgCheck = new QLabel();

	imgCenter->setFixedWidth(350);
	imgCenter->setFixedHeight(350);
	imgAverage->setFixedWidth(350);
	imgAverage->setFixedHeight(350);
	imgPresort->setFixedWidth(350);
	imgPresort->setFixedHeight(350);
	imgCheck->setFixedWidth(350);
	imgCheck->setFixedHeight(350);
	imgCenter->setPixmap(QPixmap::fromImage(myImage));
	imgAverage->setPixmap(QPixmap::fromImage(myImage));
	imgPresort->setPixmap(QPixmap::fromImage(myImage));
	imgCheck->setPixmap(QPixmap::fromImage(myImage));
	QTextEdit *logArea = new QTextEdit();
	logArea->setText("Hello, world!");
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(capCenter, 0, 0);
	layout->addWidget(capAverage, 0, 3);
	layout->addWidget(capPresort, 1, 0);
	layout->addWidget(capCheck, 1, 3);
	layout->addWidget(imgCenter, 0, 1);
	layout->addWidget(imgAverage, 0, 2);
	layout->addWidget(imgPresort, 1, 1);
	layout->addWidget(imgCheck, 1, 2);
	layout->addWidget(logArea, 2, 0, 1, 4);
	widget->setLayout(layout);
}


void MainWindow::startSearch()
{

	impactSearcherStart(cfg);
}

void MainWindow::selectSource()
{
	cfg->srcPath = QFileDialog::getExistingDirectory(this, tr("Select source directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
}

void MainWindow::selectDestination()
{
	cfg->dstPath = QFileDialog::getExistingDirectory(this, tr("Select destination directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
}

void MainWindow::keepAll()
{
	infoLabel->setText(tr("Keep all frames"));
}

void MainWindow::keepInteresting()
{
	infoLabel->setText(tr("Keep interesting frames"));
}

void MainWindow::keepCandidate()
{
	infoLabel->setText(tr("Keep frames with impact candidate"));
}

void MainWindow::keepNone()
{
	infoLabel->setText(tr("Keep no frames"));
}

void MainWindow::about()
{
	infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
						tr("Solar System Impact Project"));
}

void MainWindow::createActions()
{
	/*
		* The Search menu
		* -> Star search
		* -> quit
		*/
	searchAct = new QAction(tr("&Start"), this);
	//searchAct->setShortcuts(tr());
	searchAct->setStatusTip(tr("Start search"));
	connect(searchAct, &QAction::triggered, this, &MainWindow::startSearch);
	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit program"));
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

	/*
		* The config menu
		* -> Select source folder
		* -> Select target folder
		* -> Keep frames
		*    -> None
		*    -> All
		*    -> Interesting
		*    -> Candidate
		*/
	srcAct = new QAction(tr("&Source folder"), this);
	//srcAct->setShortcuts(tr());
	srcAct->setStatusTip(tr("Select source folder with images"));
	connect(srcAct, &QAction::triggered, this, &MainWindow::selectSource);

	dstAct = new QAction(tr("&Destination folder"), this);
	//dstAct->setShortcuts(tr());
	dstAct->setStatusTip(tr("Select destination folder for images"));
	connect(dstAct, &QAction::triggered, this, &MainWindow::selectDestination);

	keepAllAct = new QAction(tr("&Right Align"), this);
	keepAllAct->setCheckable(true);
	//keepAllAct->setShortcut(tr("Ctrl+R"));
	keepAllAct->setStatusTip(tr("Keep all frames in destination folder"));
	connect(keepAllAct, &QAction::triggered, this, &MainWindow::keepAll);

	keepInterestingAct = new QAction(tr("&Right Align"), this);
	keepInterestingAct->setCheckable(true);
	//keepInterestingAct->setShortcut(tr("Ctrl+R"));
	keepInterestingAct->setStatusTip(tr("Keep interesting frames in destination folder"));
	connect(keepInterestingAct, &QAction::triggered, this, &MainWindow::keepInteresting);

	keepCandidateAct = new QAction(tr("&Right Align"), this);
	keepCandidateAct->setCheckable(true);
	//keepCandidateAct->setShortcut(tr("Ctrl+R"));
	keepCandidateAct->setStatusTip(tr("Keep candidate frames in destination folder"));
	connect(keepCandidateAct, &QAction::triggered, this, &MainWindow::keepCandidate);

	keepNoneAct = new QAction(tr("&Right Align"), this);
	keepNoneAct->setCheckable(true);
	//keepNoneAct->setShortcut(tr("Ctrl+R"));
	keepNoneAct->setStatusTip(tr("Keep candidate frames in destination folder"));
	connect(keepNoneAct, &QAction::triggered, this, &MainWindow::keepNone);


	keepFrameGroup = new QActionGroup(this);
	keepFrameGroup->addAction(keepAllAct);
	keepFrameGroup->addAction(keepInterestingAct);
	keepFrameGroup->addAction(keepCandidateAct);
	keepFrameGroup->addAction(keepNoneAct);
	keepAllAct->setChecked(true);

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("About the project"));
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
	searchMenu = menuBar()->addMenu(tr("&Search"));
	searchMenu->addAction(searchAct);
	searchMenu->addAction(exitAct);

	configMenu = menuBar()->addMenu(tr("&Config"));
	configMenu->addAction(srcAct);
	configMenu->addAction(dstAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);

	keepFrameMenu = configMenu->addMenu(tr("&Keep frame"));
	keepFrameMenu->addAction(keepAllAct);
	keepFrameMenu->addAction(keepInterestingAct);
	keepFrameMenu->addAction(keepCandidateAct);
	keepFrameMenu->addAction(keepNoneAct);
}

Worker::Worker(config *get_cfg, QLabel *get_label, int get_mode)
{
	cfg = get_cfg;
	label = get_label;
	mode = get_mode;
}

Worker::~Worker()
{

}

void Worker::process() 
{
	if(mode == 1)
	{
		Worker::getCenter();
	}
	if(mode == 2)
	{
		Worker::getAverage();
	}
	if(mode == 3)
	{
		Worker::getPresort();
	}
	if(mode == 4)
	{
		Worker::getCheck();
	}
}

void Worker::getCenter()
{
	image *curImg = NULL;
	QImage *curQimg = NULL;
	unsigned int microseconds = 500;
	for(;;)
	{
		// lock UI to block average thread vom popping image
		cfg->mUiCenter.lock();
		// acquire average queue lock
		cfg->mAverage.lock();
		// get bottom image from queue
		curImg = cfg->qAverage.back();
		// release locks
		cfg->mAverage.unlock();
		cfg->mUiCenter.unlock();
		toQimage(curImg, cfg, curQimg);
		label->setPixmap(QPixmap::fromImage(*curQimg));
		usleep(microseconds);
	}
}

void Worker::getAverage()
{
    image *curImg = NULL;
    QImage *curQimg = NULL;
	unsigned int microseconds = 500;
	for(;;)
	{
		// lock UI to block average thread vom popping image
		cfg->mUiAverage.lock();
		// acquire average queue lock
		cfg->mPresort.lock();
		// get bottom image from queue
		curImg = cfg->qPresort.back();
		// release locks
		cfg->mPresort.unlock();
		cfg->mUiAverage.unlock();
		toQimage(curImg, cfg, curQimg);
		label->setPixmap(QPixmap::fromImage(*curQimg));
		usleep(microseconds);
	}
}

void Worker::getPresort()
{
    image *curImg = NULL;
    QImage *curQimg = NULL;
	unsigned int microseconds = 500;
	for(;;)
	{
		// lock UI to block average thread vom popping image
		cfg->mUiPresort.lock();
		// acquire average queue lock
		cfg->mCheck.lock();
		// get bottom image from queue
		curImg = cfg->qCheck.back();
		// release locks
		cfg->mCheck.unlock();
		cfg->mUiPresort.unlock();
		toQimage(curImg, cfg, curQimg);
		label->setPixmap(QPixmap::fromImage(*curQimg));
		usleep(microseconds);
	}
}

void Worker::getCheck()
{
    image *curImg = NULL;
    QImage *curQimg = NULL;
	unsigned int microseconds = 500;
	for(;;)
	{
		// lock UI to block average thread vom popping image
		//cfg->mUiCheck.lock();
		// acquire average queue lock
		//cfg->mAverage.lock();
		// get bottom image from queue
		//curImg = cfg->qCheck.back();
		// release locks
		//cfg->mAverage.unlock();
		//cfg->mUiCenter.unlock();
		//curQimg = toQimage(curImg, cfg);
		// label->setPixmap(QPixmap::fromImage(curQimg));
		usleep(microseconds);
	}
}