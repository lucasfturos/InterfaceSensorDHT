#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <memory>
#include <tuple>

class SerialCommunication : public QObject {
    Q_OBJECT
  public:
    SerialCommunication();

  public slots:
    void serialDataAvalible();

  signals:
    void newDataAvailable(const QByteArray &data);

  public:
    // Variáveis
    bool serialDeviceConnected;
    std::shared_ptr<QSerialPort> serial;

    // Funções
    void serialWrite(QByteArray data);
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();

  private:
    // Variáveis
    QStringList infoBaudList;
    QStringList infoPortList;
    QByteArray serialBuffer;
    std::shared_ptr<QSerialPortInfo> serialInfo;
};

#endif // SERIALCOMMUNICATION_H
