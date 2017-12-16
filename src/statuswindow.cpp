#include "statuswindow.h"

/* Create the main window, elements on it and timers that periodicall fetch
 * images from the worker queues to display them on the window.
 * Also adds a timer to fetch log messages.
 */
MainWindow::MainWindow()
{
	createLayout();
	createActions();
	createMenus();

	setWindowTitle(tr("Menus"));
	setMinimumSize(1280, 960);
	resize(1280, 960);

	this->cfg = new config;
	loadDefaultConfig(this->cfg);
	modifyConfig(this->cfg);

	QTimer *timer_messages = new QTimer(this);
	connect(timer_messages, SIGNAL(timeout()), this, SLOT(updateMessages()));
	timer_messages->start(100);

	QTimer *timer_imgCenter = new QTimer(this);
	connect(timer_imgCenter, SIGNAL(timeout()), this, SLOT(getCenter()));
	timer_imgCenter->start(500);
	QTimer *timer_imgAverage = new QTimer(this);
	connect(timer_imgAverage, SIGNAL(timeout()), this, SLOT(getAverage()));
	timer_imgAverage->start(500);
	QTimer *timer_imgPresort = new QTimer(this);
	connect(timer_imgPresort, SIGNAL(timeout()), this, SLOT(getPresort()));
	timer_imgPresort->start(500);
	QTimer *timer_imgCheck = new QTimer(this);
	connect(timer_imgCheck, SIGNAL(timeout()), this, SLOT(getCheck()));
	timer_imgCheck->start(500);
}

/* Order the elements on the main window
 */
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

	this->imgCenter = new QLabel();
	this->imgAverage = new QLabel();
	this->imgPresort = new QLabel();
	this->imgCheck = new QLabel();

	this->imgCenter->setFixedWidth(350);
	this->imgCenter->setFixedHeight(350);
	this->imgCenter->setPixmap(QPixmap::fromImage(myImage).scaled(this->imgCenter->width(), this->imgCenter->height(), Qt::KeepAspectRatio));

	this->imgAverage->setFixedWidth(350);
	this->imgAverage->setFixedHeight(350);
	this->imgAverage->setPixmap(QPixmap::fromImage(myImage).scaled(this->imgAverage->width(), this->imgAverage->height(), Qt::KeepAspectRatio));

	this->imgPresort->setFixedWidth(350);
	this->imgPresort->setFixedHeight(350);
	this->imgPresort->setPixmap(QPixmap::fromImage(myImage).scaled(this->imgPresort->width(), this->imgPresort->height(), Qt::KeepAspectRatio));

	this->imgCheck->setFixedWidth(350);
	this->imgCheck->setFixedHeight(350);
	this->imgCheck->setPixmap(QPixmap::fromImage(myImage).scaled(this->imgCheck->width(), this->imgCheck->height(), Qt::KeepAspectRatio));

	this->logArea = new QTextEdit();
	this->logArea->setReadOnly(true);
	this->logArea->setText("Log\n========================================================");
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(capCenter, 0, 0);
	layout->addWidget(capAverage, 0, 3);
	layout->addWidget(capPresort, 1, 0);
	layout->addWidget(capCheck, 1, 3);
	layout->addWidget(this->imgCenter, 0, 1);
	layout->addWidget(imgAverage, 0, 2);
	layout->addWidget(imgPresort, 1, 1);
	layout->addWidget(imgCheck, 1, 2);
	layout->addWidget(this->logArea, 2, 0, 1, 4);
	widget->setLayout(layout);
}

/* Start the worker threads. This requires that the configuration is valid.
 */
void MainWindow::startSearch()
{
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "<b>Starting search</b>";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
	impactSearcherStart(this->cfg);
}

/* Open a dialog to select the source folder of images
 */
