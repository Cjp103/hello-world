/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;


//------------------------------Game Code------------------------------------
void setup() {

  Serial.begin(115200);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }


}

//accelerometer
int x = 0;
int y = 0;
int z = 0;

//game
int score = 0;
int gameDelay = 51000;

void loop() {
  //game code
  gameDelay -= 1000;

  //give command
  int comm = random(1,4);

  for (int i=0;i<3000;i++){
    //beep;
  }

  switch(comm) {
    case 1:
      //call beep;
      //forehand
      break;
    case 2:
      //call beep x 2
      //backhand
      break;
    case 3:
      //call beep x 3
      //serve
      break;
  }

  int temp = gameDelay;
  int input = readData();

  if (input == comm){
    score++;
    //success sound
  }
  else{
    //whomp whomp sound
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

/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/


// void setup() 
// {
//   Serial.begin(115200);

//   Serial.println("Initialize MPU6050");

//   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
//   {
//     Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
//     delay(500);
//   }

//   // If you want, you can set accelerometer offsets
//   // mpu.setAccelOffsetX();
//   // mpu.setAccelOffsetY();
//   // mpu.setAccelOffsetZ();
  
//   checkSettings();
// }


// void loop()
// {


//   Serial.print(" Xraw = ");
//   Serial.print(rawAccel.XAxis);
//   Serial.print(" Yraw = ");
//   Serial.print(rawAccel.YAxis);
//   Serial.print(" Zraw = ");

//   Serial.println(rawAccel.ZAxis);
//   Serial.print(" Xnorm = ");
//   Serial.print(normAccel.XAxis);
//   Serial.print(" Ynorm = ");
//   Serial.print(normAccel.YAxis);
//   Serial.print(" Znorm = ");
//   Serial.println(normAccel.ZAxis);
  
//   delay(10);
// }




