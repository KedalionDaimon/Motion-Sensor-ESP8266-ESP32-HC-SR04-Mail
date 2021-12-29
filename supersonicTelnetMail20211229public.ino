// ----------------- START OF USER SETTINGS

#define SSIDNAME "YourWifiNetworkName"
#define PASSWORD "YourWifiPassword"

#define TARGETMAILSERVER "some throwaway-mail provider"
// "mail.harakirimail.com" and "spam4.me" (guerillamail) seem to work

// Adjust the sensor name differently for each sensor, so you know
// "who is writing you":
#define SENSORNAME "X"
#define YOURSOURCEMAIL "<X@spam4.me>"
// e.g. <X@harakirimail.com> or <X@spam4.me>

#define TARGETADDRESS "yourmailbox@trashmail.provider"
// e.g. <yourmailbox@harakirimail.com> or <yourmailbox@spam4.me>

#define RECENTDATE "Tue, 28 Dec 2021 17:00:00 +0000"
// SOME recent date, not important, but many servers insist on the header.

#define HOURS 1
// How many hours have to pass for a periodic ping.
// If your provider keeps mails just for 1h, set this to 1.

// Pre-configured for attaching the HC-SR04 to pins D5 & D6 on an
// ESP8266 LOLIN(WEMOS) D1 mini
#define echoPin 14 // ESP32 Wrover 16 // 14 ESP8266 D6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 // ESP32 Wrover 17 // 12 ESP8266 D5 // attach pin D3 Arduino to pin Trig of HC-SR04

// ----------------- END OF USER SETTINGS

// Ignore:
#define REMOTEIP { 0, 0, 0, 0 }
// to be used in client.connect below if you do not have a host-"name"

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

byte ip[] = REMOTEIP;

int i = 0;
int j = 0;
long duration;
int expectdist = 0;
int lowdist = 0;
int highdist = 0;
int distance;
int hhhhhh = 0;
short mm = 0;
short ss = 0;
int timearrayh[MEMORIES];
short timearraym[MEMORIES];
short timearrays[MEMORIES];
int distancearray[MEMORIES];
int increasesec = 0;
char increasemin = 0;
char increaseh = 0;

unsigned int recmin = 0;
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int dist4 = 0;
int dist5 = 0;

int sixhours = 0;

