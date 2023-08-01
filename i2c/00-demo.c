#define RASP_ADDR 0x00
#define RASP_WRITE 0x00
#define RASP_READ 0x01

// 初始化 i2c 模拟时序涉及到的两个GPIO口
void demo_i2c_gpio_init(void)
{
    clk_out();
    data_out();
}

// 起始信号
void demo_i2c_start(void)
{
    data_out();
    // 将数据置1
    data_set();
    // 将时钟置1
    clk_set();
    demo_i2c_dalay();
    data_clear();
    demo_i2c_dalay();
    // 空闲时钟为低电平
    clk_clear();
}

// 终止信号
void demo_i2c_stop(void)
{
    data_out();
    // 将数据置0
    data_clear();
    // 将时钟置1
    clk_set();
    demo_i2c_dalay();
    data_set();
    demo_i2c_dalay();
    // 空闲时钟为高电平
    clk_clear();
}

void demo_i2c_send_byte(unsigned char data)
{
    data_out();
    int i;
    clk_clear(); // 时钟为低电平开始准备
    for (i = 0; i < 8; i++)
    {
        if (data & (1 << (7 - i)))
            data_set();
        else
            data_clear();

        // 等待准备的数据稳定
        demo_i2c_dalay();
        // 数据已稳定对方可以读取
        clk_set();
        // 等待对方读取数据
        demo_i2c_dalay();
        clk_clear();
    }
}

unsigned char demo_i2c_recv_byte(viod)
{
    unsigned char data = 0;
    int i;
    data_in();
    clk_clear(); // 时钟为低电平对方开始准备
    for (i = 0; i < 8; i++)
    {
        // 等待对方准备好数据
        demo_i2c_dalay();
        // 数据已稳定可以读取
        clk_set();
        // 先延时再读，避免发送临界
        demo_i2c_dalay();
        data |= data_get_in() << (7 - i);
        clk_clear();
    }
    return data;
}

void demo_i2c_send_ack(unsigned char ack)
{
    data_out();
    int i;
    clk_clear(); // 时钟为低电平开始准备
    if (ack)
        data_set();
    else
        data_clear();

    // 等待准备的数据稳定
    demo_i2c_dalay();
    // 数据已稳定对方可以读取
    clk_set();
    // 等待对方读取数据
    demo_i2c_dalay();
    clk_clear();
}

unsigned char demo_i2c_recv_ack(viod)
{
    unsigned char ack = 0;
    data_in();
    // 时钟为低电平对方开始准备
    clk_clear();

    // 等待对方准备好数据
    demo_i2c_dalay();
    // 数据已稳定可以读取
    clk_set();
    // 先延时再读，避免发送临界
    demo_i2c_dalay();
    ack = data_get_in();
    clk_clear();
    return ack;
}

// 将 buf 中的长度为 lem 的数据写到 reg 的寄存器里面
void demo_i2c_send(unsigned char *buf, unsigned char reg, int len)
{
    demo_i2c_start();
    // 发送芯片地址，因为包的最后一位有读写标志位所以把数据左移一位
    demo_i2c_send_byte((RASP_ADDR << 1) | RASP_WRITE);
    demo_i2c_recv_ack();
    // 发送数据存放的寄存器地址
    demo_i2c_send_byte(reg);
    demo_i2c_recv_ack();
    int i = len;
    for (; i >= 0; i--)
    {
        demo_i2c_send_byte(*buf);
        demo_i2c_recv_ack();
        buf++;
    }
    demo_i2c_stop();
}

// 将 reg寄存器的数据读取len长度存储到 buf 里面
void demo_i2c_recv(unsigned char *buf, unsigned char reg, int len)
{
    demo_i2c_start();
    // 发送芯片地址，因为包的最后一位有读写标志位所以把数据左移一位
    demo_i2c_send_byte((RASP_ADDR << 1) | RASP_READ);
    demo_i2c_recv_ack();
    // 发送数据存放的寄存器地址
    demo_i2c_re_byte(reg);
    demo_i2c_recv_ack();
    int i = len;
    while (len--)
    {
        buf[i++] = demo_i2c_recv_byte();
        demo_i2c_send_ack(0);
        buf++;
    }
    demo_i2c_stop();
}

int main(int argc, char const *argv[])
{

    return 0;
}