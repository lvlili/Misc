//除法
int divid(uint32_t a, uint32_t b)
{
    if (a < b || b == 0) return 0;

    //q是商，r是余数
    uint32_t q = 0;
    uint32_t r = 0;
    uint32_t highNum = 0x80000000;
    uint32_t index = 32;

    while (a != 0)
    {
        uint32_t firstData = a & highNum;
        if (firstData != 0)
            break;

        a = a << 1;
        --index;
    }

    while (index != 0)
    {
        r = r << 1;
        q = q << 1;

        //得到a的最高位，并把它放到最低位
        uint32_t lastData = a & highNum;
        lastData = lastData >> 31;
        r += lastData;  

        //如果余数>=b，余数减去b，同时商最低位设为1
        if (r >= b)
        {
            q += 1;
            r -= b;
        }

        a = a << 1;
        --index;
    }

    return q;
}
