
int ledGreen = 52;
int ledBlue = 53;
int ledRed = 50;
int ledYellow = 51;
int option;

void setup() {
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}

void loop() {
  
  if(Serial.available() > 0 ) {
    //leemos lo que se envian a travez del Serial
    option = Serial.read();
      
    if(option == 'G'){
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, LOW);
    } 
    if(option == 'B')  {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, LOW);
    }
    if(option == 'R')  {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledYellow, LOW); 
    }
    if(option == 'Y')  {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, HIGH); 
    }
    if (option == '1') {
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledYellow, HIGH);
    } 
    if (option == '0') {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, LOW);
    }
    
  }

  
}
