#include "statuswindow.h"

MainWindow::MainWindow()
{
	createLayout();
	createActions();
	createMenus();

	setWindowTitle(tr("Menus"));
	setMinimumSize(1280, 960);
	resize(1280, 960);

	this->cfg = new config;
	setStdConf(this->cfg);

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
	this->imgAverage->setFixedWidth(350);
	this->imgAverage->setFixedHeight(350);
	this->imgPresort->setFixedWidth(350);
	this->imgPresort->setFixedHeight(350);
	this->imgCheck->setFixedWidth(350);
	this->imgCheck->setFixedHeight(350);
	this->imgCenter->setPixmap(QPixmap::fromImage(myImage));
	this->imgAverage->setPixmap(QPixmap::fromImage(myImage));
	this->imgPresort->setPixmap(QPixmap::fromImage(myImage));
	this->imgCheck->setPixmap(QPixmap::fromImage(myImage));
	this->logArea = new QTextEdit();
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


void MainWindow::startSearch()
{
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "<b>Starting search</b>";
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
	impactSearcherStart(this->cfg);
}

void MainWindow::selectSource()
{
	this->cfg->srcPath = QFileDialog::getExistingDirectory(this, tr("Select source directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Selected image source path: "<< this->cfg->srcPath;
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
}

void MainWindow::selectDestination()
{
	this->cfg->dstPath = QFileDialog::getExistingDirectory(this, tr("Select destination directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
	this->cfg->mMessages.lock();
	stringstream ss;
	ss << "Selected image destination path: "<< this->cfg->dstPath;
	this->cfg->qMessages.push(ss.str());
	this->cfg->mMessages.unlock();
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

void MainWindow::updateMessages()
{
	this->cfg->mMessages.lock();
	while(!this->cfg->qMessages.empty()) {
		logArea->append(QString::fromStdString(cfg->qMessages.front()));
		this->cfg->qMessages.pop();
	}
	this->cfg->mMessages.unlock();
}

void MainWindow::getCenter()
{
	QImage curQimg((int)this->cfg->imageResX, (int)this->cfg->imageResY, QImage::Format_RGB888);
	image *curImg = NULL;
	// lock UI to block average thread vom popping image
	this->cfg->mUiCenter.lock();
	// acquire average queue lock
	this->cfg->mAverage.lock();
	// get bottom image from queue
	if(!this->cfg->qAverage.empty())
	{
		curImg = this->cfg->qAverage.back();
		toQimage(curImg, this->cfg, &curQimg);
		this->cfg->mAverage.unlock();
		this->cfg->mUiCenter.unlock();
		this->imgCenter->setPixmap(QPixmap::fromImage(curQimg));
	}
	else
	{
		this->cfg->mAverage.unlock();
		this->cfg->mUiCenter.unlock();
		return;
	}
}

void MainWindow::getAverage()
{
	QImage curQimg((int)this->cfg->imageResX, (int)this->cfg->imageResY, QImage::Format_RGB888);
	image *curImg = NULL;
	// lock UI to block average thread vom popping image
	this->cfg->mUiAverage.lock();
	// acquire average queue lock
	this->cfg->mPresort.lock();
	// get bottom image from queue
	if(!this->cfg->qPresort.empty())
	{
		curImg = this->cfg->qPresort.back();
		toQimage(curImg, this->cfg, &curQimg);
		this->cfg->mPresort.unlock();
		this->cfg->mUiAverage.unlock();
		this->imgAverage->setPixmap(QPixmap::fromImage(curQimg));
	}
	else
	{
		this->cfg->mPresort.unlock();
		this->cfg->mUiAverage.unlock();
		return;
	}
}

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
		toQimage(curImg, this->cfg, &curQimg);
		this->cfg->mCheck.unlock();
		this->cfg->mUiPresort.unlock();
		this->imgPresort->setPixmap(QPixmap::fromImage(curQimg));
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
