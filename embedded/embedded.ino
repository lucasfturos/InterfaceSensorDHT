// #include "serialdht.hpp"
#include "serverdht.hpp"

const uint8_t DHTPIN = 13;
const uint8_t DHTTYPE = DHT11;

std::shared_ptr<ServerDHT> serverDHT;
// std::shared_ptr<SerialDHT> serialDHT;

void setup() {
    Serial.begin(9600);
    //     serialDHT = std::make_shared<SerialDHT>(DHTPIN, DHTTYPE);
    serverDHT = std::make_shared<ServerDHT>(DHTPIN, DHTTYPE, "LucasESP32", "lucasesp32",
                                            "http://localhost:3000/");
}

void loop() {
      // serialDHT->loop();
    serverDHT->loop();
}