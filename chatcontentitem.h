#ifndef CHATCONTENTITEM_H
#define CHATCONTENTITEM_H

#include <QObject>
#include<QString>
#include<QDateTime>
class ChatContentItem : public QObject
{
    Q_OBJECT
private:
    QString content;
    QDateTime time;
    bool isRecv ;
public:
    explicit ChatContentItem(const QString& content, const QDateTime& time, QObject *parent = nullptr, bool isRecv = true);
    ChatContentItem(const ChatContentItem& c);

    ChatContentItem &operator=(const ChatContentItem& c);
    QString getContent() const;
    QDateTime getTime()const;
    bool getIsRecv()const;
signals:
};

#endif // CHATCONTENTITEM_H
