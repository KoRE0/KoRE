#include <QGuiApplication>
#include "glwindow.h"

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);
	GLWindow w;
	w.show();
	return a.exec();
}
