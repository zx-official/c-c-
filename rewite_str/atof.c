double my_atof( char *str) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1; 
    double decimal_place = 0.1; 

    while (*str == ' ') 
    {
        str++;
    }
    if (*str == '-') 
    {
        sign = -1;
        str++;
    } else if (*str == '+') 
    {
        str++;
    }

    // 将整数部分转换为浮点数
    while (*str >= '0' && *str <= '9') 
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    // 处理小数部分
    if (*str == '.') {
        str++;

        while (*str >= '0' && *str <= '9') {
            fraction += (*str - '0') * decimal_place;
            decimal_place *= 0.1;
            str++;
        }
    }

    return (result + fraction) * sign;
}