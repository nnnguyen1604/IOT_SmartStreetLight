#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Firebase.h>
#define M0 19
#define M1 21
#define RXD2 4
#define TXD2 17
#define WIFI_SSID "G1 324"
#define WIFI_PASSWORD "22222222"
#define REFERENCE_URL "https://lediot-6777b-default-rtdb.firebaseio.com/"  // Your Firebase project reference url

#define LORA_GATEWAY 0x11       //  Gateway

unsigned long lastReadTime = 0;
const unsigned long readInterval = 100;  // Adjust this interval as needed
Firebase firebase(REFERENCE_URL);
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000;
int hourResult1, hourResult2, minuteResult1, minuteResult2;
void setup()
{
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set M0 and M1 to LOW to operate in Normal mode
  digitalWrite(M1, LOW);
}

void processSerialData(String data) {
  int aIndex = data.indexOf('a');
  int bIndex = data.indexOf('b');
  int cIndex = data.indexOf('c');
  int dIndex = data.indexOf('d');
  int eIndex = data.indexOf('e');
  int fIndex = data.indexOf('f');
  int gIndex = data.indexOf('g');

  String receivedGateID = data.substring(aIndex + 1, bIndex);
  Serial.println(receivedGateID);
  String receivedAreaID = data.substring(bIndex + 1, cIndex);
  Serial.println(receivedAreaID);
  String receivedLightID = data.substring(cIndex + 1, dIndex);
  Serial.println(receivedLightID);
  int lightEnv = data.substring(dIndex + 1, eIndex).toInt();
  Serial.println("LightEnv: "+String(lightEnv));
  int lightVal = data.substring(eIndex + 1, fIndex).toInt();
  Serial.println("LightVal: "+String(lightVal));
  int dimValue = data.substring(fIndex + 1, gIndex).toInt();
  Serial.println("Dimvalue: "+String(dimValue));
  int error = data.substring(gIndex + 1).toInt();
  Serial.println("Error: "+String(error));

  if (receivedGateID.equalsIgnoreCase("0xFF") ) {
    int areaID = strtol(receivedAreaID.c_str(), NULL, 16); // Convert receivedAreaID from hex to int
    int lightID = strtol(receivedLightID.c_str(), NULL, 16); // Convert receivedLightID from hex to int
  
    String envPath = "LightStreet/Khuvuc" + String(areaID) + "/Light" + String(lightID) + "/sensorEnv";
    String valPath = "LightStreet/Khuvuc" + String(areaID) + "/Light" + String(lightID) + "/sensorLig";
    String dimPath = "LightStreet/Khuvuc" + String(areaID) + "/Light" + String(lightID) + "/value";
    String errorPath = "LightStreet/Khuvuc" + String(areaID) + "/Light" + String(lightID) + "/error";
    firebase.setString(envPath.c_str(), String(lightEnv));
    firebase.setString(valPath.c_str(), String(lightVal));
    firebase.setString(errorPath.c_str(), String(error));
  }
}
// The loop function is called in an endless loop
void loop()
{
  if (Serial2.available() > 0) {
    String data = Serial2.readString();
    Serial.println("Received from Node: " + data);
    processSerialData(data);

  }
  if (runEvery(5000)) {
    for (int i = 1; i < 2; i++) {
      String addr = "LightStreet/Khuvuc"+String(i);
      for (int j = 1; j < 2; j ++) {
        String addr2 = addr + "/Light"+String(j);
        Serial.println(addr2);
        int Control = firebase.getInt(addr2 + "/Control");       // LightStreet/Khuvuc1/Light1
        String Mode = firebase.getString(addr2 + "/Mode");
        String value = firebase.getString(addr2 + "/value"); 

        Serial.println(Control);
        int arrDimLevel[24] = {0};
        if (Control == 1) {
          for (int k = 1; k<3;k++){
            String starttime = firebase.getString(addr2+"/LightChart/Option"+String(k)+"/StartTime");
            String endtime = firebase.getString(addr2+"/LightChart/Option"+String(k)+"/EndTime");
            int Level = firebase.getInt(addr2+"/LightChart/Option"+String(k)+"/Level");
            int colonPosition = starttime.indexOf(':');
            if (colonPosition != -1) { 
              String hourString1 = starttime.substring(0, colonPosition);
              String minuteString1 = starttime.substring(colonPosition + 1);
              hourResult1 = hourString1.toInt();
              minuteResult1 = minuteString1.toInt();
            }
            int colonPosition2 = endtime.indexOf(':');
            if (colonPosition2 != -1) { 
              String hourString2 = endtime.substring(0, colonPosition2);
              String minuteString2 = endtime.substring(colonPosition2 + 1);
              hourResult2 = hourString2.toInt();
              minuteResult2 = minuteString2.toInt();
            }
            for (int i = hourResult1; i <hourResult2; i++) {
              arrDimLevel[i] += Level;
            }
            printArray(arrDimLevel, 24);
          }
          String stringArrDim = "";
          for (int i = 0; i < 24; i++) {
            stringArrDim.concat(String(arrDimLevel[i]));
          }
          String AREA_ID = (i < 10) ? "0" + String(i) : String(i);
          String LIGHT_ID = (j < 10) ? "0" + String(j) : String(j);
          String mess1 = 'a' + String("0x") + AREA_ID + 'b' + String("0x") + LIGHT_ID + 'c' + String(Control) + 'd' + Mode + 'e' value + 'f'+ stringArrDim;
          Serial2.println(mess1);
          Serial.println("Sended Message: " + mess1);
        } else if (Control == 0) {
          String stringArrDim = "000000000000000000000000";
          String AREA_ID = (i < 10) ? "0" + String(i) : String(i);
          String LIGHT_ID = (j < 10) ? "0" + String(j) : String(j);
          String mess2 = 'a' + String("0x") + AREA_ID + 'b' + String("0x") + LIGHT_ID + 'c' + String(Control) + 'd' + Mode + 'e' value + 'f'+ stringArrDim;
          Serial2.println(mess2);
        }
      }
    }
  }
}
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
