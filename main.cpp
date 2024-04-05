#include "mainwindow.h"

#include <QApplication>
#include"sockettool.h"
#include"chatwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow c;
    c.show();
    return a.exec();
}
