#include "mainwindow.h"

#include <QApplication>
#include"sockettool.h"
#include"chatwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow c;
    MainWindow m;
    SocketTool sock_tool(&a, "localhost", 5050);
    m.setSocketTool(&sock_tool);
    c.setSocketTool(&sock_tool);
    c.setConnect();
    m.setC(&c);
    m.show();
    return a.exec();
}
