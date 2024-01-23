#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>


class CSerialport : public QObject
{
    Q_OBJECT
public:
    static CSerialport* getInstance(); // 获取类实例的静态函数

    bool open(QString portName, int baudRate); // 打开串口
    void close(); // 关闭串口
    void sendMessage(const QString& message); // 发送消息
    QMap<QString, QString> getAvailablePorts(); // 获取可用串口列表

signals:
    void dataReceived(const QString& data); // 数据接收信号

private:
    explicit CSerialport(QObject *parent = nullptr); // 构造函数
    ~CSerialport(); // 析构函数
    void startReceiving(); // 开始接收数据
    QSerialPort m_serialPort; // 串口对象
};

#endif // CSERIALPORT_H
