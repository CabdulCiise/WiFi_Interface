#include "msp.h"
#include "stdint.h"
#include "string.h"

#include "ClockSystem/ClockSystem.h"
#include "hal.h"
#include "ili9341.h"
#include "colors.h"

void write_init_commands (const uint8_t *addr);
void set_addr_location (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void set_color(uint16_t color);

void INIT_LCD (void)
{
    deassert_LCD_CS();
    assert_LCD_RESET();
    SysTick_delay(500);
    deassert_LCD_RESET();
    SysTick_delay(500);
    assert_LCD_RESET();
    SysTick_delay(500);

    UCA3CTLW0 = UCSWRST;
    UCA3CTLW0 = 0xAD83;//UCMSB | UCSPB | UCMODE_2 | UCSYNC | UCSSEL_2 | UCTXBRK | UCSWRST;
    UCA3BRW = 1;
    UCA3MCTLW = 0;
    UCA3CTLW0 &= ~UCSWRST;
    UCA3IE &= ~(UCTXIE | UCRXIE);

    write_init_commands(Bcmd);

    set_addr_location(0,0,0,0);

    ILI_fill_screen(BACKGROUND);
}

uint8_t static write_command (uint8_t cmd)
{
    while((UCA3IFG & UCTXIFG) == 0x00);
    deassert_LCD_DC();
    UCA3TXBUF = cmd;
    while((UCA3IFG & UCRXIFG) == 0x00);
    return UCA3RXBUF;
}

uint8_t static write_data (uint8_t data)
{
    while((UCA3IFG & UCTXIFG) == 0x00);
    assert_LCD_DC();
    UCA3TXBUF = data;
    while((UCA3IFG & UCRXIFG) == 0x00);
    return UCA3RXBUF;
}

void ILI_draw_pixel (int16_t x, int16_t y, uint16_t color)
{
    if((x < 0) || (x > ILI_TFTWIDTH) || (y < 0) || (y > ILI_TFTHEIGHT))
        return;

    set_addr_location(x,y,x,y);
    set_color(color);
}

void ILI_draw_fast_V_line(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    uint8_t colorMSB = color >> 8;
    uint8_t colorLSB = color;
    if((x >= ILI_TFTWIDTH) || (y >= ILI_TFTHEIGHT))
        return;
    set_addr_location(x,y,x,y+h-1);
    while(h--)
    {
        write_data(colorMSB);
        write_data(colorLSB);
    }
}

void ILI_draw_fast_H_line(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    uint8_t colorMSB = color >> 8;
    uint8_t colorLSB = color;
    if((x >= ILI_TFTWIDTH) || (y >= ILI_TFTHEIGHT))
        return;
    set_addr_location(x,y,x+w-1,y);
    while(w--)
    {
        write_data(colorMSB);
        write_data(colorLSB);
    }
}

void ILI_fill_screen(uint16_t color)
{
    ILI_fill_rectangle(0,0,ILI_TFTWIDTH,ILI_TFTHEIGHT,color);
}

void ILI_fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    uint8_t colorMSB = color >> 8;
    uint8_t colorLSB = color;
    if((x >= ILI_TFTWIDTH) || (y >= ILI_TFTHEIGHT))
        return;
    set_addr_location(x, y, x+w-1, y+h-1);
    for(y=h; y>0; y--)
    {
        for(x=w; x>0; x--)
        {
            write_data(colorMSB);
            write_data(colorLSB);
        }
    }
}

uint16_t ILI_color_565 (uint8_t red, uint8_t green, uint8_t blue)
{
    return ((blue & 0xF8) << 8) | ((green & 0xFC) << 3) | (red >> 3);
}

void ILI_DrawBitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h)
{
    int16_t skipC = 0;                      // non-zero if columns need to be skipped due to clipping
    int16_t originalWidth = w;              // save this value; even if not all columns fit on the screen, the image is still this width in ROM
    int i = w*(h - 1);

    if((x >= ILI_TFTWIDTH) || ((y - h + 1) >= ILI_TFTHEIGHT) || ((x + w) <= 0) || (y < 0))
        return;
    if((w > ILI_TFTWIDTH) || (h > ILI_TFTHEIGHT))
        return;

    if((x + w - 1) >= ILI_TFTWIDTH)
    {            // image exceeds right of screen
        skipC = (x + w) - ILI_TFTWIDTH;           // skip cut off columns
        w = ILI_TFTWIDTH - x;
    }

    if((y - h + 1) < 0)
    {                  // image exceeds top of screen
        i = i - (h - y - 1)*originalWidth;  // skip the last cut off rows
        h = y + 1;
    }

    if(x < 0)
    {                            // image exceeds left of screen
        w = w + x;
        skipC = -1*x;                       // skip cut off columns
        i = i - x;                          // skip the first cut off columns
        x = 0;
    }

    if(y >= ILI_TFTHEIGHT)
    {                     // image exceeds bottom of screen
        h = h - (y - ILI_TFTHEIGHT + 1);
        y = ILI_TFTHEIGHT - 1;
    }

    set_addr_location(x, y-h+1, x+w-1, y);

    for(y=0; y<h; y=y+1)
    {
        for(x=0; x<w; x=x+1)
        {
                                        // send the top 8 bits
            write_data((uint8_t)(image[i] >> 8));
                                        // send the bottom 8 bits
            write_data((uint8_t)image[i]);
            i = i + 1;                        // go to the next pixel
        }
        i = i + skipC;
        i = i - 2*originalWidth;
    }
}

