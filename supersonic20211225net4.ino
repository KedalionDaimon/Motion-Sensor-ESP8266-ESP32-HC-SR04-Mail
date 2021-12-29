
#define echoPin 14 // ESP32 Wrover 16 // 14 ESP8266 D6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 // ESP32 Wrover 17 // 12 ESP8266 D5 // attach pin D3 Arduino to pin Trig of HC-SR04
#define PAUSESECONDS 10
#define MEMORIES 250
#define INTERMEASURE 10

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// #include <ESP8266WiFi.h>
// #include "WiFi.h"

int i = 0;
int j = 0;
long duration;
int expectdist = 0;
int lowdist = 0;
int highdist = 0;
int distance;
unsigned int hhhhhh = 0;
unsigned short mm = 0;
unsigned short ss = 0;
unsigned int timearrayh[MEMORIES];
unsigned short timearraym[MEMORIES];
unsigned short timearrays[MEMORIES];
unsigned int distancearray[MEMORIES];
int increasesec = 0;
char increasemin = 0;
char increaseh = 0;

unsigned int recmin = 0;
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int dist4 = 0;
int dist5 = 0;

WiFiServer wifiServer(8023);
WiFiClient client = wifiServer.available();

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  //Serial.begin(115200); // // 9600 baudrate speed
  //Serial.println("Ultrasonic Sensor"); // print some text in Serial Monitor

  
  WiFi.softAP("OnePingOnlyZ", "GiveMeAPingVassily");
  // WiFi.softAP("OnePingOnlyZ", "GiveMeAPingVassily", 1, 1); // channel & hidden SSID
  delay(500);
  wifiServer.begin();
  //Serial.print(" Net:OnePingOnlyZ Password:GiveMeAPingVassily");
  //Serial.print(" IP:");
  //Serial.print(WiFi.softAPIP());
  //Serial.println(" Port:8023");
  delay(20000);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist1 = duration * 0.034 / 2;
  delay(200);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist2 = duration * 0.034 / 2; 
  delay(200);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist3 = duration * 0.034 / 2; 
  delay(200);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist4 = duration * 0.034 / 2; 
  delay(200);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist5 = duration * 0.034 / 2;
  expectdist = (dist1 + dist2 + dist3 + dist4 + dist5)/5;
  for (j = 0; j<4; j++) {
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist1 = duration * 0.034 / 2;
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist2 = duration * 0.034 / 2; 
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist3 = duration * 0.034 / 2; 
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist4 = duration * 0.034 / 2; 
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist5 = duration * 0.034 / 2;
    expectdist = (5*expectdist + dist1 + dist2 + dist3
                 + dist4 + dist5)/10;
  }
  lowdist = 0.8 * expectdist;
  highdist = 1.25 * expectdist;

}



void loop() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; 
    //Serial.print("dist1=");
    //Serial.print(dist1);
    //Serial.print("   dist2=");
    //Serial.print(dist2);
    //Serial.print("   dist3=");
    //Serial.print(dist3);
    //Serial.print("   dist4=");
    //Serial.print(dist4);
    //Serial.print("   dist5=");
    //Serial.print(dist5);
    //Serial.print("   h=");
    //Serial.print(hhhhhh);
    //Serial.print(" m=");
    //Serial.print(mm);
    //Serial.print(" s=");
    //Serial.print(ss);
    //Serial.print("   recmin=");
    //Serial.println(recmin);

    dist5 = dist4;
    dist4 = dist3;
    dist3 = dist2;
    dist2 = dist1;
    dist1 = distance;
    delay(INTERMEASURE);

    if ((dist1>0) && (dist2>0) && (dist3>0) &&
        (dist4>0) && (dist5>0) &&
        (((dist1<lowdist) && (dist2<lowdist) && (dist3<lowdist) &&
          (dist4<lowdist) && (dist5<lowdist)) ||
         ((dist1>highdist) && (dist2>highdist) && (dist3>highdist) &&
          (dist4>highdist) && (dist5>highdist))) &&
        (recmin >= PAUSESECONDS)) {
      //Serial.println("    TRIGGERING---------------------------------------------------------");
      for (i = (MEMORIES - 1); i > 0; i--) {
        timearrayh[i] = timearrayh[i - 1];
        timearraym[i] = timearraym[i - 1];
        timearrays[i] = timearrays[i - 1];
        distancearray[i] = distancearray[i - 1];
      }
      distancearray[0] = (dist1 + dist2 + dist3 + dist4 + dist5) / 5;
      dist1 = 0;
      dist2 = 0;
      dist3 = 0;
      dist4 = 0;
      dist5 = 0;
      recmin = 0;

      timearrayh[0] = hhhhhh;
      timearraym[0] = mm;
      timearrays[0] = ss;

      
        delay(420);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        dist1 = duration * 0.034 / 2;
        delay(20);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        dist2 = duration * 0.034 / 2; 
        delay(20);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        dist3 = duration * 0.034 / 2; 
        delay(20);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        dist4 = duration * 0.034 / 2; 
        delay(20);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        dist5 = duration * 0.034 / 2;
        expectdist = (dist1 + dist2 + dist3
                      + dist4 + dist5)/5;
      
      lowdist = 0.8 * expectdist;
      highdist = 1.25 * expectdist;
      increasesec = 1000; // not "precise", but better than nothing.

    }

    increasesec = increasesec + INTERMEASURE;
    // or 999 = 37*27
    if (increasesec >= 1000) {
      increasesec = 0;

      if (ss < 59) {
        ss = ss + 1;
      } else {
        increasemin = 1;
        ss = 0;
      }

      if (recmin < 65535) {
        recmin = recmin + 1;
      }

      ESP.wdtFeed();
    }

    if (increasemin > 0) {
      increasemin = 0;

      if (mm < 59) {
        mm = mm + 1;
      } else {
        increaseh = 1;
        mm = 0;
      }
    }

     if (increaseh > 0) {
      increaseh = 0;
        hhhhhh = hhhhhh + 1;
    }

    client = wifiServer.available();
    if (client) {
      while (client.connected()) {
      client.println(" ");
      for (i = (MEMORIES - 1); i >= 0; i--) {
        client.print("TIME: ");
        client.print(timearrayh[i]);
        client.print("h ");
        client.print(timearraym[i]);
        client.print("m ");
        client.print(timearrays[i]);
        client.print("s     DISTANCE: ");
        client.print(distancearray[i]);
        client.println(" cm");
      }
      
      client.println(" ");
      break;
    }}
}
