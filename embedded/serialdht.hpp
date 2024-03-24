#pragma once

#include <DHT.h>
#include <cstdint>
#include <memory>

class SerialDHT {
  private:
    float h, t;

    std::string dataSensor;
    std::string humidity;
    std::string temperature;

    std::shared_ptr<DHT> dht;

  public:
    void loop();

    SerialDHT(const uint8_t &DHTPIN, const uint8_t &DHTTYPE);
};