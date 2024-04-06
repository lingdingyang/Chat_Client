#include "chatcontent.h"

QString ChatContent::getName() const
{
    return name;
}

void ChatContent::addContent( ChatContentItem* item)
{
    content_list.append(item);
}

const QList<ChatContentItem*>& ChatContent::getContentList()const
{
    return content_list;
}

ChatContent::ChatContent(QString name, QObject *parent)
    : QObject{parent}, name(name)
{}

ChatContent::~ChatContent()
{
    qDebug() << "~ChatContent" ;
}
