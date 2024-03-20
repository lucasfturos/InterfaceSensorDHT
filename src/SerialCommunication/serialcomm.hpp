#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <memory>
#include <tuple>

/**
 * @brief Classe para comunicação serial.
 *
 * A classe SerialCommunication fornece funcionalidades para comunicação serial,
 * incluindo leitura e escrita de dados em uma porta serial, detecção de
 * dispositivos seriais disponíveis e sinais/slots para lidar com novos dados
 * recebidos.
 */
class SerialCommunication : public QObject {
    Q_OBJECT
  public:
    /**
     * @brief Construtor da classe SerialCommunication.
     *
     * Inicializa a classe SerialCommunication.
     */
    SerialCommunication();

  public slots:
    /**
     * @brief Slot para lidar com dados seriais recebidos.
     *
     * Este slot é chamado quando novos dados são recebidos na porta serial.
     */
    void serialDataAvalible();

  signals:
    /**
     * @brief Sinal emitido quando novos dados estão disponíveis.
     *
     * Este sinal é emitido quando novos dados são recebidos na porta serial.
     * @param data Os dados recebidos.
     */
    void newDataAvailable(const QByteArray &data);

  public:
    //! Variáveis

    /**
     * @brief Indica se um dispositivo serial está conectado.
     */
    bool serialDeviceConnected;
    /**
     * @brief Objeto compartilhado para a porta serial.
     */
    std::shared_ptr<QSerialPort> serial;

    //! Funções

    /**
     * @brief Escreve dados na porta serial.
     *
     * @param data Os dados a serem escritos.
     */
    void serialWrite(QByteArray data);
    /**
     * @brief Obtém a lista de dispositivos seriais disponíveis.
     *
     * @return Uma tupla contendo duas listas de strings: uma lista de nomes de
     * portas e uma lista de baud rates suportados.
     */
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();

  private:
    //! Variáveis

    /**
     * @brief Lista de baud rates disponíveis.
     */
    QStringList infoBaudList;
    /**
     * @brief Lista de portas disponíveis.
     */
    QStringList infoPortList;
    /**
     * @brief Buffer para armazenar dados recebidos pela porta serial.
     */
    QByteArray serialBuffer;
    /**
     * @brief Informações sobre a porta serial.
     */
    std::shared_ptr<QSerialPortInfo> serialInfo;
};

#endif // SERIALCOMMUNICATION_H
