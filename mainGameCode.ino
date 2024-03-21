// Kappa Bop-it Project

//define pitches
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#include <MPU6050.h>

MPU6050 mpu;

// -----------------------------------Initialize-------------------------------------
// Game Start (Wii Theme)
int theme[] = {
  0, 0, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_G4
};  // notes in the melody

int themeDurations[] = {
  8, 8, 8, 8, 3, 3, 4, 2, 2
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int themeSize = sizeof(theme) / sizeof(theme[0]);

// ----------------------------------------------------------------------------------

// Game End (Minor Wii Theme)
int minorTheme[] = {
  0, 0, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_G4
};  // notes in the melody

int minorThemeDurations[] = {
  8, 8, 8, 8, 3, 3, 4, 2, 2
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int minorThemeSize = sizeof(minorTheme) / sizeof(minorTheme[0]);

// ----------------------------------------------------------------------------------


// Forehand
int forehand[] = {
  NOTE_C5
};  // notes in the melody

int forehandDurations[] = {
  4
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int forehandSize = sizeof(forehand) / sizeof(forehand[0]);

// ----------------------------------------------------------------------------------
// Backhand
int backhand[] = {
  NOTE_C5, NOTE_C5
};

int backhandDurations[] = {
  4, 4
};

int backhandSize = sizeof(backhand) / sizeof(backhand[0]);

// ----------------------------------------------------------------------------------
// Serve
int serve[] = {
  NOTE_C5, NOTE_C5, NOTE_C5
};

int serveDurations[] = {
  4, 4, 4
};

int serveSize = sizeof(serve) / sizeof(serve[0]);

// ----------------------------------------------------------------------------------

//accelerometer
int x = 0;
int y = 0;
int z = 0;

//game
int bScore[6];
int score = 0;
int gameDelay = 51000;

//hex pins
int A = 4;
int B = 3; 
int C = 2; 
int D = 5; 
int E = 9; 
int F = 10;

// ----------------------------------------------------------------------------------
// -----------------------------------Game Code--------------------------------------


void setup() {

  pinMode(7, OUTPUT);   // green
  pinMode(8, OUTPUT);   // red
  // put your setup code here, to run once:
  Serial.begin(115200);

  // testing hex displays
  int D = 5; int C = 2; int B = 3; int A = 4;
  int E = 9; int F = 10;
  pinMode(F, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(A, OUTPUT);
    
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

  //score display
  hexDisplay(score);
  //give command    
  int comm = random(1,4);

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
        delay(10000);
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

void hexDisplay(int score){
    int TOTAL [6];
	int one = score % 10;
	int ten = score / 10;
	int ones[4];
	int tens[4];
	
	for (int i=0;i<4;i++){
		ones[i] = one % 2;
		one /= 2;
	}
	
	for (int q=0;q<4;q++){
		tens[q] = ten % 2;
		ten /= 2;
	}
	
	TOTAL[5] = ones[0];
	TOTAL[4] = ones[1];
	TOTAL[3] = ones[2];
	TOTAL[2] = ones[3];
	TOTAL[1] = tens[0];
	TOTAL[0] = tens[1];

   // hex decoder inputs are active HIGH
   digitalWrite(A, TOTAL[5]);  // 1's 
   digitalWrite(B, TOTAL[4]);  // 2's
   digitalWrite(C, TOTAL[3]);   // 4's
   digitalWrite(D, TOTAL[2]);   // 8's
   digitalWrite(E, TOTAL[1]);  // 1's (tens)
   digitalWrite(F, TOTAL[0]);   // 2's   (tens)
		    
}
