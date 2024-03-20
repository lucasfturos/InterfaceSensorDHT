#include "sensordht.hpp"

SensorDHT::SensorDHT(QObject *parent,
                     std::shared_ptr<SerialCommunication> comSerial)
    : QObject(parent), commSerial(comSerial), m_temperature(0.0),
      m_humidity(0.0) {
    connect(commSerial.get(), &SerialCommunication::newDataAvailable, this,
            &SensorDHT::processReceivedData);
}

void SensorDHT::processReceivedData(const QByteArray &data) {
    QString bufferData(data);

    int humidityIndex = bufferData.indexOf("H");
    int temperatureIndex = bufferData.indexOf("T");

    if (humidityIndex != -1 && temperatureIndex != -1) {
        QString strHumidity = bufferData.mid(humidityIndex + 1, 5);
        QString strTemperature = bufferData.mid(temperatureIndex + 1, 5);

        bool conversionOk;
        double humidity = strHumidity.toDouble(&conversionOk);
        if (!conversionOk) {
            qDebug() << "Erro ao converter umidade para double";
            return;
        }

        double temperature = strTemperature.toDouble(&conversionOk);
        if (!conversionOk) {
            qDebug() << "Erro ao converter temperatura para double";
            return;
        }

        m_temperature = qCeil(temperature * 10) / 10.0;
        m_humidity = qCeil(humidity * 10) / 10.0;

        emit temperatureChanged(m_temperature);
        emit humidityChanged(m_humidity);
    } else {
        qDebug()
            << "Índices de umidade ou temperatura não encontrados nos dados";
    }
}
