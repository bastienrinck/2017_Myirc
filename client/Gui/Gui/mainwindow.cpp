#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    connect(ui->btnSend, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    qDebug() << ui->lineMessage->text() << "\n";
    ui->textEdit->append(ui->lineMessage->text());
    ui->lineMessage->clear();
}
