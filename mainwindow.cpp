#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    csp = new CSerialport();
    csp = CSerialport::getInstance();
    init();
    connect(csp, &CSerialport::dataReceived, this, &MainWindow::showMessage);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //获取所有可用的串口
    initPorts();

    //设置停止位
    ui->stopBitsCmd->addItem("1",QSerialPort::OneStop);
    ui->stopBitsCmd->addItem("1.5",QSerialPort::OneAndHalfStop);
    ui->stopBitsCmd->addItem("2",QSerialPort::TwoStop);

    //设置数据位
    ui->dataCmd->addItem("5",QSerialPort::Data5);
    ui->dataCmd->addItem("6",QSerialPort::Data6);
    ui->dataCmd->addItem("7",QSerialPort::Data7);
    ui->dataCmd->addItem("8",QSerialPort::Data8);
    ui->dataCmd->setCurrentText("8");

    //设置校验位
    ui->parityCmd->addItem("None",QSerialPort::NoParity);
    ui->parityCmd->addItem("Even",QSerialPort::EvenParity);
    ui->parityCmd->addItem("Odd",QSerialPort::OddParity);


}

void MainWindow::initPorts()
{
    ui->portsCmd->clear();
    // 调用 csp->fresh() 获取最新的串口列表
    QMap<QString,QString> portsMap = csp->getAvailablePorts();

    // 添加串口信息到下拉框选项
    // 使用迭代器遍历键值对
    QMap<QString, QString>::const_iterator iter;
    for (iter = portsMap.constBegin(); iter != portsMap.constEnd(); ++iter) {
        QString portName = iter.key(); // 获取键
        QString portDesc = iter.value(); // 获取值
        ui->portsCmd->addItem(portName+":"+portDesc, portName);
        qDebug() << "portName:" << portName << ", portDesc:" << portDesc;
    }


    ui->baudrateCmd->clear();
    // 获取标准的波特率
    auto baudRates = QSerialPortInfo::standardBaudRates();
    for(auto br : baudRates)
    {
        ui->baudrateCmd->addItem(QString::number(br),br);
    }
    ui->baudrateCmd->setCurrentText("9600");
}



void MainWindow::on_m_btn_open_clicked()
{
    //从界面获取串口的初始信息，串口号，波特率
    // 获取串口名
    QString portName = ui->portsCmd->currentData().toString();
    // 获取波特率
    auto baudRate = ui->baudrateCmd->currentData().value<QSerialPort::BaudRate>();

    qDebug() << portName << baudRate;
    //检测当前选择的串口是否被打开
    if(csp->open(portName,baudRate))
    {
        //如果打开了，则提示
        QMessageBox::information(nullptr, "连接成功", "成功连接到服务器！");
        ui->m_btn_open->setText("关闭串口");
    }
    else
    {
        //提示打开成功或失败
        int result = QMessageBox::question(this, "询问", "串口已经打开，您要关闭吗？", QMessageBox::Yes | QMessageBox::No);
        //继续打开的操作
        if (result == QMessageBox::Yes)
        {
//            qDebug()<<"211";
            csp->close();
            ui->m_btn_open->setText("打开串口");
        }
        else
        {
            return;
        }
    }
}


void MainWindow::on_m_btn_fresh_clicked()
{
    // 串口列表
    initPorts();
}


void MainWindow::on_m_btn_send_clicked()
{
        auto datastr = ui->sendEdit->toPlainText() + (ui->sendNewLineChx->isChecked() ? "\r\n":"");
                csp->sendMessage(datastr);
}




void MainWindow::showMessage(QString dataStr)
{

ui->recvEdit->appendPlainText(dataStr);


}
