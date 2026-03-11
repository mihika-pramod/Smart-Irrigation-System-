#define BLYNK_TEMPLATE_ID "TMPL3rSZmEvT9"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "dNlUwFISU7QH_oKWyMXfBCCsORnDog8Z"
#define BLYNK_DEFAULT_PORT 8080


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h> 

#define SOIL_MOISTURE_PIN 34
#define THRESHOLD_MOISTURE 100
#define PUMP_PIN 25
#define PUMP_SWITCH V6

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";

BlynkTimer timer;
bool isPumpOn = false;

BLYNK_CONNECTED() {
  Serial.println("✅ Blynk Cloud CONNECTED");
}
  
BLYNK_DISCONNECTED() {
  Serial.println("❌ Blynk Cloud DISCONNECTED");
}

void sendSensorData()
{
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture Raw: ");
  Serial.println(soilMoisture);

  int soilMoisturePercentage = map(soilMoisture,0,4095,0,100);
  Serial.print("Soil Moisture %: ");
  Serial.println(soilMoisturePercentage);

  if (Blynk.connected()) {
    Serial.println("📤 PUSHING data to Blynk...");
    Blynk.virtualWrite(V5, soilMoisturePercentage);
    Serial.println("✅ PUSH SUCCESS");
  } else {
    Serial.println("❌ PUSH FAILED (Blynk offline)");
  }

  if (isPumpOn || soilMoisturePercentage < THRESHOLD_MOISTURE) {
    digitalWrite(PUMP_PIN, HIGH);

    if (!isPumpOn && Blynk.connected()) {
      Blynk.logEvent("moisture_alert", "Soil moisture is below the threshold!");
      Serial.println("⚠️ Alert SENT");
    }
  } else {
    if (!isPumpOn) digitalWrite(PUMP_PIN, LOW);
  }
}

BLYNK_WRITE(PUMP_SWITCH)
{
  isPumpOn = param.asInt();
  Serial.println(isPumpOn ? "🔘 Pump ON" : "🔘 Pump OFF");
}

void setup()
{
  Serial.begin(115200);   // 🔴 FIX IS HERE
  delay(100);

  pinMode(PUMP_PIN, OUTPUT);

  Serial.println("🔄 Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi CONNECTED");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("🔄 Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(300L, sendSensorData);

  Blynk.virtualWrite(PUMP_SWITCH, isPumpOn);
  Blynk.syncVirtual(PUMP_SWITCH);
}

void loop()
{
  Blynk.run();
  timer.run();
}
