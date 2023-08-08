int my_atoi( char *str)
{
    int result = 0;
    int sign = 1; 

    while (*str == ' ') {
        str++;
    }

    // 处理正负号
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // 将字符串转换为整数
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}