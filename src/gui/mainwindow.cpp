#include "mainwindow.h"

#include "element/loadelement.h"

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>

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

void MainWindow::open_file()
{
	// #TODO Dir /home/simon/GIT/qet/elements/ veranderen
	QStringList data = QFileDialog::getOpenFileNames(
		this,
		tr("Open Element"),
		"/home/simon/GIT/qet/elements/",
		tr("Element Files (*.elmt)"));
	qDebug() << "QStringList:" << data;
	for (QString var : data)
	{
		try
		{
			LoadElement test(var);
			qDebug() << var;
			qDebug() << "name:            " << test.name();
			qDebug() << "uuid:            " << test.uuid();
			qDebug() << "informations:    " << test.informations();
			qDebug() << "description:     ";
			for (QMap<QString, QVariant> description : test.description())
			{ qDebug() << description; }
			qDebug() << "kindInformation: " << test.kindInformation();
			qDebug() << "definition:      " << test.definition();
		}
		catch (std::exception& e)
		{
			qWarning() << e.what(); // what is exception?
			qWarning() << "!! exception !!" << __LINE__ << __FILE__;
			qDebug() << "_____________________________________________________";
		}
	}
}
