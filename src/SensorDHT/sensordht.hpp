#ifndef SENSORDHT_HPP
#define SENSORDHT_HPP

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <memory>
#include <src/SerialCommunication/serialcomm.hpp>

class SensorDHT : public QObject {
    Q_OBJECT
    Q_PROPERTY(double humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(bool isConnectedServer READ isConnectedServer NOTIFY
                   isConnectedServerChanged)

  public:
    explicit SensorDHT(
        QObject *parent = nullptr,
        std::shared_ptr<SerialCommunication> comSerial = nullptr);

  signals:
    void humidityChanged(double humidity);
    void temperatureChanged(double temperature);
    void isConnectedServerChanged(bool isConnected);

  public slots:
    void onServerReceivedData(QNetworkReply *reply);
    void onSerialReceivedData(const QByteArray & /*data*/);

  private:
    double m_humidity;
    double m_temperature;
    bool m_isConnectedServer;

    std::shared_ptr<SerialCommunication> commSerial;
    std::shared_ptr<QNetworkAccessManager> m_networkManager;

  public:
    double humidity() const { return m_humidity; }
    double temperature() const { return m_temperature; }
    bool isConnectedServer() const { return m_isConnectedServer; }

    void fetchDataFromServer();
};

#endif // SENSORDHT_HPP
