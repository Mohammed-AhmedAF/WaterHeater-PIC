#include "Std_Types.h"
#include "Macros.h"
#include "I2C_interface.h"
#include "EEPROM_interface.h"


u8 EEPROM_u8WriteByte(u16 u16Location,u8 u8ByteCpy)
{
u8 SLA_W;
	u8 P1,P0;
	SLA_W=0b10100000;
	P1=GET_BIT(u16Location,9);
	P0=GET_BIT(u16Location,8);
	SLA_W |=(P1<<2);
	SLA_W |=(P0<<1);
	I2C_vidSendStart();
	if(I2C_u8CheckACK()==1)
	{
		I2C_vidSendByte(SLA_W);
		if(I2C_u8CheckACK()==1)
		{
			I2C_vidSendByte((u8)u16Location);
			if(I2C_u8CheckACK()==1)
			{
				I2C_vidSendByte(u8ByteCpy);
				if(I2C_u8CheckACK()==1)
				{
					I2C_vidSendStop();
					return EEPROM_STATUS_SUCCESS;
				}
			}
		}
	}
	return EEPROM_STATUS_FAIL;
}

u8 EEPROM_u8ReadByte(u16 u16LocationCpy,u8 * u8DataCpy)
{
u8 SLA_W;
	u8 P1,P0;
	SLA_W=0b10100000;
	P1=GET_BIT(u16LocationCpy,9);
	P0=GET_BIT(u16LocationCpy,8);
	SLA_W |=(P1<<2);
	SLA_W |=(P0<<1);

	I2C_vidSendStart();
	if(I2C_u8CheckACK() == 1) {
		I2C_vidSendByte(SLA_W);
		if(I2C_u8CheckACK() == 1) {
			I2C_vidSendByte((u8)u16LocationCpy);
			if(I2C_u8CheckACK() == 1) {
				I2C_vidSendRepeatedStart();
				if(I2C_u8CheckACK()== 1) {
                    /*Read command*/
					SET_BIT(SLA_W,0);
					I2C_vidSendByte(SLA_W);
					if(I2C_u8CheckACK() == 1) {
						*u8DataCpy = I2C_u8ReceiveByte();
                        I2C_vidSendNACK();
						I2C_vidSendStop();
						return EEPROM_STATUS_SUCCESS;
					}
				}
			}
		}
	}
	return EEPROM_STATUS_FAIL;
    }

void EEPROM_vidWriteByte(unsigned int add, unsigned char data)
{
  I2C_vidSendStart();
  // Wait Until EEPROM Is IDLE
while(I2C_vidSendByte(0xA0));
    I2C_vidSendRepeatedStart();
  I2C_vidSendByte(add>>8);
  I2C_vidSendByte((unsigned char)add);
  I2C_vidSendByte(data);
  I2C_vidSendStop();
}