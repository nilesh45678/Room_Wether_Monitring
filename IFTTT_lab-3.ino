#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>;
//#include <ESP8266WiFi.h>
/* DHT SENSOR SETUP */
#define DHTTYPE DHT11
#define DHTPIN 0
DHT dht(DHTPIN, DHTTYPE,11);
float humidity, temp_f; // Values read from
const char* ssid = "V2022";
const char* password = "SagarPandey";
//define the parameters for the IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "Temperature_Warning"
#define IFTTTKEY "g6oz69sBqEue_OeqhASsBb5xjmDVmOZqrtq1zgt4QTN"
WiFiClientSecure client;
void setup() {
Serial.begin(115200);
delay(10);
dht.begin();
delay(2000);
temp_f = dht.readTemperature();
humidity = dht.readHumidity();
client.setInsecure();
WiFi.begin(ssid, password);
Serial.println("");
Serial.print("Waiting to connect to WiFi... ");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);

Serial.print("IP address: ");
Serial.println(WiFi.localIP());
delay(1000);
Serial.print("Initial Temp: ");
Serial.println(temp_f);
Serial.print("Initial Humi: ");
Serial.println(humidity);
if (client.connected())
{
client.stop();
}
client.flush();
if (client.connect(HOSTIFTTT,443)) {
Serial.println("Connected");
// build the HTTP request
String toSend = "GET /trigger/";
toSend += EVENTO;
toSend += "/with/key/";
toSend += IFTTTKEY;
toSend += "?value1=";
toSend += temp_f;
toSend += "&value2=";
toSend += humidity;
toSend += " HTTP/1.1\r\n";
toSend += "Host: ";
toSend += HOSTIFTTT;
toSend += "\r\n";
toSend += "Connection: close\r\n\r\n";
client.print(toSend);
}
client.flush();
client.stop();
delay(500);
}
void loop() {
}
