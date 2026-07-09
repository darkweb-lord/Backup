#include <xc.h>             // Standard XC16 header
#include <stdint.h>         // Required for uint8_t definitions

// 1. You MUST define your clock speed here BEFORE libpic30.h
// Assuming 8MHz internal oscillator (Fosc = 8MHz, FCY = Fosc/2 = 4000000)
// If you enabled the PLL for 32MHz, change this to 16000000UL
#define FCY 16000000UL       

// 2. Delay library included AFTER the speed is defined
#include <libpic30.h>       

// 3. Your local headers
#include "LCD_I2C.h"
#include "I2c_Header.h"

/* FIX C4: datasheet-correct AiP31068 write address (was 0x4E) */
#define LCD_ADDR   0x7C          /* 0x3E<<1 ; use 0x4C only if a PCF8574 @0x26 is confirmed */
#define LCD_CTRL_CMD   0x00      /* control byte: next byte is a command (RS=0) */
#define LCD_CTRL_DATA  0x40      /* control byte: next byte is data    (RS=1) */

/* returns 0 on success, 1 if slave did not ACK (FIX C5) */
static uint8_t LCD_XFER(uint8_t control, uint8_t value)
{
    uint8_t nack = 0;
    I2C1_START();
    nack |= I2C1_WRITE(LCD_ADDR);      /* ACKSTAT: 0=ACK, 1=NACK */
    nack |= I2C1_WRITE(control);
    nack |= I2C1_WRITE(value);
    I2C1_STOP();
    return nack;
}

void LCD_CMD(uint8_t cmd)  { LCD_XFER(LCD_CTRL_CMD,  cmd);  }
void LCD_DATA(uint8_t d)   { LCD_XFER(LCD_CTRL_DATA, d);    }

void LCD_INIT(void)
{
    __delay_ms(50);              /* local guard; bulk EN delay is in main.c (FIX C2) */
    LCD_CMD(0x38); __delay_ms(5);        /* function set: 8-bit, 2-line, 5x8 */
    LCD_CMD(0x38); __delay_us(150);
    LCD_CMD(0x38);
    LCD_CMD(0x0C);               /* display ON, cursor off, blink off */
    LCD_CMD(0x01); __delay_ms(2);        /* clear (needs >1.5 ms; BF high) */
    LCD_CMD(0x06); __delay_ms(2);        /* entry mode: increment, no shift */
}

// Move cursor to a specific Row (0 or 1) and Column (0 to 15)
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    static const uint8_t off[2] = {0x00, 0x40};
    LCD_CMD(0x80 | (off[row & 1] + col));
}

// Print a standard C string
void LCD_PRINT(char *s)
{
    while (*s) LCD_DATA((uint8_t)*s++);
}