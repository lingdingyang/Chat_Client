#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include<QPushButton>
#include<QListWidgetItem>
#include"sockettool.h"
#include<QHash>
#include"chatcontent.h"
namespace Ui
{
    class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT
private:
    QHash<QString, ChatContent*> name_to_content;
    SocketTool *tool = nullptr;
    QPushButton *btn_send;
    QStringList username_list;
    QString selected_name;

    void updateUserList();
    void updateChatList();
    // void clear_name_to_content();

private slots:
    void handleSizeChange(const QModelIndex& index);
    void on_btn_update_user_list_clicked();
    void handle_get_user_list( QString user_list);
    void handle_check_user( QListWidgetItem* current,  QListWidgetItem* previous);
    void handle_add_chat_item(const QString& sender, const QString& content);
    void handle_add_chat_item_back(const QString& recver, const QString& content);
    void handle_btn_send_clicked();
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    void setSocketTool( SocketTool* tool);
    void setConnect();
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CHATWINDOW_H
