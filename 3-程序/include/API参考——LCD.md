# API参考（LCD.h）

>`void LCD_WriteCom(u8 com);`

功能
- 向LCD发送命令

参数
 - `u8 com` 想要发送的命令

<br>

>`void LCD_WriteDat(u8 dat);`

功能
- 向LCD发送数据

参数
 - `u8 dat` 想要发送的数据

<br>
---

>`void LCD_Init();`

功能
- 初始化LCD为默认。5×8字符，不显示光标，每次输入光标右移，清屏，光标移动到左上角


<br>

>`void LCD_Clear();`

功能
- 清屏


<br>

>`void LCD_Back();`

功能
- 将光标移动到左上角


<br>

>`void LCD_SetInputMode(u8 direction, bit displayMove);`

功能
- 设置LCD输入方式

参数
 - `u8 direction` 输入新字符后光标移动方向。0为左移，1为右移
 - `bit displayMove` 输入新数据后显示显示屏是否移动，为1则向右移动

<br>

>`void LCD_DisplayEnable(u8 displayEn, u8 cursor, u8 cursorMode);`

功能
- 显示开关

参数
 - `u8 displayEn` 为1则打开显示
 - `u8 cursor` 为1则显示光标
 - `u8 cursorMode` 为0光标闪烁，为1光标不闪烁

<br>

>`void LCD_Move(u8 which, u8 direction, u8 step);`

功能
- 移动光标或者屏幕显示内容

参数
 - `u8 which` 为0移动光标，为1移动屏幕文字
 - `u8 direction` 0 左，1 右
 - `u8 step` 移动几个位置

<br>

>`void LCD_SetNextDataAddr(u8 addr);`

功能
- 设置下一次输入的地址（光标位置）

参数
 - `u8 addr` 地址

<br>

>`void LCD_AddCGRAM(u8 addr, unsigned char *val);`

功能
- 添加自定义字符到CGRAM

参数
 - `u8 addr` 自定义字符位置（0-7）
 - `char *val` 每一行的内容，传递一个2维 8*8的数组（8行，每一行有8个位）

<br>

>`void LCD_ShowString(u8 addr, unsigned char *str);`

功能
- 在某地址及其之后显示一个字符串（不支持跨行）

参数
 - `u8 addr` 首地址
 - `char *str` 字符串数组名

<br>

>`void LCD_ShowStringAtNext(unsigned char *str);`

功能
- 下一个光标处显示一个字符串（不支持跨行）

参数
 - `char *str` 字符串数组名

<br>

>`void LCD_ShowCharAtNext(u8 valAddr);`

功能
- 在光标位置输出一个字符

参数
 - `u8 valAddr` 字符地址

<br>

>`void LCD_ShowChar(u8 addr, u8 val);`

功能
- 在x行第y个位置上显示一个字符

参数
 - `u8 addr` 地址
 - `u8 val` 字符地址

<br>

>`u8 LCD_GetAddrByPosition(u8 x, u8 y);`

功能
- 取得x行第y个位置对应的地址

参数
 - `u8 x` 第x行（1-2）
 - `u8 y` 第y个（0-15）

返回值
 - 类型：`u8` 取得的地址 

<br>

>`void LCD_ShowDouble(u8 addr, double db);`

功能
- 在地址addr上显示一个double，保留两位小数

参数
 - `u8 addr` 地址
 - `double` 要显示的double

<br>

>`void LCD_ShowDoubleAtNext(double db);`

功能
- 在光标位置上显示一个double，保留两位小数

参数
 - `double` 要显示的double

<br>