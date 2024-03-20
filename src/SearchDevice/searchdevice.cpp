#include "searchdevice.hpp"

SearchDevice::SearchDevice(QObject *parent,
                           std::shared_ptr<SerialCommunication> comSerial)
    : QObject(parent), commSerial(comSerial) {
    setupSerial();
}

void SearchDevice::setupSerial() {
    commSerial->serial = std::make_shared<QSerialPort>();
    std::tie(m_portList, m_baudList) = commSerial->getAvalilableSerialDevice();

    QObject::connect(commSerial->serial.get(), &QSerialPort::readyRead, this,
                     [=]() { commSerial->serialDataAvalible(); });

    QObject *rootObject = qobject_cast<QObject *>(parent());
    if (!rootObject) {
        qDebug() << "Parent QObject not found.";
        return;
    }

    // Encontra os botões pelos seus ids
    QObject *btnConnect = rootObject->findChild<QObject *>("btnConnect");
    QObject *btnDisconnect = rootObject->findChild<QObject *>("btnDisconnect");

    // Conecta os slots aos sinais dos botões
    if (btnConnect && btnDisconnect) {
        connect(btnConnect, SIGNAL(clicked()), this,
                SLOT(onConnectButtonClicked()));
        connect(btnDisconnect, SIGNAL(clicked()), this,
                SLOT(onDisconnectButtonClicked()));
    } else {
        qDebug() << "Buttons not found.";
    }

    commSerial->serialDeviceConnected = false;
}

// Ação para conectar com o dispositivo
void SearchDevice::connectDevice(const QString &selectedPort,
                                 const QString &selectedBaud) {
    // Mostra as portas USBs disponíveis
    commSerial->serial->setPortName(selectedPort.toUtf8());
    // commSerial->serial->setPortName("/dev/pts/1"); // Porta virtual de
    // testes
    qDebug() << "Se conectando com a porta: " << selectedPort;

    // Caso tenha escolhido a porta tal, realiza a conexão
    if (commSerial->serial->open(QIODevice::ReadWrite)) {
        if (!commSerial->serial->setBaudRate(selectedBaud.toInt())) {
            qDebug() << "Conectado com taxa de transmissão de "
                     << selectedBaud.toInt();
            qDebug() << commSerial->serial->errorString();
        }
        if (!commSerial->serial->setDataBits(QSerialPort::Data8)) {
            qDebug() << commSerial->serial->errorString();
        }
        if (!commSerial->serial->setParity(QSerialPort::NoParity)) {
            qDebug() << commSerial->serial->errorString();
        }
        if (!commSerial->serial->setStopBits(QSerialPort::OneStop)) {
            qDebug() << commSerial->serial->errorString();
        }
        if (!commSerial->serial->setFlowControl(QSerialPort::NoFlowControl)) {
            qDebug() << commSerial->serial->errorString();
        }

        m_statusConnection = "connected";

        qDebug() << "Conectado na porta : " << commSerial->serial->portName();

        commSerial->serialDeviceConnected = true;
        emit connectionChanged();
        emit statusConnectionChanged();
    } else { // Caso a conexão seja mal sucedida, mostra o erro na caixa de
             // texto
        m_statusConnection = "error";

        qDebug() << "Ocorreu um erro ao se conectar a porta "
                 << commSerial->serial->portName();
        qDebug() << "Error: " << commSerial->serial->errorString();

        commSerial->serialDeviceConnected = false;
        emit connectionChanged();
        emit statusConnectionChanged();
    }
}

// Ação para desconectar o dispositivo
void SearchDevice::disconnectDevice(const QString &selectedPort) {
    // Caso tenha um dispositivo conectado, realiza a desconexão do mesmo
    if (commSerial->serialDeviceConnected) {
        commSerial->serial->close();
        qDebug() << "A porta" << selectedPort
                 << "foi desconectada com sucesso.";

        // Atualiza o aviso de desconexão bem sucedida
        // Ao desconectar, fecha a janela da área de controle
        m_statusConnection = "disconnected";
        commSerial->serialDeviceConnected = false;
        emit connectionChanged();
        emit statusConnectionChanged();
    } else { // Se não tiver dispositivo conectado, mostra o erro na caixa de
             // texto
        m_statusConnection = "error";

        qDebug() << "Nenhum dispositivo conectado";

        commSerial->serialDeviceConnected = false;
        emit connectionChanged();
        emit statusConnectionChanged();
    }
}
