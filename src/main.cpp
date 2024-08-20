#include <ESP8266WiFi.h>

const char *password = "12345678";
const char *ssid = "esp_01swifi";

IPAddress serverIP(192, 168, 4, 1); // AP模式ESP8266的IP地址
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("连接到AP...");
  }
  Serial.println("已连接到AP");
  Serial.print("IP地址: ");
  Serial.println(WiFi.localIP()); // 打印STA的IP地址

  // 连接到服务器
  client.connect(serverIP, 5000);
}

String statu = "ON\r";

void loop()
{
  if (client.connected())
  {
    Serial.println("已连接到服务器");
    Serial.println(statu);
    client.print(statu);
    statu == "ON\r" ? statu = "OFF\r" : statu = "ON\r";//要加/r否则server读取会出问题
  }
  else
  {
    client.connect(serverIP, 5000);
  }
  delay(1000);
}