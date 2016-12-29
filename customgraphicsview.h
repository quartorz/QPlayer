#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class QGraphicsVideoItem;

class CustomGraphicsView : public QGraphicsView
{
public:
    CustomGraphicsView(QWidget *parent = nullptr);

    QGraphicsVideoItem *getVideoItem() const;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QGraphicsScene *m_scene;
    QGraphicsVideoItem *m_videoItem;
};

#endif // CUSTOMGRAPHICSVIEW_H
