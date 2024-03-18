#include <DHT.h>
#include <string>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    std::string dataString = "H" + std::to_string(h) + "T" + std::to_string(t);

    while (Serial.available() > 0) {
        Serial.read();
    }

    Serial.println(dataString.c_str());

    delay(100);
    dataString.clear();
}
