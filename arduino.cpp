#include "arduino.h"
#include<QDebug>
Arduino::Arduino()
{

}

int Arduino::connect_arduino()
{
    foreach(const QSerialPortInfo &serial_port_info , QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id)
            {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is:" << arduino_port_name;
    if(arduino_is_available==true)
    {
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl((QSerialPort::NoFlowControl));
            return 0;
        }
        return 1;
    }
    return (-1);
}
int Arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}

int Arduino::write_to_arduino(QString d)
{

    QByteArray donnee = d.toUtf8();
    if(serial->isWritable())
    {
        serial->write(donnee);
    }
    else
    {
        qDebug() << "couldn't write to serial !";
    }
}
QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable())
    {
        data=serial->readAll();
        return data;
    }
}
QSerialPort * Arduino::getserial()
{
    return serial;
}
QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}
