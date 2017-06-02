#include <MechaQMC5883.h>
#include <Wire.h>
/*
 * MechaQMC5883 qmc(); //Default-Constructor is used, Object is named "qmc()"
 * MechaQMC5883 qmc;  //Default-Constructor is used, Objekt is named "qmc"
 * MechaQMC5883 qmc(0x0D); //Overloaded-Constructor is used, Objekt is named "qmc"
 */
 
// The LabVIEW.vi is located in ...\Documents\Arduino\libraries\GY271-Magnetometer-Fake\examples\LabVIEW-Demo

//Objects must be declared before Setup
MechaQMC5883 qmc(0x0D);

void setup() {
  Wire.begin();                                           //Is needed for the Sensor
  Serial.begin(9600);                                     //Is needed for print_xx-methods
  
  qmc.init();                                             //Init with Defaultmode
  qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_512);   //Change the Sensormode
}

void loop() {
  FLOATDATA floatValues;        //Typedef with three values of float-type (x,y,z)
  float temperature;            //Temperaturedata-Storage
 
  floatValues=qmc.get_uT();
  temperature=qmc.get_T();

  //Make Spreadsheet output for LabVIEW
  Serial.print(floatValues.x,3); //Print x
  Serial.print("\t");
  Serial.print(floatValues.y,3); //Print y
  Serial.print("\t");
  Serial.print(floatValues.z,3); //Print z
  Serial.print("\t");
  Serial.print(temperature,3); //Print z
  Serial.println();

}
