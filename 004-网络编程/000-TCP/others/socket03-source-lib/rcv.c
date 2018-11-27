/*
 * Copyright 2015 tristan_fei <feixiaoxing@163.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include <malloc.h>

#include "type.h"
#include "rcv.h"
#include "assert.h"
#include "send.h"
#include "define.h"

// define global variable

static ListNode g_handle[HANDLE_HASH_NUM];

static func g_onConnect;
static func g_onClose;
static func g_onRecv;


// define function here

void init_handle() {

	int i;

	// init node

	for(i = 0; i < HANDLE_HASH_NUM; i ++) {

		init_node(&g_handle[i]);
	}

	// init func parameters

	g_onConnect = 0x0;
	g_onClose = 0x0;
	g_onRecv = 0x0;
}

// init struct

static void init_handle_struct(RCV_SOCK* p_hand, int sock) {

	init_node(&p_hand->node);
	init_node(&p_hand->read);

	p_hand-> sock = sock;
	p_hand-> onConnect = g_onConnect;
	p_hand-> onClose = g_onClose;
	p_hand-> onRecv = g_onRecv;
}

// register sock

static void register_sock(RCV_SOCK* p_hand) {

	add_node(&g_handle[p_hand-> sock % HANDLE_HASH_NUM], &p_hand->node);
}

void register_callback_func(func onConnect, func onClose, func onRecv) {

	g_onConnect = onConnect;
	g_onClose = onClose;
	g_onRecv = onRecv;
}

// remove sock

static void remove_rcv_node(RCV_SOCK* p_hand) {

	delete_node(&p_hand->node);
}

// find sock

RCV_SOCK* find_handle(int sock) {

	RCV_SOCK* p_hand;
	ListNode* p_node;
	int num;

	num = sock % HANDLE_HASH_NUM;
	p_node = g_handle[num].next;

	for(; p_node != &g_handle[num]; p_node = p_node-> next){

		p_hand = (RCV_SOCK*)(p_node);
		if(p_hand-> sock == sock) {

			return p_hand;
		}
	}

	return (RCV_SOCK*)0x0;
}

// process sock message from epoll

void process_message(int type, int sock) {

	RCV_SOCK* p_hand;
	s8* p_buf;
	u32 len;

	switch(type) {

		case NEW_SOCK:

			p_hand = (RCV_SOCK*) malloc(sizeof(RCV_SOCK));
			if(!p_hand) {
				assert(0);
			}

			// init struct and register sock to whole structure

			init_handle_struct(p_hand, sock);
			register_sock(p_hand);

			assert(p_hand->onConnect);
			p_hand->onConnect(p_hand);

			break;

		case SOCK_CLOSE:

			// remove sock when it is not connected already

			p_hand = find_handle(sock);
			if(p_hand) {

				assert(p_hand->onClose);
				p_hand->onClose(p_hand);
			}

			// remove all rcv buffer data

			while(TRUE == get_rcv_buf(p_hand-> sock, &p_buf, &len)) {

				free(p_buf);
			}

			remove_rcv_node(p_hand);
			free(p_hand);

			break;

		case RECV_DATA:

			p_hand = find_handle(sock);
			if(p_hand) {

				assert(p_hand->onRecv);
				p_hand->onRecv(p_hand);
			}

			break;


		default:
			assert(0);
	}

}

// send buf data

STATUS send_buf(RCV_SOCK* p_hand, s8* buf, u32 len) {

	SEND_BUF* p_buf;

	// add send buf

	p_buf = (SEND_BUF*) malloc(sizeof(SEND_BUF));
	if(!buf) {

		assert(0);
		return FALSE;
	}

	init_send_buf(p_buf, buf, len);
	add_send_buf(p_hand-> sock, p_buf);

	// modify event

	epoll_mod_socket(p_hand-> sock);

	return TRUE;

}

// init rcv buffer

void init_rcv_buf(RCV_BUF* p_rcv, s8* buf, u32 len) {

	init_node(&p_rcv->node);

	p_rcv->buf = buf;
	p_rcv->len = len;

}

// add buf to socket

STATUS add_buf_to_sock(int sock, RCV_BUF* p_rcv) {

	RCV_SOCK* p_hand;

	p_hand = find_handle(sock);
	if(!p_hand){

		return FALSE;
	}

	add_node(&p_hand->read, &p_rcv-> node);

	return TRUE;
}

// get buf from socket

STATUS get_rcv_buf(int sock, s8** buf, u32* len) {

	RCV_SOCK* p_hand;
	RCV_BUF* p_rcv;
	ListNode* p_node;

	p_hand = find_handle(sock);
	if(!p_hand) {

		return FALSE;
	}

	p_node = p_hand->read.next;
	if(p_node == &p_hand->read) {

		return FALSE;
	}

	p_rcv = (RCV_BUF*)p_node;
	*buf = p_rcv-> buf;
	*len = p_rcv->len;

	delete_node(p_node);
	free(p_rcv);

	return TRUE;

}

// remove rcv sock

void remove_rcv_sock(int sock) {

	RCV_SOCK* p_hand;
	s8* p_buf;
	u32 len;

	p_hand = find_handle(sock);
	if(!p_hand) {

		return;
	}

	// remove all rcv buffer data

	while(TRUE == get_rcv_buf(p_hand-> sock, &p_buf, &len)) {

		free(p_buf);
	}

	remove_rcv_node(p_hand);
	free(p_hand);

}
// remove all recv socket

void remove_all_rcv_socket() {

	RCV_SOCK* p_hand;
	ListNode* p_node;
	s32 i;

	for(i = 0; i < HANDLE_HASH_NUM; i ++) {

		p_node = g_handle[i].next;
		if(p_node == &g_handle[i]) {

			continue;
		}

		for(; p_node != &g_handle[i]; p_node = p_node-> next) {

			p_hand = (RCV_SOCK*) p_node;
			remove_rcv_sock(p_hand->sock);
		}
	}


}

// dump rcv sock

void dump_all_recv_sock() {

	RCV_SOCK* p_hand;
	ListNode* p_node;
	s32 i;

	log_print_msg("All rcv sock is as follows:\n");

	for(i = 0; i < HANDLE_HASH_NUM; i ++) {

		p_node = g_handle[i].next;
		if(p_node == &g_handle[i]) {

			continue;
		}

		for(; p_node != &g_handle[i]; p_node = p_node-> next) {

			p_hand = (RCV_SOCK*) p_node;
			log_print_msg("    %d\n", p_hand->sock);
		}
	}

}

// dump rcv buf by sock

void dump_rcv_buf(int sock) {

	RCV_SOCK* p_hand;
	RCV_BUF* p_rcv;
	ListNode* p_node;

	log_print_msg("Rcv buf is as follows:\n");

	p_hand = find_handle(sock);
	if(!p_hand) {

		log_print_msg("    No sock.\n");
		return;
	}

	p_node = p_hand->read.next;
	if(p_node == &p_hand->read) {

		log_print_msg("    No rcv buf.\n");
		return;
	}

	for(; p_node != &p_hand->read; p_node = p_node-> next) {

		p_rcv = (RCV_BUF*)(p_node);

		log_print_msg("    addr:0x%x\n", p_rcv-> buf);
		log_print_msg("    len:%d\n", p_rcv-> len);
		log_print_msg("\n");
	}
}


