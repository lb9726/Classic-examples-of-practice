#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/vfs.h>
#include <sys/reboot.h>
#include <QString>
#include "LcdCommon.h"
#include "LcdCtrl.h"
#include "Calc.h"

#define np NPROCESSORS_COUNT
#define sc 255

static int uuid = -1;
static int pageid = 0;

int init_com(char *dev)
{
    int fd = -1;
    struct termios options;

    fd = open(dev, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0) {
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
    static unsigned int count = 1;

    if (uuid < 0) {
        uuid = init_com(LCD_DEVICE);
        if (uuid < 0) {
            printf(".");
            if (count++ % 80 == 0) {
                printf("\n");
            }
            fflush(stdout);
            return -1;
        }
        printf("Connected!\n");
        lcd_send_cmd("sendme");
    }

    return uuid;
}

int machine_exit()
{
    if (uuid > 0) {
        close(uuid);
        uuid = -1;
    }

    pageid = 0;

    return 0;
}

int cmd_parse(char *buf, int nlen)
{
    if ((NULL == buf) || (nlen <= 0)) {
        return -1;
    }

    for (int i = 0; i < nlen; i++) {
        printf("0x%02x ", buf[i]);
    }
    printf("\n");

    switch (buf[0]) {
    case LCD_CMD_TOUCH:
        break;
    case LCD_CMD_PAGE:
        pageid = buf[1];
        break;
    case LCD_CMD_VALUE:
        {
            char data[LCD_MSG_LENGTH];
            memset(data, LCD_MSG_STRING_END, LCD_MSG_LENGTH);

            for (int i = 1, j = 0; i < nlen; i++, j++) {
                if ((char)LCD_CMD_DATA_END == buf[i]) {
                    break;
                }
                data[j] = buf[i];
            }

            if (pageid == LCD_PAGE_CALC) {
                printf("data: %s\n", data);
                double ret = calc(data);
                lcd_send_cmd("t0.txt=\"%s%.4f\"", data, ret);
            }
            else if (pageid == LCD_PAGE_CTRL) {
                printf("data: %s\n", data);
                if (0 == strcmp(data, "reboot")) {
                    sync();
                    printf("do reboot\n");
                    //reboot(RB_AUTOBOOT);

                }
                else if (0 == strcmp(data, "halt")) {
                    sync();
                    printf("do halt\n");
                    //reboot(RB_HALT_SYSTEM);
                }
                else {
                    // do nothing
                }
            }
            else {
                // do nothing
            }
        }
        break;
    default:
        break;
    }

    return 0;
}

int cmd_run()
{
    switch (pageid) {
    case LCD_PAGE_MAIN:
        break;
    case LCD_PAGE_CPU:
        get_cpu_usage();
        break;
    case LCD_PAGE_MEM:
        get_mem_usage();
        break;
    case LCD_PAGE_NET:
        get_net_usage();
        break;
    case LCD_PAGE_DISK:
        get_disk_usage();
        break;
    case LCD_PAGE_CTRL:
        break;
    case LCD_PAGE_CALC:
        break;
    case LCD_PAGE_CAL:
        break;
    case LCD_PAGE_PHOTO:
        break;
    default:
        break;
    }

    return 0;
}

int lcd_send_cmd(char *cmd, ...)
{
    if (NULL == cmd) {
        return -1;
    }

    char cmdstr[LCD_MSG_LENGTH];
    char end = LCD_CMD_DATA_END;

    memset(cmdstr, LCD_MSG_STRING_END, LCD_MSG_LENGTH);

    va_list arg;
    va_start(arg, cmd);
    vsprintf(cmdstr, cmd, arg);
    va_end(arg);

    int nlen = strlen(cmdstr);

    printf("cmd %s len %d\n", cmdstr, nlen);

    ssize_t ret = 0;
    ret = write(uuid, cmdstr, nlen);
    ret = write(uuid, &end, 1);
    ret = write(uuid, &end, 1);
    ret = write(uuid, &end, 1);

    return ret;
}

int get_cpu_usage()
{
    FILE *file = NULL;
    char buffer[1024];
    char *ch_pointer = NULL;
    static int first_time = 1;

    long int user[np], nice[np], sys[np], idle[np], iowait[np], irq[np], softirq[np];
    static long int userl[np], nicel[np], sysl[np], idlel[np], iowaitl[np], irql[np], softirql[np];

    if ((file = fopen("/proc/stat", "r")) != NULL) {
        memset(buffer, LCD_MSG_STRING_END, sizeof(buffer));

        /* Skip first line of file */
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // do nothing
        }

        int i = 0;
        /* Search iface_name and scan values */
        while ((fgets(buffer, sizeof(buffer), file) != NULL)) {
            if (NULL != (ch_pointer = strstr(buffer, "cpu"))) {
                sscanf(ch_pointer, "%*s %ld %ld %ld %ld %ld %ld %ld",
                       &user[i], &nice[i], &sys[i], &idle[i], &iowait[i], &irq[i], &softirq[i]);
            }
            i++;
        }

        if (first_time) {
            first_time = 0;
        } else {
            for (i = 0; i < np; i++) {
                long int total = user[i] + nice[i] + sys[i] + idle[i] + iowait[i] + irq[i] + softirq[i];
                long int totall = userl[i] + nicel[i] + sysl[i] + idlel[i] + iowaitl[i] + irql[i] + softirql[i];

                int usage = 100 * ((total - totall) - (idle[i] - idlel[i])) / (total - totall);
                usage = usage > 99 ? 99 : usage;
                //printf("cpu%d usage %d\n", i, usage);

                lcd_send_cmd("n%d.val=%d", i, usage);
                lcd_send_cmd("add %d,%d,%d", 4, i, usage * sc / 100);
            }
        }

        for (i = 0; i < np; i++) {
            userl[i] = user[i];
            nicel[i] = nice[i];
            sysl[i] = sys[i];
            idlel[i] = idle[i];
            iowaitl[i] = iowait[i];
            irql[i] = irq[i];
            softirql[i] = softirq[i];
        }

        fclose(file);
    }

    return 0;
}

