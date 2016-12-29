#include "customgraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QResizeEvent>

CustomGraphicsView::CustomGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_videoItem(new QGraphicsVideoItem())
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setScene(m_scene);
    m_scene->addItem(m_videoItem);
    m_videoItem->setOffset(QPointF(0.0f, 0.0f));
    m_videoItem->setSize(size());
}

QGraphicsVideoItem *CustomGraphicsView::getVideoItem() const
{
    return m_videoItem;
}

void CustomGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(this->viewport());

    painter.setPen(Qt::black);
    painter.drawRect(10, 10, 200, 200);
    painter.drawText(10, 10, "hello");
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    m_videoItem->setSize(event->size());
}
