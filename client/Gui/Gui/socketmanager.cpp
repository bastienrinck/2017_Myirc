#include "socketmanager.h"
#include <QDebug>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

Ui::socketManager::socketManager()
{
    memset(_fds, 0, sizeof(_fds));
    _fds[0].events = POLLIN;
}

Ui::socketManager::~socketManager()
{
    this->close();
}

void Ui::socketManager::close()
{
    ::close(_sock);
    _sock = -1;
}

bool Ui::socketManager::create()
{
        this->create_tcp_socket();
        _fds[0].fd = _sock;
        return (VALID_SOCKET(_sock));
}

bool Ui::socketManager::write(const char *str)
{
    std::string tmp = str;

    tmp.erase(0, 1);
    tmp.push_back('\r');
    return dprintf(_sock, tmp.c_str());
}

bool Ui::socketManager::connect()
{
    struct sockaddr_in sin;

    if (this->create() == false)
        return false;
    memset(&sin, 0, sizeof(sin));
    qDebug() << "je suis dans la fonction connect\n";
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(_port);
    if (::connect(_sock, (sockaddr*)&sin, sizeof(sin)) == -1)
        return (this->printError(__func__, __LINE__, __FILE__));
    return (true);
}

bool Ui::socketManager::create_tcp_socket()
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!VALID_SOCKET(_sock))
          return (this->printError(__func__, __LINE__, __FILE__));
    return (true);
}

QString Ui::socketManager::read()
{
    char buffer[1024 + 1];
    nfds_t nfds = 0;

    int rc = poll(_fds, nfds, -1);
    if (rc < 0)
        _cmd = "Error";
    else if (rc == 0)
        _cmd = "TimeOut";
    else {
        int n = ::read(_sock, buffer, 1024);
        buffer[n] = 0;
        _cmd = buffer;
    }
    return _cmd;
}

bool Ui::socketManager::printError(const char *fname, const int line, const char *filename)
{
        dprintf(2, "Error in %s line %d: %s: %s.\n", filename, line - 1, fname,
                strerror(errno));
        return (false);
}