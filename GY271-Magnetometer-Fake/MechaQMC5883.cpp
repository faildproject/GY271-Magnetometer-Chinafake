#include "MechaQMC5883.h"
#include <Wire.h>

//####Public Methods####

//Default-Constructor
MechaQMC5883::MechaQMC5883(){
  setAddress(QMC5883_ADDR);
  setCalibValues(1, 1, 1);
}

//Overloaded-Constructor
MechaQMC5883::MechaQMC5883(uint8_t addr){
  setAddress(addr);
  setCalibValues(1, 1, 1);
}

//Initialize the Sensor and setup the Defaultmode
void MechaQMC5883::init(){
  WriteReg(0x0B,0x01);
  //Define Set/Reset period
  setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
  /*
  Define
  OSR = 512
  Full Scale Range = 8G(Gauss)
  ODR = 200HZ
  set continuous measurement mode
  */
}

//Change the mode of the Sensor
void MechaQMC5883::setMode(uint8_t mode,uint8_t odr,uint8_t rng,uint8_t osr){
  WriteReg(0x09,mode|odr|rng|osr);
  //Calculate the resolution of the ADC
  switch (rng){
    case RNG_2G:
      resolution =(float)4/65535;     //ADC has a resolution of 16-Bit (65536) (float)=explizit typecast
      break;                          //break ends the case
    case RNG_8G:
      resolution =(float)16/65535;
      break;
    default:
      resolution =(float)4/65535;
      break;
  }
}

//Setup calibration-values. To get these Values use the "Calibration.ino"
void MechaQMC5883::setCalibValues(float x, float y, float z){
  calib_x=x;
  calib_y=y;
  calib_z=z;
}

//#########Measurement-Methods for Magneticfield########

//Reading the RAW-Data from Sensor
RAWDATA MechaQMC5883::getRaw(){
  Wire.beginTransmission(address);    //Start talking
  Wire.write(0x00);                   // go to Register 0x00
  Wire.endTransmission();             //Stop talking
  Wire.requestFrom(address, 6);       //read 6-Bytes (Reg 0x00 to 0x05

  //Transform the Data
  xyzRAW.x = Wire.read(); //LSB  x
  xyzRAW.x |= Wire.read() << 8; //MSB  x
  xyzRAW.y = Wire.read(); //LSB  z
  xyzRAW.y |= Wire.read() << 8; //MSB z
  xyzRAW.z = Wire.read(); //LSB y
  xyzRAW.z |= Wire.read() << 8; //MSB y
  return xyzRAW;
}

//reading Raw and calc Gaus
FLOATDATA MechaQMC5883::get_Gaus(){
  return calc_Gaus(getRaw());
}

//reading Raw and calc mT
FLOATDATA MechaQMC5883::get_mT(){
  return calc_mT(getRaw());      
}

//reading Raw and calc uT
FLOATDATA MechaQMC5883::get_uT(){
  return calc_uT(getRaw());      
}

//Calculate the Gaus-Value from a RAW-Value
FLOATDATA MechaQMC5883::calc_Gaus(RAWDATA xyzRAW){
  xyzFLOAT.x=xyzRAW.x*resolution*calib_x;
  xyzFLOAT.y=xyzRAW.y*resolution*calib_y;
  xyzFLOAT.z=xyzRAW.z*resolution*calib_z;
  return xyzFLOAT;
}

//Calculate the mT-Value from a RAW-Value
FLOATDATA MechaQMC5883::calc_mT(RAWDATA xyzRAW){
  xyzFLOAT.x=xyzRAW.x*resolution*0.1*calib_x;
  xyzFLOAT.y=xyzRAW.y*resolution*0.1*calib_y;
  xyzFLOAT.z=xyzRAW.z*resolution*0.1*calib_z;
  return xyzFLOAT;
}

//Calculate the uT-Value from a RAW-Value
FLOATDATA MechaQMC5883::calc_uT(RAWDATA xyzRAW){
  xyzFLOAT.x=xyzRAW.x*resolution*100*calib_x;
  xyzFLOAT.y=xyzRAW.y*resolution*100*calib_y;
  xyzFLOAT.z=xyzRAW.z*resolution*100*calib_z;
  return xyzFLOAT;
}

