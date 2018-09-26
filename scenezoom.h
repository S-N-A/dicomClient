#ifndef SCENEZOOM_H
#define SCENEZOOM_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class SceneZoom: public QGraphicsView
{
    Q_OBJECT
public:
    SceneZoom(QWidget * parent=nullptr);
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent *event);
};

#endif // SCENEZOOM_H
