#include <SoftwareSerial.h>

SoftwareSerial miBT(10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("READY");
  miBT.begin(38400);
}

void loop() {
  if (miBT.available()){    // lee BT y envia a ARDUINOo
    Serial.write(miBT.read());
  }

  if(Serial.available()){   // lee SERIAL y envia a BT
    miBT.write(Serial.read());
  }

}
