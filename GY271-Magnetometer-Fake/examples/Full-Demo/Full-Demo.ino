#include <MechaQMC5883.h>
#include <Wire.h>
/*
 * MechaQMC5883 qmc(); //Default-Constructor is used, Object is named "qmc()"
 * MechaQMC5883 qmc;  //Default-Constructor is used, Objekt is named "qmc"
 * MechaQMC5883 qmc(0x0D); //Overloaded-Constructor is used, Objekt is named "qmc"
 */

//Objects must be declared before Setup
MechaQMC5883 qmc(0x0D);

void setup() {
  Wire.begin();                                           //Is needed for the Sensor
  Serial.begin(9600);                                     //Is needed for print_xx-methods
  
  qmc.init();                                             //Init with Defaultmode
  qmc.setMode(Mode_Continuous,ODR_10Hz,RNG_8G,OSR_512);   //Change the Sensormode
  qmc.setCalibValues(1.377,1.314,1.47);                   //Setup the CalibrationValues if needed in order of (x,y,z)
                                                          //To get these Values use the "Calibration.ino"  
}

void loop() {
  RAWDATA rawValues;            //Typedef with three values on int-type (x,y,z)
  FLOATDATA floatValues;        //Typedef with three values of float-type (x,y,z)

  //#########Read the RAW-Data#######################
  rawValues=qmc.getRaw();
  Serial.println();
  Serial.println("------Begin------");
  Serial.print("Raw x: ");
  Serial.print(rawValues.x);
  Serial.print(" y: ");
  Serial.print(rawValues.y);
  Serial.print(" z: ");
  Serial.print(rawValues.z);
  Serial.println();

  Serial.println();
  //#########Testing the calculating-Functions#######
  floatValues=qmc.calc_mT(rawValues);
  Serial.print("Function calc_mT x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  floatValues=qmc.calc_Gaus(rawValues);
  Serial.print("Function calc_Gaus x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  floatValues=qmc.calc_uT(rawValues);
  Serial.print("Function calc_uT x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  Serial.println();
  //#########Testing getFunctions##########
  floatValues=qmc.get_mT();
  Serial.print("Test get_mT x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  floatValues=qmc.get_Gaus();
  Serial.print("Test get_Gaus x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  floatValues=qmc.get_uT();
  Serial.print("Test get_uT x: ");
  Serial.print(floatValues.x,3);
  Serial.print(" y: ");
  Serial.print(floatValues.y,3);
  Serial.print(" z: ");
  Serial.print(floatValues.z,3);
  Serial.println();

  Serial.println();
  //##########Test the direct Print-Fkt##########
  Serial.println("Testing direct Print");
  qmc.print_Raw();                        //Need "Serial.begin()" in Setup
  qmc.print_Gaus();                       //Need "Serial.begin()" in Setup
  qmc.print_mT();                         //Need "Serial.begin()" in Setup
  qmc.print_uT();                         //Need "Serial.begin()" in Setup
  Serial.println("Change precision");
  qmc.print_Gaus(5);                      //Need "Serial.begin()" in Setup
  qmc.print_mT(5);                        //Need "Serial.begin()" in Setup
  qmc.print_uT(5);                        //Need "Serial.begin()" in Setup
  Serial.println("Printing Temperatures");
  qmc.print_RawT();                       //Need "Serial.begin()" in Setup
  qmc.print_T();                          //Need "Serial.begin()" in Setup
  qmc.print_T(5);                          //Need "Serial.begin()" in Setup
  Serial.println("------End------");
}
