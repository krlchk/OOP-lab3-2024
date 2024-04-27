#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    if (thread)
    {
        thread->terminate();
        delete thread;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open text file"), "", tr("Text Files (*.txt)"));
    ui->label->setText(fileName);
    ui->listWidget->clear();
    if (thread)
    {
        thread->terminate();
        delete thread;
    }
    thread = new CalculationThread(fileName, ui->checkBox->isChecked());
    thread->start();
    thread->wait();
    for (auto& item : thread->getFrMap())
    {
        ui->listWidget->addItem(QString::fromStdString(item.first) + " - " + QString::fromStdString(std::to_string(item.second)));
    }
}
