#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QuaZip-Qt5-1.3/quazip/JlCompress.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QDir dir("/tmp/imview");
    if (dir.exists())
    {
        dir.removeRecursively();
    }
    if (argc == 2)
    {
        QString filename(argv[1]);
        w.LoadProject(filename);
    }
    w.show();
    return a.exec();
}
