#include "serialdht.hpp"

SerialDHT::SerialDHT(const uint8_t &DHTPIN, const uint8_t &DHTTYPE) {
    dht = std::make_shared<DHT>(DHTPIN, DHTTYPE);
    dht->begin();
}

void SerialDHT::loop() {
    delay(2000);
    h = dht->readHumidity();
    t = dht->readTemperature();

    humidity = "H" + std::to_string(h);
    temperature = "T" + std::to_string(t);
    dataSensor = humidity + temperature;

    while (Serial.available() > 0) {
        Serial.read();
    }

    Serial.println(dataSensor.c_str());

    delay(100);
}