#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// AD0 to ground
Adafruit_MPU6050 mpu_right;

// AD0 to vcc
Adafruit_MPU6050 mpu_left;

// rgb led pins
int red = 14;
int green = 15;
int blue = 12;

void setup(void) {
  Wire.begin();
  
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // Try to initialize first mpu!
  if (!mpu_right.begin(0x68)) {
    Serial.println("Failed to find MPU6050 chip at address 0x68");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 at address 0x68 found!");

  mpu_right.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu_right.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu_right.setFilterBandwidth(MPU6050_BAND_5_HZ);
  

  // Try to initialize first mpu!
  if (!mpu_left.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip at address 0x69");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 at address 0x69 found!");

  mpu_left.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu_left.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu_left.setFilterBandwidth(MPU6050_BAND_5_HZ);


  // initialize rgb led pins
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  getEmotion();
}

void getEmotion() {
  String rightPos = getMPUAccelerationRight();
  String leftPos = getMPUAccelerationLeft();
  
  if(rightPos == "seitwärts" && leftPos == "seitwärts") {
    Serial.print("Standard-Position");
    RGB_color(255, 255, 255);
  }
  if(rightPos == "oben" && leftPos == "oben") {
    Serial.print("Glücklich / Freude");
    RGB_color(0, 255, 0);
  }
  if(rightPos == "gesicht" && leftPos == "gesicht") {
    Serial.print("Traurig / Schämen");
    RGB_color(0, 0, 255);
  }

  Serial.println("");
  delay(1000);
}

String getMPUAccelerationRight() {
  sensors_event_t a, g, temp;
  mpu_right.getEvent(&a, &g, &temp);

  if(a.acceleration.x < 6 && a.acceleration.x > 1) {
    if(a.acceleration.y < -8 && a.acceleration.y > -11) {
      if(a.acceleration.z < 2 && a.acceleration.z > -2) {
        return "seitwärts";
      }
    }
  }

  if(a.acceleration.x < -7 && a.acceleration.x > -10) {
    if(a.acceleration.y < 0 && a.acceleration.y > -6) {
      if(a.acceleration.z < 5 && a.acceleration.z > -2) {
        return "oben";
      }
    }
  }

  if(a.acceleration.x < 2 && a.acceleration.x > -3) {
    if(a.acceleration.y < -8 && a.acceleration.y > -11) {
      if(a.acceleration.z < 1 && a.acceleration.z > -3) {
        return "gesicht";
      }
    }
  }
}

String getMPUAccelerationLeft() {
  sensors_event_t a, g, temp;
  mpu_left.getEvent(&a, &g, &temp);

  if(a.acceleration.x < 4 && a.acceleration.x > -2) {
    if(a.acceleration.y < 11 && a.acceleration.y > 8) {
      if(a.acceleration.z < 3 && a.acceleration.z > -1) {
        return "seitwärts";
      }
    }
  }

  if(a.acceleration.x < -6 && a.acceleration.x > -10) {
    if(a.acceleration.y < 5 && a.acceleration.y > 0) {
      if(a.acceleration.z < 6 && a.acceleration.z > -2) {
        return "oben";
      }
    }
  }

  if(a.acceleration.x < -3 && a.acceleration.x > -7) {
    if(a.acceleration.y < 10 && a.acceleration.y > 6) {
      if(a.acceleration.z < 1 && a.acceleration.z > -4) {
        return "gesicht";
      }
    }
  }
}

void RGB_color(int red_value, int green_value, int blue_value) {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}
