#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>
#include<QModelIndex>
namespace Ui
{
    class ChatItem;
}

class ChatItem : public QWidget
{
    Q_OBJECT
signals:
    void sizeChanged(QModelIndex index);
public:
    int totalHeight();
    explicit ChatItem( QModelIndex index, QWidget *parent = nullptr);
    ~ChatItem();
private slots:
    void handleSizeChanged();
private:
    QModelIndex index;
    Ui::ChatItem *ui;
};

#endif // CHATITEM_H
