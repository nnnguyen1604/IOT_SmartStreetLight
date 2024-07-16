#include <SoftwareSerial.h>
#include "RTClib.h"

const uint8_t AREA_ID = 0x01;
const uint8_t LIGHT_ID = 0x01;

const int lightEnvpin = A6;
const int lightValpin = A7;

#define TX 2
#define RX 3

#define M0_M1 4
#define Relay 5

unsigned long lastReadTime = 0;
const unsigned long readInterval = 100;  // Adjust this interval as needed
RTC_DS3231 rtc;
SoftwareSerial Serial2(TX, RX); // TX, RX

int dimValue = 0;
int error = 0;

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600);      
    pinMode(M0_M1, OUTPUT);
    pinMode(Relay,OUTPUT);
    digitalWrite(M0_M1, LOW); 
    delay(3000);
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
    if (rtc.lostPower()) {
      Serial.println("RTC lost power, lets set the time!");

      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void Zero(){
  delay(500);
  dimValue = 0;
  Serial.println("DimLevel: 0");Serial.println();
  digitalWrite(PIN_A2, LOW);   
  digitalWrite(PIN_A1, HIGH);   
  digitalWrite(PIN_A0, LOW);   
};

void One(){
  delay(500);
  dimValue = 1;
  Serial.println("DimLevel: 1");Serial.println();
  digitalWrite(PIN_A2, HIGH);   
  digitalWrite(PIN_A1, LOW);   
  digitalWrite(PIN_A0, LOW);   
};

void Two(){
  delay(500);
  dimValue = 2;
  Serial.println("DimLevel: 2");Serial.println();
  digitalWrite(PIN_A2, LOW);   
  digitalWrite(PIN_A1, HIGH);   
  digitalWrite(PIN_A0, HIGH);   
};

void Three(){
  delay(500);
  dimValue = 3;
  Serial.println("DimLevel: 3");Serial.println();
  digitalWrite(PIN_A2, LOW);   
  digitalWrite(PIN_A1, LOW);   
  digitalWrite(PIN_A0, HIGH);   
};

void Four(){
  delay(500);
  dimValue = 4;
  Serial.println("DimLevel: 4");Serial.println();
  digitalWrite(PIN_A2, HIGH);   
  digitalWrite(PIN_A1, LOW);   
  digitalWrite(PIN_A0, HIGH);   
};

void Five(){
  delay(500);
  dimValue = 5;
  Serial.println("DimLevel: 5");Serial.println();
  digitalWrite(PIN_A0, HIGH);   
  digitalWrite(PIN_A1, HIGH);   
  digitalWrite(PIN_A2, HIGH);   
};

void Six(){
  delay(500);
  dimValue = 6;
  Serial.println("DimLevel: 6");Serial.println();
  digitalWrite(PIN_A2, HIGH);   
  digitalWrite(PIN_A1, HIGH);   
  digitalWrite(PIN_A0, LOW);   
};

void Seven(){
  delay(500);
  dimValue = 7;
  Serial.println("DimLevel: 7");Serial.println();
  digitalWrite(PIN_A2, LOW);   
  digitalWrite(PIN_A1, LOW);   
  digitalWrite(PIN_A0, LOW);   
};

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
}

void processSerialData(String data, int lightEnv, int time) {
  String str = data;
  int aIndex = str.indexOf('a');
  int bIndex = str.indexOf('b');
  int cIndex = str.indexOf('c');
  int dIndex = str.indexOf('d');
  int arrDimLevel[24] = {0};

  String receivedAreaID = str.substring(aIndex + 1, bIndex);
  Serial.println("AreID:"+receivedAreaID);
  String receivedLightID = str.substring(bIndex + 1, cIndex);
  Serial.println("LightID:"+receivedLightID);
  int control = str.substring(cIndex + 1, dIndex).toInt();
  String stringArrDim = str.substring(dIndex + 1);
  for (int i = 0; i < 24; i++) {
      arrDimLevel[i] = stringArrDim.substring(i, i + 1).toInt();
  }
  char expectedAreaID[5]; // Định nghĩa một mảng char để lưu chuỗi
  sprintf(expectedAreaID, "0x%02X", AREA_ID); // Định dạng chuỗi "0x01"
  char expectedLightID[5];
  sprintf(expectedLightID, "0x%02X", LIGHT_ID);
  if (receivedAreaID.equalsIgnoreCase(expectedAreaID) && receivedLightID.equalsIgnoreCase(expectedLightID)) {
    Serial.println("Message from Gateway: "+data);  Serial.print("Hour: "+String(time)+"; "); 
    Serial.println("AreID: "+receivedAreaID+", LightID: "+receivedLightID+", Control: "+String(control)+", ArrayDim: "+stringArrDim);
    Serial.print("Current Time: "+String(time)+", LightEnviroment: "+String(lightEnv)+", ");
    switch(control) {
      case 0: mode_0(lightEnv); break;
      case 1: mode_1(time,arrDimLevel); break;
      case 2: mode_2(lightEnv,time,arrDimLevel); break;
      default: break;
    }
  }
}

