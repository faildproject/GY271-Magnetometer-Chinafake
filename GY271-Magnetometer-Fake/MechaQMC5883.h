#ifndef Mecha_QMC5883
#define Mecha_QMC5883

#include "Arduino.h"
#include <Wire.h>

//Doxygen-Kommentare
/**
* @mainpage New Class for the GY271-Fakesensor
*
* When you have a GY271-Magnetometer with the I2C-address 0x0D, you can use this libary. 
* You can get the magneticfield in diffrent Formats, like (floats)Gaus, µT, mT and (int)RAW
*
* Simple usage:
* 
*	
*	@include Simple-Demo.cpp 
*	
*
*/ 

#define QMC5883_ADDR 0x0D // Defaultadress


//REG CONTROL
#define Mode_Standby    0b00000000
#define Mode_Continuous 0b00000001

#define ODR_10Hz        0b00000000
#define ODR_50Hz        0b00000100
#define ODR_100Hz       0b00001000
#define ODR_200Hz       0b00001100

#define RNG_2G          0b00000000
#define RNG_8G          0b00010000

#define OSR_512         0b00000000
#define OSR_256         0b01000000
#define OSR_128         0b10000000
#define OSR_64          0b11000000

//Tell the Compiler a "new Datatype" (Type=RAWDATA)
/** Datacontainer for xyz Integers  
 *   
 *  @author Philipp Heise 
 *  @date 02.06.2017
 * 
 */
 
typedef struct{
  int x;
  int y;
  int z;
}RAWDATA;

//Tell the Compiler a "new Datatype" (Type=FLOATDATA)

/** Datacontainer for xyz Floats (like Gaus, µT, mT)  
 *   
 *  @author Philipp Heise 
 *  @date 02.06.2017
 * 
 */
typedef struct{
  float x;
  float y;
  float z;
}FLOATDATA;

/** The class for the GY271-Fake  
 *  
 *	@class MechaQMC5883 
 *
 *  @author Philipp Heise 
 *  @date 02.06.2017
 * 	
 *	@brief Use the GY271-QMC5883-Magnetometer
 *	
 *	If the class not working, checkout your wireing. Use diffrent methods to get the Values which you want. 
 */

//Begin a Class
class MechaQMC5883{

public:
  MechaQMC5883();             //Default-Constructor

/**
*
* If needed you can use a other Sensor-Address
*
*/  
  
  MechaQMC5883(uint8_t addr); //Overloaded-Constructor
  
/**
*
* Setup the Sensor in Continuous-Mode and 200Hz Samplerate
* by Fullscale-Range (+-8 Gaus)
*/

  void init();
 
/**
*  Change the Sensormode
*
*  @param[in] mode Valid Values are: Mode_Standby,Mode_Continuous
*  @param[in] odr Valid Values are: ODR_10Hz,ODR_50Hz,ODR_100Hz,ODR_200Hz
*  @param[in] rng Valid Values are: RNG_2G,RNG_8G
*  @param[in] osr Valid Values are: OSR_512,OSR_256,OSR_128,OSR_64
*
*/ 

  void setMode(uint8_t mode,uint8_t odr,uint8_t rng,uint8_t osr); // setting
  
/**
*  Calibrate the Sensordata
*
*  @warning Factors are not used with RAWDATA
*
*  @param[in] x Is the factor which is multiplied with the Original-x-Value 
*  @param[in] y Is the factor which is multiplied with the Original-y-Value 
*  @param[in] z Is the factor which is multiplied with the Original-z-Value 
*
*/ 

  void setCalibValues(float x, float y, float z);

  //#########Measurement-Methods for Magneticfield########

/**
*
*	Reads the Sensordata
*  @return RAWDATA from the Sensor as an Integer
*
*/ 
  
  RAWDATA getRaw();                           //reading Raw from Reg
  
/**
*
*	Reads the Sensordata and calculate the Gaus-Value
*  @return FLOATDATA as Gaus
*
*/ 
  
  FLOATDATA get_Gaus();                       //reading Raw and calc Gaus
  
/**
*
*	Reads the Sensordata and calculate the mT-Value
*  @return FLOATDATA as mT
*
*/ 

  FLOATDATA get_mT();                         //reading Raw and calc mT
  
/**
*
*	Reads the Sensordata and calculate the µT-Value
*  @return FLOATDATA as µT
*
*/ 

  FLOATDATA get_uT();                         //reading Raw and calc uT
  
/**
*
*	Can use to calculate the Gaus-Value from spezified RAWDATA-Input
*  @param[in] RAWDATA The RAWDATA which you want to calculate. 
*  @return FLOATDATA as Gaus
*
*/ 

