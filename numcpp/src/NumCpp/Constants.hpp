#pragma once

#include"NumCpp/Types.hpp"

#include<cmath>
#include<limits>
#include<string>

namespace nc
{
    namespace constants
    {
        constexpr double        c = 3.0e8; // 光速
        constexpr double        e = 2.718281828459045;  // 自然对数
        constexpr double        inf = std::numeric_limits<double>::infinity(); // 系统支持最大数
        constexpr double        pi = 3.14159265358979323846; // 圆周率
        const double            nan = std::nan("1"); // 非法数值

        constexpr double        DAYS_PER_WEEK = 7; // 一周天数
        constexpr double        MINUTES_PER_HOUR = 60; // 每小时分钟数
        constexpr double        SECONDS_PER_MINUTE = 60; // 每分钟秒数
        constexpr double        MILLISECONDS_PER_SECOND = 1000; //  一秒钟的毫秒数
        constexpr double        SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE; // 一小时大的秒数
        constexpr double        HOURS_PER_DAY = 24; // 一天的小时数
        constexpr double        MINUTES_PER_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR; // 一天的分钟数
        constexpr double        SECONDS_PER_DAY = MINUTES_PER_DAY * SECONDS_PER_MINUTE; // 一天的秒数
        constexpr double        MILLISECONDS_PER_DAY = SECONDS_PER_DAY * MILLISECONDS_PER_SECOND; // 一天的毫秒数
        constexpr double        SECONDS_PER_WEEK = SECONDS_PER_DAY * DAYS_PER_WEEK; // 一周的秒数

        const std::string       VERSION = "1.0"; // 当前numpy的版本号
    }
}
