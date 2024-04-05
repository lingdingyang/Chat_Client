#ifndef CHATCONTENTITEM_H
#define CHATCONTENTITEM_H

#include <QObject>
#include<QString>
#include<QTime>
class ChatContentItem : public QObject
{
    Q_OBJECT
private:
    QString content;
    QTime time;
public:
    explicit ChatContentItem(const QString& content, const QTime& time, QObject *parent = nullptr);
    ChatContentItem(const ChatContentItem& c);

    ChatContentItem &operator=(const ChatContentItem& c);
    QString getContent() const;
    QTime getTime()const;
signals:
};

#endif // CHATCONTENTITEM_H