void mode_0(int lightEnv) {
  if(lightEnv >= 700) {
    digitalWrite(Relay, LOW); 
  }
  else if(lightEnv >= 600 && lightEnv < 700) {
    digitalWrite(Relay, HIGH);  Zero();
  }
  else if(lightEnv >= 500 && lightEnv < 600) {
      digitalWrite(Relay, HIGH);  One();
  }
  else if(lightEnv >= 400 && lightEnv < 500) {
       digitalWrite(Relay, HIGH); Two();
  }
  else if(lightEnv >=300 && lightEnv < 400) {
       digitalWrite(Relay, HIGH); Three();
  }
  else if(lightEnv >=200 && lightEnv < 300) {
       digitalWrite(Relay, HIGH); Four();
  }
  else if(lightEnv >= 100 && lightEnv < 200) {
       digitalWrite(Relay, HIGH); Six();
  }
  else if(lightEnv >= 0 && lightEnv < 100) {
       digitalWrite(Relay, HIGH); Seven();
  }
}

void mappingdim(int value) {
  switch(value) {
    case 0: digitalWrite(Relay, LOW); break;
    case 1: digitalWrite(Relay, HIGH); Zero();
    case 2: digitalWrite(Relay, HIGH); One(); break;
    case 3: digitalWrite(Relay, HIGH); Two(); break;
    case 4: digitalWrite(Relay, HIGH); Three(); break;
    case 5: digitalWrite(Relay, HIGH); Four(); break;
    case 6: digitalWrite(Relay, HIGH); Five(); break;
    case 7: digitalWrite(Relay, HIGH); Six(); break;
    case 8: digitalWrite(Relay, HIGH); Seven(); break;
    default: 
      break;
  }
}

void mode_1(int time, int dimLevel[]){
  switch(time) {
    case 0:mappingdim(dimLevel[0]); break;
    case 1:mappingdim(dimLevel[1]); break;
    case 2:mappingdim(dimLevel[2]); break;
    case 3:mappingdim(dimLevel[3]); break;
    case 4:mappingdim(dimLevel[4]); break;
    case 5:mappingdim(dimLevel[5]); break;
    case 6:mappingdim(dimLevel[6]); break;
    case 7:mappingdim(dimLevel[7]); break;
    case 8:mappingdim(dimLevel[8]); break;
    case 9:mappingdim(dimLevel[9]); break;
    case 10:mappingdim(dimLevel[10]); break;
    case 11:mappingdim(dimLevel[11]); break;
    case 12:mappingdim(dimLevel[12]); break;
    case 13:mappingdim(dimLevel[13]); break;
    case 14:mappingdim(dimLevel[14]); break;
    case 15:mappingdim(dimLevel[15]); break;
    case 16:mappingdim(dimLevel[16]); break;
    case 17:mappingdim(dimLevel[17]); break;
    case 18:mappingdim(dimLevel[18]); break;
    case 19:mappingdim(dimLevel[19]); break;
    case 20:mappingdim(dimLevel[20]); break;
    case 21:mappingdim(dimLevel[21]); break;
    case 22:mappingdim(dimLevel[22]); break;
    case 23:mappingdim(dimLevel[23]); break;
    default: break;
  }
}

void mode_2(int lightEnv, int time, int arrDimLevel[]) {
  if(time < 18) {
    mode_0(lightEnv);
  }
  else{
    mode_1(time,arrDimLevel);
  }
}
void checkLightEnv(int lightVal) {
  if ((dimValue == 0 && lightVal >= 0 && lightVal < 100) ||
      (dimValue == 1 && lightVal >= 100 && lightVal < 200) ||
      (dimValue == 2 && lightVal >= 200 && lightVal < 300) ||
      (dimValue == 3 && lightVal >= 300 && lightVal < 400) ||
      (dimValue == 4 && lightVal >= 400 && lightVal < 500) ||
      (dimValue == 5 && lightVal >= 500 && lightVal < 600) ||
      (dimValue == 6 && lightVal >= 600 && lightVal < 700) ||
      (dimValue == 7 && lightVal >= 700)) {
    error = 0;
  } else {
    error = 1;
  }
}
void loop() {
    unsigned long currentMillis = millis();
    int lightEnv=analogRead(lightEnvpin);
    int lightVal = analogRead(lightValpin);
    DateTime now = rtc.now();
    int thisSec, thisMin, thisHour;
    // get time từ bộ định thời
    thisSec = now.second();
    thisMin = now.minute();
    thisHour = now.hour();
    if (Serial.available() > 0) {
        String data = Serial.readString(); // get data
        Serial.println(data);
        processSerialData(data,lightEnv,thisHour);
    }

    if (Serial2.available() > 0) {
        String data = Serial2.readString();
        processSerialData(data,lightEnv,thisHour);
        String envData = "Env:" + String(lightEnv);
        String valData = "Val:" + String(lightVal);
        char expectedAreaID[5]; // Định nghĩa một mảng char để lưu chuỗi
        sprintf(expectedAreaID, "0x%02X", AREA_ID); // Định dạng chuỗi "0x01"
        char expectedLightID[5];
        sprintf(expectedLightID, "0x%02X", LIGHT_ID);

        // ID Area + value sensor + value light + value dim + TB Error

        String message = String("a0xFFb") + expectedAreaID + 'c'+ expectedLightID+'d'+String(lightEnv) + 'e' + String(lightVal) + 'f'+String(dimValue)+'g'+String(error);
        Serial2.println(message);
    }

    if (currentMillis - lastReadTime >= readInterval) {
        lastReadTime = currentMillis;
    }
    delay(1000);
}