void MainWindow::selectSource()
{
	this->cfg->srcPath = QFileDialog::getExistingDirectory(this, tr("Select source directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Selected image source path: "<< this->cfg->srcPath;
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}

/* Open a dialog to select the destination folder of images
 */
void MainWindow::selectDestination()
{
	this->cfg->dstPath = QFileDialog::getExistingDirectory(this, tr("Select destination directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Selected image destination path: "<< this->cfg->dstPath;
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}

/* Change search configuration to
 *   - keep all or
 *   - keep interesting or
 *   - keep candidate or
 *   - keep no
 * images in destination folder.
 */
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

/* Change search algorithm verbosity to
 *   - no messages or
 *   - normal amount of messages or
 *   - more messages or
 *   - all messages or
 *   - add debug output.
 */
void MainWindow::logNone()
{
	this->cfg->verbosity = 0;
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Verbosity set to None";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}
void MainWindow::logDefault()
{
	this->cfg->verbosity = 1;
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Verbosity set to Default";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}
void MainWindow::logMore()
{
	this->cfg->verbosity = 2;
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Verbosity set to More";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}
void MainWindow::logAll()
{
	this->cfg->verbosity = 3;
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Verbosity set to All";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}
void MainWindow::logDebug()
{
	this->cfg->verbosity = 4;
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Verbosity set to Debug";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}

/* Display information about the project.
 */
void MainWindow::about()
{
	infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
						tr("Solar System Impact Project"));
}

/* Create actions for menu items. Called when window is created.
 */
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
		* -> Log level
		*    -> 0 (None)
		*    -> 1 (Default)
		*    -> 2 (More)
		*    -> 3 (All)
		*    -> 4 (Debug)
		*/
	srcAct = new QAction(tr("&Source folder"), this);
	//srcAct->setShortcuts(tr());
	srcAct->setStatusTip(tr("Select source folder with images"));
	connect(srcAct, &QAction::triggered, this, &MainWindow::selectSource);

	dstAct = new QAction(tr("&Destination folder"), this);
	dstAct->setStatusTip(tr("Select destination folder for images"));
	connect(dstAct, &QAction::triggered, this, &MainWindow::selectDestination);

	keepAllAct = new QAction(tr("All"), this);
	keepAllAct->setCheckable(true);
	keepAllAct->setStatusTip(tr("Keep all frames in destination folder"));
	connect(keepAllAct, &QAction::triggered, this, &MainWindow::keepAll);
	keepInterestingAct = new QAction(tr("Interesting"), this);
	keepInterestingAct->setCheckable(true);
	keepInterestingAct->setStatusTip(tr("Keep interesting frames in destination folder"));
	connect(keepInterestingAct, &QAction::triggered, this, &MainWindow::keepInteresting);
	keepCandidateAct = new QAction(tr("Candidates"), this);
	keepCandidateAct->setCheckable(true);
	keepCandidateAct->setStatusTip(tr("Keep candidate frames in destination folder"));
	connect(keepCandidateAct, &QAction::triggered, this, &MainWindow::keepCandidate);
	keepNoneAct = new QAction(tr("None"), this);
	keepNoneAct->setCheckable(true);
	keepNoneAct->setStatusTip(tr("Keep no frames in destination folder"));
	connect(keepNoneAct, &QAction::triggered, this, &MainWindow::keepNone);
	keepFrameGroup = new QActionGroup(this);
	keepFrameGroup->addAction(keepAllAct);
	keepFrameGroup->addAction(keepInterestingAct);
	keepFrameGroup->addAction(keepCandidateAct);
	keepFrameGroup->addAction(keepNoneAct);
	keepAllAct->setChecked(true);

	logNoneAct = new QAction(tr("No messages"), this);
	logNoneAct->setCheckable(true);
	logNoneAct->setStatusTip(tr("0 (None)"));
	connect(logNoneAct, &QAction::triggered, this, &MainWindow::logNone);
	logDefaultAct = new QAction(tr("Default"), this);
	logDefaultAct->setCheckable(true);
	logDefaultAct->setStatusTip(tr("1 (Default)"));
	connect(logDefaultAct, &QAction::triggered, this, &MainWindow::logDefault);
	logMoreAct = new QAction(tr("More messages"), this);
	logMoreAct->setCheckable(true);
	logMoreAct->setStatusTip(tr("2 (More)"));
	connect(logMoreAct, &QAction::triggered, this, &MainWindow::logMore);
	logAllAct = new QAction(tr("All messages"), this);
	logAllAct->setCheckable(true);
	logAllAct->setStatusTip(tr("3 (All)"));
	connect(logAllAct, &QAction::triggered, this, &MainWindow::logAll);
	logDebugAct = new QAction(tr("Debug output"), this);
	logDebugAct->setCheckable(true);
	logDebugAct->setStatusTip(tr("May change results"));
	connect(logDebugAct, &QAction::triggered, this, &MainWindow::logDebug);
	logMenuGroup = new QActionGroup(this);
	logMenuGroup->addAction(logNoneAct);
	logMenuGroup->addAction(logDefaultAct);
	logMenuGroup->addAction(logMoreAct);
	logMenuGroup->addAction(logAllAct);
	logMenuGroup->addAction(logDebugAct);
	logDefaultAct->setChecked(true);

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("About the project"));
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

/* Create the menus. Called when window is created.
 */
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

	logLevelMenu = configMenu->addMenu(tr("Set &Log level"));
	logLevelMenu->addAction(logNoneAct);
	logLevelMenu->addAction(logDefaultAct);
	logLevelMenu->addAction(logMoreAct);
	logLevelMenu->addAction(logAllAct);
	logLevelMenu->addAction(logDebugAct);
}

/* Get messages from search algorithm and display in text area. This function
 * is called periodically and then fetches all available messages.
 */
void MainWindow::updateMessages()
{
	this->cfg->mMessages.lock();
	while(!this->cfg->qMessages.empty()) {
		logArea->append(QString::fromStdString(cfg->qMessages.front()));
		this->cfg->qMessages.pop();
		logArea->verticalScrollBar()->setValue(logArea->verticalScrollBar()->maximum());
	}
	this->cfg->mMessages.unlock();
}

/* Get image from queue between centering and averaging threads and display
 * it as the upper left image.
 */
void MainWindow::getCenter()
{
	QImage curQimg((int)this->cfg->imageResX, (int)this->cfg->imageResY, QImage::Format_RGB32);
	image *curImg = NULL;
	// lock UI to block average thread vom popping image
	this->cfg->mUiCenter.lock();
	// acquire average queue lock
	this->cfg->mAverage.lock();
	// get bottom image from queue
	if(!this->cfg->qAverage.empty())
	{
		curImg = this->cfg->qAverage.back();
		toQimage8Bit(curImg->rawBitmap, this->cfg, &curQimg);
		this->cfg->mAverage.unlock();
		this->cfg->mUiCenter.unlock();
		this->imgCenter->setPixmap(QPixmap::fromImage(curQimg).scaled(this->imgCenter->width(), this->imgCenter->height(), Qt::KeepAspectRatio));
	}
	else
	{
		this->cfg->mAverage.unlock();
		this->cfg->mUiCenter.unlock();
		return;
	}
}

/* Get image from queue between averaging and presorting threads and display
 * it as the upper right image.
 */
void MainWindow::getAverage()
{
	QImage curQimg((int)this->cfg->imageResX, (int)this->cfg->imageResY, QImage::Format_RGB16);
	image *curImg = NULL;
	// lock UI to block average thread vom popping image
	this->cfg->mUiAverage.lock();
	// acquire average queue lock
	this->cfg->mPresort.lock();
	// get bottom image from queue
	if(!this->cfg->qPresort.empty())
	{
		curImg = this->cfg->qPresort.back();
		toQimage16Bit(curImg->diffBitmap, this->cfg, &curQimg);
		this->cfg->mPresort.unlock();
		this->cfg->mUiAverage.unlock();
		this->imgAverage->setPixmap(QPixmap::fromImage(curQimg).scaled(this->imgAverage->width(), this->imgAverage->height(), Qt::KeepAspectRatio));
	}
	else
	{
		this->cfg->mPresort.unlock();
		this->cfg->mUiAverage.unlock();
		return;
	}
}

/* Get image from queue between presorting and final check threads and display
 * it as the lower left image.
 */
void MainWindow::getPresort()
{
	QImage curQimg((int)this->cfg->imageResX, (int)this->cfg->imageResY, QImage::Format_RGB888);
	image *curImg = NULL;
	// lock UI to block average thread vom popping image
	this->cfg->mUiPresort.lock();
	// acquire average queue lock
	this->cfg->mCheck.lock();
	// get bottom image from queue
	if(!this->cfg->qCheck.empty())
	{
		curImg = this->cfg->qCheck.back();
		toQimage8Bit(curImg->rawBitmap, this->cfg, &curQimg);
		this->cfg->mCheck.unlock();
		this->cfg->mUiPresort.unlock();
		this->imgPresort->setPixmap(QPixmap::fromImage(curQimg).scaled(this->imgPresort->width(), this->imgPresort->height(), Qt::KeepAspectRatio));
	}
	else
	{
		this->cfg->mCheck.unlock();
		this->cfg->mUiPresort.unlock();
		return;
	}
}

void MainWindow::getCheck()
{
    image *curImg = NULL;
	// lock UI to block average thread vom popping image
	//this->cfg->mUiCheck.lock();
	// acquire average queue lock
	//this->cfg->mAverage.lock();
	// get bottom image from queue
	//curImg = cfg->qCheck.back();
	// release locks
	//this->cfg->mAverage.unlock();
	//this->cfg->mUiCenter.unlock();
	//curQimg = toQimage(curImg, cfg);
	// this->label->setPixmap(QPixmap::fromImage(curQimg));
}
