// #include <arpa/inet.h>
// #include <asm-generic/socket.h>
// #include <cstdio>
// #include <iostream>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <string>
// #include <sys/poll.h>
// #include <sys/socket.h>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <vector>
//
// using namespace std;
// const string PORT = "6969";
//
// int get_listening_socket() noexcept {
//   addrinfo hints{};
//   addrinfo *server_info{};
//
//   hints.ai_family = AF_UNSPEC;
//   hints.ai_socktype = SOCK_STREAM;
//   hints.ai_flags = AI_PASSIVE;
//
//   int get_addr_status = getaddrinfo(NULL, PORT.data(), &hints, &server_info);
//   if (get_addr_status == -1) {
//     cerr << "getaddrinfo: " << gai_strerror(get_addr_status) << endl;
//     return -1;
//   }
//
//   int sock_fd;
//   addrinfo *p;
//   for (p = server_info; p != NULL; p = p->ai_next) {
//     sock_fd = socket(server_info->ai_family, server_info->ai_socktype,
//                      server_info->ai_protocol);
//     if (sock_fd < 0) {
//       continue;
//     }
//
//     int yes = 1;
//     int sock_opt_status =
//         setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
//     if (sock_opt_status == -1) {
//       perror("setsockopt");
//       continue;
//     }
//
//     int bind_status = bind(sock_fd, p->ai_addr, p->ai_addrlen);
//     if (bind_status == -1) {
//       close(sock_fd);
//       continue;
//     }
//
//     // break on first socket connection
//     break;
//   }
//
//   // if code gets here, this means that bind failed
//   if (p == NULL) {
//     return -1;
//   }
//
//   freeaddrinfo(server_info);
//
//   if (listen(sock_fd, 10) == -1) {
//     return -1;
//   }
//
//   return sock_fd;
// }
//
// void *get_in_addr(sockaddr *sa) {
//   if (sa->sa_family == AF_INET) {
//     return &((sockaddr_in *)sa)->sin_addr;
//   }
//
//   return &((sockaddr_in6 *)sa)->sin6_addr;
// }
//
// int main(int argc, char *argv[]) {
//   string hostname = "";
//   if (gethostname(hostname.data(), INET6_ADDRSTRLEN) == -1) {
//     cerr << "coouldn't get hostname" << endl;
//   }
//   vector<pollfd> pfds{};
//   int listener = get_listening_socket();
//   if (listener == -1) {
//     cerr << "get_listening_socket" << endl;
//     exit(1);
//   }
//
//   pfds.push_back({listener, POLLIN, 0});
//
//   while (true) {
//     const int TIMEOUT = 5 * 1000;
//     int num_events = poll(pfds.data(), pfds.size(), TIMEOUT);
//
//     if (num_events == -1) {
//       perror("poll");
//       exit(1);
//     }
//
//     // optimization: switch from iterators to indicies
//     for (auto it = pfds.begin(); it != pfds.end(); /* leave this empty */) {
//       pollfd pfd = *it;
//       // check if someone is ready to read
//       if (pfd.revents & (POLLIN | POLLHUP)) {
//
//         // check if current polled fd is the same fd for listener sock_fd
//         if (pfd.fd == listener) {
//           // accept a new connection
//           sockaddr_storage connector{};
//           socklen_t addrlen = sizeof(connector);
//           int new_fd = accept(
//               listener, reinterpret_cast<sockaddr *>(&connector), &addrlen);
//           if (new_fd == -1) {
//             perror("accept");
//           } else {
//             pfds.emplace_back(pollfd{new_fd, POLLIN, 0});
//             string connecting_ip = "";
//             inet_ntop(connector.ss_family,
//                       get_in_addr(reinterpret_cast<sockaddr *>(&connector)),
//                       connecting_ip.data(), INET6_ADDRSTRLEN);
//             cout << hostname.data()
//                  << " resolved a connection from: " << connecting_ip.data()
//                  << " on socket: " << new_fd << endl;
//
//             // modifying vector elements invalidates iterator
//             break;
//           }
//         } else {
//           // poll received from a client socket
//           char buf[256];
//           int recv_bytes = recv(pfd.fd, buf, sizeof(buf) - 1, 0);
//           cout << "Received message from socket " << pfd.fd << " of size "
//                << recv_bytes << endl;
//
//           if (recv_bytes <= 0) {
//             // if recv_bytes == 0, connection closed on us
//             if (recv_bytes == 0) {
//               cout << "Connection closed on " << pfd.fd << endl;
//             } else {
//               perror("recv");
//             }
//
//             close(pfd.fd);
//
//             // moves it to the next element in pfds
//             it = pfds.erase(it);
//             continue;
//           } else {
//             // socket sent valid data
//             buf[recv_bytes] = '\0';
//             cout << buf << endl;
//           }
//         }
//       }
//       ++it;
//     }
//   }
// }
