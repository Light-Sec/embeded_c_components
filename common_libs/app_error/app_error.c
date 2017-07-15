#include "app_error.h"

#include "port.h"

#include "log.h"

/**@brief Function for error handling, which is called when an error has occurred.
 */
void app_error_handler(void)
{
    //�쳣������������ѭ�����ȴ�Ӳ����λϵͳ
    APP_ERROR_HANDLER();
}

/**@brief Function for error handling, which is called when an error has occurred.
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name.
 */
void app_error_handler_log(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    //��ӡ�쳣����Ϣ
    LOG(LEVEL_DEBUG, "[app_error]error_code = %d, line_num = %d, file = %s", error_code, line_num, p_file_name);

    //�����쳣
    app_error_handler();
}

