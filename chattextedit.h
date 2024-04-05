#ifndef CHATTEXTEDIT_H
#define CHATTEXTEDIT_H

#include <QObject>
#include <QTextEdit>

class ChatTextEdit : public QTextEdit
{
    Q_OBJECT
private slots:
    void handleChange();
public:
    ChatTextEdit(QWidget *parent);
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
signals:
    void sizeChanged();
};

#endif // CHATTEXTEDIT_H