WiFiClient client;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200); // // 300 or 1200 or 9600 or 115200 baudrate speed
  Serial.println("Ultrasonic Sensor"); // print some text in Serial Monitor

  WiFi.begin(SSIDNAME, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Retry");
    delay(2000);
  }

  delay(20000);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist1 = duration * 0.034 / 2;
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist2 = duration * 0.034 / 2;
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist3 = duration * 0.034 / 2;
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist4 = duration * 0.034 / 2;
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist5 = duration * 0.034 / 2;
  expectdist = (dist1 + dist2 + dist3 + dist4 + dist5) / 5;
  for (j = 0; j < 4; j++) {
    delay(100);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist1 = duration * 0.034 / 2;
    delay(100);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist2 = duration * 0.034 / 2;
    delay(100);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist3 = duration * 0.034 / 2;
    delay(100);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist4 = duration * 0.034 / 2;
    delay(100);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist5 = duration * 0.034 / 2;
    expectdist = (5 * expectdist + dist1 + dist2 + dist3
                  + dist4 + dist5) / 10;
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

  Serial.print("dist1=");
  Serial.print(dist1);
  Serial.print("   dist2=");
  Serial.print(dist2);
  Serial.print("   dist3=");
  Serial.print(dist3);
  Serial.print("   dist4=");
  Serial.print(dist4);
  Serial.print("   dist5=");
  Serial.print(dist5);
  Serial.print("   h=");
  Serial.print(hhhhhh);
  Serial.print(" m=");
  Serial.print(mm);
  Serial.print(" s=");
  Serial.print(ss);
  Serial.print("   recmin=");
  Serial.println(recmin);

  dist5 = dist4;
  dist4 = dist3;
  dist3 = dist2;
  dist2 = dist1;
  dist1 = distance;
  delay(INTERMEASURE);

  if ((dist1 > 0) && (dist2 > 0) && (dist3 > 0) &&
      (dist4 > 0) && (dist5 > 0) &&
      (((dist1 < lowdist) && (dist2 < lowdist) && (dist3 < lowdist) &&
        (dist4 < lowdist) && (dist5 < lowdist)) ||
       ((dist1 > highdist) && (dist2 > highdist) && (dist3 > highdist) &&
        (dist4 > highdist) && (dist5 > highdist))) &&
      (recmin >= PAUSESECONDS)) {
    Serial.println("T-R-I-G-G-E-R-I-N-G---------------------------");

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
                  + dist4 + dist5) / 5;

    lowdist = 0.8 * expectdist;
    highdist = 1.25 * expectdist;

    // telnet target mail server port 25
    // alterinatively, if you have a numeric ip: (client.connect(ip, 25))
    if (client.connect(TARGETMAILSERVER, 25)) {
      while (client.connected()) {
        Serial.println("= = = = = = = = SENDING E-MAIL = = = = = = = =");

        delay(5);
        client.print("HELO ");
        client.println(TARGETMAILSERVER);
        delay(165);
        client.print("MAIL FROM:");
        client.println(YOURSOURCEMAIL);
        delay(160);
        client.print("RCPT TO:");
        client.println(TARGETADDRESS);
        delay(160);
        client.println("DATA");
        delay(2);
        client.print("From: \"");
        client.print(SENSORNAME);
        client.print("\" ");
        client.println(YOURSOURCEMAIL);
        delay(2);
        client.print("To: \"");
        client.print(TARGETADDRESS);
        client.print("\" ");
        client.println(TARGETADDRESS);
        delay(2);
        client.print("Subject: ACTIVATION OF ");
        client.println(SENSORNAME);
        delay(2);
        client.print("Date: ");
        client.println(RECENTDATE);
        delay(2);
        client.println("");

        // NEWEST DOWN: (i = (MEMORIES - 1); i >= 0; i--)
        // NEWEST UP:
        for (i = 0; i < MEMORIES; i++) {
          client.print("TIME: ");
          client.print(timearrayh[i]);
          client.print("h ");
          client.print(timearraym[i]);
          client.print("m ");
          client.print(timearrays[i]);
          client.print("s     DISTANCE: ");
          client.print(distancearray[i]);
          client.print(" cm\r\n");
          client.print("\r\n");
          delay(2);
        }

        client.println(".");
        delay(2);
        client.println("QUIT");
        delay(2);
        client.stop();

        ss = ss + 1; // not "precise", but better than nothing.
        break;

      }
    }
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

    if (recmin < 32767) {
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

    sixhours++;
    if (sixhours >= HOURS) {
      sixhours = 0;
      // telnet target mail server port 25
      // alterinatively, if you have a numeric ip: (client.connect(ip, 25))
      if (client.connect(TARGETMAILSERVER, 25)) {
        while (client.connected()) {
          Serial.println("= = = = = = = = PERIODIC E-MAIL = = = = = = = =");

          delay(5);
          client.print("HELO ");
          client.println(TARGETMAILSERVER);
          delay(160);
          client.print("MAIL FROM:");
          client.println(YOURSOURCEMAIL);
          delay(155);
          client.print("RCPT TO:");
          client.println(TARGETADDRESS);
          delay(155);
          client.println("DATA");
          delay(2);
          client.print("From: \"");
          client.print(SENSORNAME);
          client.print("\" ");
          client.println(YOURSOURCEMAIL);
          delay(2);
          client.print("To: \"");
          client.print(TARGETADDRESS);
          client.print("\" ");
          client.println(TARGETADDRESS);
          delay(2);
          client.print("Subject: ALIVE PING ");
          client.print(SENSORNAME);
          client.print(" ");
          client.print(hhhhhh);
          client.println(" h");
          delay(2);
          client.print("Date: ");
          client.println(RECENTDATE);
          delay(2);
          client.println("");

          client.print("SENSOR IS ACTIVE AND ONLINE: ");
          client.print(hhhhhh);
          client.print(" h    ");
          client.print(expectdist);
          client.println(" cm    ");

          // (HOURS < 6) ... but rather make it "anyway":
          if (1) {
            // NEWEST DOWN: (i = (MEMORIES - 1); i >= 0; i--)
            // NEWEST UP:
            for (i = 0; i < MEMORIES; i++) {
              client.print("TIME: ");
              client.print(timearrayh[i]);
              client.print("h ");
              client.print(timearraym[i]);
              client.print("m ");
              client.print(timearrays[i]);
              client.print("s     DISTANCE: ");
              client.print(distancearray[i]);
              client.print(" cm\r\n");
              client.print("\r\n");
              delay(2);
            }
          }

          client.println(".");
          delay(10);
          client.println("QUIT");
          delay(5);
          client.stop();

          ss = ss + 1; // not "precise", but better than nothing.
          break;

        }
      }
    }
  }
}
