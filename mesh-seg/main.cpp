#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow mainWindow;
	QRect available_geom = QDesktopWidget().availableGeometry();
	int W = available_geom.width();
	int H = available_geom.height();
	int w = 1200;
	int h = 600;
	int x = (W - w) / 2;
	int y = (H - h) / 2;
//	MainWindow.setWindowIcon(QIcon("david.ico"));
	mainWindow.setGeometry(x, y, w, h);
	mainWindow.showNormal();
	mainWindow.show();
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);      //设置初始显示模式
	return a.exec();
}
