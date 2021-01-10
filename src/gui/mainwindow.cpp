#include "mainwindow.h"

#include "../../include/element/convertelement.h"
#include "../../include/element/loadelement.h"
#include "../../include/element/safeelement.h"
#include "../../include/element/virtualelement.h"

#include <QApplication>
#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>
#include <QFuture>
#include <QStringList>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    mdiArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(&mdiArea);
    statusBar()->showMessage("createActions", 5000);
    createActions();
    statusBar()->showMessage("createMenus", 5000);
    createMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    /* info: maakt de actions voor de menus */
    /* WindowMenu */
    A_Close.setText(RemoveAmpersand(tr("Cl&ose")));
    A_Close.setStatusTip(tr("Close the active window"));
    connect(
        &A_Close,
        &QAction::triggered,
        &mdiArea,
        &QMdiArea::closeActiveSubWindow);

    A_CloseAll.setText(RemoveAmpersand(tr("Close &All")));
    A_CloseAll.setStatusTip(tr("Close all the windows"));
    connect(
        &A_CloseAll,
        &QAction::triggered,
        &mdiArea,
        &QMdiArea::closeAllSubWindows);

    A_Tile.setText(RemoveAmpersand(tr("&Tile")));
    A_Tile.setStatusTip(tr("Tile the windows"));
    connect(&A_Tile, &QAction::triggered, &mdiArea, &QMdiArea::tileSubWindows);

    A_Cascade.setText(RemoveAmpersand(tr("&Cascade")));
    A_Cascade.setStatusTip(tr("Cascade the windows"));
    connect(
        &A_Cascade,
        &QAction::triggered,
        &mdiArea,
        &QMdiArea::cascadeSubWindows);

    /* menu */
    A_Exit.setText(RemoveAmpersand(tr("&Exit")));
    A_Exit.setStatusTip(tr("Exit the program"));
    connect(&A_Exit, &QAction::triggered, this, &MainWindow::close);

    A_Open.setText(RemoveAmpersand(tr("&Open")));
    A_Open.setStatusTip(tr("open file"));
    connect(&A_Open, SIGNAL(triggered()), this, SLOT(open_file()));

    A_Open_dir.setText(RemoveAmpersand(tr("&Open Dir")));
    A_Open_dir.setStatusTip(tr("open Dir"));
    connect(&A_Open_dir, SIGNAL(triggered()), this, SLOT(open_dir()));

    /* help */
    A_AboutQt.setText(RemoveAmpersand(tr("About &Qt")));
    connect(&A_AboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    /* info: maakt de menu structuur */
    M_File.setTitle(RemoveAmpersand(tr("&File")));
    menuBar()->addMenu(&M_File);

    M_File.addAction(&A_Open);
    M_File.addAction(&A_Open_dir);

#ifndef Q_OS_ANDROID
    M_File.addSeparator();
#endif
    M_File.addAction(&A_Exit);

    /* menu window */
    M_Window.setTitle(RemoveAmpersand(tr("&Window")));
    menuBar()->addMenu(&M_Window);
    M_Window.addAction(&A_Tile);
    M_Window.addAction(&A_Cascade);
#ifndef Q_OS_ANDROID
    M_Window.addSeparator();
#endif
    M_Window.addAction(&A_Close);
    M_Window.addAction(&A_CloseAll);
#ifndef Q_OS_ANDROID
    M_Window.addSeparator();
#endif
    /* QMenu *helpMenu; */
    M_Help.setTitle(RemoveAmpersand(tr("&help")));
    menuBar()->addMenu(&M_Help);
    M_Help.addAction(&A_AboutQt);
}

QString MainWindow::RemoveAmpersand(QString var)
{
#ifndef Q_OS_ANDROID
    return var;
#else
    return var.remove("&");
#endif
}

void MainWindow::Load_Convert_Safe(QString file_in, QString file_out)
{
    try
    {
        LoadElement    test(file_in);                      // 1 Load Element
        ConvertElement cetest(test);                       // 2 Convert Element
        VElement       test_element = cetest.GetElement(); // 3 Element
        SafeElement    test_safe(file_out, test_element);  // 4 Safe Element
    }
    catch (std::exception& e)
    {
        qWarning() << e.what(); // what is exception?
        qWarning() << "!! exception !!" << __LINE__ << __FILE__;
        qDebug() << "_____________________________________________________";
    }
    catch (...)
    {
        qWarning() << "!! exception !!" << __LINE__ << __FILE__;
    }
}

void MainWindow::open_file()
{
    QStringList data = QFileDialog::getOpenFileNames(
        this,
        tr("Open Element"),
        QDir::homePath(),
        tr("Element Files (*.elmt)"));
    for (QString filename : data)
    {
        QtConcurrent::run(
            this,
            &MainWindow::Load_Convert_Safe,
            filename,
            filename);
    }
}

void MainWindow::open_dir()
{

    QStringList  elements;
    QString      data_dir = QFileDialog::getExistingDirectory(
        this,
        tr("Open Element dir"),
        QDir::homePath() + "/GIT/qet/elements/");
    QDirIterator it(
        data_dir,
        QStringList() << "*.elmt",
        QDir::Files,
        QDirIterator::Subdirectories);
    QString Safe_dir = QFileDialog::getExistingDirectory(
        this,
        tr("Safe Element dir"),
        QDir::homePath() + "/.qet/elements/test/");
    while (it.hasNext()) elements << it.next();

    QStringList version_elements;
    for (QString filename : elements)
    {
        try
        {
            LoadElement    test(filename); // 1 Load Element
            ConvertElement CElem(test);    // 2 Convert Element
            VElement       test_element = CElem.GetElement(); // 3 Element
            qDebug() << Safe_dir + filename.remove(data_dir);
            SafeElement test_safe(
                Safe_dir + filename.remove(data_dir),
                test_element); // 4 Safe Element

            // 1 qDebug info-->
            qDebug() << "file: " + filename;
            qDebug() << "version             : "
                     << test.definition()
                            .value("version", "! no version gevonden")
                            .toString();
            version_elements << test.definition()
                                    .value("version", "! no version gevonden")
                                    .toString();
            qDebug() << "definition          : " << test.definition().size();
            qDebug() << "uuid                : " << test.uuid();
            qDebug() << "name                : " << test.name().size();
            qDebug() << "kindInformation     : "
                     << test.kindInformation().size();
            qDebug() << "elementInformations : "
                     << test.elementInformations().size();
            qDebug() << "informations        :" << test.informations();
            qDebug() << "description         : " << test.description().size();
            // <--1 qDebug info
        }
        catch (std::exception& e)
        {
            qWarning() << e.what(); // what is exception?
            qWarning() << "!! exception !!" << __LINE__ << __FILE__;
            qDebug() << "_____________________________________________________";
        }
    }
    qDebug() << "elements count :" << version_elements.count();
    for (int var = 0; var < 255; ++var)
    {
        if (0 < version_elements.count(QString("0.%1").arg(var)))
        {
            qDebug() << QString("nr of version 0.%1 :").arg(var)
                     << version_elements.count(QString("0.%1").arg(var));
        }
    }
}
