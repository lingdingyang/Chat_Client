#include "sockettool.h"

#include"Cmd.h"
#include"Error.h"
void SocketTool::readN(char *addr, int len)
{
    int left = len;
    int readed = 0;
    int count;
    while(left > 0) {
        count = socket->read(addr + readed, left);
        readed += count;
        left = len - readed;
    }
}

SocketTool::SocketTool(QObject *parent)
{
    socket = new QTcpSocket(parent);
}

bool SocketTool::connect_to_host(const QString &ip, int port)
{
    socket->connectToHost(ip, port);
    if( socket->waitForConnected()) {
        qDebug() << "连接完成" ;
        // login("testName");
        connect(socket, &QTcpSocket::readyRead, this, &SocketTool::handle_recv);
        return true;
    } else {
        qDebug() << "连接失败";
        return false;
    }
}

bool SocketTool::login(const QString& name)
{
    qDebug() << "name:" << name;
    user_name = name;
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
bool SocketTool::send_msg( const QString& recver, const QString &msg)
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("cmd", OP::SEND);
    obj.insert("data", msg.toUtf8().data());
    obj.insert("sender", user_name.toUtf8().data());
    obj.insert("recver", recver.toUtf8().data());
    doc.setObject(obj);
    QByteArray array = doc.toJson(QJsonDocument::JsonFormat::Compact);
    int len = array.length();
    // qDebug().noquote() << len << ":" << array;
    socket->write((char *)&len, 4);
    if( socket->waitForBytesWritten()) {
        qDebug() << "发送长度成功";
        socket->write(array.data(), len);
        if(socket->waitForBytesWritten()) {
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

QString SocketTool::get_user_name()
{
    return this->user_name;
}

void SocketTool::handle_recv()
{
    int len;
    readN((char*)&len, 4);
    qDebug().noquote() << "len：" << len;
    char* res = new char[len + 1];
    memset(res, 0, len + 1);
    readN(res, len);
    QString str_res = QString(res);
    delete[] res;
    qDebug() << "原始数据：" << str_res;
    qDebug().noquote()  << "收到数据：" << str_res;
    QJsonDocument doc = QJsonDocument::fromJson(str_res.toUtf8());
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
                QString sender =  obj["sender"].toString();
                QString content = obj["data"].toString();
                emit get_message(sender, content);
            }
        } else if(obj["op"].toInt() == OP::SEND_BACK) {
            qDebug() << "接收到发送确认";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
                QString recver =  obj["recver"].toString();
                QString content = obj["data"].toString();
                emit get_message_back(recver, content);
            }
        } else if(obj["op"].toInt() == OP::LIST) {
            qDebug().noquote() << "接收到用户列表";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
                QString data = obj["data"].toString();
                qDebug().noquote() << data;
                emit get_user_list(data);
            }
        } else if(obj["op"].toInt() == OP::LOGIN) {
            qDebug().noquote() << "收到登录返回";
            if(obj["error"].toInt() == ERROR_CODE::NO_ERROR) {
                qDebug().noquote() << "登陆成功";
            }
        }
    }
}
