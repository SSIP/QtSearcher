#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    /*
protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU
*/
private slots:
    void startSearch();
    void selectSource();
    void selectDestination();
    void keepAll();
    void keepInteresting();
    void keepCandidate();
    void keepNone();
    void about();
    void aboutQt();

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
};

#endif