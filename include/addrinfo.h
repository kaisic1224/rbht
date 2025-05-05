#include <cstdint>
#include <sys/types.h>

using namespace std;

struct addrinfo {
  int ai_flags; // AI_PASSIVE
  int ai_family; // AF_INET or AF_INET6
  int ai_socktype; // SOCK_STREAM or DATA_STREAM
  int ai_protocol; // 0 or "getprotobyname("tcp")" / "getprotobyname("udp")"
  size_t addr_len;
  struct sockaddr *ai_addr;
  char *ai_cannonname;
  struct addrinfo* ai_next; // returns from getaddrinfo(), a linked list of objects
};

struct sockaddr {
  unsigned short sa_family; // AF_INET (IPv4) or AF_INET6 (IPV6)
  char *sa_data[14];
};

struct in_addr {
  uint32_t s_addr;
};

// IPv4 socket address (INTERNET=IP)
struct sockaddr_in {
  short int sin_family;
  unsigned short int sin_port;  // MUT BE IN NETWORK BYTE ORDER
  struct in_addr sin_addr;
  unsigned char sin_zero[8]; // to make up padding wise so same as sockaddr
};

struct in6_addr {
  unsigned char s6_addr[16];
};

// IPv6 socket address (INTERNET=IP)
struct sockaddr_in6 {
  short int sin6_family;
  unsigned short int sin6_port;
  u_int32_t sin6_flowinfo;
  struct in6_addr sin6_addr;
  u_int32_t sin6_scope_id;
};

// struct sockaddr sibling, you can use this to downcast to v6 or v4 depending on needs
// struct sockaddr_storage {
//     sa_family_t  ss_family;     // address family
//
//     // all this is padding, implementation specific, ignore it:
//     char      __ss_pad1[_SS_PAD1SIZE];
//     int64_t   __ss_align;
//     char      __ss_pad2[_SS_PAD2SIZE];
// };


// API REFERENCE


// int socket(int domain, int type, int protocol) domain - family, type - socktype, protocol - protocol or 0 for autodetermine
// int bind(int sockfd, struct sockaddr* my_addr, int addrlen)
// int connect(int sockfd, struct sockaddr* serv_addr, int addrlen)
// int accept(int sockfd, struct sockaddr* my_addr, int addrlen)
// int listen(int sockfd, int backlog) sockfd - socket, backlog - size of queue before you accept
// int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) sockfd - socket, addr - buffer to place connecting IP into
// void close(int sockfd) closes the socket connection
// inet_ntop(AF_INET, *in_addr or *in6_addr, string, sizeof(string))
// string.data() - turn into char*
//
//
// CONNECTING =
// getaddrinfo()
// socket()
// connect()
// send(new_fd), recv(new_fd) - flag always set to 0
//
// HOSTING =
// getaddrinfo()
// socket()
// bind(socket, address)
// listen(socket)
// new_fd = accept(socket, connection_info)
// send(new_fd), recv(new_fd) - flag always set to 0
//
// UDP =
// int sendto(sockfd, msg, len, flags, const struct sockaddr* to, socklen_t tolen)
// int recvfrom(sockfd, buf, len, flags, struct sockaddr* from, int* fromlen) from is a pointer to the address of the sender, will be filled in
//
//
// int getpeername(int sockfd, struct sockaddr *addr, int *addrlen) updates addr and addrlen with the peer connection
// int gethostname(char *hostname, size_t size) updates hostname and size (len in bytes) with name of server
//
// select(int nu) 
//
// NOTE ABOUT PACKING-
// all data is usually sent in a buffer: char buf[size_t n], even structs are packed similarily
// so when data is meant to be received, we need to "unpack" this data.
// data is usually stored sequentially when packed via a struct, so buf is the natural way to do so
// need to create your own pack() and unpack() variadic functions that can parse any amount of
// fields from buf into the variables provided, tbh better to use a library to pack instead
