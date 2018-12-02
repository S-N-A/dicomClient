#ifndef SCENEZOOM_H
#define SCENEZOOM_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

/*!
 * \brief Класс реализующий логику зумирования изображения в сцене на виджете
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для реализации функции зумирования в сценах на виджете
 */
class SceneZoom: public QGraphicsView
{
    Q_OBJECT
public:
    /*!
     * \brief SceneZoom
     * \param parent Указатель на родительский виджет
     *
     * Конструктор класса сцены с зумированием
     */
    SceneZoom(QWidget * parent=nullptr);
    /*!
     * \brief zoomIn
     *
     * Функция для увеличения масштаба изображения в сцене
     */
    void zoomIn();
    /*!
     * \brief zoomOut
     *
     * Функция для уменьшения масштаба изображения в сцене
     */
    void zoomOut();
    /*!
     * \brief wheelEvent
     * \param event Событие прокрутки колеса мыши
     *
     * Функция отлавливает события прокрутки колеса мыши для осуществления зумирования
     */
    void wheelEvent(QWheelEvent *event);
};

#endif // SCENEZOOM_H
