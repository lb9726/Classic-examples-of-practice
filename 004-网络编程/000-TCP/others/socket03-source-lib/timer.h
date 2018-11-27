
#ifndef _TIMER_H
#define _TIMER_H

#include "list.h"

// define struct

typedef struct _Timer {

	ListNode node;
	u32 gap;
	u32 tick;
	void(*func)(void*);
	void* param;

}Timer;

// define function


void init_timer();
Timer* create_timer(int gap, void(*func)(void*), void* param);
void start_timer(Timer* p_tm);
void delete_timer(Timer* p_tm);
void update_timer();

#endif
