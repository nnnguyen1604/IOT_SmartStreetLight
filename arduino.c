#include <SoftwareSerial.h>

const String ID = "Q7/2"; // id device

SoftwareSerial mySerial(6, 7); // TX, RX

const int numID = ID.length();
const int lightSensor1 = A0;
const int lightSensor2 = A1;
#define M0 8
#define M1 9

unsigned long lastReadTime = 0;
const unsigned long readInterval = 100;  // Adjust this interval as needed

String setID(String id, char prefix, String original) {
    return id + String(prefix) + original; // Add prefix and ID to the beginning of the string
}

char getIdLightSensor(String idLightSensor) {
  if (idLightSensor.length() > 0) {
    return idLightSensor.charAt(0);
  }
  return '\0';
}

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(M0, OUTPUT);        
    pinMode(M1, OUTPUT);
    digitalWrite(M0, LOW); // Set M0 and M1 pins to LOW 
    digitalWrite(M1, LOW); // to operate in Normal mode
}

void processSerialData(String data) {
    String idSlave = data.substring(0, numID); // get ID

    if (idSlave == ID) {
        // check ID device

        String value = data.substring(numID);
        char IdlightSensor = getIdLightSensor(value);

        if (IdlightSensor == 'c') {

            // get and check id control mode
            String data1 = value.substring(1);
            int Control = data1.toInt();

            if (Control == 0) {
                // if control = 0 
                // send data sensor 1, 2 and data error
                int lightValue1 = analogRead(lightSensor1);
                int lightValue2 = analogRead(lightSensor2);

                String light1 = String(lightValue1);
                String LightSensor1 = setID(ID, 'u', light1);

                String light2 = String(lightValue2);
                String LightSensor2 = setID(ID, 'd', light2);

                int a = random(0, 1000);
                if (a % 2 == 0) {
                    mySerial.println(LightSensor1);
                    Serial.println(LightSensor1);
                } else {
                    mySerial.println(LightSensor2);
                    Serial.println(LightSensor2);
                }
            }
        } else {

            // if control != 0
            // use data to control led
            String data2 = value.substring(1);
            int Value = data2.toInt();
            Serial.println("Value: ");
            Serial.println(Value);
        }
    }
}

void loop() {
    unsigned long currentMillis = millis();

    if (Serial.available() > 0) {
        String data = Serial.readString(); // get data from lora
        processSerialData(data);
    }

    if (mySerial.available() > 0) {
        String data = mySerial.readString();
        processSerialData(data);
    }

    if (currentMillis - lastReadTime >= readInterval) {
        lastReadTime = currentMillis;
    }
}
