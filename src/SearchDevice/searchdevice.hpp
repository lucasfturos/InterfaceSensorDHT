#ifndef SEARCHDEVICE_HPP
#define SEARCHDEVICE_HPP

#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <src/SerialCommunication/serialcomm.hpp>

class SearchDevice : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList portList READ portList NOTIFY portListChanged)
    Q_PROPERTY(QStringList baudList READ baudList NOTIFY baudListChanged)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStatusChanged)
    Q_PROPERTY(QString statusConnection READ statusConnection NOTIFY
                   statusConnectionChanged)

  public:
    explicit SearchDevice(
        QObject *parent = nullptr,
        std::shared_ptr<SerialCommunication> comSerial = nullptr);

  signals:
    void portListChanged();
    void baudListChanged();
    void statusConnectionChanged();
    void connectionStatusChanged();

  public slots:
    void connectDevice(const QString &selectedPort,
                       const QString &selectedBaud);
    void disconnectDevice(const QString &selectedPort);

  private:
    QStringList m_baudList;
    QStringList m_portList;
    QString m_statusConnection;

    void setupSerial();

    std::shared_ptr<SerialCommunication> commSerial;

  public:
    const QStringList &portList() const { return m_portList; }
    const QStringList &baudList() const { return m_baudList; }
    QString statusConnection() const { return m_statusConnection; }
    bool isConnected() const { return commSerial->serialDeviceConnected; }
};

#endif // SEARCHDEVICE_HPP
