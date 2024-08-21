#include <ESP8266WiFi.h>

const char *password = "12345678";
const char *ssid = "esp_01swifi";

IPAddress serverIP(192, 168, 4, 1); // AP模式ESP8266的IP地址
WiFiClient client;

bool IsButtonPressed(uint8_t pin)
{
  if (digitalRead(pin) == HIGH) // button is pressed
  {
    delay(50);
    if (digitalRead(pin) == HIGH) // button is pressed
    {
      return true;
    }
  }
  else
  {
    return false;
  }
  return false;
}

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

  pinMode(0,INPUT);
}

// String statu = "OFF\r";

void loop()
{
  if (client.connected())
  {
    Serial.println("已连接到服务器");
    // Serial.println(statu);
    // client.print(statu);
    // statu == "ON\r" ? statu = "OFF\r" : statu = "ON\r"; // 要加/r否则server读取会出问题

    if (IsButtonPressed(0))
    {
      Serial.println("ON");
      client.print("ON");
    }
    else
    {
      Serial.println("OFF");
      client.print("OFF");
    }
  }
  else
  {
    Serial.println("连接断开！");
    client.connect(serverIP, 5000);
  }
  delay(1000);
}