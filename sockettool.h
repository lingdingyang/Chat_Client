#ifndef SOCKETTOOL_H
#define SOCKETTOOL_H

#include <QObject>
#include<QTcpSocket>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>
class SocketTool: public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    bool is_login = false;
    QString user_name;
signals:
    void get_user_list(QString user_list);
    void get_message(const QString& sender, const QString& content);
    void get_message_back(const QString&recver, const QString &content);
public:
    SocketTool(QObject *parent, const QString &ip, int port);
    bool login(const QString& name);
    bool send_msg( const QString& recver, const QString &msg);
    bool get_list();
    bool check_login();
    QString get_user_name();
private slots:
    void handle_recv();
};

#endif // SOCKETTOOL_H
