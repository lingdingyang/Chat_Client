#include "sockettool.h"

#include"Cmd.h"
#include"Error.h"
SocketTool::SocketTool(QObject *parent, const QString &ip, int port)
{
    socket = new QTcpSocket(parent);
    socket->connectToHost(ip, port);
    if( socket->waitForConnected()) {
        qDebug() << "连接完成" ;
        login("testName");
        connect(socket, &QTcpSocket::readyRead, this, &SocketTool::handle_recv);
    } else {
        qDebug() << "连接失败";
    }
}

bool SocketTool::login(const QString &name)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("cmd", OP::LOGIN);
    obj.insert("data", name);
    doc.setObject(obj);
    QString str = doc.toJson(QJsonDocument::JsonFormat::Compact);
    int len = strlen( str.toUtf8().data());
    qDebug() << len << "\n" << str.toUtf8().data() << "\n" << str << "\n" << str.length() << "\n"
             << str.toUtf8() << "\n" << str.toUtf8().length();
    socket->write((char *)&len, 4);
    if( socket->waitForBytesWritten(2000)) {
        qDebug() << "发送长度成功";
        socket->write(str.toUtf8().data(), len);
        if(socket->waitForBytesWritten(2000)) {
            qDebug() << "发送成功";
            is_login = true;
            return true;
        } else {
            qDebug() << "发送失败";
            return false;
        }
    } else {
        qDebug() << "发送长度失败";
        return false;
    }
}
bool SocketTool::send_msg(const QString &sender, const QString& recver, const QString &msg)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("cmd", OP::SEND);
    obj.insert("data", msg.toUtf8().data());
    obj.insert("sender", sender.toUtf8().data());
    obj.insert("recver", recver.toUtf8().data());
    QByteArray array = doc.toJson(QJsonDocument::JsonFormat::Compact);
    int len = array.length();
    socket->write((char *)&len, 4);
    if( socket->waitForBytesWritten()) {
        qDebug() << "发送长度成功\n";
        socket->write(array.data(), len);
        if(socket->waitForBytesWritten()) {
            qDebug() << "发送成功\n";
            return true;
        } else {
            qDebug() << "发送失败\n";
            return false;
        }
    } else {
        qDebug() << "发送长度失败\n";
        return false;
    }
}

bool SocketTool::get_list()
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("cmd", OP::LIST);
    doc.setObject(obj);
    QString str = doc.toJson(QJsonDocument::JsonFormat::Compact);
    int len = strlen( str.toUtf8().data());
    qDebug() << len << "\n" << str.toUtf8().data() << "\n" << str << "\n" << str.length() << "\n"
             << str.toUtf8() << "\n" << str.toUtf8().length();
    socket->write((char *)&len, 4);
    if( socket->waitForBytesWritten(2000)) {
        qDebug() << "发送长度成功";
        socket->write(str.toUtf8().data(), len);
        if(socket->waitForBytesWritten(2000)) {
            qDebug() << "发送成功";
            return true;
        } else {
            qDebug() << "发送失败";
            return false;
        }
    } else {
        qDebug() << "发送长度失败";
        return false;
    }
}

bool SocketTool::check_login()
{
    return is_login;
}

void SocketTool::handle_recv()
{
    QByteArray res = socket->readAll();
    QString str = QString::fromUtf8(res);
    str = str.mid(4);
    qDebug().noquote()  << "收到数据：" << str;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON.";
    } else if (!doc.isObject()) {
        qDebug() << "JSON is not an object.";
    } else {
        QJsonObject obj = doc.object();
        qDebug() << "Received JSON object:" << obj;
        if(obj["op"].toInt() == OP::SEND) {
            qDebug() << "接收到消息";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
            }
        } else if(obj["op"].toInt() == OP::SEND_BACK) {
            qDebug() << "接收到发送确认";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
            }
        } else if(obj["op"].toInt() == OP::LIST) {
            qDebug().noquote() << "接收到用户列表";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
                QString data = obj["data"].toString();
                qDebug().noquote() << data;
                emit get_user_list(data);
            }
        }
    }
}
