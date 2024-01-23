#ifndef CDEVICE_H
#define CDEVICE_H

#include <QObject>

class CDevice : public QObject
{
    Q_OBJECT
public:
    explicit CDevice(QObject *parent = nullptr);
    virtual bool open() = 0;
    virtual bool close() = 0;
signals:

};

#endif // CDEVICE_H
