#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>
#include <src/SearchDevice/searchdevice.hpp>
#include <src/SensorDHT/sensordht.hpp>

int main(int argc, char *argv[]) {
    auto app = std::make_shared<QGuiApplication>(argc, argv);
    auto engine = std::make_shared<QQmlApplicationEngine>();
    auto serial = std::make_shared<SerialCommunication>();
    auto searchDevice = std::make_shared<SearchDevice>(nullptr, serial);
    auto sensor = std::make_shared<SensorDHT>(nullptr, serial);

    engine->rootContext()->setContextProperty("searchDevice",
                                              searchDevice.get());
    engine->rootContext()->setContextProperty("sensor", sensor.get());

    QObject::connect(
        engine.get(), &QQmlApplicationEngine::objectCreationFailed, app.get(),
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    const QUrl url(u"qrc:/qml/Main.qml"_qs);
    engine->load(url);

    return app->exec();
}
