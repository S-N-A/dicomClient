#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTableWidgetItem>
#include <QBuffer>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <logger.h>
#include <tagshelpers.h>
#include <serializehelper.h>
#include "senddialog.h"


namespace Ui {
class DbForm;
}

using addInfoMap = QMap<QString,QString>;

/*!
 * \brief Класс формы для отображения содержимого базы данных
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для отбражения информации, хранящейся в локальной базе о изученных объектах
 */
class DbForm : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief DbForm
     * \param parent Указатель на родительский класс - виджет
     *
     * Конструктор виджета
     */
    explicit DbForm(QWidget *parent = nullptr);
    /*!
     * Объявления класса SendDialog дружественным классом для предоставления форме SendDialog доступа
     * к БД средствами данного класса
     */
    friend class SendDialog;
    /*!
     * \brief initFooterTable
     * \param widget Ссылка на виджет типа таблицы
     * \param dict Словарь содержащий информацию о dicom объекте
     */
    static void initFooterTable(QTableWidget* widget, const dicomDict& dict);
    ~DbForm();

public slots:
    /*!
     * \brief acceptInsertSignal
     * \param name Имя пациента
     * \param image Медицинское изображение
     * \param dict Словарь содержащий информацию о dicom объекте
     * \param map Словарь содержащий дополнительную информацию о запросе\ответе
     *
     * Слот для приема сигнала о необходимости записи объекта в базу данных
     */
    void acceptInsertSignal(QString& name, QImage& image, dicomDict& dict, addInfoMap& map);


private slots:
    /*!
     * \brief on_dbTableWidget_cellClicked
     * \param row Номер строки таблицы
     * \param column Номер столбца таблицы
     *
     * Слот для отображения информации в виджете при клике на соответсвующий объект из таблицы
     */
    void on_dbTableWidget_cellClicked(int row, int column);

    /*!
     * \brief on_updateButton_clicked
     *
     * Слот для синхронизации таблицы в виджете и информации в базе данных
     */
    void on_updateButton_clicked();

private:
    /*!
     * \brief ui
     *
     * Ссылка на объект интерфейса для данной формы
     */
    Ui::DbForm *ui;
    /*!
     * \brief The columns enum
     *
     * Перечисление столбцов таблицы для отображения числовых значений на смысловое содержание информации, хранящейся в таблице
     */
    enum class columns {id = 0, name = 1, image = 2, data = 3};
    /*!
     * \brief The columns enum
     *
     * Перечисление столбцов таблицы для отображения числовых значений на смысловое содержание информации, хранящейся в таблице
     */
    enum dicomColumns{tag, description, value};
    /*!
     * \brief askForSave
     * \return Возвращает значение типа boolean, указывающее на необходимость сохранения в базу данных
     *
     * Если функция вернула true - посылаем сигнал сохранения в базу данных
     */
    bool askForSave();
    /*!
     * \brief previewImage
     * \param id Номер объекта в базе данных
     *
     * Функция для отображения изображения в виджете, по выбранному номеру объекта
     */
    void previewImage(const int& id);
    /*!
     * \brief m_dbPath
     *
     * Константа, хранящая путь до базы данных
     */
    const QString m_dbPath;
    /*!
     * \brief m_dbTable
     *
     * Константа, хранящая название таблицы
     */
    const QString m_dbTable;
    /*!
     * \brief m_okIcon
     *
     * Константа, хранящая иконку, отображающую наличие информации в базе данных
     */
    const QIcon m_okIcon;
    /*!
     * \brief m_unavailableIcon
     *
     * Константа, хранящая иконку, отображающую отсутствие информации в базе данных
     */
    const QIcon m_unavailableIcon;
    /*!
     * \brief m_updateIcon
     *
     * Константа, хранящая иконку для обновления данных в виджете. Используется на кнопке обновления данных
     */
    const QIcon m_updateIcon;
    /*!
     * \brief m_db
     *
     * Объект открытой программой базы данных
     */
    QSqlDatabase m_db;
    /*!
     * \brief m_previewScene
     *
     * Сцена для демонстрации изображения в виджете из базы данных
     */
    QGraphicsScene m_previewScene;
    /*!
     * \brief initTableWidget
     * \return true, если таблица информации в базе данных успешно инициализировалась из базы данных
     *
     * Функция для инициализации таблицы информацией из базы данных
     */
    bool initTableWidget();
    /*!
     * \brief dumpToDb
     * \param name Имя пациента
     * \param image Медицинское изображение
     * \param dict Словарь для хранения информации dicom
     * \param map Словарь с дополнительными данных о запросе\ответе
     * \return true - если запись в базу прошла успешно
     *
     * Функция для записи в базу информации о запросе\ответе
     */
    bool dumpToDb(QString& name, QImage& image, dicomDict& dict, addInfoMap& map);
    /*!
     * \brief insertAdditionalInfo
     * \param query Объект запроса в базу данных
     * \param map Словарь с дополнительными данных о запросе\ответе
     *
     * Функция записывает информацию о запросе\ответе в базу данных
     */
    void insertAdditionalInfo(QSqlQuery& query, const addInfoMap& map);
};

#endif // DBFORM_H
