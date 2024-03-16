#ifndef SENSORDHT_HPP
#define SENSORDHT_HPP

#include <QObject>
#include <memory>
#include <src/SerialCommunication/serialcomm.hpp>

class SensorDHT : public QObject {
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double humidity READ humidity NOTIFY humidityChanged)

  public:
    explicit SensorDHT(
        QObject *parent = nullptr,
        std::shared_ptr<SerialCommunication> comSerial = nullptr);

  signals:
    void temperatureChanged(double temperature);
    void humidityChanged(double humidity);

  public:
    void processReceivedData(const QByteArray & /*data*/);

  private:
    double m_temperature;
    double m_humidity;

    std::shared_ptr<SerialCommunication> commSerial;

  public:
    double temperature() const { return m_temperature; }
    double humidity() const { return m_humidity; }
};

#endif // SENSORDHT_HPP
