
// TROUBLESHOOTING ACCELEROMETER


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

//MUST CALIBRATE FOR LOOP TO BE .5 SEC
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
