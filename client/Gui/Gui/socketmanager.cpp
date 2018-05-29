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
    _connect = false;
}

Ui::socketManager::~socketManager()
{
    this->close();
}

bool Ui::socketManager::isConnect()
{
    if (_sock == -1)
        _connect = false;
    return _connect;
}

void Ui::socketManager::close()
{
    shutdown(_sock, 0);
    //::close(_sock);
    _sock = -1;
}

bool Ui::socketManager::create()
{
    this->create_tcp_socket();
    return (VALID_SOCKET(_sock));
}

bool Ui::socketManager::write(const char *str)
{
    std::string tmp = str;

    tmp.erase(0, 1);
    qDebug() << tmp.c_str();
    tmp += "\r\n";
    ::send(_sock, tmp.c_str(), tmp.size(), 0);
    return true;
}

bool Ui::socketManager::connect()
{
    struct sockaddr_in sin;

    if (this->create() == false)
        return false;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(_port);
    if (::connect(_sock, (sockaddr*)&sin, sizeof(sin)) == -1)
        return (this->printError(__func__, __LINE__, __FILE__));
    _connect = true;
    return (true);
}

bool Ui::socketManager::create_tcp_socket()
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!VALID_SOCKET(_sock))
          return (this->printError(__func__, __LINE__, __FILE__));
    return (true);
}

QString Ui::socketManager::read(bool state)
{
    int n = 0;
    char buffer[4096 + 1] = {0};
    nfds_t nfds = 1;

    _cmd.clear();
    this->fds[0].events = POLLIN;
    this->fds[0].fd = _sock;
    int rc = poll(fds, nfds, 1000);
    if (rc < 0)
        _cmd = "Error";
    else if (rc == 0)
        _cmd = "TimeOut";
    else {
            n = ::read(_sock, buffer, 4096);
            buffer[n] = 0;
            _cmd = buffer;
            memset(buffer, 0, sizeof(buffer));
    }
    if (!state)
        _cmd.clear();
    if (poll(fds, nfds, 500) > 0) {
        n = ::read(_sock, buffer, 4096);
        buffer[n] = 0;
        _cmd += buffer;
    }
    return _cmd;
}

bool Ui::socketManager::printError(const char *fname, const int line, const char *filename)
{
        dprintf(2, "Error in %s line %d: %s: %s.\n", filename, line - 1, fname,
                strerror(errno));
        return (false);
}
