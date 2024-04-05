#include "chatcontentitem.h"

QString ChatContentItem::getContent() const
{
    return content;
}

QTime ChatContentItem::getTime() const
{
    return time;
}

ChatContentItem::ChatContentItem(const QString &content, const QTime &time, QObject *parent)
    : QObject{parent}, content(content), time(time)
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
