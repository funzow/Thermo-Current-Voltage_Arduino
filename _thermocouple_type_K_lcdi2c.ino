#include <max6675.h>

int thermo1sck = 38;
int thermo1cs = 40;
int thermo1so = 42;

MAX6675 T1(thermo1sck,thermo1cs,thermo1so);

int thermo2sck = A3;
int thermo2cs = A4;
int thermo2so = A5;

MAX6675 T2(thermo2sck,thermo2cs,thermo2so);

int thermo3sck = 5;
int thermo3cs = 6;
int thermo3so = 7;

MAX6675 T3(thermo3sck,thermo3cs,thermo3so);

int thermo4sck = A12;
int thermo4cs = A13;
int thermo4so = A14;

MAX6675 T4(thermo4sck,thermo4cs,thermo4so);

int thermo5sck = A8;
int thermo5cs = A9;
int thermo5so = A10;

MAX6675 T5(thermo5sck,thermo5cs,thermo5so);

int thermo6sck = 28;
int thermo6cs = 30;
int thermo6so = 32;

MAX6675 T6(thermo6sck,thermo6cs,thermo6so);

//Arus (acs712)
const int currentPin = A0;
int sensitivity = 100;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;

int offset =20;// set the correction offset value

void setup() {
  Serial.begin (9600);

//PLX-DAQ
  Serial.println ("CLEARDATA");
  Serial.println ("LABEL, Time, Date, T1, T2, T3, T4, T5, T6, V, A");
}

void loop() {

// ACS712
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  // voltage sensor
  int volt = analogRead(A1); //ad the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  
  voltage /=100;// divide by 100 to get the decimal 
    
  Serial.print ("DATA, TIME, DATE,");

  Serial.print(T1.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,");
  
  Serial.print(T2.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,");
 
  Serial.print(T3.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,"); 
  
  Serial.print(T4.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,");
  
  Serial.print(T5.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,");
  
  Serial.print(T6.readCelsius());
  Serial.print(" C ");
  Serial.print(" ,");

  Serial.print(voltage);//print the voltge
  Serial.print("V");
  Serial.print(" ,");
  
  Serial.print(currentValue,3);
  Serial.print("A");
  Serial.print(" ,");
  Serial.println(" ");
  
  delay(1000);
}
