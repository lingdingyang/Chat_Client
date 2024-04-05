#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include<QPushButton>

namespace Ui
{
    class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btn_send;
    QStringList getNameList();
    void updateUserList();
    void updateChatList();

private slots:
    void handleSizeChange(const QModelIndex& index);
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CHATWINDOW_H
