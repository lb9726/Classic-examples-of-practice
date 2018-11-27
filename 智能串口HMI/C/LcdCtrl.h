#ifndef __LCD_CTRL_H__
#define __LCD_CTRL_H__

// DEV
#define LCD_DEVICE ("/dev/ttyS3")

// CMD
#define LCD_CMD_HEAD  0xF8
#define LCD_CMD_CLEAR 0x01
#define LCD_CMD_RESET 0x02
#define LCD_CMD_DATA  0x03
#define LCD_CMD_DATA_END 0xA0
#define LCD_CMD_CURSOR_LEFT  0x05
#define LCD_CMD_CURSOR_RIGHT 0x06
#define LCD_CMD_CURSOR_HIDE  0x0C
#define LCD_CMD_CURSOR_SHOW  0x0F
#define LCD_CMD_CURSOR_MOVELEFT  0x10
#define LCD_CMD_CURSOR_MOVERIGHT 0x14
#define LCD_CMD_SCREEN_MOVELEFT  0x18
#define LCD_CMD_SCREEN_MOVERIGHT 0x1C
#define LCD_CMD_SCREEN_POSITION  0x80
#define LCD_CMD_SCREEN_LINE1_START 0x00
#define LCD_CMD_SCREEN_LINE2_START 0x40
#define LCD_CMD_BACKLIGHT_ON  0x28
#define LCD_CMD_BACKLIGHT_OFF 0x2C

// Machine Init
int machine_init();

// Machine Exit
int machine_exit();

// Send Cmd
int lcd_send_cmd(char code, char param = LCD_MSG_STRING_END);

// Line1 Display
int line1_disp(char *buf);

// Lin2 Display
int line2_disp(char *buf);

// Line1 Data
char *get_line1_data();

// Line2_Data
char *get_line2_data();

#endif // __LCD_CTRL_H__
