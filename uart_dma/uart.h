#ifndef __UART_H
#define __UART_H

#define dbg_msg(p) uart_send_str(p)
//#define dbg_msg(p){}

extern void 	uart_config();
extern int 		uart_send(char *pb, int n);
extern int 		uart_send_str(char *pb);
extern void 	uart_putch(unsigned char b);
extern int 		uart_read(char *pb, int nb);

#endif
