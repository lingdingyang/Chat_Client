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
        if(name == tool->get_user_name()) {
            continue;
        }
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
    if(selected_name.isEmpty()) {
        return;
    }
    ChatContent* contents = name_to_content[selected_name];
    QList<ChatContentItem*> content_list = contents->getContentList();
    for(auto i = content_list.begin(); i != content_list.end(); ++i) {
        QString content = (*i)->getContent();
        QDateTime time = (*i)->getTime();
        QListWidgetItem *item = new QListWidgetItem(ui->chat_list);
        ui->chat_list->addItem(item);
        QModelIndex index = ui->chat_list->indexFromItem(item);
        ChatItem *widget = new ChatItem( index, this);
        if((*i)->getIsRecv()) {
            widget->setName(selected_name);
        } else {
            widget->setName(tool->get_user_name());
        }
        widget->setTime(time);
        widget->setContent(content);
        item->setSizeHint(widget->size());
        ui->chat_list->setItemWidget(item, widget);
        connect(widget, &ChatItem::sizeChanged, this, &ChatWindow::handleSizeChange);
    }
}

// void ChatWindow::clear_name_to_content()
// {
//     for(auto i = name_to_content.begin(); i != name_to_content.end(); ++i) {
//         if(*i != nullptr) {
//             delete *i;
//         }
//     }
// }

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
    connect(tool, &SocketTool::get_message, this, &ChatWindow::handle_add_chat_item);
    connect(tool, &SocketTool::get_message_back, this, &ChatWindow::handle_add_chat_item_back);
    connect(btn_send, &QPushButton::clicked, this, &ChatWindow::handle_btn_send_clicked);
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
    qDebug().noquote() << "handle:" << user_list;
    QJsonDocument doc = QJsonDocument::fromJson(user_list.toUtf8());
    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON.";
    } else if (!doc.isArray()) {
        qDebug() << "JSON is not an array.";
    } else {
        username_list.clear();
        QJsonArray obj = doc.array();
        for(int i = 0; i < obj.count(); i++) {
            QString name = obj[i].toString();
            username_list.append(name);
        }
        for(auto i = username_list.begin(); i != username_list.end(); ++i) {
            if(name_to_content.find(*i) == name_to_content.end()) {
                name_to_content[*i] = new ChatContent(*i, this);
            }
        }
        updateUserList();
    }
}

void ChatWindow::handle_check_user( QListWidgetItem* current,  QListWidgetItem* previous)
{
    qDebug() << "handle_check_user";
    if(current == nullptr) {
        return;
    }
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

void ChatWindow::handle_add_chat_item(const QString &sender, const QString &content)
{
    qDebug() << "handle_add_chat_item：";
    qDebug() << "sender:" << sender << "content:" << content;
    if(name_to_content.find(sender) == name_to_content.end()) {
        qDebug() << "接收到未知用户信息";
        return;
    }
    name_to_content[sender]->addContent(new ChatContentItem(content, QDateTime::currentDateTime(), this));
    updateChatList();
}

void ChatWindow::handle_add_chat_item_back(const QString &recver, const QString &content)
{
    qDebug() << "handle_add_chat_item_back";
    qDebug() << "recver:" << recver << "content:" << content;
    if(name_to_content.find(recver) == name_to_content.end()) {
        qDebug() << "接收到未知用户信息";
        return;
    }
    name_to_content[recver]->addContent(new ChatContentItem(content, QDateTime::currentDateTime(), this, false));
    updateChatList();
}

void ChatWindow::handle_btn_send_clicked()
{
    qDebug() << "handle_btn_send_clicked";
    if(selected_name.isEmpty()) {
        return;
    }
    QString input_content = ui->edit_input->toPlainText().trimmed();
    if(input_content.isEmpty()) {
        return;
    }
    tool->send_msg(selected_name, input_content);
}

