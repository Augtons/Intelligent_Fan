# API参考（Timer.h）

>`void Timer[0/1]_init();`

功能
- 按照默认值初始化定时器 0/1
- - 工作方式1(共从0到3,共4种方式)
- - 门控位为0，定时器开关仅由TRx决定
- - 允许定时器0中断，并允许单片机接收中断(`EA = 1`)

<br>

>`void Timer2_init();`【仅`Timer2`】

功能
- 按照默认值初始化定时器 2
- - 工作方式为16位自动重装载定时器，向上计时，不允许外部使能。
- - 允许定时器1中断，并允许单片机接收中断(`EA = 1`)

<br>

>`void Timer2_clearIntrState();`【仅`Timer2`】

功能
- 清楚定时器2中断标志（定时器2比较特殊，需要软件手动清零）

<br>

>`void Timer[0/1/2]_setValue(u8 th, u8 tl);`

功能
- 配置定时器 0、1 或 2 的初始值（THx和TLx寄存器）

参数
 - `u8 th` 初值高八位（THx）
 - `u8 tl` 初值低八位（TLx）

<br>

>`void Timer[0/1/2]_enable(u8 enable);`

功能
- 打开/关闭 定时器（TRx）

参数
 - `u8 enable` 为 0 关闭定时器，为 1 打开定时器

<br>

>`void Timer[0/1/2]_intr_register(void (*intrFunc)());`

功能
- 绑定中断函数

参数
 - `void (*intrFunc)()` 函数指针（其实就是函数名），指向一个返回值为void，无形参的函数，作为定时器 0、1 或 2 发生中断时要执行的函数

<br>

>`u16 getTimer[0/1/2]Count();`

功能
- 暂停定时器 0、1 或 2 ，并返回定时器当前的值
