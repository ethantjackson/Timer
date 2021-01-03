#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

int secondsVal = 0;
int minutesVal = 0;
int hoursVal = 0;

bool running = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateClock = new QTimer(this);
    connect(updateClock, SIGNAL(timeout()), this, SLOT(update()));
    updateClock->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SecondsDial_valueChanged(int dialVal)
{
    secondsVal = dialVal;
    if (secondsVal >= 10) {
        ui->SecondsLabel->setText(QString::number(secondsVal));
    } else {
        ui->SecondsLabel->setText('0'+QString::number(secondsVal));
    }
}


void MainWindow::on_MinutesDial_valueChanged(int dialVal)
{
    minutesVal = dialVal;
    if (minutesVal >= 10) {
        ui->MinutesLabel->setText(QString::number(minutesVal));
    } else {
        ui->MinutesLabel->setText('0'+QString::number(minutesVal));
    }
}

void MainWindow::on_HoursSlider_valueChanged(int sliderVal)
{
    hoursVal = sliderVal;
    if (hoursVal >= 10) {
        ui->HoursLabel->setText(QString::number(hoursVal));
    } else {
        ui->HoursLabel->setText('0'+QString::number(hoursVal));
    }
}


void MainWindow::on_StartStopButton_clicked()
{
    if (running == false) {
        running = true;
        ui->StartStopButton->setText("STOP");
        ui->StartStopButton->setStyleSheet("* { color: red }");
    }
    else {
        running = false;
        ui->StartStopButton->setText("START");
        ui->StartStopButton->setStyleSheet("* { color: green }");
    }
//    qDebug() << running << secondsVal << ' ' << minutesVal << ' ' << hoursVal;
}

void MainWindow::update() {
    if (secondsVal == 0 && minutesVal == 0 && hoursVal == 0) {
        running = false;
        ui->StartStopButton->setText("START");
        ui->StartStopButton->setStyleSheet("* { color: green }");
    }
    if (running) {
        if (secondsVal % 2 == 0) {
            ui->ColonLabel1->setText(" ");
            ui->ColonLabel2->setText(" ");
        } else {
            ui->ColonLabel1->setText(":");
            ui->ColonLabel2->setText(":");
        }
        if (secondsVal > 0) {
            --secondsVal;
            ui->SecondsDial->setValue(secondsVal);
            on_SecondsDial_valueChanged(secondsVal);
        } else if (minutesVal > 0) {
            secondsVal = 59;
            ui->SecondsDial->setValue(secondsVal);
            on_SecondsDial_valueChanged(secondsVal);
            --minutesVal;
            ui->MinutesDial->setValue(minutesVal);
            on_MinutesDial_valueChanged(minutesVal);
        } else {
            secondsVal = 59;
            ui->SecondsDial->setValue(secondsVal);
            on_SecondsDial_valueChanged(secondsVal);
            minutesVal = 59;
            ui->MinutesDial->setValue(minutesVal);
            on_MinutesDial_valueChanged(minutesVal);
            --hoursVal;
            ui->HoursSlider->setValue(hoursVal);
            on_HoursSlider_valueChanged(hoursVal);
        }
    }
}
