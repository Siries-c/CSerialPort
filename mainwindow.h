#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cserialport.h"
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QTimer>
#include<QComboBox>
#include<QFileDialog>
#include<QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CSerialport *csp = nullptr;
    void init();
    void initPorts();
private:

private slots:
    void showMessage(QString dataStr);
    void on_m_btn_open_clicked();

    void on_m_btn_fresh_clicked();

    void on_m_btn_send_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;

};
#endif // MAINWINDOW_H
