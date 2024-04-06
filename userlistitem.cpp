#include "userlistitem.h"
#include "ui_userlistitem.h"

UserListItem::UserListItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserListItem)
{
    ui->setupUi(this);
}

void UserListItem::setName(const QString &name)
{
    this->name = name;
    this->ui->lab_name->setText(name);
}

void UserListItem::setTime(const QString &time)
{
}

void UserListItem::setAccept()
{
    this->ui->lab_time->setText("有新的消息");
}

void UserListItem::setNotAccept()
{
    this->ui->lab_time->clear();
}

QString UserListItem::getName()
{
    return name;
}

UserListItem::~UserListItem()
{
    // qDebug() << "~UserListItem " << name;
    delete ui;
}
