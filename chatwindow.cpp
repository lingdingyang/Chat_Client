#include "chatwindow.h"
#include "ui_chatwindow.h"
#include"chatitem.h"
#include"userlistitem.h"


void ChatWindow::updateUserList()
{
    ui->user_list->setContentsMargins(0, 0, 0, 0);
    ui->user_list->setSpacing(3);
    this->ui->user_list->clear();
    for(const QString &name : username_list) {
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
    connect(ui->user_list, &QListWidget::currentItemChanged, this, &ChatWindow::handle_check_user);
    btn_send = new QPushButton(this);
    // 获取窗口的宽度和高度(含边框)
    btn_send->setText("发送");
    btn_send->setMinimumHeight(50);
    btn_send->setMinimumWidth(150);
    updateUserList();
    updateChatList();
}

void ChatWindow::setSocketTool(SocketTool *tool)
{
    this->tool = tool;
}

void ChatWindow::setConnect()
{
    connect(tool, &SocketTool::get_user_list, this, &ChatWindow::handle_get_user_list);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::resizeEvent(QResizeEvent *event)
{
    btn_send->move(this->frameGeometry().width() - btn_send->width() - 20, this->frameGeometry().height() - btn_send->height() - 50);
}

void ChatWindow::on_btn_update_user_list_clicked()
{
    tool->get_list();
}

void ChatWindow::handle_get_user_list(QString user_list)
{
    username_list.clear();
    qDebug().noquote() << "handle:" << user_list;
    QJsonDocument doc = QJsonDocument::fromJson(user_list.toUtf8());
    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON.";
    } else if (!doc.isArray()) {
        qDebug() << "JSON is not an array.";
    } else {
        QJsonArray obj = doc.array();
        for(int i = 0; i < obj.count(); i++) {
            qDebug() << obj[i].toString();
            username_list.append(obj[i].toString());
        }
    }
    updateUserList();
}

void ChatWindow::handle_check_user( QListWidgetItem* current,  QListWidgetItem* previous)
{
    qDebug() << "handle_check_user";
    UserListItem *current_widget = (UserListItem*)ui->user_list->itemWidget(current);
    QString current_name = current_widget->getName();
    if(selected_name != current_name) {
        selected_name = current_name;
        updateChatList();
    }
    // if(previous != nullptr) {
    //     UserListItem *previous_widget = (UserListItem*)ui->user_list->itemWidget(previous);
    //     QString previous_name = previous_widget->getName();
    //     qDebug() << current_name << " " << previous_name;
    //     if(current_name == previous_name ) {
    //         return;
    //     }
    // } else {
    //     qDebug() << "nullptr";
    // }
}

