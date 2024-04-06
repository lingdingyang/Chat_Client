#include "chatitem.h"
#include "ui_chatitem.h"



int ChatItem::totalHeight()
{
    return ui->lab_name->height() + ui->lab_time->height() + ui->textEdit->height() + 10;
}

ChatItem::ChatItem(QModelIndex index, QWidget *parent)    : QWidget(parent)
    , ui(new Ui::ChatItem), index(index)
{
    ui->setupUi(this);
    connect(ui->textEdit, &ChatTextEdit::textChanged, this, &ChatItem::handleSizeChanged);
}

void ChatItem::setName(const QString& name)
{
    ui->lab_name->setText(name);
}

void ChatItem::setTime(const QDateTime& time)
{
    ui->lab_time->setText(time.toString("yyyy-MM-dd hh-mm-ss"));
}

void ChatItem::setContent(const QString& content)
{
    ui->textEdit->setText(content);
}


ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::handleSizeChanged()
{
    qDebug() << "chat item:" << size();
    emit sizeChanged(index);
}
