#pragma once

#include <DHT.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <cstdint>
#include <memory>

class ServerDHT {
  private:
    std::string m_serverName;
    const uint8_t timerDelay = 5000;
    uint32_t lastTime = 0;

    float h, t;

    std::string humidity;
    std::string temperature;
    std::string dataSensor;
    std::string serverPath;

    std::shared_ptr<DHT> dht;
    std::shared_ptr<WiFiClass> wifi;
    std::shared_ptr<HTTPClient> http;

  public:
    void loop();

    ServerDHT(const uint8_t &DHTPIN, const uint8_t &DHTTYPE,
              const std::string &ssid, const std::string &password,
              const std::string &serverName);
};
