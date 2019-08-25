#include "notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	notepad w;
	w.show();
	return a.exec();
}
