#include "mainwindow.h"
#include "./ui_mainwindow.h"
QTcpSocket *socket;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::setSocketTool(SocketTool *socket)
{
    this->socket_tool = socket;
}

void MainWindow::setC(ChatWindow *c)
{
    this->c = c;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
    qDebug() << "on_btn_login_clicked";
    socket_tool ->connect_to_host(ui->lineEdit->text(), 5050);
    socket_tool->login(ui->edt_user_name->text());
    c->setWindowTitle(socket_tool->get_user_name());
    c->show();
    socket_tool->get_list();
    this->close();
}
