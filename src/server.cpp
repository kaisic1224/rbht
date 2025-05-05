// #include <array>
// #include <arpa/inet.h> // inet_ntop
// #include <csignal>
// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
// #include <iomanip>
// #include <iostream>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <poll.h>
// #include <sys/poll.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h> // close
// #include <vector>
//
// using namespace std;
//
// void sigchild_handler(int s) {
//   int saved_errno = errno;
//   while (waitpid(-1, NULL, WNOHANG) > 0)
//     ;
//
//   errno = saved_errno;
// }
//
// int main(int argc, char *argv[]) {
//   int status;
//   char ipstr[INET6_ADDRSTRLEN];
//   struct addrinfo hints{};
//   struct addrinfo *server_info{};
//
//   hints.ai_family = AF_UNSPEC;     // don't care between v4 or v6
//   hints.ai_socktype = SOCK_STREAM; // tcp, data_stream = udp
//   hints.ai_flags = AI_PASSIVE;     // fill in ip for me, use for when IP is null
//                                    // (listening sockets)
//
//   // (hostname: char*, port: char*, hints: *addrinfo, server_info: *addrinfo)
//   // returns *addrinfo, with a next member field
//   if ((status = getaddrinfo(NULL, "1224", &hints, &server_info)) != 0) {
//     cerr << "getaddrinfo: " << gai_strerror(status) << endl;
//     exit(1);
//   }
//
//   for (struct addrinfo *p = server_info; p != NULL; p = p->ai_next) {
//     void *ia = nullptr;
//     int port{};
//     if (p->ai_family == AF_INET) {
//       sockaddr_in *ipv4 = reinterpret_cast<sockaddr_in *>(p->ai_addr);
//       ia = &(ipv4->sin_addr);
//       port = ipv4->sin_port;
//     } else if (p->ai_family == AF_INET6) {
//       sockaddr_in6 *ipv6 = reinterpret_cast<sockaddr_in6 *>(p->ai_addr);
//       // * on RHS (as an rvalue = deref),
//       // * on LHS (as an lvalue = pointer)
//       // , then if assigning a pointer to a value, need it to point to a
//       // refernce
//       ia = &(ipv6->sin6_addr);
//       port = ipv6->sin6_port;
//     }
//     inet_ntop(p->ai_family, ia, ipstr, sizeof(ipstr));
//     cout << "Listening on " << ipstr << ":" << htons(port) << endl;
//   }
//
//   int sock_fd = socket(server_info->ai_family, server_info->ai_socktype,
//                        server_info->ai_protocol);
//   if (sock_fd == -1) {
//     perror("server: socket");
//     exit(1);
//   }
//
//   int reuseaddr_true = 1;
//   if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_true,
//                  sizeof(int)) == -1) {
//     perror("setsockopt");
//     exit(1);
//   }
//
//   int bind_status{};
//   // bind = listen, connect = receive
//   if ((bind_status = bind(sock_fd, server_info->ai_addr,
//                           server_info->ai_addrlen)) == -1) {
//     perror("server: bind");
//     close(sock_fd);
//     exit(1);
//   }
//
//   freeaddrinfo(server_info);
//
//   // listen to socket, accept up to 5 connections
//   if (listen(sock_fd, 5) == -1) {
//     perror("listen");
//     exit(1);
//   }
//
//   struct sigaction sa{};
//   sa.sa_handler = sigchild_handler;
//   sigemptyset(&sa.sa_mask);
//   sa.sa_flags = SA_RESTART;
//   if (sigaction(SIGCHLD, &sa, NULL) == -1) {
//     perror("sigaction");
//     exit(1);
//   }
//   cout << "Awaiting a connection" << endl;
//
//   while (true) {
//     // information about the incoming connection goes into sockaddr_storage
//     // connector this lets us cast down to ipv6 or ipv4 regardless later if
//     // necessary
//     struct sockaddr_storage connector{};
//     socklen_t connector_size = sizeof(connector);
//     int new_fd =
//         accept(sock_fd, (struct sockaddr *)&connector, &connector_size);
//     if (new_fd == -1)
//       perror("accept");
//     string connecting_ipstr = "";
//     inet_ntop(connector.ss_family, (struct sockaddr *)&connector,
//               connecting_ipstr.data(), sizeof(connecting_ipstr));
//     cout << "Received connection from " << connecting_ipstr.data() << endl;
//
//     if (!fork()) {    // if child, returns 0, !0 = TRUE
//       close(sock_fd); // child processes dont need listener socket
//       string msg =
//           "qweqwewqeqweqweqweeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
//           "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n";
//       size_t total = 0;
//       while (total < msg.length()) {
//         int bytes_sent = send(new_fd, msg.data() + total, msg.length(), 0);
//         if (bytes_sent <= 0)
//           continue;
//         total += bytes_sent;
//       }
//       close(new_fd);
//       exit(0);
//     }
//
//     // vector<struct pollfd> pfds{};
//     // pfds.push_back(pollfd{new_fd, POLLIN, POLLIN});
//
//     char recvmsg[256];
//     ssize_t rstatus = recv(new_fd, recvmsg, sizeof(recvmsg), 0);
//     while (rstatus > 0) {
//       // int pollin_happened = pfds[0].revents & POLLIN;
//       // cout << pollin_happened << endl;
//       cout << "the size of msg: " << rstatus << endl;
//       if (rstatus > 0) {
//         recvmsg[rstatus] =
//             '\0'; // null terminate if you want to treat it as a C-string
//         cout << "Received: " << recvmsg;
//         for (int i = 0; i < rstatus; ++i)
//           cout << recvmsg[i] << " ";
//         cout << endl;
//         for (int i = 0; i < rstatus; ++i)
//           cout << hex << setfill('0') << setw(2) << static_cast<int>(recvmsg[i])
//                << " ";
//         cout << endl;
//         rstatus = recv(new_fd, recvmsg, sizeof(recvmsg), 0);
//       }
//     }
//
//     close(new_fd);
//   }
//
//   close(sock_fd);
// }
