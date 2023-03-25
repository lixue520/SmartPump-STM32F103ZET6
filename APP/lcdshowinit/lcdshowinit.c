#include "lcdshowinit.h"
#include "tftlcd.h"
#include "DavidNan.h"
u8 my_str[10]; // 注意要保证字符数组足够存储转换后的字符串
u16 my_num = 0; //用来保存数字

void New_Lcd_Show_Init()
{
    FRONT_COLOR = BLACK;

    u16_to_string(my_num, my_str);

    /**
     * 静态显示区：
     */
    LCD_ShowString(80, 10, tftlcd_data.width, tftlcd_data.height, 24, "Real-time display");
    LCD_ShowString(10, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, "Height:");
    LCD_ShowString(60 + 60, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
   
    LCD_ShowString(10, 40 + 30, tftlcd_data.width, tftlcd_data.height, 24, "OutPut:");
    LCD_ShowString(60 + 60, 40 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);

    LCD_ShowString(10, 70 + 30, tftlcd_data.width, tftlcd_data.height, 24, "Surplus:"); // 只能显示英文，需要录入字库
    LCD_ShowString(60 + 60, 70 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);

    // LCD_ShowFontHZ(10, 80, "覃志炜");//这里需要人为录入字库否则显示不出来。
    LCD_ShowString(10, 100 + 30, tftlcd_data.width, tftlcd_data.height, 24, "Camera:");
    LCD_ShowString(60 + 60, 100 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
    /**
     * 接受静态数据并显示:
     */

    // 接入按键显示动态数据，计数器

    LCD_ShowPicture(10, 150 + 20, 100, 100, (u8 *)gImage_DavidNan);
}

/**
 * 记录按键个数，当按下个数为100时清零返回，
 * 否则将buttoN值返回
 */
u8 button_count(u8 button)
{
    u8 count = 0;
    if (button == 100)
    {
        button = 0;
        return count;
    }
    count = button;
    return count;
}



void u16_to_string(u16 num, u8 *str)
{
    sprintf(str, "%u", num);
}
