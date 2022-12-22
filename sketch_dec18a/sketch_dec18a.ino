Code: 
#define DEBUG 0 
 
// 6 consecutive digital pins for the LEDs 
int first = 2; 
int second = 3; int third = 4; int fourth = 5; int fifth = 6; int sixth = 7; 
 
// View analog for the output of Clapswitch int analog = A0; 
// value to check state of analog int val = 0;  void setup() { 
  // set all LED pins to OUTPUT 
  for (int i=first; i<=sixth; i++) { 
    pinMode(i, OUTPUT); 
  } 
  // set analog to INPUT 
  pinMode(analog,INPUT); 
  
  // initialize random seed by noise from analog pin 0 (should be unconnected)   randomSeed(analogRead(0)); 
 
// if we're debugging, connect to serial  
  #ifdef DEBUG 
    Serial.begin(38400); 
  #endif 
 
} 
 
void buildUpTension() { 
  // light LEDs from left to right and back to build up tension 
  // while waiting for the dice to be thrown 
 
  // left to right   for (int i=first; i<=sixth; i++) { 
    if (i!=first) { 
      digitalWrite(i-1, LOW); 
    } 
    digitalWrite(i, HIGH);     delay(100); 
  }   // right to left   for (int i=sixth; i>=first; i--) {     if (i!=sixth) { 
      digitalWrite(i+1, LOW); 
    } 
    digitalWrite(i, HIGH);     delay(100); 
  } 
} 
 
void showNumber(int number) { 
  digitalWrite(first, HIGH);   if (number >= 2) {     digitalWrite(second, HIGH); 
  } 
  if (number >= 3) {     digitalWrite(third, HIGH);     
  } 
  if (number >= 4) {     digitalWrite(fourth, HIGH);     
  } 
  if (number >= 5) {     digitalWrite(fifth, HIGH);     
  } 
  if (number == 6) {     digitalWrite(sixth, HIGH);     
  } 
} 
 
int throwDice() { 
  // get a random number in the range [1,6]   int randNumber = random(1,7); 
   
  #ifdef DEBUG 
    Serial.println(randNumber); 
  #endif 
   
  return randNumber; 
} 
 
void setAllLEDs(int value) { 
  for (int i=first; i<=sixth; i++) {     digitalWrite(i, value); 
  } 
} 
 
void loop() {   val = analogRead(analog);   if (val > 600){ 
    // remove previous number     setAllLEDs(LOW); 
     
    buildUpTension();     int thrownNumber = throwDice();     showNumber(thrownNumber); 
    delay(1000); 
     setAllLEDs(LOW); 
  }  
//View state analog in Arduino software 
  Serial.println(val); 
}