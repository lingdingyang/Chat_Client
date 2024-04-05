#ifndef USERLISTITEM_H
#define USERLISTITEM_H

#include <QWidget>

namespace Ui
{
    class UserListItem;
}

class UserListItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserListItem(QWidget *parent = nullptr);
    void setName(const QString& name);
    void setTime(const QString& time);
    ~UserListItem();

private:
    Ui::UserListItem *ui;
};

#endif // USERLISTITEM_H
