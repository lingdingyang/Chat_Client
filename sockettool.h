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
public:
    SocketTool(QObject *parent, const QString &ip, int port);
    bool login(const QString &name);
    bool send_msg(const QString &sender, const QString& recver, const QString &msg);
    bool get_list();
    bool check_login();
};

#endif // SOCKETTOOL_H