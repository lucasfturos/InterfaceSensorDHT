#include "serialcomm.hpp"

SerialCommunication::SerialCommunication()
    : serial(std::make_shared<QSerialPort>()),
      serialInfo(std::make_shared<QSerialPortInfo>()) {}

std::tuple<QStringList, QStringList>
SerialCommunication::getAvalilableSerialDevice() {
    qDebug() << "Número de portas disponiveis: "
             << serialInfo->availablePorts().length();

    infoBaudList << "";
    infoPortList << "";
    foreach (const QSerialPortInfo &listInfo, serialInfo->availablePorts()) {
        QString dbgString;
        dbgString += "Nome: " + listInfo.portName();
        qDebug() << dbgString;
        infoPortList.push_back(listInfo.portName());
    }

    const QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();
    for (const qint32 baudRate : baudRates) {
        infoBaudList.push_back(QString::number(baudRate));
    }

    return std::make_tuple(infoPortList, infoBaudList);
}

void SerialCommunication::serialWrite(QByteArray data) {
    if (serialDeviceConnected == true) {
        qDebug() << "Enviando: " << data;
        // Manda a escrita para o dispositivo
        serial->write(data);
        serial->flush();
        qDebug() << "Dados enviados.";
    }
}

void SerialCommunication::serialDataAvalible() {
    if (serialDeviceConnected == true) {
        // Lê todos os dados disponíveis na porta serial
        QByteArray data = serial->readAll();
        // Adiciona os dados lidos ao buffer
        serialBuffer.append(data);

        // Verifica se há uma mensagem completa no buffer
        while (serialBuffer.contains('\n')) {
            // Encontra a posição do primeiro '\n'
            int newlinePos = serialBuffer.indexOf('\n');
            // Extrai a mensagem até o primeiro '\n'
            QByteArray message = serialBuffer.left(newlinePos + 1);
            // Remove a mensagem do buffer
            serialBuffer.remove(0, newlinePos + 1);

            // Emite o sinal com a mensagem completa
            qDebug() << "Recebido: " << message;
            emit newDataAvailable(message);
        }
    }
}
