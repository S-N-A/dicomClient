#ifndef TABLEFIELDS_H
#define TABLEFIELDS_H

/*!
 * Структура для отображения числовых значений колонок в таблице базы данных на смысловое значение информации в этих колонках
 */
namespace tableFields{
enum tableFields {
    table_id = 0,
    table_name = 1,
    table_image = 2,
    table_data = 3,
    table_request = 4,
    table_response = 5,
    table_request_date = 6,
    table_response_date = 7,
    table_requester = 8,
    table_responser = 9
};
}

#endif // TABLEFIELDS_H
