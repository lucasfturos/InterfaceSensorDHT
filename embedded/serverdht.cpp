#include "serverdht.hpp"

ServerDHT::ServerDHT(const uint8_t &DHTPIN, const uint8_t &DHTTYPE,
                     const std::string &ssid, const std::string &password,
                     const std::string &serverName)
    : m_serverName(serverName) {
    wifi = std::make_shared<WiFiClass>();
    dht = std::make_shared<DHT>(DHTPIN, DHTTYPE);
    http = std::make_shared<HTTPClient>();

    dht->begin();
    wifi->begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi");

    while (wifi->status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi network");
}

void ServerDHT::loop() {
    uint32_t currentTime = millis();

    if ((currentTime - lastTime) >= timerDelay) {
        lastTime = currentTime;

        if (wifi->status() == WL_CONNECTED) {
            h = dht->readHumidity();
            t = dht->readTemperature();

            if (isnan(h) || isnan(t)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
            }

            humidityStr = "H=" + std::to_string(h);
            temperatureStr = "T=" + std::to_string(t);
            dataSensor = humidityStr + "&" + temperatureStr;
            std::string serverPath = m_serverName + "setData?" + dataSensor;

            http->begin(serverPath.c_str());
            int httpResponseCode = http->GET();

            if (httpResponseCode > 0) {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
                String payload = http->getString();
                Serial.println(payload);
            } else {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
            }

            http->end();
        } else {
            Serial.println("WiFi Disconnected");
        }
    }
}