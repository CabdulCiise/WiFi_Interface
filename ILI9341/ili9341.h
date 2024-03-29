#ifndef ILI9341_ILI9341_H_
#define ILI9341_ILI9341_H_

#include <stdint.h>

void INIT_LCD (void);
uint8_t static write_command (uint8_t cmd);
uint8_t static write_data (uint8_t data);
void ILI_draw_pixel (int16_t x, int16_t y, uint16_t color);
void ILI_draw_fast_V_line(int16_t x, int16_t y, int16_t h, uint16_t color);
void ILI_draw_fast_H_line(int16_t x, int16_t y, int16_t w, uint16_t color);
void ILI_fill_screen(uint16_t color);
void ILI_fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
uint16_t ILI_color_565 (uint8_t red, uint8_t green, uint8_t blue);
void ILI_DrawBitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h);
void ILI_draw_char_S(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);
void ILI_draw_char_scroll(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size, int scrollLine);
void ILI_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);
uint32_t ILI_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor);
void ILI_InvertDisplay(int i);
void ILI_Write_String (uint8_t *message, int x, int y, uint16_t txtColor, uint16_t bgColor, uint8_t txtSize);
void ILI_Write_Scroll_String (uint8_t *message, int x, int y, uint16_t txtColor, uint16_t bgColor, uint8_t txtSize, int scrollLine);


// *****    MACROS                  *****
#define ILI_NOP     0x00    // no operation
#define ILI_SWRESET 0x01    // software reset
#define ILI_RDDID   0x04    // read display identification information
#define ILI_RDDST   0x09    // read dsplay status
#define ILI_RDPWR   0x0A    // read display power mode
#define ILI_RDMAD   0x0B    // read display MADCTL
#define ILI_RDPF    0x0C    // read display pixel format
#define ILI_RDIF    0x0D    // read display image format
#define ILI_RDSM    0x0E    // read display signal mode
#define ILI_RDSDR   0x0F    // read display self diagnostic result
#define ILI_SLPIN   0x10    // enter sleep mode
#define ILI_SLPOUT  0x11    // exit sleep mode
#define ILI_PTLON   0x12    // partial mode on
#define ILI_NORON   0x13    // normal display mode on
#define ILI_INVOFF  0x20    // display inversion off
#define ILI_INVON   0x21    // display inversion on
#define ILI_GAMMA   0x26    // gamma set
#define ILI_DISPOFF 0x28    // display off
#define ILI_DISPON  0x29    // display on
#define ILI_CASET   0x2A    // column address set
#define ILI_RASET   0x2B    // page address set
#define ILI_RAMWR   0x2C    // memory write
#define ILI_COLOR   0x2D    // color set
#define ILI_RAMRD   0x2E    // memory read
#define ILI_PTLAR   0x30    // partial area
#define ILI_VSD     0x33    // verticle scrolling definition
#define ILI_TELOFF  0x34    // tearing effect line off
#define ILI_TELON   0x35    // tearing effect line on
#define ILI_MADCTL  0x36    // memory access control
#define ILI_VSSA    0x37    // verticle scrolling start address
#define ILI_IDLMOFF 0x38    // idle mode off
#define ILI_IDLMON  0x39    // idle mode on
#define ILI_COLMOD  0x3A    //
#define ILI_WRMEMC  0x3C    // write memory continue
#define ILI_RDMEMC  0x3E    // read memory continue
#define ILI_SETTSL  0x44    // set tear scanline
#define ILI_GETTSL  0x45    // get tear scanline
#define ILI_WDB     0x51    // write display brightness
#define ILI_RDB     0x52    // read display brightness
#define ILI_WCTRLD  0x53    // write CTRL display
#define ILI_RCTRLD  0x54    // read CTRL display
#define ILI_WCABC   0x55    // write content adaptive brightness control
#define ILI_RCABC   0x56    // read content adaptive brightness control
#define ILI_WCABCMB 0x5E    // write CABC minimum brightness control
#define ILI_RCABCMB 0x5F    // read CABC minimum brightness control
#define ILI_RGBISC  0xB0    // RGB interface signal control
#define ILI_FRMCTR1 0xB1    // frame control (normal mode)
#define ILI_FRMCTR2 0xB2    // frame control (idle mode)
#define ILI_FRMCTR3 0xB3    // frame control (partial mode)
#define ILI_INVCTR  0xB4    // display inversion control
#define ILI_BLPC    0xB5    // blanking porch control
#define ILI_DISSET5 0xB6    // display function control
#define ILI_ENTMS   0xB7    // entry mode set
#define ILI_BACKLC1 0xB8    // backlight control 1
#define ILI_BACKLC2 0xB9    // backlight control 2
#define ILI_BACKLC3 0xBA    // backlight control 3
#define ILI_BACKLC4 0xBB    // backlight control 4
#define ILI_BACKLC5 0xBC    // backlight control 5
#define ILI_BACKLC7 0xBE    // backlight control 7
#define ILI_BACKLC8 0xBF    // backlight control 8
#define ILI_PWCTR1  0xC0    // power control 1
#define ILI_PWCTR2  0xC1    // power control 2
#define ILI_PWCTR3  0xC2
#define ILI_VMCTR1  0xC5    // VCOM control 1
#define ILI_VMCTR2  0xC7    // VCOM control 2
#define ILI_NVMW    0xD0    // NV memory write
#define ILI_NVMPK   0xD1    // NV memory protection key
#define ILI_NVMSR   0xD2    // NV memory status read
#define ILI_RDID4   0xD3    // read ID4
#define ILI_PWCTR6  0xFC
#define ILI_GMCTRP1 0xE0    // positive gamma correction
#define ILI_GMCTRN1 0xE1    // negative gamma correction
#define TFT_CS                  (*((volatile uint8_t *)0x40004C82))  /* Port 9 Output, bit 4 is TFT CS */
#define TFT_CS_BIT              0x10        // CS normally controlled by hardware
#define DC                      (*((volatile uint8_t *)0x40004C82))  /* Port 9 Output, bit 2 is DC */
#define DC_BIT                  0x04
#define RESET                   (*((volatile uint8_t *)0x40004C82))  /* Port 9 Output, bit 3 is RESET*/
#define RESET_BIT               0x08
#define ILI_TFTWIDTH  240
#define ILI_TFTHEIGHT 320

