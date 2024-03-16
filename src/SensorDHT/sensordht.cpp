#include "sensordht.hpp"

SensorDHT::SensorDHT(QObject *parent,
                     std::shared_ptr<SerialCommunication> comSerial)
    : QObject(parent), commSerial(comSerial), m_temperature(0.0),
      m_humidity(0.0) {
    connect(commSerial.get(), &SerialCommunication::newDataAvailable, this,
            &SensorDHT::processReceivedData);
}

void SensorDHT::processReceivedData(const QByteArray &data) {
    QString dataString(data);

    int humidityIndex = dataString.indexOf("H");
    int temperatureIndex = dataString.indexOf("T");

    if (humidityIndex != -1 && temperatureIndex != -1) {
        QString humidityString = dataString.mid(humidityIndex + 1, 5);
        QString temperatureString = dataString.mid(temperatureIndex + 1, 5);

        bool conversionOk;
        double humidity = humidityString.toDouble(&conversionOk);
        if (!conversionOk) {
            qDebug() << "Erro ao converter umidade para double";
            return;
        }

        double temperature = temperatureString.toDouble(&conversionOk);
        if (!conversionOk) {
            qDebug() << "Erro ao converter temperatura para double";
            return;
        }

        m_temperature = temperature;
        m_humidity = humidity;

        emit temperatureChanged(m_temperature);
        emit humidityChanged(m_humidity);
    } else {
        qDebug() << "Índices de umidade ou temperatura não encontrados na "
                    "string de dados";
    }
}
