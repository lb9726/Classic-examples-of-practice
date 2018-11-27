#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/sysinfo.h>
#include "LcdCommon.h"
#include "LcdCtrl.h"
#include "LcdClient.h"

static int uuid = -1;

int init_com(char *dev)
{
    int fd = -1;
    struct termios options;

    fd = open(dev, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0) {
        perror("init_com");
        return -1;
    }

    tcgetattr(fd, &options);
    options.c_cflag |= (CLOCAL|CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    options.c_cc[VTIME] = 10;
    options.c_cc[VMIN] = 1;
    cfsetospeed(&options, B9600);

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    return fd;
}

int machine_init()
{
    if (uuid < 0) {
        uuid = init_com(LCD_DEVICE);
        if (uuid < 0) {
            printf("init_com error!\n");
            return -1;
        }
    }

    lcd_send_cmd(LCD_CMD_RESET);
    lcd_send_cmd(LCD_CMD_CLEAR);

    return 0;
}

int machine_exit()
{
    if (uuid > 0) {
        close(uuid);
        uuid = -1;
    }

    return 0;
}

int lcd_send_cmd(char code, char param)
{
    char cmd[4];

    cmd[0] = LCD_CMD_HEAD;
    cmd[1] = code;
    cmd[2] = param;
    cmd[3] = LCD_MSG_STRING_END;

    ssize_t ret = write(uuid, cmd, sizeof(cmd));

    return ret;
}

int line_disp(char *buf)
{
    int nlen;
    char cmd[20];

    if (NULL == buf) {
        printf("%s NULL == buf\n", __PRETTY_FUNCTION__);
        return -1;
    }

    memset(cmd, LCD_MSG_STRING_END, sizeof(cmd));
    nlen = strlen(buf) > 16 ? 16 : strlen(buf);

    cmd[0] = LCD_CMD_HEAD;
    cmd[1] = LCD_CMD_DATA;
    strncpy(&cmd[2], buf, nlen);
    cmd[++nlen + 2] = LCD_CMD_DATA_END;
    cmd[++nlen + 2] = LCD_MSG_STRING_END;

    ssize_t ret = write(uuid, cmd, sizeof(cmd));

    return ret;
}

int line1_disp(char *buf)
{
    lcd_send_cmd(LCD_CMD_SCREEN_POSITION, LCD_CMD_SCREEN_LINE1_START);
    return line_disp(buf);
}

int line2_disp(char *buf)
{
    lcd_send_cmd(LCD_CMD_SCREEN_POSITION, LCD_CMD_SCREEN_LINE2_START);
    return line_disp(buf);
}

char *get_line1_data()
{
    static int  nloadchar = 0;
    static char buf[LCD_MSG_LENGTH + 1];
    static char *loadchar[] = {"#", "+"};
    static char *month[] = {"Jan.", "Feb.", "Mar.", "Apr.", "May ", "Jun.",
                            "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."};

    time_t now;
    struct tm timeNow;

    time(&now);
    localtime_r(&now, &timeNow);

    memset(buf, LCD_MSG_STRING_END, sizeof(buf));
    int npos = nloadchar++ % (sizeof(loadchar)/sizeof(loadchar[0]));

    // Jan.01#20:20:20#
    snprintf(buf, LCD_MSG_LENGTH, "%s%02d%s%02d:%02d:%02d%s",
            month[timeNow.tm_mon], timeNow.tm_mday, loadchar[npos],
            timeNow.tm_hour, timeNow.tm_min, timeNow.tm_sec, loadchar[npos]);

    buf[LCD_MSG_LENGTH] = '\0';

    return buf;
}

char *get_line2_data()
{
    if (get_cpu_usage() > 25) {
        lcd_send_cmd(LCD_CMD_BACKLIGHT_ON);
    } else {
        lcd_send_cmd(LCD_CMD_BACKLIGHT_OFF);
    }

    return get_line_data();
}
