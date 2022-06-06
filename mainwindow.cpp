#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "parcer.h"
#include "dialog.h"

using namespace std;

Parcer parc;
QString directory;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    directory = QFileDialog::getExistingDirectory(this, "Выбор директории с csv");
    if (directory.size() == 0){
        ui->ANCER->setText("Ошибка чтения файлов");
    }
    if (!parc.initDatabase(directory)){
        ui->ANCER->setText("Ошибка чтения файлов");
    }
    ui->ANCER->setText("");
    ui->pbcosts->setEnabled(true);
    ui->pbcaffe->setEnabled(true);
    ui->pbinst->setEnabled(true);
    ui->pbtrans->setEnabled(true);
    ui-> pushButton_2 ->setEnabled(true);
}



void MainWindow::on_pbcalc_clicked()
{
    int age = stoi(ui-> lineage -> text().toStdString()) ;
    string city = ui-> linecity ->text().toStdString();
    string address = ui-> lineaddress ->text().toStdString();
    string institute = ui-> lineinst ->text().toStdString();
    bool ageCost = ui->radioButton->isChecked();
    string cafe = ui-> linecafy ->text().toStdString();
    string cinema = ui-> linecinema ->text().toStdString();

    if (ageCost){
        int sum;
        sum = parc.getCosts(city, address, institute, cinema, cafe, age);
        QString Ancer = QString::number(sum);
        ui -> ANCER -> setText(Ancer);
    }
    else{
        int sum;
        sum = parc.getCosts(city, address, institute, cinema, cafe, age);
        sum -= parc.getOtherMontlyCosts(city, age);
        QString Ancer = QString::number(sum);
        ui -> ANCER -> setText(Ancer);
    }
}

void MainWindow::on_pbcaffe_clicked()
{
   Dialog f(this, parc.caffy, 0, parc, directory);
   f.exec();
   ui -> pbcaffe -> setEnabled(0);
}


void MainWindow::on_pbinst_clicked()
{
    Dialog f(this, parc.inst, 1, parc, directory);
    f.exec();
    ui -> pbinst -> setEnabled(0);
}

void MainWindow::on_pbtrans_clicked()
{
    Dialog f(this, parc.transport, 3, parc, directory);
    f.exec();
    ui -> pbtrans -> setEnabled(0);
}


void MainWindow::on_pbcosts_clicked()
{
    Dialog f(this, parc.costs, 2, parc, directory);
    f.exec();
    ui -> pbcosts -> setEnabled(0);
}


void MainWindow::on_pushButton_2_clicked()
{
    parc.caffy.clear();
    parc.costs.clear();
    parc.inst.clear();
    parc.transport.clear();
    parc.initDatabase(directory);
    ui->pbcosts->setEnabled(true);
    ui->pbcaffe->setEnabled(true);
    ui->pbinst->setEnabled(true);
    ui->pbtrans->setEnabled(true);
}

