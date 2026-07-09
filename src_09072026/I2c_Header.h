/* 
 * File:   I2c_Header.h
 * Author: Nawab John
 *
 * Created on April 13, 2026, 9:20 AM
 */

#ifndef I2C_HEADER_H
#define	I2C_HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void I2C1_BUS_RECOVERY(void);
void I2C_INIT(void);
void I2C1_WAIT(void);
void I2C1_START(void);
void I2C1_STOP(void);
uint8_t I2C1_WRITE(uint8_t DATA);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_HEADER_H */

