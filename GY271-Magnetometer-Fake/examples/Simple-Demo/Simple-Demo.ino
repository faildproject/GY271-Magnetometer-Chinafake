#include <MechaQMC5883.h>
#include <Wire.h>

//Objects must be declared before Setup
MechaQMC5883 qmc(0x0D);

void setup() {
  Wire.begin();                                           //Is needed for the Sensor
  Serial.begin(9600);                                     //Is needed for print_xx-methods
  
  qmc.init();                                             //Init with Defaultmode
  qmc.setMode(Mode_Continuous,ODR_10Hz,RNG_2G,OSR_512);   //Change the Sensormode
  qmc.setCalibValues(1.377,1.314,1.47);                   //Setup the CalibrationValues if needed in order of (x,y,z)
                                                          //To get these Values use the "Calibration.ino"  
}

void loop() {

  qmc.print_uT();                         //Print the Magneticfield in µT
  qmc.print_T();                          //Print the Temperature in °C
  
}
