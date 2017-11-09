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
	MainWindow::setStdConf(&cfg);

	QThread* thread = new QThread;
	Worker* worker = new Worker(&cfg);
	worker->moveToThread(thread);
	/*connect(worker, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
	//connect(thread, SIGNAL (started()), worker, SLOT (process()));
	connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
	connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
	connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));*/
	thread->start();
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

void MainWindow::setStdConf(config* cfg) {
	//cfg->imageResX = cfg->imageResY = 480;
	cfg->srcPath = QDir::homePath().toStdString();
	cfg->dstPath = QDir::homePath().toStdString();;
	cfg->keepFrames = KEEP_ALL;
	//cfg->archiveType = ARCHIVE_PNG; //todo: test bmp and png values
	cfg->centerSkipPixels = 5;
	cfg->centerAlgo = CENTER_OF_MASS;
	cfg->centerThreshold = 50;
	cfg->averageLength = 10;
	//cfg->averageFilterSize = 0.125;
	cfg->avgCrit = 1.5;
	cfg->devCrit = 1.5;
	cfg->checkSNR = 5.0;
	cfg->checkRadius = 1.0;
	cfg->verbosity = 2;
	cfg->rayBrightnessThreshold = 0.3;
}

void MainWindow::startSearch()
{

	infoLabel->setText(tr("start the search run"));
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

Worker::Worker(config *get_cfg)
{
	cfg = get_cfg;
}

Worker::~Worker()
{

}

void Worker::process() 
{
	unsigned int microseconds = 500;
	for(;;)
	{
		cfg->mUiAverage.lock();
		cfg->mUiAverage.unlock();
		usleep(microseconds);
	}
    emit finished();
}