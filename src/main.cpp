#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

#define ENA 15
#define IN1 5
#define IN2 4

#define BUZZER 23

AsyncWebServer server(80);

const char* ssid = "ESP32";
const char* password = "12345678";

int speed = 0;
bool isActive = false;
bool isForward = true;
int mappedSpeed = 0;
bool isConnected = false;                                                                                                                                                                                                                                         

void buzz(int time, int times)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(BUZZER, HIGH);
    delay(time);
    digitalWrite(BUZZER, LOW);
    delay(time);
  }
}

void blink(int speed)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(speed);
  digitalWrite(LED_BUILTIN, LOW);
  delay(speed);
}

void handleSAP()
{
  if (isActive) { analogWrite(ENA, mappedSpeed); }
  else analogWrite(ENA, 0);
}

void HTTPRouter()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/vite.svg", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/vite.svg", "image/svg+xml");
  });
 
  server.on("/assets/index-uzEnO-1i.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/assets/index-uzEnO-1i.css", "text/css");
  });

  server.on("/assets/index-OoUDtJHD.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/assets/index-OoUDtJHD.js", "text/javascript");
  });

  server.on("/speed", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    speed = request->getParam("speed")->value().toInt();
    Serial.print("[INFO] [SPEED] ");
    Serial.println(speed);

    mappedSpeed = map(speed, 0, 100, 0, 255);

    handleSAP();
  });

  server.on("/status", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    isActive = request->getParam("status")->value().toInt() == 1;
    Serial.print("[INFO] [STATUS] ");
    Serial.println(isActive);

    handleSAP();
  });

  server.on("/buzz", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    int time = request->getParam("time")->value().toInt();
    int times = request->getParam("times")->value().toInt();

    buzz(time, times);
  });

  server.on("/direction", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    isForward = request->getParam("direction")->value().toInt() == 1;
    Serial.print("[INFO] [DIRECT] ");
    Serial.println(isForward);

    if (isForward)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }

    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  });

  server.begin();
  Serial.println("[INFO] [ROUTER] Added routes");
}

void InitWiFi()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  HTTPRouter();
}

void WiFiEventHandler(WiFiEvent_t event)
{
  switch (event)
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      isConnected = true;
      Serial.print("[INFO] [ADDRESS] ");
      Serial.println(WiFi.localIP());
      buzz(100, 2);
      HTTPRouter();
      break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
      if (isConnected) { buzz(150, 3); }
      isConnected = false;
      InitWiFi();
      break;

    default:
      break;
  }
}

void InitSPIFFS()
{
  if(!SPIFFS.begin())
  {
    Serial.println("[ERR] [SPIFFS] An error occurred in the SPIFFS module");
    return;
  }
}

void Awake()
{
  Serial.println("Ball Mill Project");
  Serial.println(" ");
  Serial.println("[INFO] [CREATED] JMota");

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  buzz(100, 1);
}

void setup()
{
  Serial.begin(115200);

  WiFi.onEvent(WiFiEventHandler);

  InitSPIFFS();
  Awake();
  InitWiFi();
}

void loop()
{
  if (isConnected) { digitalWrite(LED_BUILTIN, HIGH); } 
  else { blink(800); }
}