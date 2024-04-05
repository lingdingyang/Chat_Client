#ifndef CHATCONTENT_H
#define CHATCONTENT_H

#include <QObject>
#include"chatcontentitem.h"
class ChatContent : public QObject
{
    Q_OBJECT
private:
    QString name;
    QList<ChatContentItem> content_list;
public:
    explicit ChatContent(QString name, QObject *parent = nullptr);
    QString getName() const;
    void addContent( ChatContentItem item);
    const QList<ChatContentItem>& getContentList()const;

signals:
};

#endif // CHATCONTENT_H
