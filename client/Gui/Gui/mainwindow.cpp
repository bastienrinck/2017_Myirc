#include "mainwindow.h"
#include <QTime>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QDate dateTmp = QDate::currentDate();
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->dateEdit->setDate(dateTmp);
    connect(ui->btnSend, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    qDebug() << ui->lineMessage->text() << "\n";
    if (ui->lineMessage->text() != "") {
        ui->textEdit->append(ui->lineMessage->text());
        ui->lineMessage->clear();
    }
}
