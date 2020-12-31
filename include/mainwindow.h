#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

  private:
	QMdiArea mdiArea;

	QMenu
		/* Menu */
		M_File,
		/* menu window */
		M_Window,
		/* help */
		M_Help;
	QAction
		/* Menu */
		A_Exit,
		A_Open,
		/* menu window */
		A_Close, A_CloseAll, A_Tile, A_Cascade,
		/* help */
		A_AboutQt;
	void	createActions();
	void	createMenus();
	QString RemoveAmpersand(QString var);
  private slots:
	void open_file();
};
#endif // MAINWINDOW_H
