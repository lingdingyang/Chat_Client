#include "chatwindow.h"
#include "ui_chatwindow.h"
#include<QAbstractItemView>
#include<QListWidgetItem>
#include"chatitem.h"
#include"userlistitem.h"
QStringList ChatWindow::getNameList()
{
    QStringList s;
    s.append("aaa");
    s.append("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    return s;
}

void ChatWindow::updateUserList()
{
    ui->user_list->setContentsMargins(0, 0, 0, 0);
    ui->user_list->setSpacing(3);
    this->ui->user_list->clear();
    QStringList name_list = getNameList();
    for(QString &name : name_list) {
        UserListItem *widget = new UserListItem(this);
        widget->setName(name);
        QListWidgetItem *item = new QListWidgetItem(ui->user_list);
        item->setSizeHint(widget->size());
        ui->user_list->addItem(item);
        ui->user_list->setItemWidget(item, widget);
    }
}

void ChatWindow::updateChatList()
{
    this->ui->chat_list->clear();
    ui->chat_list->setSelectionMode(QAbstractItemView::NoSelection);
    for(int i = 0; i < 3; i++) {
        QListWidgetItem *item = new QListWidgetItem(ui->chat_list);
        ui->chat_list->addItem(item);
        QModelIndex index = ui->chat_list->indexFromItem(item);
        ChatItem *widget = new ChatItem( index, this);
        item->setSizeHint(widget->size());
        ui->chat_list->setItemWidget(item, widget);
        connect(widget, &ChatItem::sizeChanged, this, &ChatWindow::handleSizeChange);
    }
}

void ChatWindow::handleSizeChange(const QModelIndex& index)
{
    QListWidgetItem* item = ui->chat_list->itemFromIndex(index);
    ChatItem* widget = (ChatItem*)ui->chat_list->itemWidget(item);
    item->setSizeHint(QSize(widget->minimumWidth(), widget->totalHeight()));
}


ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    btn_send = new QPushButton(this);
    // 获取窗口的宽度和高度(含边框)
    btn_send->setText("发送");
    btn_send->setMinimumHeight(50);
    btn_send->setMinimumWidth(150);
    updateUserList();
    updateChatList();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::resizeEvent(QResizeEvent *event)
{
    btn_send->move(this->frameGeometry().width() - btn_send->width() - 20, this->frameGeometry().height() - btn_send->height() - 50);
}