#define ILI_BLACK   0x0000
#define ILI_BLUE    0xF800
#define ILI_RED     0x001F
#define ILI_GREEN   0x07E0
#define ILI_CYAN    0xFFE0
#define ILI_MAGENTA 0xF81F
#define ILI_YELLOW  0x07FF
#define ILI_WHITE   0xFFFF


static const uint8_t Font[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
    0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
    0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
    0x18, 0x3C, 0x7E, 0x3C, 0x18,
    0x1C, 0x57, 0x7D, 0x57, 0x1C,
    0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
    0x00, 0x18, 0x3C, 0x18, 0x00,
    0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
    0x00, 0x18, 0x24, 0x18, 0x00,
    0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
    0x30, 0x48, 0x3A, 0x06, 0x0E,
    0x26, 0x29, 0x79, 0x29, 0x26,
    0x40, 0x7F, 0x05, 0x05, 0x07,
    0x40, 0x7F, 0x05, 0x25, 0x3F,
    0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
    0x7F, 0x3E, 0x1C, 0x1C, 0x08,
    0x08, 0x1C, 0x1C, 0x3E, 0x7F,
    0x14, 0x22, 0x7F, 0x22, 0x14,
    0x5F, 0x5F, 0x00, 0x5F, 0x5F,
    0x06, 0x09, 0x7F, 0x01, 0x7F,
    0x00, 0x66, 0x89, 0x95, 0x6A,
    0x60, 0x60, 0x60, 0x60, 0x60,
    0x94, 0xA2, 0xFF, 0xA2, 0x94,
    0x08, 0x04, 0x7E, 0x04, 0x08,
    0x10, 0x20, 0x7E, 0x20, 0x10,
    0x08, 0x08, 0x2A, 0x1C, 0x08,
    0x08, 0x1C, 0x2A, 0x08, 0x08,
    0x1E, 0x10, 0x10, 0x10, 0x10,
    0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
    0x30, 0x38, 0x3E, 0x38, 0x30,
    0x06, 0x0E, 0x3E, 0x0E, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5F, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x07, 0x00,
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    0x23, 0x13, 0x08, 0x64, 0x62,
    0x36, 0x49, 0x56, 0x20, 0x50,
    0x00, 0x08, 0x07, 0x03, 0x00,
    0x00, 0x1C, 0x22, 0x41, 0x00,
    0x00, 0x41, 0x22, 0x1C, 0x00,
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
    0x08, 0x08, 0x3E, 0x08, 0x08,
    0x00, 0x80, 0x70, 0x30, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x60, 0x60, 0x00,
    0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x72, 0x49, 0x49, 0x49, 0x46, // 2
    0x21, 0x41, 0x49, 0x4D, 0x33, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x31, // 6
    0x41, 0x21, 0x11, 0x09, 0x07, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x46, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x41, 0x22, 0x14, 0x08,
    0x02, 0x01, 0x59, 0x09, 0x06,
    0x07, 0x51, 0x72, 0x51, 0x07, // @
    0x7E, 0x11, 0x11, 0x11, 0x7E,// A
    0x7F, 0x49, 0x49, 0x49, 0x36,// B
    0x3E, 0x41, 0x41, 0x41, 0x22,// C
    0x7F, 0x41, 0x41, 0x22, 0x1C,// D
    0x7F, 0x49, 0x49, 0x49, 0x41,// E
    0x7F, 0x09, 0x09, 0x01, 0x01,// F
    0x3E, 0x41, 0x41, 0x51, 0x32,// G
    0x7F, 0x08, 0x08, 0x08, 0x7F,// H
    0x00, 0x41, 0x7F, 0x41, 0x00,// I
    0x20, 0x40, 0x41, 0x3F, 0x01,// J
    0x7F, 0x08, 0x14, 0x22, 0x41,// K
    0x7F, 0x40, 0x40, 0x40, 0x40,// L
    0x7F, 0x02, 0x04, 0x02, 0x7F,// M
    0x7F, 0x04, 0x08, 0x10, 0x7F,// N
    0x3E, 0x41, 0x41, 0x41, 0x3E,// O
    0x7F, 0x09, 0x09, 0x09, 0x06,// P
    0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
    0x7F, 0x09, 0x19, 0x29, 0x46,// R
    0x46, 0x49, 0x49, 0x49, 0x31,// S
    0x01, 0x01, 0x7F, 0x01, 0x01,// T
    0x3F, 0x40, 0x40, 0x40, 0x3F,// U
    0x1F, 0x20, 0x40, 0x20, 0x1F,// V
    0x7F, 0x20, 0x18, 0x20, 0x7F,// W
    0x63, 0x14, 0x08, 0x14, 0x63,// X
    0x03, 0x04, 0x78, 0x04, 0x03,// Y
    0x61, 0x51, 0x49, 0x45, 0x43,// Z
    0x00, 0x7F, 0x41, 0x41, 0x41,
    0x02, 0x04, 0x08, 0x10, 0x20,
    0x00, 0x41, 0x41, 0x41, 0x7F,
    0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00,
    0x20, 0x54, 0x54, 0x78, 0x40, // a
    0x7F, 0x28, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x28, // c
    0x38, 0x44, 0x44, 0x28, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x02, // f
    0x18, 0xA4, 0xA4, 0x9C, 0x78, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x40, 0x3D, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x78, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0xFC, 0x18, 0x24, 0x24, 0x18, // p
    0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x48, 0x54, 0x54, 0x54, 0x24, // s
    0x04, 0x04, 0x3F, 0x44, 0x24, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x4C, 0x90, 0x90, 0x90, 0x7C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x00,
    0x00, 0x00, 0x77, 0x00, 0x00,
    0x00, 0x41, 0x36, 0x08, 0x00,
    0x02, 0x01, 0x02, 0x04, 0x02,
    0x3C, 0x26, 0x23, 0x26, 0x3C,
    0x1E, 0xA1, 0xA1, 0x61, 0x12,
    0x3A, 0x40, 0x40, 0x20, 0x7A,
    0x38, 0x54, 0x54, 0x55, 0x59,
    0x21, 0x55, 0x55, 0x79, 0x41,
    0x21, 0x54, 0x54, 0x78, 0x41,
    0x21, 0x55, 0x54, 0x78, 0x40,
    0x20, 0x54, 0x55, 0x79, 0x40,
    0x0C, 0x1E, 0x52, 0x72, 0x12,
    0x39, 0x55, 0x55, 0x55, 0x59,
    0x39, 0x54, 0x54, 0x54, 0x59,
    0x39, 0x55, 0x54, 0x54, 0x58,
    0x00, 0x00, 0x45, 0x7C, 0x41,
    0x00, 0x02, 0x45, 0x7D, 0x42,
    0x00, 0x01, 0x45, 0x7C, 0x40,
    0xF0, 0x29, 0x24, 0x29, 0xF0,
    0xF0, 0x28, 0x25, 0x28, 0xF0,
    0x7C, 0x54, 0x55, 0x45, 0x00,
    0x20, 0x54, 0x54, 0x7C, 0x54,
    0x7C, 0x0A, 0x09, 0x7F, 0x49,
    0x32, 0x49, 0x49, 0x49, 0x32,
    0x32, 0x48, 0x48, 0x48, 0x32,
    0x32, 0x4A, 0x48, 0x48, 0x30,
    0x3A, 0x41, 0x41, 0x21, 0x7A,
    0x3A, 0x42, 0x40, 0x20, 0x78,
    0x00, 0x9D, 0xA0, 0xA0, 0x7D,
    0x39, 0x44, 0x44, 0x44, 0x39,
    0x3D, 0x40, 0x40, 0x40, 0x3D,
    0x3C, 0x24, 0xFF, 0x24, 0x24,
    0x48, 0x7E, 0x49, 0x43, 0x66,
    0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
    0xFF, 0x09, 0x29, 0xF6, 0x20,
    0xC0, 0x88, 0x7E, 0x09, 0x03,
    0x20, 0x54, 0x54, 0x79, 0x41,
    0x00, 0x00, 0x44, 0x7D, 0x41,
    0x30, 0x48, 0x48, 0x4A, 0x32,
    0x38, 0x40, 0x40, 0x22, 0x7A,
    0x00, 0x7A, 0x0A, 0x0A, 0x72,
    0x7D, 0x0D, 0x19, 0x31, 0x7D,
    0x26, 0x29, 0x29, 0x2F, 0x28,
    0x26, 0x29, 0x29, 0x29, 0x26,
    0x30, 0x48, 0x4D, 0x40, 0x20,
    0x38, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x38,
    0x2F, 0x10, 0xC8, 0xAC, 0xBA,
    0x2F, 0x10, 0x28, 0x34, 0xFA,
    0x00, 0x00, 0x7B, 0x00, 0x00,
    0x08, 0x14, 0x2A, 0x14, 0x22,
    0x22, 0x14, 0x2A, 0x14, 0x08,
    0xAA, 0x00, 0x55, 0x00, 0xAA,
    0xAA, 0x55, 0xAA, 0x55, 0xAA,
    0x00, 0x00, 0x00, 0xFF, 0x00,
    0x10, 0x10, 0x10, 0xFF, 0x00,
    0x14, 0x14, 0x14, 0xFF, 0x00,
    0x10, 0x10, 0xFF, 0x00, 0xFF,
    0x10, 0x10, 0xF0, 0x10, 0xF0,
    0x14, 0x14, 0x14, 0xFC, 0x00,
    0x14, 0x14, 0xF7, 0x00, 0xFF,
    0x00, 0x00, 0xFF, 0x00, 0xFF,
    0x14, 0x14, 0xF4, 0x04, 0xFC,
    0x14, 0x14, 0x17, 0x10, 0x1F,
    0x10, 0x10, 0x1F, 0x10, 0x1F,
    0x14, 0x14, 0x14, 0x1F, 0x00,
    0x10, 0x10, 0x10, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x1F, 0x10,
    0x10, 0x10, 0x10, 0x1F, 0x10,
    0x10, 0x10, 0x10, 0xF0, 0x10,
    0x00, 0x00, 0x00, 0xFF, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0xFF, 0x10,
    0x00, 0x00, 0x00, 0xFF, 0x14,
    0x00, 0x00, 0xFF, 0x00, 0xFF,
    0x00, 0x00, 0x1F, 0x10, 0x17,
    0x00, 0x00, 0xFC, 0x04, 0xF4,
    0x14, 0x14, 0x17, 0x10, 0x17,
    0x14, 0x14, 0xF4, 0x04, 0xF4,
    0x00, 0x00, 0xFF, 0x00, 0xF7,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0xF7, 0x00, 0xF7,
    0x14, 0x14, 0x14, 0x17, 0x14,
    0x10, 0x10, 0x1F, 0x10, 0x1F,
    0x14, 0x14, 0x14, 0xF4, 0x14,
    0x10, 0x10, 0xF0, 0x10, 0xF0,
    0x00, 0x00, 0x1F, 0x10, 0x1F,
    0x00, 0x00, 0x00, 0x1F, 0x14,
    0x00, 0x00, 0x00, 0xFC, 0x14,
    0x00, 0x00, 0xF0, 0x10, 0xF0,
    0x10, 0x10, 0xFF, 0x10, 0xFF,
    0x14, 0x14, 0x14, 0xFF, 0x14,
    0x10, 0x10, 0x10, 0x1F, 0x00,
    0x00, 0x00, 0x00, 0xF0, 0x10,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
    0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x38, 0x44, 0x44, 0x38, 0x44,
    0x7C, 0x2A, 0x2A, 0x3E, 0x14,
    0x7E, 0x02, 0x02, 0x06, 0x06,
    0x02, 0x7E, 0x02, 0x7E, 0x02,
    0x63, 0x55, 0x49, 0x41, 0x63,
    0x38, 0x44, 0x44, 0x3C, 0x04,
    0x40, 0x7E, 0x20, 0x1E, 0x20,
    0x06, 0x02, 0x7E, 0x02, 0x02,
    0x99, 0xA5, 0xE7, 0xA5, 0x99,
    0x1C, 0x2A, 0x49, 0x2A, 0x1C,
    0x4C, 0x72, 0x01, 0x72, 0x4C,
    0x30, 0x4A, 0x4D, 0x4D, 0x30,
    0x30, 0x48, 0x78, 0x48, 0x30,
    0xBC, 0x62, 0x5A, 0x46, 0x3D,
    0x3E, 0x49, 0x49, 0x49, 0x00,
    0x7E, 0x01, 0x01, 0x01, 0x7E,
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
    0x44, 0x44, 0x5F, 0x44, 0x44,
    0x40, 0x51, 0x4A, 0x44, 0x40,
    0x40, 0x44, 0x4A, 0x51, 0x40,
    0x00, 0x00, 0xFF, 0x01, 0x03,
    0xE0, 0x80, 0xFF, 0x00, 0x00,
    0x08, 0x08, 0x6B, 0x6B, 0x08,
    0x36, 0x12, 0x36, 0x24, 0x36,
    0x06, 0x0F, 0x09, 0x0F, 0x06,
    0x00, 0x00, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x00,
    0x30, 0x40, 0xFF, 0x01, 0x01,
    0x00, 0x1F, 0x01, 0x01, 0x1E,
    0x00, 0x19, 0x1D, 0x17, 0x12,
    0x00, 0x3C, 0x3C, 0x3C, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x00,
};


