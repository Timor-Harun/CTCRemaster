#include "CTCMainWindow.h"
#include <QtWidgets/QApplication>
#include "PythonCodeEditor.h"
#include <qglobal.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTCMainWindow w; 
    w.show();
    return a.exec();
}