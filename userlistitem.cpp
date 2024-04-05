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
    this->ui->lab_name->setText(name);
}

void UserListItem::setTime(const QString &time)
{

}

UserListItem::~UserListItem()
{
    delete ui;
}
