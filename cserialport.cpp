#include "cserialport.h"
#include "qdebug.h"

CSerialport::CSerialport(QObject *parent)
    : QObject(parent)
{
    // 当串口有数据可读时，连接到 startReceiving() 槽函数
    connect(&m_serialPort, &QSerialPort::readyRead, this, &CSerialport::startReceiving);
}

CSerialport::~CSerialport()
{
    // 析构函数为空
}

CSerialport* CSerialport::getInstance()
{
    static CSerialport instance; // 静态局部变量，保证只创建一个实例
    return &instance;
}


bool CSerialport::open(QString portName, int baudRate)
{
    m_serialPort.setPortName(portName); // 设置串口名
    m_serialPort.setBaudRate(baudRate); // 设置波特率
    if (!m_serialPort.open(QIODevice::ReadWrite))
    {
        // 串口打开失败
        return false;
    }
    else
    {
        // 串口打开成功
        return true;
    }
}

void CSerialport::close()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close(); // 关闭串口
    }
}

void CSerialport::startReceiving()
{
    if (m_serialPort.isOpen())
    {
        QString data = m_serialPort.readAll(); // 读取串口接收到的数据
        qDebug() << data;
        emit dataReceived(data); // 发出数据接收信号，通知其他对象
    }
}

void CSerialport::sendMessage(const QString& message)
{
    m_serialPort.write(message.toUtf8()); // 向串口写入数据
}

QMap<QString, QString> CSerialport::getAvailablePorts()
{
    close(); // 关闭串口

    auto portsInfo = QSerialPortInfo::availablePorts(); // 获取可用串口信息列表
    QMap<QString, QString> map;

    // 遍历可用串口信息
    for (const auto& info : portsInfo)
    {
        qInfo() << info.description() << info.portName() << info.systemLocation();
        // 将串口名和描述信息添加到映射中
        map.insert(info.portName(), info.description());
    }

    return map; // 返回串口名和描述信息的映射
}
