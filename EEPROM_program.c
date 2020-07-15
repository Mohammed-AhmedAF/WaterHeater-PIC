#include "Std_Types.h"
#include "Macros.h"
#include "I2C_interface.h"
#include "EEPROM_interface.h"

void EEPROM_vidWriteByte(unsigned int add, unsigned char data)
{
  I2C_vidSendStart();
  // Wait Until EEPROM Is IDLE
  while(I2C_vidSendByte(0xA0))
   I2C_vidSendRepeatedStart();
  I2C_vidSendByte((unsigned char)add);
  I2C_vidSendByte(data);
  I2C_vidSendStop();
}

u8 EEPROM_u8ReadByte(unsigned int add)
{
     unsigned char Data;
  I2C_vidSendStart();
  // Wait Until EEPROM Is IDLE
  while(I2C_vidSendByte(0xA0))
    I2C_vidSendRepeatedStart();
  
  I2C_vidSendByte((unsigned char)add);
  I2C_vidSendRepeatedStart();
  I2C_vidSendByte(0xA1);
  Data = I2C_u8ReceiveByte();
  I2C_vidSendNACK();
  I2C_vidSendStop();
  return Data;
}