int get_mem_usage()
{
    struct sysinfo sysInfo;

    sysinfo(&sysInfo);

    long int used = (sysInfo.totalram - sysInfo.freeram) * 100 / sysInfo.totalram;
    long int free = sysInfo.freeram * 100 / sysInfo.totalram;
    long int shared = sysInfo.sharedram * 100 / sysInfo.totalram;
    long int buffered = sysInfo.bufferram * 100 / sysInfo.totalram;
    long int swap = (sysInfo.totalswap - sysInfo.freeswap) * 100 / sysInfo.totalswap;

    printf("used %ld free %ld shca %ld swap %ld\n", used, free, shared + buffered, swap);

    // used
    lcd_send_cmd("n0.val=%ld", used);
    lcd_send_cmd("add 4,0,%ld", used * sc / 100);

    // free
    lcd_send_cmd("n1.val=%ld", free);
    lcd_send_cmd("add 4,1,%ld", free * sc / 100);

    // shared + buffer
    lcd_send_cmd("n2.val=%ld", shared + buffered);
    lcd_send_cmd("add 4,2,%ld", (shared + buffered) * sc / 100);

    // swap
    lcd_send_cmd("n3.val=%ld", swap);
    lcd_send_cmd("add 4,3,%ld", swap * sc / 99);

    return 0;
}

int get_net_usage()
{
    FILE *file = NULL;
    char buffer[1024];
    static int first_time = 1;
    char *ch_pointer = NULL;

    static time_t lasttime;
    static double grc_byte, gtr_byte;

    if ((file = fopen("/proc/net/dev", "r")) != NULL) {
        /* Skip first 2 header lines of file */
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // do nothing
        }
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // do nothing
        }

        /* Search iface_name and scan values */
        while ((fgets(buffer, sizeof(buffer), file) != NULL)) {
            if (strstr(buffer, "eth0")) {
                /* interface exists */
                double rc_byte, tr_byte;

                /* search ':' and skip over it */
                ch_pointer = strchr(buffer, ':');
                ch_pointer++;

                /* Scan values from here */
                sscanf(ch_pointer, "%lf %*s %*s %*s %*s %*s %*s %*s %lf", &rc_byte, &tr_byte);

                if (first_time) {
                    first_time = 0;
                } else {
                    unsigned int interval = difftime(time(NULL), lasttime);
                    interval = interval == 0 ? 1 : interval;
                    //printf("Net: %lf %lf %lf %lf %lu\n", rc_byte, grc_byte, tr_byte, gtr_byte, interval);

                    int dl = (rc_byte - grc_byte) / interval / 1024;
                    int ul = (tr_byte - gtr_byte) / interval / 1024;

                    // upload
                    lcd_send_cmd("n0.val=%d", ul);
                    lcd_send_cmd("add 4,0,%d", ul / 4);

                    // download
                    lcd_send_cmd("n3.val=%d", dl);
                    lcd_send_cmd("add 4,1,%d", dl / 4);
                }

                grc_byte = rc_byte;
                gtr_byte = tr_byte;
                lasttime = time(NULL);
            }
        }

        fclose(file);
    }

    return 0;
}

int get_disk_usage()
{
    static char *path[] = {"/", "/storage/SG", "/storage/SG", "/storage/WD", "/storage/AV"};

    for (unsigned int i = 0; i < sizeof(path)/sizeof(path[0]); i++) {
        struct statfs diskinfo;

        statfs(path[i], &diskinfo);

        unsigned long total_size = diskinfo.f_bsize * diskinfo.f_blocks;
        unsigned long used_size = total_size - (diskinfo.f_bsize * diskinfo.f_bfree);

        int total = total_size >> 30;
        int used = used_size >> 30;

        lcd_send_cmd("j%d.val=%d", i, used * 100 / total);
    }

    return 0;
}
