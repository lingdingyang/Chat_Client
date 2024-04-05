#include "mainwindow.h"

#include <QApplication>
#include"sockettool.h"
#include"chatwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow c;
    SocketTool sock_tool(&a, "localhost", 5050);
    c.setSocketTool(&sock_tool);
    c.setConnect();
    c.show();
    return a.exec();
}
