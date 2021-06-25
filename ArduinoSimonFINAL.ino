float posX;
float posY;
bool gameBegin;
bool pointPlus;

int dificultyLvl;
int nbLeds;
String oldSequence; 
int buttonState = 0; // current state of the button
int lastButtonState = 1;
int buttonPushCounter = 1;

void setup()
{
  pinMode(0, OUTPUT); // barre horizontale haute
  pinMode(1, OUTPUT); // barre verticale haute droite
  pinMode(2, OUTPUT); // barre verticale bas droite
  pinMode(3, OUTPUT); // barre horizontale bas
  pinMode(4, OUTPUT); // barre verticale bas gauche
  pinMode(5, OUTPUT); // barre verticale haut gauche
  pinMode(6, OUTPUT); // barre horizontale milieu
  pinMode(7, OUTPUT); // LED Verte
  pinMode(8, OUTPUT); // LED Rouge
  pinMode(9, OUTPUT); // LED Jaune
  pinMode(10, OUTPUT); // LED Blanche 
  pinMode(11, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  nbLeds = 1;
  dificultyLvl = 1;
  gameBegin = false;
  selectLvl();
  while(true){
    wholeGame();
  }
}




//GAME----------------------------------------------------
void wholeGame(){
 
  if(gameBegin){
     if(game()){
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        for (int i = 0; i <60; i++) 
        {
           digitalWrite(11, HIGH);
           delay(6);
           digitalWrite(11, LOW);
           delay(6); 
        }
         ledLighting(-1);
         nbLeds = 1;
         selectLvl();
      }else{
        for (int y = 0; y < 4; y++){
          ledLighting(y);
        }
        ledLighting(0);
        for (int y = 3; y > -1; y--){
          ledLighting(y);
        }
        for (int z = 0; z < 4; z++){
          ledLighting(-2);
          delay(150);
          ledLighting(-1);
          delay(150);
        }
        nbLeds++;
      }
  }
}
bool game() {
  char typeLeds[nbLeds];
  oldSequence.toCharArray(typeLeds, nbLeds * sizeof(char)); 
  int input = 0;
  pointPlus = false;
  int idLed = -1;
  bool error = false;

  // ANIMATION
  for (int y = 0; y < 4; y++){
    ledLighting(y);
    delay(150);
    ledLighting(-1);
  }
  
  for (int z = 0; z < 4; z++){
    ledLighting(-2);
    delay(150);
    ledLighting(-1);
    delay(150);
  }
  // END ANIMATION
  
  delay (750); // Temporisation

  //GENERATION COULEUR
  randomSeed(analogRead(13));
  
  typeLeds[nbLeds - 1] = random(0, 4);

  //DISPLAY SEQUENCE
  for (int h = 0; h < nbLeds; h++) {
    ledLighting(typeLeds[h]);
    delay(200 * (dificultyLvl));
    ledLighting(-1);
    delay(1);
  }
  
  while (input < nbLeds && !error) { //&& !error
    //digitalWrite(0, HIGH);
    //digitalWrite(1, HIGH);
    //digitalWrite(2, HIGH);
    //digitalWrite(3, HIGH);
    
    posX = analogRead(A0);
    delay(100);
    posY = analogRead(A1);
    
    if (posX < 100) {
      idLed = 0; // 0 -> VERT
      pointPlus = true;
    }
    else if(posX > 923) {
      idLed = 2;
      pointPlus = true;
    }
    else if (posY < 100) {
      idLed = 1;
      pointPlus = true;
    }
    else if (posY > 924) {
      idLed = 3;
      pointPlus = true;
    }
    if(pointPlus && (posX < 600 && posX > 400) && (posY < 600 && posY > 400)){
     
      ledLighting(idLed);
      ledLighting(-1);
      if(typeLeds[input] != idLed && pointPlus) {
        error = true;
       }
      idLed = -1;
      pointPlus = false;
      input++;
    }
  }

 delay(500);

 oldSequence = String(typeLeds);
 return error;
  
}
//-----------------------------------------------------------------------

void selectLvl(){
   digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  buttonPushCounter = 1;
  while(true){
    buttonState = digitalRead(12); 
    if (buttonState != lastButtonState) {
        if (buttonState == LOW) {
          buttonPushCounter++;
        }
    }
    
      posY = analogRead(A0);
      if (posY < 100) {
        if(dificultyLvl > 1){
          dificultyLvl--;
          delay(250);
        }
      }
      else if (posY > 924) {
        if(dificultyLvl < 4){
          dificultyLvl++;
          delay(250);
        }
      }
      lightingLvl(dificultyLvl);
 
    lastButtonState = buttonState;
    if (buttonPushCounter % 2 == 0) {
      gameBegin = true;
      break;
    } 
 }
}
  
void lightingLvl(int lvl) {
  switch (lvl) {
    case 1: // Vert
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(1, LOW);
    digitalWrite(0, LOW);
      break;
    case 2: // Vert
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(0, LOW);
      break;
    case 3: // Vert
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(0, LOW);
      break;
    case 4: // Vert
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(0, HIGH);
      break;
    default:
     digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(0, HIGH);
    break;
  }
}
void ledLighting(int led) {

  Serial.print(led + "  ");
  
  
  switch (led) {
    case 0: // Vert
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
       for (int i = 0; i <25; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(5);
          digitalWrite(11, LOW);
          delay(5);
        }
      break;

    case 1: // Rouge
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      for (int i = 0; i <50; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(2);
          digitalWrite(11, LOW);
          delay(2);
        }
      break;

    case 2: // Jaune
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
       for (int i = 0; i <33; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(3);
          digitalWrite(11, LOW);
          delay(3);
        }
      break;

    case 3: // Blanche
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
       for (int i = 0; i <25; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(4);
          digitalWrite(11, LOW);
          delay(4);
        }
      break;

    case -2: 
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
       for (int i = 0; i <20; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(1);
          digitalWrite(11, LOW);
          delay(1);
        }
      break;
      
    default:
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      break;
  }
}
  
  /*if(buttonState =! lastButtonState){
    for (int z = 0; z < 4; z++){
        digitalWrite(0, HIGH);
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
       for (int i = 0; i <6; i++) // When a frequency sound
        {
          digitalWrite(11, HIGH);
          delay(8);
          digitalWrite(11, LOW);
          delay(8);
        }
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
       delay(150);
    }

    buttonState = 0;
    lastButtonState = 0;
    buttonState = digitalRead(12);
    while(buttonState == lastButtonState){
       posY = analogRead(A1);
      if (posY < 100) {
        if(dificultyLvl > 1){
          dificultyLvl--;
        }
      }
      else if (posY > 924) {
        if(dificultyLvl < 4){
          dificultyLvl++;
        }
      }
      
      lightingLvl(3);
      lastButtonState = buttonState;
    }
  }
  delay(2000);*/