  FLOATDATA calc_Gaus(RAWDATA xyzRAW);       //Calculate the Gaus-Value from RAW
  
/**
*
*	Can use to calculate the mT-Value from spezified RAWDATA-Input
*  @param[in] RAWDATA The RAWDATA which you want to calculate. 
*  @return FLOATDATA as mT
*
*/ 

  FLOATDATA calc_mT(RAWDATA xyzRAW);         //Calculate the mT-Value from RAW
  
/**
*
*	Can use to calculate the uT-Value from spezified RAWDATA-Input
*  @param[in] RAWDATA The RAWDATA which you want to calculate. 
*  @return FLOATDATA as uT
*
*/ 
  FLOATDATA calc_uT(RAWDATA xyzRAW);         //Calculate the mT-Value from RAW
  
/**
*  Print the RAW-Data like "|x=...|y=...|z=...|RAW\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_Raw();                          //print Sensordata directly in Raw-Format

/**
*  Print the Gaus-Data like "|x=...|y=...|z=...|Gaus\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_Gaus();                         //print Sensordata directly in Gaus-Format
  
/**
*  Print the mT-Data like "|x=...|y=...|z=...|mT\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/
 
  void print_mT();                           //print Sensordata directly in mT-Format
  
/**
*  Print the uT-Data like "|x=...|y=...|z=...|uT\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_uT();                           //print Sensordata directly in uT-Format
  
/**
*  Print the Gaus-Data like "|x=...|y=...|z=...|Gaus\r\n" with variable precision
*  @see print_Gaus()
*  @param[in] dez Percision 
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_Gaus(int dez);                  //print Sensordata directly in Gaus-Format (var precision)
  
/**
*  Print the mT-Data like "|x=...|y=...|z=...|mT\r\n" with variable precision
*  @see print_mT()
*  @param[in] dez Percision 
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_mT(int dez);                    //print Sensordata directly in mT-Format (var precision)
  
/**
*  Print the uT-Data like "|x=...|y=...|z=...|uT\r\n" with variable precision
*  @see print_mT()
*  @param[in] dez Percision 
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_uT(int dez);                    //print Sensordata directly in uT-Format (var precision)

  //#########Measurement-Methods for Temperature########

/**
*
*	Reads the Temperature in RAW from the Sensor
*  @return temperature as Integer
*
*/ 
  
  int getRawT();                              //reading Raw from Reg
  
/**
*
*	Reads the Temperature in RAW and calculate °C
*  @return Temperature as Float
*
*/ 

  float get_T();                              //reading Raw-Temp and calc °C
 
/**
*
*	Calculate °C from RAW-Input
*  @param[in] RAWT The value that you want to cast 
*  @return Temperature as Float
*
*/  

  float calc_T(int RAWT);                     //Calculate the °C from RAW
  
/**
*  Print the Temperature like "|Temp=...|RAW\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_RawT();                          //print Temperature directly in Raw-Format
  
/**
*  Print the Temperature like "|Temp=...|C\r\n"
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_T();                             //print Temperature directly in °C

/**
*  Print the Gaus-Data like "|Temp=...|C\r\n" with variable precision
*  @see print_T()
*  @param[in] dez Percision 
*
*  @warning You must use Serial.begin() in Setup-Loop
*
*/ 

  void print_T(int dez);                      //print Temperature directly in °C (var precision)

  //####################################################
  
/**
*
*	Perform a Softreset on the Sensor
*
*/

  void softReset(); //soft RESET
  
private:

  //Variables
  float resolution;            //Resolution of the ADC varies with the chosen Sensorrange (+-2 Gauses or +-8 Gauses)
    
  float calib_x;               //Calibration-Value for x
  float calib_y;               //Calibration-Value for y
  float calib_z;               //Calibration-Value for z

  //Magneticfield Data
  RAWDATA xyzRAW;              //Storage for RAWDATA
  FLOATDATA xyzFLOAT;          //Storage for calculated Floatdata

  //Temperature Data
  int TRAW;
  float T;

  int address = QMC5883_ADDR;             //I2C-Adress of the Sensor

  //Methods
  
/**
*
*	Change Sensor-Address internal
*
*/

  void setAddress(uint8_t addr);          //Setup the I2C-Adress
  void WriteReg(uint8_t Reg,uint8_t val); //Write Registers in Sensor
  
/**
*  Print the FLOATDATA-Type like "|x=...|y=...|z=...|" with variable precision
*  @see print_T()
*  @param[in] dez Percision 
*  
*  @warning You must use Serial.begin() in Setup-Loop
*
*/
  
  void print_float(int digit);            //printing float-values directly with var precision
  
/**
*  Print the FLOATDATA-Type like "|x=...|y=...|z=...|"
*  
*  @warning You must use Serial.begin() in Setup-Loop
*
*/

  void print_float();                     //printing float-values directly

};

#endif
