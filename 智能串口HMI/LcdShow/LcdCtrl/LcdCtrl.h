#ifndef __LCD_CTRL_H__
#define __LCD_CTRL_H__

// DEV
#define LCD_DEVICE ("/dev/ttyUSB0")

// CMD
#define LCD_CMD_ERROR       0x00
#define LCD_CMD_SUCCESS     0x01
#define LCD_CMD_ECC         0x02
#define LCD_CMD_EPAGE       0x03
#define LCD_CMD_EIMAGE      0x04
#define LCD_CMD_EDICT       0x05
#define LCD_CMD_EBURD       0x11
#define LCD_CMD_ECHANNEL    0x12
#define LCD_CMD_EVALUE      0x1A
#define LCD_CMD_ECAL        0x1B
#define LCD_CMD_EASSIGN     0x1C
#define LCD_CMD_EE2PROM     0x1D
#define LCD_CMD_EPARAM      0x1E
#define LCD_CMD_EIO         0x1F
#define LCD_CMD_EEE         0x20
#define LCD_CMD_ELONG       0x23
#define LCD_CMD_TOUCH       0x65
#define LCD_CMD_PAGE        0x66
#define LCD_CMD_TOUCHPOS    0x67
#define LCD_CMD_SLEEPPOS    0x68
#define LCD_CMD_STRING      0x69
#define LCD_CMD_VALUE       0x70
#define LCD_CMD_ENSLEEP     0x86
#define LCD_CMD_WAKEUP      0x87
#define LCD_CMD_BOOTOK      0x88
#define LCD_CMD_SDUPDATE    0x89
#define LCD_CMD_TRANSEND    0xFD
#define LCD_CMD_DATAREADY   0xFE
#define LCD_CMD_DATA_END    0xFF

// PAGE
#define LCD_PAGE_MAIN       0
#define LCD_PAGE_CPU        1
#define LCD_PAGE_MEM        2
#define LCD_PAGE_NET        3
#define LCD_PAGE_DISK       4
#define LCD_PAGE_CTRL       5
#define LCD_PAGE_CALC       6
#define LCD_PAGE_CAL        7
#define LCD_PAGE_PHOTO      8

// Machine Init
int machine_init();

// Machine Exit
int machine_exit();

// CMD Parser
int cmd_parse(char *buf, int nlen);

// CMD Run
int cmd_run();

// Send Cmd
int lcd_send_cmd(char *cmd, ...);

// Get CPU Usage
int get_cpu_usage();

// Get MEM Usage
int get_mem_usage();

// Get NET Usage
int get_net_usage();

// Get DISK Usage
int get_disk_usage();

#endif