//print Sensordata directly in Raw-Format
void MechaQMC5883::print_Raw(){
  getRaw();
  Serial.print("|x=");
  Serial.print(xyzRAW.x);
  Serial.print("|y=");
  Serial.print(xyzRAW.y);
  Serial.print("|z=");
  Serial.print(xyzRAW.z);
  Serial.println("|RAW");
  
}

//print Sensordata directly in Gaus-Format
void MechaQMC5883::print_Gaus(){
  get_Gaus();
  print_float();
  Serial.println("Gaus");
}

//print Sensordata directly in mT-Format
void MechaQMC5883::print_mT(){
  get_mT();
  print_float();
  Serial.println("mT");
  
}

//print Sensordata directly in uT-Format
void MechaQMC5883::print_uT(){
  get_uT();
  print_float();
  Serial.println("uT");
}

//print Sensordata directly in Gaus-Format and set precision
void MechaQMC5883::print_Gaus(int dez){
  get_Gaus();
  print_float(dez);
  Serial.println("Gaus");
}

//print Sensordata directly in mT-Format and set precision
void MechaQMC5883::print_mT(int dez){
  get_mT();
  print_float(dez);
  Serial.println("mT");
  
}

//print Sensordata directly in uT-Format and set precision
void MechaQMC5883::print_uT(int dez){
  get_uT();
  print_float(dez);
  Serial.println("uT");
}

//#########Measurement-Methods for Temperature########

//reading Raw from Reg
int MechaQMC5883::getRawT(){
  Wire.beginTransmission(address);    //Start talking
  Wire.write(0x07);                   // go to Register 0x00
  Wire.endTransmission();             //Stop talking
  Wire.requestFrom(address, 2);       //read 2-Bytes (Reg 0x07 to 0x08)

  //Transform the Data
  TRAW = Wire.read(); //LSB  x
  TRAW |= Wire.read() << 8; //MSB  x
  return TRAW;
}

//reading Raw-Temp and calc °C
float MechaQMC5883::get_T(){
  return calc_T(getRawT());
}

//Calculate the °C from RAW
float MechaQMC5883::calc_T(int RAWT){
  T=(float)RAWT/100+40;
  return T;
}

//print Temperature directly in Raw-Format
void MechaQMC5883::print_RawT(){
  Serial.print("|Temp=");
  Serial.print(getRawT());
  Serial.println("|RAW");
}

//print Temperature directly in °C
void MechaQMC5883::print_T(){
  Serial.print("|Temp=");
  Serial.print(get_T());
  Serial.println("|C");
}

//print Temperature directly in °C (var precision)
void MechaQMC5883::print_T(int dez){
  Serial.print("|Temp=");
  Serial.print(get_T(),dez);
  Serial.println("|C");  
}

  //####################################################

//Perform a Sensorreset
void MechaQMC5883::softReset(){
  WriteReg(0x0A,0x80);
}

//####Private Methods####

//Setup the I2C-Address
void MechaQMC5883::setAddress(uint8_t addr){
  address = addr;
}

//Change a Sensorregister
void MechaQMC5883::WriteReg(byte Reg,byte val){
  Wire.beginTransmission(address);  // start talking
  Wire.write(Reg);                  // Change Registeraddress
  Wire.write(val);                  // Set the Register
  Wire.endTransmission();           // stop talking
}

//Printing floatvalues from typedef with var precision
void MechaQMC5883::print_float(int digit){
  Serial.print("|x=");
  Serial.print(xyzFLOAT.x,digit);
  Serial.print("|y=");
  Serial.print(xyzFLOAT.y,digit);
  Serial.print("|z=");
  Serial.print(xyzFLOAT.z,digit);
  Serial.print("|");
}

//Printing floatvalues from typedef
void MechaQMC5883::print_float(){
  Serial.print("|x=");
  Serial.print(xyzFLOAT.x);
  Serial.print("|y=");
  Serial.print(xyzFLOAT.y);
  Serial.print("|z=");
  Serial.print(xyzFLOAT.z);
  Serial.print("|");
}
