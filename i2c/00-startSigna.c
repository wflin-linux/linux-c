
// 初始化 i2c 模拟时序涉及到的两个GPIO口
void demo_i2c_gpio_init(void)
{
}

// 起始信号
void demo_i2c_start(void)
{
    // 将数据置1
    data_set();
    // 将时钟置1
    clk_set();
    demo_i2c_dalay();
    data_clear();
    demo_i2c_dalay();
    // 空闲时钟为低电平
    data_clear();
}

// 终止信号
void demo_i2c_stop(void)
{
    // 将数据置0
    data_clear();
    // 将时钟置1
    clk_set();
    demo_i2c_dalay();
    data_set();
    demo_i2c_dalay();
    // 空闲时钟为高电平
    data_clear();
}

int main(int argc, char const *argv[])
{

    return 0;
}
