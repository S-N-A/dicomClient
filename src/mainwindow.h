#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QMessageBox>


#include <viewerform.h>
#include <converters.h>

namespace Ui {
class MainWindow;
}

using addInfoMap = QMap<QString, QString>;

/*!
 * \brief Класс главного окна программы.
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для управления функциями главного окна приложения
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief fileName
     *
     * Глобальное имя файла загружаемого объекта - dicom
     */
    QString fileName;
    /*!
     * \brief initSidebar
     *
     * Функция для инициализации боковой панели выбора виджетов
     */
    void initSidebar();
    /*!
     * \brief MainWindow
     * \param parent Указатель на родительский класс виджет
     *
     * Конструктор класса главного окна приложения
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief displayViewerLayout
     *
     * Слот для отображения виджета просмотра файла полученного с файловой системы
     */
    void displayViewerLayout();
    /*!
     * \brief displayDbLayout
     *
     * Слот для отображения виджета просмотра содержимго базы данных
     */
    void displayDbLayout();
    /*!
     * \brief displayAccessibilityLayout
     *
     * Слот для отображения виджета сетевого взаимодействия
     */
    void displayAccessibilityLayout();
    /*!
     * \brief getData
     * \param block Набор байт
     *
     * Функция используется исключительно в целях тестирования. Записывает полученный набор байт в лог программы
     */
    void getData(QByteArray block);

private:
    /*!
     * \brief m_standartXGeom
     *
     * Отступ по горизонтали отображаемых виджетов в главном окне
     */
    const int m_standartXGeom = 300;
    /*!
     * \brief m_standartYGeom
     *
     * Отступ по вертикали отображаемых виджетов в главном окне
     */
    const int m_standartYGeom = 24;
    /*!
     * \brief m_standartWidth
     *
     * Фиксированная ширина отображаемого виджета
     */
    const int m_standartWidth = 1051;
    /*!
     * \brief m_standartHeight
     *
     * Фиксированная высота отображаемого виджета
     */
    const int m_standartHeight = 975;
    /*!
     * \brief ui
     *
     * Указатель на объект интерфейса для главного окна
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
