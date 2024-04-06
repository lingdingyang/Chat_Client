#include "chatcontentitem.h"

QString ChatContentItem::getContent() const
{
    return content;
}

QDateTime ChatContentItem::getTime() const
{
    return time;
}

bool ChatContentItem::getIsRecv() const
{
    return this->isRecv;
}

ChatContentItem::ChatContentItem(const QString &content, const QDateTime &time,  QObject *parent, bool isRecv)
    : QObject{parent}, content(content), time(time), isRecv(isRecv)
{}

ChatContentItem::ChatContentItem(const ChatContentItem &other)
{
    content = other.content;
    time = other.time;
}

ChatContentItem &ChatContentItem::operator=(const ChatContentItem &other)
{
    if(this != &other) {
        this->content = other.content;
        this->time = other.time;
    }
    return *this;
}