#define DELAY 0x80
static const uint8_t
Bcmd[] = {                  // Initialization commands for 9341 screens
      16,                       // 16 commands in list:
      ILI_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
      50,                     //     50 ms delay
      ILI_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
      255,                    //     255 = 500 ms delay
      ILI_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
      0x55,                   //     16-bit color
      10,                     //     10 ms delay
      ILI_FRMCTR1, 2+DELAY,  //  4: Frame rate control, 3 args + delay:
      0x00,                   // no clock divider
      0x27,                   // 119Hz refersh
      10,                     //     10 ms delay
      ILI_MADCTL , 1      ,  //  5: Memory access ctrl (directions), 1 arg:
      0x40,                   //     Row addr/col addr, bottom to top refresh
      ILI_DISSET5, 3     ,  //  6: Display settings #5, 2 args, no delay:
      0x00,                   //   normal scan
      0x80,                   //
      0x27,                   //
      ILI_INVCTR , 1      ,  //  7: Display inversion control, 1 arg:
      0x0,                    //     Line inversion
      ILI_PWCTR1 , 1+DELAY,  //  8: Power control, 2 args + delay:
      0x09,                   //     GVDD = 3.3V
      10,                     //     10 ms delay
      ILI_PWCTR2 , 1      ,  //  9: Power control, 1 arg, no delay:
      0x11,                   //     VGH = 14.7V, VGL = -7.35V
      //ILI_PWCTR3 , 2      ,  // 10: Power control, 2 args, no delay:
      //0x01,                   //     Opamp current small
      //0x02,                   //     Boost frequency
      ILI_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
      0x34,                   //     VCOMH = 4V
      0x38,                   //     VCOML = -1.1V
      10,                     //     10 ms delay
      0x51, 1+DELAY,
      0x0F,
      10,
      0x26,1+DELAY,
      0x0F,
      10,
      //ILI_PWCTR6 , 2      ,  // 12: Power control, 2 args, no delay:
      //0x11, 0x15,
      //ILI_GMCTRP1,16      ,  // 13: Magical unicorn dust, 16 args, no delay:
      //0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
      //0x21, 0x1B, 0x13, 0x19, //      these config values represent)
      //0x17, 0x15, 0x1E, 0x2B,
      //0x04, 0x05, 0x02, 0x0E,
      //ILI_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
      //0x0B, 0x14, 0x08, 0x1E, //     (ditto)
      //0x22, 0x1D, 0x18, 0x1E,
      //0x1B, 0x1A, 0x24, 0x2B,
      //0x06, 0x06, 0x02, 0x0F,
      //10,                     //     10 ms delay
      ILI_CASET  , 4      ,  // 15: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 2
      0x00, 0xF0,             //     XEND = 129
      ILI_RASET  , 4      ,  // 16: Row addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 1
      0x01, 0x40,             //     XEND = 160
      ILI_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
      10,                     //     10 ms delay
      ILI_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
      255 };                  //     255 = 500 ms delay


#endif /* ILI9341_ILI9341_H_ */
