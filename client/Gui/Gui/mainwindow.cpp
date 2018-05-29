#include <QMainWindow>
#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    _connec = false;
    QDate dateTmp = QDate::currentDate();
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->dateEdit->setDate(dateTmp);
    _ptrs["/server"] = std::bind(&MainWindow::funcConnect, this);
    _ptrs["/quit"] = std::bind(&MainWindow::funcQuit, this);
    _ptrs["/nick"] = std::bind(&MainWindow::funcNick, this);
    _ptrs["/list"] = std::bind(&MainWindow::funcList, this);
    _ptrs["/join"] = std::bind(&MainWindow::funcJoin, this);
    _ptrs["/user"] = std::bind(&MainWindow::funcUser, this);
    _ptrs["/users"] = std::bind(&MainWindow::funcUsers, this);
    _ptrs["/part"] = std::bind(&MainWindow::funcPart, this);
    _ptrs["/names"] = std::bind(&MainWindow::funcNames, this);
    _ptrs["/msg"] = std::bind(&MainWindow::funcMsg, this);
    _ptrs["/accept_file"] = std::bind(&MainWindow::funcFile, this);
    connect(ui->btnSend, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::funcUser()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(false));
}

int MainWindow::findPos(char c, QString &str)
{
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == c) {
            return i;
        }
    }
    return -1;
}

QString MainWindow::cutString(int pos, QString &str)
{
    QString tmp;

    for (;pos < str.size(); pos++) {
        tmp += str[pos];
    }
    return tmp;
}

void MainWindow::printUsers(QString &str)
{
    int pos;
    QString token;
    QString res;
    char *tmp;

    ui->clientEdit->clear();
    tmp = strtok(strdup(str.toStdString().c_str()), "\n");
    while (tmp != NULL) {
        token = tmp;
        pos = this->findPos('*', token);
        res = token.toStdString().substr(pos + 3, token.size()).c_str();
        if (!res.contains("End of WHO list."))
            ui->clientEdit->append(res);
        tmp = strtok(NULL, "\n");
        res.clear();
    }
}

void MainWindow::funcUsers()
{
    QString tmp = "/NAMES";

    _socket.write(tmp.toStdString().c_str());
    usleep(30000);
    tmp = _socket.read(true);
    this->printUsers(tmp);
}

void MainWindow::funcPart()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcList()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcNames()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcMsg()
{
    QString tmp = "/PRIVMSG";
    QString cmd = ui->lineMessage->text();
    cmd.remove(0, 4);
    tmp += cmd;
    _socket.write(tmp.toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcFile()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcQuit()
{
    ui->textEdit->append("Disconnect from 127.0.0.1:4242");
    _socket.close();
    exit(0);
}

void MainWindow::funcJoin()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::funcConnect()
{
    if (_socket.isConnect() == false) {
        ui->textEdit->append("Try to connect on 127.0.0.1:4242 . . .");
        if (_socket.connect() == false) {
            ui->textEdit->append("Can't connect to 127.0.0.1:4242");
            return ;
        }
        usleep(30000);
        ui->textEdit->append(_socket.read(true));
        _connec = true;
    } else
        ui->textEdit->append("Already connect");
}

void MainWindow::funcNick()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
    usleep(30000);
    ui->textEdit->append(_socket.read(true));
}

void MainWindow::proceedCmd()
{
    if (_connec == true && _socket.isConnect() == false)
        exit(0);
    for(auto beg = _ptrs.constBegin(); beg != _ptrs.constEnd(); beg++) {
        if (ui->lineMessage->text().contains(beg.key())) {
            beg.value()();
        }
    }
}

void MainWindow::sendMessage()
{
    if (ui->lineMessage->text() != "") {
        ui->textEdit->append(ui->lineMessage->text());
        if (ui->lineMessage->text().at(0) == '/')
            this->proceedCmd();
    }
    ui->lineMessage->clear();
}
