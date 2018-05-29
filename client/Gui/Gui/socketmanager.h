#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QVector>
#include <QString>

namespace Ui {
    class socketManager {
    public:
        socketManager();
        ~socketManager();
        bool isConnect();
        bool create();
        bool connect();
        bool create_tcp_socket();
        bool printError(const char *fname, const int line, const char *filename);
        bool write(const char *str);
        void close();
        QString read(bool state);

    private:
        struct pollfd fds[1];
        int _sock;
        bool _connect;
        uint16_t _port = 4242;
        char _ip[INET_ADDRSTRLEN];
        struct sockaddr_in _s_in;
        struct sockaddr _s_;
        QVector<size_t> _socket;
        QString _cmd;
    };
}

#define VALID_SOCKET(sck) ((sck) != -1)
#endif // SOCKETMANAGER_H
