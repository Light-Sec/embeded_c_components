#include "calendar.h"

#include "datetime.h"

/******************************************************************************
 * @brief mktime
 *****************************************************************************/
uint32_t linux_mktime(uint16_t year0, uint16_t mon0,
                           uint16_t day, uint16_t hour,
                           uint16_t min, uint16_t sec,
                           int time_zone)
{
    unsigned int mon = mon0, year = year0;

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12;    /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((uint32_t)
          (year/4 - year/100 + year/400 + 367*mon/12 + day) +
          year*365 - 719499
        )*24 + hour /* now have hours */
      )*60 + min /* now have minutes */
    )*60 + sec - /* finally seconds */
    time_zone * 3600; // add by tanghao
}

/******************************************************************************
 * @brief get_curr_timestamp_int
 * ���أ���ǰϵͳunixʱ���
 *****************************************************************************/
uint32_t get_curr_timestamp_int(bool extern_src)
{
    UTCTimeStruct utc_time;
    uint32_t curr_timestamp_int;

    get_wall_clock_time(&utc_time, extern_src);

    curr_timestamp_int = linux_mktime(  utc_time.year,
                                        utc_time.month,
                                        utc_time.day,
                                        utc_time.hour,
                                        utc_time.minute,
                                        utc_time.second,
                                        BEIJING_TIME_ZONE);
    return curr_timestamp_int;
}

/******************************************************************************
 * @brief ��ȡ����ʱ�����ֵ
 *****************************************************************************/
uint32_t get_timestamp_diff(uint32_t timestamp1, uint32_t timestamp2)
{
    uint32_t diff = 0;

    if(timestamp1 >= timestamp2)
    {
        diff = timestamp1 - timestamp2;
    }
    else
    {
        diff = timestamp2 - timestamp1;
    }
    return diff;
}

/******************************************************************************
 * @brief �������ʱ�����Ч��
 *****************************************************************************/
check_date_valid_t check_time_valid(const uint8_t start_time[6], const uint8_t stop_time[6], bool extern_src)
{
    uint32_t time_now;
    uint32_t time_start, time_stop;
    UTCTimeStruct utc_time;

    //��鵱ǰϵͳʱ��
    if (!is_systme_clock_valid())
    {
        return DATE_CHECK_ERROR;
    }

    //��ȡ��ǰϵͳʱ��
    get_wall_clock_time(&utc_time, extern_src);

    time_now = linux_mktime(utc_time.year,
                            utc_time.month,
                            utc_time.day,
                            utc_time.hour,
                            utc_time.minute,
                            utc_time.second,
                            BEIJING_TIME_ZONE);

    time_start = linux_mktime(  start_time[0]+BEGYEAR,
                                start_time[1],
                                start_time[2],
                                start_time[3],
                                start_time[4],
                                start_time[5],
                                BEIJING_TIME_ZONE);

    time_stop = linux_mktime(   stop_time[0]+BEGYEAR,
                                stop_time[1],
                                stop_time[2],
                                stop_time[3],
                                stop_time[4],
                                stop_time[5],
                                BEIJING_TIME_ZONE);

    //LOG(LEVEL_DEBUG, "curr = %d, check = [%d %d]", time_now, time_start, time_stop);
    if (time_now >= time_start && time_now <= time_stop)
    {
        return DATE_EFFECT;
    }
    else if (time_now < time_start)
    {
        return DATE_INEFFECT;
    }
    else if (time_now > time_stop)
    {
        return DATE_OVERDUE;
    }

    return DATE_CHECK_ERROR;
}

/******************************************************************************
 * @brief check_time_format
 * �������Ĳ���start_time��stop_timeʱ���ʽ
 *****************************************************************************/
bool check_time_format(const uint8_t start_time[6], const uint8_t stop_time[6])
{
    if (start_time == NULL || stop_time == NULL)
    {
        return false;
    }

    const uint8_t *ptr = NULL;

    for(uint8_t i = 0; i < 2; i++)
    {
        if(0 == i)
        {
            ptr = start_time;
        }
        else if(1 == i)
        {
            ptr = stop_time;
        }

        //���ʱ���ʽ:�����գ�ʱ����
        if ( *ptr <= 14 )//��
        {
            return false;
        }
        if ( *(ptr+1) == 0 || *(ptr+1) > 12 )//��
        {
            return false;
        }
        if ( *(ptr+2) == 0 || *(ptr+2) > 31 )//��
        {
            return false;
        }

        if ( *(ptr+3) > 24 )//ʱ
        {
            return false;
        }
        if ( *(ptr+4) > 61 )//��
        {
            return false;
        }
        if ( *(ptr+5) > 61 )//��
        {
            return false;
        }
    }

    return true;
}

