#ifndef EEPROM_INTERFACE_H
#define	EEPROM_INTERFACE_H

#define EEPROM_STATUS_FAIL 0
#define EEPROM_STATUS_SUCCESS 1


#define START_CONDITION 0x08
#define REPEATED_START 0x10
#define SLA_W_ACK 0x18
#define SLA_R_ACK 0x40
#define DATA_TX_ACK 0x28

 u8 EEPROM_u8WriteByte(u16,u8);
 u8 EEPROM_u8ReadByte(u16,u8 *);
 void EEPROM_vidWriteByte(unsigned int,u8);

#endif	/* EEPROM_INTERFACE_H */

