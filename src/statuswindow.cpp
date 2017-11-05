#include <QtWidgets>

#include "statuswindow.h"

MainWindow::MainWindow()
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
	infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	infoLabel->setAlignment(Qt::AlignCenter);

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);
	layout->addWidget(topFiller);
	layout->addWidget(infoLabel);
	layout->addWidget(bottomFiller);
	widget->setLayout(layout);

	createActions();
	createMenus();

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);

	setWindowTitle(tr("Menus"));
	setMinimumSize(800, 600);
	resize(1280, 960);
}

/*
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
*/
void MainWindow::startSearch()
{
	infoLabel->setText(tr("start the search run"));
}

void MainWindow::selectSource()
{
	infoLabel->setText(tr("Select the source folder"));
}

void MainWindow::selectDestination()
{
	infoLabel->setText(tr("Select the destination folder"));
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