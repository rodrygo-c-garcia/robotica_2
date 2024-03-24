
int ledGreen = 52;
int ledBlue = 53;
int option;

void setup() {
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}

void loop() {
  
  if(Serial.available() > 0 ) {
    //leemos lo que se envian a travez del Serial
    option = Serial.read();
      
    if(option == 'G'){
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledBlue, LOW);  
    } 
    if(option == 'B')  {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, HIGH); 
    }
    if (option == '1') {
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledBlue, HIGH);
    } 
    if (option == '0') {
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
    }
    
  }

  
}
