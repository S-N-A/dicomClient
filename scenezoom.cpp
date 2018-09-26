#include "scenezoom.h"

SceneZoom::SceneZoom(QWidget * parent):QGraphicsView(parent)
{

}

void SceneZoom::zoomIn()
{
    scale(1.5,1.5);
}

void SceneZoom::zoomOut()
{
    scale(0.75,0.75);
}

void SceneZoom::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
}
