#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDial>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SecondsDial_valueChanged(int);
    void on_MinutesDial_valueChanged(int);
    void on_HoursSlider_valueChanged(int);

    void on_StartStopButton_clicked();

    void update();
private:
    Ui::MainWindow *ui;
    QTimer *updateClock;
};
#endif // MAINWINDOW_H
