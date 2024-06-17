#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Firebase.h>

#define M0 19
#define M1 21
#define WIFI_SSID "LAPTOP"
#define WIFI_PASSWORD "200120021"
#define REFERENCE_URL "https://ledmqtt-default-rtdb.asia-southeast1.firebasedatabase.app/"  // Your Firebase project reference url

#define F1 "Q7" // ID AREA
const int numDevice = 4;

Firebase firebase(REFERENCE_URL);
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000;

void setup() {
  Serial2.begin(9600);   // Lora E32 connected to TX2 RX2 on ESP32
  Serial.begin(9600);

  // Connect to WiFi
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

void loop() {
  if (millis() - lastUpdateTime > updateInterval) {
    lastUpdateTime = millis();

    for (int i = 1; i < numDevice; i++) {


      String addr = String(F1) + "/" + String(i) ;
      // Get value mode from Firebase
      int Data = firebase.getInt(addr + "/Control");

      // print value 
      Serial.print("Data from ");
      Serial.print(addr);
      Serial.print(": ");
      Serial.println(Data);

      /*Process the received data
        data == 0 -> automode
        data == 1 -> manualmode
      */ 
      
      if (Data == 0) {
        transmitControl(addr);
        autoControlMode();
      } else {
        manualControlMode(addr);
      }
    }
  }
}

void autoControlMode() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    Serial2.println(data);
    Serial.print("\n");
    String value = data.substring(4);
    Serial2.println(getID(data));
    handleData(value, getID(data));
  }

  if (Serial2.available() > 0) {
    String data = Serial2.readString();
    Serial.println(data); 
    Serial.print("\n");
    Serial.println("ID: " + getID(data));
    String value = data.substring(4);
    Serial.println("Data: " + value);
    handleData(value, getID(data));
  }
}

void transmitControl(String ID) {
  // transmit value mode to arduino

  String controlPath = ID + "/Control";
  String control = firebase.getString(controlPath);
  String setIdControl = setID(ID, 'c', control);
  Serial2.println(setIdControl);
  Serial.println("Received Control: " + setIdControl);
}

void manualControlMode(String ID) {

  // transmit value mode and control to arduino
  String controlPath = ID + "/Control";
  String control = firebase.getString(controlPath);
  String setIdControl = setID(ID, 'c', control);
  Serial2.println(setIdControl);
  Serial.println("Received Control: " + setIdControl);

  String ValuePath = ID + "/Value";
  String Value = firebase.getString(ValuePath);
  String setIdValue = setID(ID, 'v', Value);
  Serial2.println(setIdValue);
  Serial.println("Received Value: " + setIdValue);
}

String setID(String id, char prefix, String original) {
  // set ID for data 
  // example Data after set ID:   Q7/1u1 = Q7/1 + u + data 
  return id + String(prefix) + original;
}

char getIdLightSensor(String idLightSensor) {
  if (idLightSensor.length() > 0) {

    // Get id device
    // example:  1
    return idLightSensor.charAt(0);
  }
  return '\0';
}

String getID(String ID) {
  if (ID.length() >= 4) {

    //Get id area 4 char 
    //example:   Q7/1
    return ID.substring(0, 4);

  } else {
    // If string is shorter than 4 characters, return the entire string
    return ID;
  }
}

void handleData(String data, String ID) {
  char IdlightSensor = getIdLightSensor(data);
  String firebaseAddress;

  if (IdlightSensor == 'u') {
    String data1 = data.substring(1);
    int myInt = data1.toInt();
    firebaseAddress = ID + "/AS1";
    firebase.setInt(firebaseAddress.c_str(), myInt);
  }else if(IdlightSensor == 'd'){
    String data2 = data.substring(1);
    int myInt = data2.toInt();
    firebaseAddress = ID + "/AS2";
    firebase.setInt(firebaseAddress.c_str(), myInt);
    }
  else {
    String data2 = data.substring(1);
    int myInt = data2.toInt();
    firebaseAddress = ID + "/Error";
    firebase.setInt(firebaseAddress.c_str(), myInt);
  }
}
