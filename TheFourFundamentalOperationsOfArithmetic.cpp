//加法：
int add(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    int result = 0;
    int carry = 0;
    while (b != 0)
    {
        result = a ^ b;
        carry = a & b;
        carry = carry << 1;

        a = result;
        b = carry;
    }

    return result;
}

//减法： a - b  <==> a + (-b)
int sub(int x, int y)
{
    return add(x, ~y+1); // 一个数字和它的补码的和为0
}

//除法
/*思路：
可以同时得到商和余数的方法,只是在最后没有返回余数，可以根据需要，将余数返回：
1001001/101 (73/5)
A=1001001，B=101
设被除数为A、除数为B、商为Q（初值为0）、余数为R（初值为0）。
设置一个Q单元和R单元，A由高位至低位依次左移进入R单元。每次移位进入后比较R单元和B的值，
如果R≥B，则将这一位的商单元的值置1，然后从R中减去B（做补码加法运算），否则不做操作。商单元与移位同步进行。
直到A全部进入R单元为止。此时Q中存放商、R中存放余数。
R值：0000 0000
Q值：0000 0000

1）R，Q左移一位；A=100 1001，左移入R：
R值：0000 0001
Q值：0000 0000
R<B,不对R和Q做任何处理

2)R，Q左移一位； A=001 0010,左移入R：
R值：0000 0010
Q值：0000 0000
R<B,不对R和Q做任何处理

3）R，Q左移一位； A=010 0100,左移入R：
R值：0000 0100
Q值：0000 0000
R<B,不对R和Q做任何处理

4）R，Q左移一位； A=100 1000,左移入R：
R值：0000 1001
Q值：0000 0000
R>B, R-=B, Q最后一位置为1
R值：0000 0011
Q值：0000 0001

5）R，Q左移一位； A=001 0000,左移入R：
R值：0000 1000
Q值：0000 0010
R>B, R-=B, Q最后一位置为1
R值：0000 0011
Q值：0000 0011

6）R，Q左移一位； A=010 0000,左移入R：
R值：0000 0110
Q值：0000 0110
R>B, R-=B, Q最后一位置为1
R值：0000 0001
Q值：0000 0111

7）R，Q左移一位； A=100 0000,左移入R：
R值：0000 0011
Q值：0000 1110
R<B,不对R和Q做任何处理

8) A== 0,结束
*/
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
