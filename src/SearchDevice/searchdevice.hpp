#ifndef SEARCHDEVICE_HPP
#define SEARCHDEVICE_HPP

#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <src/SerialCommunication/serialcomm.hpp>

/**
 * @brief Classe para busca e gerenciamento de dispositivos seriais.
 *
 * A classe SearchDevice fornece funcionalidades para buscar e gerenciar os
 * dispositivos conectados, incluindo a detecção de portas seriais disponíveis,
 * conexão e desconexão de dispositivos, e fornecimento de informações sobre o
 * status da conexão.
 */
class SearchDevice : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList portList READ portList NOTIFY portListChanged)
    Q_PROPERTY(QStringList baudList READ baudList NOTIFY baudListChanged)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionChanged)
    Q_PROPERTY(QString statusConnection READ statusConnection NOTIFY
                   statusConnectionChanged)

  public:
    /**
     * @brief Construtor da classe SearchDevice.
     *
     * Inicializa a classe SearchDevice com a comunicação serial especificada.
     * @param parent O objeto pai.
     * @param comSerial A instância compartilhada de SerialCommunication.
     */
    explicit SearchDevice(
        QObject *parent = nullptr,
        std::shared_ptr<SerialCommunication> comSerial = nullptr);

  signals:
    /**
     * @brief Sinal emitido quando a lista de portas disponíveis é alterada.
     */
    void portListChanged();
    /**
     * @brief Sinal emitido quando a lista de baud rates disponíveis é alterada.
     */
    void baudListChanged();
    /**
     * @brief Sinal emitido quando o status da conexão é alterado.
     */
    void statusConnectionChanged();
    /**
     * @brief Sinal emitido quando o status da conexão é alterado.
     */
    void connectionChanged();

  public slots:
    /**
     * @brief Conecta um dispositivo serial à porta e à taxa de baud rate
     * especificadas.
     *
     * @param selectedPort A porta selecionada para conexão.
     * @param selectedBaud A taxa de baud rate selecionada para conexão.
     */
    void connectDevice(const QString &selectedPort,
                       const QString &selectedBaud);
    /**
     * @brief Desconecta o dispositivo serial da porta especificada.
     *
     * @param selectedPort A porta selecionada para desconexão.
     */
    void disconnectDevice(const QString &selectedPort);

  private:
    //! Variáveis

    /**
     * @brief Lista de baud rates disponíveis.
     */
    QStringList m_baudList;
    /**
     * @brief Lista de portas disponíveis.
     */
    QStringList m_portList;
    /**
     * @brief Status da conexão.
     */
    QString m_statusConnection;
    /**
     * @brief Instância compartilhada de SerialCommunication.
     */
    std::shared_ptr<SerialCommunication> commSerial;

    //! Funções privadas

    /**
     * @brief Configuração inicial da comunicação serial.
     *
     * Esta função inicializa a comunicação serial, obtém a lista de portas e
     * baud rates disponíveis, e conecta os sinais dos botões da interface de
     * usuário aos slots correspondentes nesta classe.
     */
    void setupSerial();

  public:
    //! Métodos de acesso

    /**
     * @brief Retorna a lista de portas disponíveis.
     * @return A lista de portas disponíveis.
     */
    const QStringList &portList() const { return m_portList; }
    /**
     * @brief Retorna a lista de baud rates disponíveis.
     * @return A lista de baud rates disponíveis.
     */
    const QStringList &baudList() const { return m_baudList; }
    /**
     * @brief Retorna o status da conexão.
     * @return O status da conexão.
     */
    QString statusConnection() const { return m_statusConnection; }
    /**
     * @brief Verifica se um dispositivo está conectado.
     * @return true se um dispositivo está conectado, false caso contrário.
     */
    bool isConnected() const { return commSerial->serialDeviceConnected; }
};

#endif // SEARCHDEVICE_HPP
