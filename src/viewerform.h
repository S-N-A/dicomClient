#ifndef VIEWERFORM_H
#define VIEWERFORM_H

#include <QWidget>
#include <QString>
#include <QCheckBox>
#include <QShowEvent>
#include <QMap>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <converters.h>
#include <tagshelpers.h>
#include <QDebug>
#include <logger.h>
#include "telemedobject.h"

namespace Ui {
class ViewerForm;
}

using addInfoMap = QMap<QString,QString>;

/*!
 * \brief Класс формы для отображения файлов dcm
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 *
 */
class ViewerForm : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief fileName
     *
     * Имя файла на файловой системе
     */
    QString fileName;
    /*!
     * \brief scene
     *
     * Сцена для показа изображения
     */
    QGraphicsScene *scene;
    /*!
     * \brief showEvent
     *
     * Событие отображения изображения в сцене, масштабирующее изображение по рамке сцены
     */
    void showEvent(QShowEvent*);
    /*!
     * \brief ViewerForm
     * \param parent Указатель на родительский виджет
     *
     * Конструктор класса формы
     */
    explicit ViewerForm(QWidget *parent = nullptr);
    ~ViewerForm();

private slots:
    /*!
     * \brief on_loadImageButton_clicked
     *
     * Слот для показа диалогового окна выбора файла
     */
    void on_loadImageButton_clicked();

    /*!
     * \brief on_dicomAttributeTableWidget_cellChanged
     * \param row Строка
     * \param column Столбец
     *
     * Слот для предложения пользователю изменить значение тега в файле
     * Действует при изменении пользователем тега в таблице
     */
    void on_dicomAttributeTableWidget_cellChanged(int row, int column);

signals:
    /*!
     * \brief sendInsertSignal
     * \param name Имя пациента
     * \param image Изображение
     * \param dict Словарь с данными об исследовании
     * \param infoMap Словарь с данными о запросе\ответе
     */
    void sendInsertSignal(QString& name, QImage& image, dicomDict& dict, addInfoMap& infoMap);

private:
    /*!
     * \brief showMessageBoxAskingForChange
     * \return true - если ползователь нажал OK
     *
     * Функция для отображения диалога о необходимости сохранения информации из dcm фaйла в базу
     */
    bool showMessageBoxAskingForChange();
    /*!
     * \brief m_changeAllowed
     *
     * Флажок отображающий возможность изменения тега в файле
     */
    bool m_changeAllowed;
    /*!
     * \brief The m_columns enum
     *
     * Отображение колонок таблицы на колонки в базе данных
     */
    enum m_columns{Tag, Description, Value};
    /*!
     * \brief m_table_columns_count
     *
     * Количество столбцов в таблице виджета
     */
    const int m_table_columns_count = 3;
    /*!
     * \brief initTable
     * \param dict Словарь с данными об исследовании
     *
     * Функция для инициализации таблицы данными из dcm файла
     */
    void initTable(const dicomDict& dict); // Should be refactored with dbform;
    /*!
     * \brief ui Указатель на объект интерфейса для данного класса
     */
    Ui::ViewerForm *ui;
};

#endif // VIEWERFORM_H
