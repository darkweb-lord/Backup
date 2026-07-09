#define FCY 16000000UL
#include <xc.h>
#include <libpic30.h>
#include "mcc_generated_files/system.h"
#include "I2c_Header.h"
#include "LCD_I2C.h"

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    __delay_ms(400);          /* FIX C2: rails + LSF0108 EN bias (RC=200ms; 4.3V @ ~393ms) */
    I2C1_BUS_RECOVERY();      /* FIX C5: free a stuck slave before configuring the module */
    I2C_INIT();
    LCD_INIT();
    while (1)
    {
        // Add your application code
        LCD_SetCursor(0,0);
        LCD_PRINT("System Booting...");
        LCD_SetCursor(1,0);
        LCD_PRINT("Made by DISPL");
        __delay_ms(1000);
    }

    return 1;
}
/**
 End of File
*/

