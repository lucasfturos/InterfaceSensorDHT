#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  char temparature[10];
  char humidity[10];

  dtostrf(t, 4, 2, temparature);
  dtostrf(h, 4, 2, humidity);

  Serial.print("H");
  Serial.println(humidity);
  Serial.print("T");
  Serial.println(temparature);
}
