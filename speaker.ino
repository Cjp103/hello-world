#include "pitches.h"

// ----------------------------------------------------------------------------------
// Forehand
int melody1[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};  // notes in the melody

int durations1[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};  // note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.

int size1 = sizeof(melody1) / sizeof(melody1[0]);

// ----------------------------------------------------------------------------------
// Backhand
int melody2[] = {
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4
};

int durations2[] = {
  4, 4, 4, 4, 4, 4, 2
};

int size2 = sizeof(melody2) / sizeof(melody2[0]);

// ----------------------------------------------------------------------------------
// Serve
int melody3[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4
};

int durations3[] = {
  4, 4, 4, 4, 4, 4, 4
};

int size3 = sizeof(melody3) / sizeof(melody3[0]);

// ----------------------------------------------------------------------------------

void setup() {
  randomSeed(analogRead(0));  // no connect to this pin
}

// ----------------------------------------------------------------------------------

void loop() {

    int randomNumber = random(1,4);  // rand from 1 to 3

    switch(randomNumber){
      case 1:  // forehand

        for (int thisNote = 0; thisNote < size1; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / durations1[thisNote];

          // tone(output_pin)
          tone(8, melody1[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing at the output pin
          noTone(8);
        }

        break;      

      case 2:   // backhand

        for (int thisNote = 0; thisNote < size2; thisNote++) 
        {
          int noteDuration = 1000 / durations2[thisNote];

          tone(8, melody2[thisNote], noteDuration);

          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
      
          noTone(8);
        }      

        break;

      case 3:  // serve

        for (int thisNote = 0; thisNote < size3; thisNote++) 
        {
          int noteDuration = 1000 / durations3[thisNote];

          tone(8, melody3[thisNote], noteDuration);

          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
      
          noTone(8);
        }      

        break;

      default: 

        tone(8, 440, 1000);
        noTone(8);

    }
    



    

}
