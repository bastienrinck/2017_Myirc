#include <QMainWindow>
#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QDate dateTmp = QDate::currentDate();
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->dateEdit->setDate(dateTmp);
    _ptrs["/server"] = std::bind(&MainWindow::funcConnect, this);
    _ptrs["/quit"] = std::bind(&MainWindow::funcQuit, this);
    _ptrs["/nick"] = std::bind(&MainWindow::funcNick, this);
    _ptrs["/join"] = std::bind(&MainWindow::funcJoin, this);
    _ptrs["/users"] = std::bind(&MainWindow::funcUsers, this);
    _ptrs["/part"] = std::bind(&MainWindow::funcPart, this);
    _ptrs["/names"] = std::bind(&MainWindow::funcNames, this);
    _ptrs["/msg"] = std::bind(&MainWindow::funcMsg, this);
    _ptrs["/accept_file"] = std::bind(&MainWindow::funcFile, this);
    connect(ui->btnSend, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete &_socket;
    delete ui;
}

void MainWindow::funcUsers()
{

}

void MainWindow::funcPart()
{

}

void MainWindow::funcNames()
{

}

void MainWindow::funcMsg()
{

}

void MainWindow::funcFile()
{

}


void MainWindow::funcQuit()
{
    _socket.close();
    exit(0);
}

void MainWindow::funcJoin()
{
    _socket.write(ui->lineMessage->text().toStdString().c_str());
}

void MainWindow::funcConnect()
{
    ui->textEdit->append("Try to connect on 127.0.0.1:4242 . . .");
    if (_socket.connect() == false)
        return ;
    usleep(30000);
    ui->textEdit->append(_socket.read());
}

void MainWindow::funcNick()
{
    QString tmp = ui->lineMessage->text();

    //tmp.remove(0, 1);
    _socket.write(tmp.toStdString().c_str());
    ui->textEdit->append(_socket.read());
}

void MainWindow::proceedCmd()
{
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
