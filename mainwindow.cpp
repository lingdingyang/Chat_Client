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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
    socket_tool->login(ui->edt_user_name->text());
}


void MainWindow::on_pushButton_clicked()
{
    socket_tool->get_list();
}

