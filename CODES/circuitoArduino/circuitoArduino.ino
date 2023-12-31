/*
  Copyright (c) 2023 [Yoel Castillo]
 
  Este código ha sido escrito por mí, Yoel Castillo, para que lo uses de manera libre.
  He dedicado horas y horas a su creación, así que por favor, aprovéchalo.
  No se requiere atribución ni se impone ninguna restricción. Disfrútalo y úsalo bien.
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// PROTOTIPO DE FUNCIONES

int cuantosLedAEncender(float numericProgress);
void playMelody();

// MELODIA

#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_E6 1319
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_REST 0

int melody[] = {
  NOTE_E6, NOTE_D6, NOTE_C6, NOTE_D6,
  NOTE_E6, NOTE_D6, NOTE_C6, NOTE_D6,
  NOTE_G6, NOTE_E6, NOTE_A6, NOTE_A6,
  NOTE_G6, NOTE_E6, NOTE_D6, NOTE_D6,
  NOTE_C6, NOTE_E6, NOTE_G6, NOTE_G6,
  NOTE_A6, NOTE_A6, NOTE_A6, NOTE_REST
};

int noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4
};

// CARACTER CUADRADO COMPLETO PARA GRAFICA DEL PROGRESO EN LCD
byte solidBox[8] = {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
};

  double numericProgress = 0.0;

void setup(){
  lcd.createChar(0, solidBox);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop(){

  if (Serial.available()){
    String mensajeRecibido = Serial.readStringUntil('\n');
    numericProgress = mensajeRecibido.toDouble();

  }

  int graphicProgress = cuantosLedAEncender(numericProgress);

  lcd.home();
  lcd.print(numericProgress,15);
  lcd.setCursor(0,1);
  for (int x = 1; x<=graphicProgress;x++){
      lcd.write(byte(0));
    }
  
  while(numericProgress >= 100.0){
    lcd.clear();
    lcd.print(" ");
    lcd.print("Happy New Year");
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("   ");
    lcd.print("2024 Yoel!");
    lcd.print("   ");
    playMelody();
    delay(86400000); // NO MORE PLAYMELODY
    
  }

}

// FUNCIONES

void playMelody(){// NO HICE ESTA FUNCION NI LA DECLARACIONES DE LAS NOTAS
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++){
    // note duration
    int noteDuration = 250 / noteDurations[i];
    // play the note
    tone(9, melody[i], noteDuration);
    // delay between notes
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the actual tone
    noTone(9);
  }
}

int cuantosLedAEncender(double numericProgress){//DISTRIBUCION

  int vasAEncender = (16*numericProgress)/100;

  return vasAEncender;
}

