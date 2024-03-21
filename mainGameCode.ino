/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>
#include <pitches.h>

MPU6050 mpu;

// -----------------------------------Initialize-------------------------------------
// Game Start (Wii Theme)
int theme[] = {
  0, 0, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_G4
};  // notes in the melody

int themeDurations[] = {
  8, 8, 8, 8, 3, 3, 4, 2, 2
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int themeSize = sizeof(melody1) / sizeof(melody1[0]);

// ----------------------------------------------------------------------------------

// Game End (Minor Wii Theme)
int minorTheme[] = {
  0, 0, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_G4
};  // notes in the melody

int minorThemeDurations[] = {
  8, 8, 8, 8, 3, 3, 4, 2, 2
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int minorThemeSize = sizeof(melody1) / sizeof(melody1[0]);

// ----------------------------------------------------------------------------------


// Forehand
int forehand[] = {
  NOTE_C5
};  // notes in the melody

int forehandDurations[] = {
  4
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int forehandSize = sizeof(melody1) / sizeof(melody1[0]);

// ----------------------------------------------------------------------------------
// Backhand
int backhand[] = {
  NOTE_C5, NOTE_C5
};

int backhandDurations[] = {
  4, 4
};

int backhandSize = sizeof(melody2) / sizeof(melody2[0]);

// ----------------------------------------------------------------------------------
// Serve
int serve[] = {
  NOTE_C5, NOTE_C5, NOTE_C5
};

int serveDurations[] = {
  4, 4, 4
};

int serveSize = sizeof(melody3) / sizeof(melody3[0]);

// ----------------------------------------------------------------------------------

//accelerometer
int x = 0;
int y = 0;
int z = 0;

//game
int score = 0;
int gameDelay = 51000;

// ----------------------------------------------------------------------------------
// -----------------------------------Game Code--------------------------------------


void setup() {

  Serial.begin(115200);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  randomSeed(analogRead(0));  // no connection to this pin

}

void loop() {

    //update delay
    gameDelay -= 1000;
    //give command
    int comm = random(1,4);

    //   for (int i=0;i<3000;i++){
    //     //beep;
    //   }

  //play them if score is 0
  if(score == 0){
    for (int thisNote = 0; thisNote < themeSize; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / themeDurations[thisNote];

          // tone(output_pin)
          tone(8, theme[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
    }
  }
  

  switch(comm) {
    case 1:
      //call forehand (1 beep)

        for (int thisNote = 0; thisNote < forehandSize; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / forehandDurations[thisNote];

          // tone(output_pin)
          tone(8, forehand[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
        }

      break;

    case 2:
      //call backhand (2 beeps)

        for (int thisNote = 0; thisNote < backhandSize; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / backhandDurations[thisNote];

          // tone(output_pin)
          tone(8, backhand[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
        }  

      break;

    case 3:
      //call serve (3 beeps)

        for (int thisNote = 0; thisNote < serveSize; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / serveDurations[thisNote];

          // tone(output_pin)
          tone(8, serve[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
        }  

      break;
  }

  int temp = gameDelay;
  int input = readData();

  if (input == comm){
    score++;
    //success sound
    tone(8, NOTE_C4);
    tone(8, NOTE_E4);
    tone(8, NOTE_G4);
    tone(8, NOTE_C5);
    delay(2000);

    noTone(8);
  }
  else{
    //whomp whomp sound
        for (int thisNote = 0; thisNote < minorThemeSize; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / minorThemeDurations[thisNote];

          // tone(output_pin)
          tone(8, minorTheme[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
     
        }
        exit(-1); 
    }

}



int readData () {

  int temp = gameDelay;
  int input = 0;

  do{
    Vector normAccel = mpu.readNormalizeAccel();
    x = normAccel.XAxis;
    y = normAccel.YAxis;
    z = normAccel.ZAxis;

    bool serve = false;
    bool forehand = false;
    bool backhand = false;


//serve reading
    if(y < -16){ 
      return 3; 
    }

//forehand reading

//MUST CALIUBRATE FOR LOOP TO BE .5 SEC
    if(x > 16){ 
      int i = 10;
      do{
        delay(50);
        if(y < -16) {serve = true;}
        i--;
      }while(i>0);
        
      if (serve) {return 3;}
      else {return 1;}
    }

//backhand reading
    if(x < -16){ 
      int i = 10;
      do{
        delay(50);
        if(y < -16) {serve = true;}
        i--;
      }while(i>0);

      if (serve) {return 3;}
      else {return 2;}

    }
    temp -= 100;

  } while (temp != 0);

  return input;

}
