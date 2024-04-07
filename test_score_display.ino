
// TESTING 7-SEGMENT DISPLAYS

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

float x = 0;
float y = 0;
float z = 0;

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

  // hex decoder inputs are active HIGH
  digitalWrite(A, LOW);  // 1's
  digitalWrite(B, LOW);  // 2's
  digitalWrite(C, HIGH);   // 4's
  digitalWrite(D, LOW);   // 8's
  digitalWrite(E, LOW);  // 1's (tens)
  digitalWrite(F, HIGH);   // 2's   (tens)

//-----------------------------------------------------------------------

while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    digitalWrite(8, HIGH);  // red
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
Vector normAccel = mpu.readNormalizeAccel();
    x = normAccel.XAxis;
    y = normAccel.YAxis;
    z = normAccel.ZAxis;

    if (x > 11)
    {
      digitalWrite(7, HIGH);  // green
      delay(1000);
      digitalWrite(7, LOW);
    }
}
