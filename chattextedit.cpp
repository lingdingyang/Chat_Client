#include "chattextedit.h"
#include<QEvent>

void ChatTextEdit::handleChange()
{
    QTextDocument *document = this->document();
    this->setFixedHeight(document->size().height() + 2);
    // qDebug() << document->size().height();
    emit sizeChanged();
}

ChatTextEdit::ChatTextEdit(QWidget *parent): QTextEdit(parent)
{
    this->setReadOnly(true);
    // this->setTextInteractionFlags(Qt::NoTextInteraction);
    viewport()->setCursor(Qt::ArrowCursor);
    handleChange();
    connect(this, &QTextEdit::textChanged, this, &ChatTextEdit::handleChange);
}

void ChatTextEdit::resizeEvent(QResizeEvent *event)
{
    emit QTextEdit::textChanged();
    QTextEdit::resizeEvent(event);
}
