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
  // put your setup code here, to run once:
  // Initialize MPU6050
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // If you want, you can set gyroscope offsets
  // mpu.setGyroOffsetX(155);
  // mpu.setGyroOffsetY(15);
  // mpu.setGyroOffsetZ(15);
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
  
  // Check settings
  checkSettings();

}

//accelerometer
int x = 0;
int y = 0;
int z = 0;
//gyroscope
int zgyro = 0;
int ygyro = 0;
int xgyro = 0;
//game
int score = 0;
int gameDelay = 5100;

void loop() {
  //game code
  gameDelay -= 100;

  //give command
  int comm = random(1,3);

  for (int i=0;i<3000;i++){
    //beep;
  }

  switch(comm) {
    case 1:
      //call beep;
      //forehan
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
    score ++;
    //success sound
  }
  else{
    //whomp whomp sound
    exit;
  }

}

int readData () {
  
  int temp = gameDelay;
  int input = 0;

  //threshold values for game
  int xThresh = 0;
  int yThresh = 0;
  int zThresh = 0;

  do{
    Vector rawGyro = mpu.readRawGyro();
    Vector normGyro = mpu.readNormalizeGyro();
    x = normGyro.XAxis;
    y = normGyro.YAxis;
    z = normGyro.ZAxis;

    if(x > xThresh){
      //test to find out

    }

    temp -= 100;

  } while (temp != 0);

  return input;

}

void checkSettings(){
  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
  Serial.println();
}



// -------------------------MPU CODE------------------------------------------
// void setup() 
// {
//   Serial.begin(115200);

//   // Initialize MPU6050
//   Serial.println("Initialize MPU6050");
//   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
//   {
//     Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
//     delay(500);
//   }
  
//   // If you want, you can set gyroscope offsets
//   // mpu.setGyroOffsetX(155);
//   // mpu.setGyroOffsetY(15);
//   // mpu.setGyroOffsetZ(15);
  
//   // Calibrate gyroscope. The calibration must be at rest.
//   // If you don't want calibrate, comment this line.
//   mpu.calibrateGyro();

//   // Set threshold sensivty. Default 3.
//   // If you don't want use threshold, comment this line or set 0.
//   mpu.setThreshold(3);
  
//   // Check settings
//   checkSettings();
// }

// void checkSettings()
// {
//   Serial.println();
  
//   Serial.print(" * Sleep Mode:        ");
//   Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
//   Serial.print(" * Clock Source:      ");
//   switch(mpu.getClockSource())
//   {
//     case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
//     case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
//     case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
//     case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
//     case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
//     case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
//     case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
//   }
  
//   Serial.print(" * Gyroscope:         ");
//   switch(mpu.getScale())
//   {
//     case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
//     case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
//     case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
//     case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
//   } 
  
//   Serial.print(" * Gyroscope offsets: ");
//   Serial.print(mpu.getGyroOffsetX());
//   Serial.print(" / ");
//   Serial.print(mpu.getGyroOffsetY());
//   Serial.print(" / ");
//   Serial.println(mpu.getGyroOffsetZ());
  
//   Serial.println();
// }

// void loop()
// {
//   Vector rawGyro = mpu.readRawGyro();
//   Vector normGyro = mpu.readNormalizeGyro();

//   Serial.print(" Xraw = ");
//   Serial.print(rawGyro.XAxis);
//   Serial.print(" Yraw = ");
//   Serial.print(rawGyro.YAxis);
//   Serial.print(" Zraw = ");
//   Serial.println(rawGyro.ZAxis);

//   Serial.print(" Xnorm = ");
//   Serial.print(normGyro.XAxis);
//   Serial.print(" Ynorm = ");
//   Serial.print(normGyro.YAxis);
//   Serial.print(" Znorm = ");
//   Serial.println(normGyro.ZAxis);
  
//   delay(10);
// }
