#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "socketmanager.h"
#include <functional>
#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void sendMessage();
     void proceedCmd();
     void funcConnect();
     void funcQuit();
     void funcJoin();
     void funcNick();
     void funcUsers();
     void funcPart();
     void funcNames();
     void funcMsg();
     void funcFile();
     void funcUser();
     void funcList();
     int findPos(char c, QString &str);
     QString cutString(int pos, QString &str);
     void printUsers(QString &str);

private:

     bool _connec;
     size_t _serverSocket;
     QMap<QString, std::function<void()>> _ptrs;
     Ui::MainWindow *ui;
     Ui::socketManager _socket;
};

#endif // MAINWINDOW_H
