
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#include <DS3231.h>
DS3231  rtc(SDA, SCL);
String d;
String D;
String t;

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;

void setup(void) {

  startFingerprintSensor();
  rtc.begin();
  
}

void loop() {

  fingerprintID = getFingerprintID();
  delay(50);
  if(fingerprintID == 1)
  {
    Serial.print("HI kantha's index");
    Serial.print(" ");
    d=rtc.getDOWStr();
    D=rtc.getDateStr();
    t=rtc.getTimeStr();
    Serial.print(" Entered at Time:");
    Serial.print(t);
    Serial.print(" at ");
    Serial.print(D);
    Serial.print(" on ");
    Serial.println(d);
    
    
  }

   if(fingerprintID == 2)
  {
    Serial.println("HI kantha's thumb");
    Serial.print(" Entered at Time:");
    Serial.print(t);
    Serial.print(" at ");
    Serial.print(D);
    Serial.print(" on ");
    Serial.println(d);
  }
}





void startFingerprintSensor()
{
  Serial.begin(9600);
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor");
  }
  Serial.println("Waiting for valid finger...");
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