void ILI_draw_char_S(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size)
{
    uint8_t line;
    int32_t i, j;
    if((x >= ILI_TFTWIDTH) || (y >= ILI_TFTHEIGHT) || ((x + 5 * size - 1) < 0) || ((y + 8 * size - 1) < 0))
        return;

    for(i=0; i<6; i++)
    {
        if(i == 5)
            line = 0x0;
        else
            line = Font[(c*5)+i];

        for(j=0; j<8; j++)
        {
            if(line & 0x01)
            {
                if(size == 1)
                    ILI_draw_pixel(x+i, y+j, textColor);
                else
                {
                    ILI_fill_rectangle(x+(i*size), y+(j*size), size, size, textColor);
                }
            }
            else if (bgColor != textColor)
            {
                if(size == 1)
                    ILI_draw_pixel(x+i, y+j, bgColor);
                else
                {
                    ILI_fill_rectangle(x+i*size, y+j*size, size, size, bgColor);
                }
            }
            line >>= 1;
        }
    }
}

void ILI_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size)
{
    uint8_t line; // horizontal row of pixels of character
    int32_t col, row, i, j;// loop indices
    if(((x + 5*size - 1) >= ILI_TFTWIDTH)  || ((y + 8*size - 1) >= ILI_TFTHEIGHT) || ((x + 5*size - 1) < 0) || ((y + 8*size - 1) < 0))
        return;
    set_addr_location(x, y, x+6*size-1, y+8*size-1);
    line = 0x01;        // print the top row first
    // print the rows, starting at the top
    for(row=0; row<8; row=row+1)
    {
        for(i=0; i<size; i=i+1)
        {
            // print the columns, starting on the left
            for(col=0; col<5; col=col+1)
            {
                if(Font[(c*5)+col]&line)
                {
                    // bit is set in Font, print pixel(s) in text color
                    for(j=0; j<size; j=j+1)
                    {
                        set_color(textColor);
                    }
                }
                else
                {
                    // bit is cleared in Font, print pixel(s) in background color
                    for(j=0; j<size; j=j+1)
                    {
                        set_color(bgColor);
                    }
                }
            }
            // print blank column(s) to the right of character
            for(j=0; j<size; j=j+1)
            {
                set_color(bgColor);
            }
        }
        line = line<<1;   // move up to the next row
    }
}

uint32_t ILI_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor)
{
    uint32_t count = 0;
    if(y>15)
        return 0;
    while(*pt)
    {
      //ILI_DrawCharS(x*6, y*10, *pt, textColor, ILI_BLACK, 1);
        ILI_draw_char_S(x*6, y*10, *pt, textColor, ILI_BLACK, 2);
        pt++;
        x = x+1;
        if(x>20)
            return count;  // number of characters printed
        count++;
    }
    return count;  // number of characters printed
}

void ILI_InvertDisplay(int i)
{
    if(i)
        write_command(ILI_INVON);
    else
        write_command(ILI_INVOFF);
}

void ILI_Write_String (uint8_t *message,int x, int y, uint16_t txtColor, uint16_t bgColor, uint8_t txtSize)
{
    uint8_t     length;
    uint8_t     i;
    length = strlen(message);
    for (i=0;i<length;i++)
    {
        ILI_draw_char_S(x+i*6*txtSize,y,message[i],txtColor,bgColor,txtSize);
    }
}

// *****        PRIVATE FUNCTIONS       *****
void write_init_commands (const uint8_t *addr)
{
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *(addr++);               // Number of commands to follow
    while(numCommands--)
    {                 // For each command...
        write_command(*(addr++));             //   Read, issue command
        numArgs  = *(addr++);                //   Number of args to follow
        ms       = numArgs & DELAY;          //   If hibit set, delay follows args
        numArgs &= ~DELAY;                   //   Mask out delay bit
        while(numArgs--)
        {                   //   For each argument...
            write_data(*(addr++));              //     Read, issue argument
        }
        if(ms)
        {
            ms = *(addr++);             // Read post-command delay time (ms)
            if(ms == 255) ms = 500;     // If 255, delay for 500 ms
            SysTick_delay(ms);
        }
    }
}

void set_addr_location (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    write_command(ILI_CASET);   // column addr set
    write_data(x0 >> 8);        // X start MSB
    write_data(x0);             // x start LSB
    write_data(x1 >> 8);        // x end MSB
    write_data(x1);             // x end LSB
    write_command(ILI_RASET);   // row addr set
    write_data(y0>>8);          // y start MSB
    write_data(y0);             // y start LSB
    write_data(y1>>8);          // y end MSB
    write_data(y1);             // y end LSB
    write_command(ILI_RAMWR);   // write to RAM
}

void set_color(uint16_t color)
{
    write_data((uint8_t)(color >> 8));
    write_data((uint8_t)color);
}

