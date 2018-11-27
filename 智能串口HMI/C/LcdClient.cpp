#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <sys/socket.h>
#include <sys/vfs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include "LcdCommon.h"
#include "LcdClient.h"

char *get_line_data()
{
    static int  nline = 0;
    static char buf[LCD_MSG_LENGTH + 1];
    static char *sline[] = {"OS Ubuntu %s",
                            "UP:%s",
                            "IP:%s",
                            "CPU:%2d%%  MEM:%2d%%",
                            "NET:%3d/%-3dK I/O",
                            "DISK: %3d/%-3d GB"};

    memset(buf, LCD_MSG_STRING_END, sizeof(buf));

    if (0 == nline) {
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], "Xenial");
    } else if (1 == nline) {
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], get_uptime());
    } else if (2 == nline) {
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], get_ipaddr());
    } else if (3 == nline) {
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], get_cpu_usage(), get_mem_usage());
    } else if (4 == nline) {
        int in, out;
        get_net_usage(&in, &out);
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], in, out);
    } else if (5 == nline) {
        int used, total;
        get_disk_usage(&used, &total);
        snprintf(buf, LCD_MSG_LENGTH, sline[nline++], used, total);
    } else {
        nline = 0;
    }

    //printf("data: %s\n", buf);

    return buf;
}

char *get_uptime()
{
    struct sysinfo sysInfo;
    static char buf[LCD_MSG_LENGTH + 1];

    sysinfo(&sysInfo);

    int days = sysInfo.uptime / 86400;
    int hours = sysInfo.uptime % 86400 / 3600;
    int minuts = sysInfo.uptime % 86400 % 3600 / 60;
    int seconds = sysInfo.uptime % 60;

    memset(buf, LCD_MSG_STRING_END, sizeof(buf));
    snprintf(buf, sizeof(buf) - 1, "%3dD %02d:%02d:%02d", days, hours, minuts, seconds);

    return buf;
}

void strreplace(char *line, const char *search, const char *replace)
{
    char *sp = NULL;

    if ((sp = strstr(line, search)) == NULL) {
        return;
    }
    
    int search_len = strlen(search);
    int replace_len = strlen(replace);
    int tail_len = strlen(sp + search_len);

    memmove(sp + replace_len, sp + search_len, tail_len + 1);
    memcpy(sp, replace, replace_len);
}

char *get_ipaddr() 
{
    struct ifreq req;
    static char ipaddr[16];

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(req.ifr_name, "eth0", IFNAMSIZ);
    ioctl(sock, SIOCGIFADDR, &req);

    char *ip = inet_ntoa(*(struct in_addr *)&((struct sockaddr_in *)&req.ifr_addr)->sin_addr);
    //printf("ip: %s\n", ip);
    memset(ipaddr, LCD_MSG_STRING_END, sizeof(ipaddr));
    strcpy(ipaddr, ip);
    if (strlen(ipaddr) > 13) {
        strreplace(ipaddr, "168", "X");
        printf("ipaddr: %s\n", ipaddr);
    }

    close(sock);

    return ipaddr;
}

int get_cpu_usage()
{
    int usage = 0;
    struct sysinfo sysInfo;

    sysinfo(&sysInfo);

    //printf("cpu: %ld %ld %ld\n", sysInfo.loads[0], sysInfo.loads[1], sysInfo.loads[2]);
    usage = sysInfo.loads[0] * 100 / 65536;
    usage = usage > 99 ? 99 : usage;

    return usage;
}

int get_mem_usage()
{
    int usage = 0;
    struct sysinfo sysInfo;

    sysinfo(&sysInfo);

    usage = (sysInfo.totalram - sysInfo.freeram) * 100 / sysInfo.totalram;
    usage = usage > 99 ? 99 : usage;

    return usage;
}

int get_net_usage(int *in, int *out)
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
                    *in = *out = 0;
                    first_time = 0;
                    return 0;
                } else {
                    unsigned int interval = difftime(time(NULL), lasttime);
                    interval = interval == 0 ? 1 : interval;
                    //printf("Net: %lf %lf %lf %lf %lu\n", rc_byte, grc_byte, tr_byte, gtr_byte, interval);
                    *in = (rc_byte - grc_byte) / interval / 1024;
                    *in = *in > 999 ? 999 : *in;
                    *out = (tr_byte - gtr_byte) / interval / 1024;
                    *out = *out > 999 ? 999 : *out;
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

int get_disk_usage(int *used, int *total)
{
    struct statfs diskinfo;

    statfs("/storage", &diskinfo);

    unsigned long total_size = diskinfo.f_bsize * diskinfo.f_blocks;
    unsigned long used_size = total_size - (diskinfo.f_bsize * diskinfo.f_bfree);
    
    *total = total_size >> 30;
    *used = used_size >> 30;
    //printf("DISK: %d/%d GB\n", *used, *total);

    return 0;
}
