const int red_led = 4;
const int yellow_led = 7;
const int green_led = 5;
const int blue_led = 6;
const int red_button = 2;
const int yellow_button = 9;
const int green_button = 3;
const int blue_button = 10;

int red_state;
int yellow_state;
int green_state;
int blue_state;

int i = 0, count = 0, t = 0, mistake = 0, move = 0, n;
int simon_sequence[100];

// functions
void correct(void);
void lost(void);
int get_answer(void);

void setup() {
  
  Serial.begin(9600);
   
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  pinMode(red_button, INPUT);
  pinMode(yellow_button, INPUT);
  pinMode(green_button, INPUT);
  pinMode(blue_button, INPUT);
 
  pinMode(8, OUTPUT); // speaker (theremin)

  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);

  delay(2800);

}

void loop() {
  
  randomSeed(analogRead(0)); // unconnected pin
  delay(2);

  n = random(4, 8); // random between 4 and 7

  simon_sequence[i] = n; 

  // Show the sequence to follow
  for (t = 0; t <= i; t++) {                                                      
    if (simon_sequence[t] == 6) {
      analogWrite(simon_sequence[t], 167);
    } else {
      digitalWrite(simon_sequence[t], HIGH);
    }
    tone(8, 350);
    delay(450);
    digitalWrite(simon_sequence[t], LOW);
    noTone(8);
    delay(600);
  }
                     
  do { 
    do {
      move = get_answer();
    } while (!move);
     
    delay(300);
    
    if (move != simon_sequence[count]) {
      mistake = 1;
    }
                               
    noTone(8);
    count++;

  } while(count <= i && !mistake); // Keep pressing buttons until the sequence is complete

  i++;
  count = 0;

  if (mistake) {
    i = 0;
    mistake = 0;
    lost();
  }

  delay(1300);

}

void lost(void) { // it reproduces the sound of super mario bros when someone loses

  delay(500);

  tone(8, 493, 250);
  for (int j = 4; j <= 7; j++) {
    if (j == 6) {
      analogWrite(j, 167);
    } else {
      digitalWrite(j, HIGH);        
    }
  }
  delay(300); 

  tone(8, 698, 265);
  for (int j = 4; j <= 7; j++) {
    digitalWrite(j, LOW);
  }
  delay(540);

  tone(8, 698, 250);
  for (int j = 4; j <= 7; j++) {
    if (j == 6) {
      analogWrite(j, 167);
    } else {
      digitalWrite(j, HIGH);        
    }
  }
  delay(300);                     

  tone(8, 698, 250);              
  for (int j = 4; j <= 7; j++) {
    digitalWrite(j, LOW);
  }
  delay(300);

  tone(8, 659, 250);
  for (int j = 4; j <= 7; j++) {
    if (j == 6) {
      analogWrite(j, 167);
    } else {
      digitalWrite(j, HIGH);         
    }
  }
  delay(300);                     

  tone(8, 587, 250);               
  for (int j = 4; j <= 7; j++) {
    digitalWrite(j, LOW);
  }
  delay(300);

  tone(8, 523, 250);
  for (int j = 4; j <= 7; j++) {
    if (j == 6) {
      analogWrite(j, 167);
    } else {
      digitalWrite(j, HIGH);      
    }
  }
  delay(600);                     

  tone(8, 329, 280);               
  for (int j = 4; j <= 7; j++) {
    digitalWrite(j, LOW);
  }
  delay(500);
}

int get_answer(void) {
  
  red_state = digitalRead(red_button);   
  if (red_state == HIGH) {
    tone(8, 350);  
    return red_led;
  }
  delay(5);

  yellow_state = digitalRead(yellow_button);  
  if (yellow_state == HIGH) {
    tone(8, 350);  
    return yellow_led;
  }
  delay(5);

  green_state = digitalRead(green_button);  
  if (green_state == HIGH) {
    tone(8, 350);  
    return green_led;
  }
  delay(5);

  blue_state = digitalRead(blue_button);   
  if (blue_state == HIGH) {
    tone(8, 350);  
    return blue_led;
  }
  delay(5);
   
  return 0;
}
