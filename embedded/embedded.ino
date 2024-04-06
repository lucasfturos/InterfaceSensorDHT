#include "serialdht.hpp"
#include "serverdht.hpp"
#include "key_events.hpp"

// Sensor
const uint8_t DHTPIN = 13;
const uint8_t DHTTYPE = DHT11;

std::shared_ptr<ServerDHT> serverDHT;
std::shared_ptr<SerialDHT> serialDHT;

// Wi-Fi
const std::string &SSID = "LucasESP32";
const std::string &PASSWORD = "lucasesp32";
const std::string &SERVER = "http://localhost:3000/";

void setup() {
    Serial.begin(9600);
    serialDHT = std::make_shared<SerialDHT>(DHTPIN, DHTTYPE);
    serverDHT =
        std::make_shared<ServerDHT>(DHTPIN, DHTTYPE, SSID, PASSWORD, SERVER);
}

void loop() {
    uint8_t events = keyEvents();

    switch (events) {
    case 1:
        Serial.println("Serial Mode");
        serialDHT->loop();
        break;
    case 2:
        Serial.println("Wi-Fi Mode");
        serverDHT->loop();
        break;
    case 3:
        Serial.println("Bluetooth Mode");
        break;
    default:
        break;
    }
}