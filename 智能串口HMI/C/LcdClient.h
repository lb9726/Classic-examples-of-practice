#ifndef __LCD_CLIENT_H__
#define __LCD_CLIENT_H__

// Line_Data
char *get_line_data();

// Get Uptime
char *get_uptime();

// Get IP Addr
char *get_ipaddr();

// Get CPU Usage
int get_cpu_usage();

// Get MEM Usage
int get_mem_usage();

// Get NET Usage
int get_net_usage(int *in, int *out);

// Get DISK Usage
int get_disk_usage(int *used, int *total);

#endif // __LCD_CLIENT_H__
