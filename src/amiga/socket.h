/* amiga/socket.h */

#ifndef AMIGA_SOCKET_H
#define AMIGA_SOCKET_H

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
 * Note: if a module (.c file) uses these functions on both socket and
 *       file descriptors, function calls on file descriptors must have
 *       the function name parenthesized to keep the preprocessor from
 *       expanding the macro, eg
 *
 *       (close)(file_fd);      ->      close(file_fd);
 *       close(socket_fd);      ->      CloseSocket(socket_fd)
 */
#undef close
#undef ioctl
#undef write
#undef read

/*
 * AmiTCP
 */
#ifdef AMITCP

#define close(s) CloseSocket(s)
#define ioctl(s,t,u) IoctlSocket(s,t,(char *)u)
#define write(s,b,l) send(s,b,l,0)
#define read(s,b,l) recv(s,b,l,0)
#define getsockname(a,b,c) getsockname(a,b,(LONG *)c)
#define accept(a,b,c) accept(a,b,(LONG *)c)
#define recvfrom(a,b,c,d,e,f) recvfrom(a,b,c,d,e,(LONG *)f)

#endif /* AMITCP */

/*
 * AS225
 */
#ifdef AS225

#define FD_SETSIZE 256
#define SOCKET_T int

#define close(s) s_close(s)
#define ioctl(s,t,u) s_ioctl(s,t,u)
#define write(s,b,l) send(s,b,l,0)
#define read(s,b,l) recv(s,b,l,0)

#endif /* AS225 */

void amiga_sockinit(void);
void amiga_sockexit(void);

#endif /* AMIGA_SOCKET_H */
