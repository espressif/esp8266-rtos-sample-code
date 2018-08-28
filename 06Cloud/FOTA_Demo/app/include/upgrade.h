#ifndef __UPGRADE_H__
#define __UPGRADE_H__

#define SPI_FLASH_SEC_SIZE      4096

#define USER_BIN1               0x00
#define USER_BIN2               0x01

#define UPGRADE_FLAG_IDLE       0x00
#define UPGRADE_FLAG_START      0x01
#define UPGRADE_FLAG_FINISH     0x02

#define UPGRADE_FW_BIN1         0x00
#define UPGRADE_FW_BIN2         0x01

#define SYSTEM_BIN_NO_MAP_MAX_SECTOR    58
#define SYSTEM_BIN_MAP_512_512_MAX_SECTOR  122
#define SYSTEM_BIN_MAP_1024_1024_MAX_SECTOR 250


void system_upgrade_init();
bool system_upgrade(uint8 *data, uint32 len);

#endif
