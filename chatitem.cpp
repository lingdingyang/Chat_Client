#include "chatitem.h"
#include "ui_chatitem.h"



int ChatItem::totalHeight()
{
    return ui->label->height() + ui->label_2->height() + ui->textEdit->height() + 10;
}

ChatItem::ChatItem(QModelIndex index, QWidget *parent)    : QWidget(parent)
    , ui(new Ui::ChatItem), index(index)
{
    ui->setupUi(this);
    connect(ui->textEdit, &ChatTextEdit::textChanged, this, &ChatItem::handleSizeChanged);
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
