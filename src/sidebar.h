#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QAction>
#include <QWidget>

#include <logger.h>
/*!
 * \brief Класс формы боковой панели выбора виджета
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Класс формы боковой панели выбора виджета
 */
class SideBar : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief SideBar
     * \param parent Указатель на родительский виджет
     *
     * Конструктор класса боковой панели
     */
    explicit SideBar(QWidget *parent=nullptr);
    /*!
     * \brief addAction
     * \param action Объект действия при нажатии на выбранный виджет
     *
     * Функция добавляет поле в боковую панель
     */
    void addAction(QAction *action);
    /*!
     * \brief addAction
     * \param text Текст в поле боковой панели
     * \param icon Иконка в поле боковой панели
     * \return Объект действия при нажатии на выбранный виджет
     */
    QAction *addAction(const QString &text, const QIcon &icon = QIcon());
    /*!
     * \brief minimumSizeHint
     * \return Размер поля
     *
     * Функция для получения валидного размера поля в боковой панели
     */
    QSize minimumSizeHint() const;


protected:
    /*!
     * \brief paintEvent
     * \param event Событие отрисовки
     *
     * Событие для отрисовки поля в боковой панели при его добавлении
     */
    void paintEvent(QPaintEvent *event);
    /*!
     * \brief mousePressEvent
     * \param event Событие нажатия мыши
     *
     * Событие при нажатии кнопкой мыши на поле, посылает сигнал в главное окно для отображения выбранного виджета
     */
    void mousePressEvent(QMouseEvent *event);
    /*!
     * \brief mouseMoveEvent
     * \param event Событие наведение мыши
     *
     * Событие подсвечивает поле, на котором расположен курсор
     */
    void mouseMoveEvent(QMouseEvent *event);
    /*!
     * \brief leaveEvent
     * \param event Событие увода курсора с поля
     *
     * Событие отменяет подсветку, если курсор больше не находится на выбранном поле
     */
    void leaveEvent(QEvent * event);

    /*!
     * \brief actionAt
     * \param at Координаты расположения курсора
     * \return Объект действия при нажатии на выбранный виджет
     *
     * Функция возвращающая объект поля по заданным координатам
     */
    QAction *actionAt(const QPoint &at);


private:
    /*!
     * \brief mActions
     *
     * Список полей в боковой панели
     */
    QList<QAction *> mActions;

    /*!
     * \brief mCheckedAction
     *
     * Выбранное поле
     */
    QAction *mCheckedAction;
    /*!
     * \brief mOverAction
     *
     * Поле на котором расположен курсор
     */
    QAction *mOverAction;
};

#endif // SIDEBAR_H
