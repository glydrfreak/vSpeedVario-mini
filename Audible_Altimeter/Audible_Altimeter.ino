#include "MS5611.h"
#include "FILTER.h"
#define BAUD_RATE                 115200    // Serial Monitor baud rate
#define POT_UD                        A0
#define POT_INC                       A1
#define VOL_DOWN                      A2
#define VOL_UP                        A3
#define POT_CS                        A4
#define BEEP_CTRL                     A5
#define MS5611_CSB                    13
#define VBATPIN                        9    // Pin monitors battery level (Pin A7)
#define START_UP_VOLUME               32    // 0-32
#define ALTITUDE_UNITS                 1    // [1]FEET, [2]METERS
#define VELOCITY_UNITS                 1    // [1]FEET_PER_SECOND, [2]METERS_PER_SECOND, [3]FEET_PER_MINUTE
#define PRESSURE_FILTER_DURATION       0    // (AVERAGING DURATION: 1ms to 2000ms)
#define ALTITUDE_FILTER_DURATION    1000    // (AVERAGING DURATION: 1ms to 2000ms)
#define VSPEED_FILTER_DURATION       750    // (AVERAGING DURATION: 1ms to 2000ms)
#define TEMPERATURE_FILTER_DURATION    0    // (AVERAGING DURATION: 1ms to 2000ms)
#define ARMED_ALTITUDE              7000    // must climb above this altitude to activate audible beeps
#define DISARM_ALTITUDE             1000    // must descend below this altitude to deactivate audible beeps
#define BREAK_OFF                   5500    // Break-off altitude
#define PULL                        4000    // Pull altitude
#define DECISION_ALTITUDE           2500    // You f***ed up, idiot!


MS5611 MS5611(MS5611_CSB);
FILTER1 FILTER1;
FILTER2 FILTER2;
FILTER3 FILTER3;
FILTER4 FILTER4;


void adjustVolumeTo(int volLevel);  // 0 - 100;
void volumeUp();
void volumeDown();
float getBatteryLvl();    //Volts


int volDelay = 150;   // Volume shall only be changed every 150ms;
unsigned long volMillis = 0;
unsigned long previousMillis = 0;
int samplesThisSec = 0;    // Used for calculating averaging duration
int samplesPerSec = 0;     // Used for displaying samplesPerSec updated every once second
long battMillis = -5000;
float batteryLvl = 0;
int batteryPercent = 100;
bool measure_battery = 1;
int estimatedVolume = 0;
float temperatureF = 0;
float pressurePa = 0;
float altitudeFt = 0;
float velocityFtPerSec = 0;
float altitude = 0;
float AGL = 0;
float AGL_offset = 0;
float velocity = 0;
bool armed = false;
bool breakOffBeepInitiated = false;
bool pullBeepInitiated = false;
bool decisionAltitudeBeepInitiated = false;


void setup() {
  delay(1000);
  
  Serial.begin(BAUD_RATE);
  
  Serial.println("********SETUP********");
  pinMode(VBATPIN, INPUT);
  
  pinMode(POT_CS,OUTPUT);
  pinMode(POT_UD,OUTPUT);
  pinMode(POT_INC,OUTPUT);
  digitalWrite(POT_INC,HIGH);
  digitalWrite(POT_UD,LOW);
  digitalWrite(POT_CS,HIGH);

  pinMode(VOL_UP, INPUT);
  pinMode(VOL_DOWN, INPUT);

  MS5611_init();
  int result = MS5611.read();
  if(result != 0){
    Serial.print("Error in read: ");
    Serial.println(result);
  }
  temperatureF = MS5611.getTemperature()*0.01*(9/5.0)+32;
  pressurePa = MS5611.getPressure();
  altitudeFt = getAltitudeFt(temperatureF, pressurePa);
  AGL_offset = altitudeFt;

  adjustVolumeTo(START_UP_VOLUME);
  estimatedVolume = START_UP_VOLUME;

  batteryLvl = getBatteryLvl();
  batteryPercent = (int)(batteryLvl*156.25 - 556.25);  //conversion to percent;
  if(batteryPercent > 99){batteryPercent = 99;}
  else if(batteryPercent < 0){batteryPercent = 0;}
  if(batteryPercent>=66){
    Serial.print("BATT:>=66");
    tone(BEEP_CTRL, 300, 100);
    delay(200);
    tone(BEEP_CTRL, 400, 100);
    delay(200);
    tone(BEEP_CTRL, 500, 100);
    delay(200);
  }
  else if(batteryPercent>=33){
    Serial.print("BATT:>=33");
    tone(BEEP_CTRL, 400, 100);
    delay(200);
    tone(BEEP_CTRL, 400, 100);
    delay(200);
    tone(BEEP_CTRL, 400, 100);
    delay(200);
  }
  else if(batteryPercent<33){
    Serial.print("BATT:<33");
    tone(BEEP_CTRL, 500, 100);
    delay(200);
    tone(BEEP_CTRL, 400, 100);
    delay(200);
    tone(BEEP_CTRL, 300, 100);
    delay(200);
  }
  Serial.print("==");
  Serial.println(batteryPercent);  
  Serial.println("******END SETUP******");

}

void loop() {
  //delay(100);
  samplesThisSec++; //increment each time the loop cycles
  if(millis() - previousMillis >= 1000){ // Update value of samplesPerSec once every second:
    previousMillis=millis();
    samplesPerSec = samplesThisSec;
    samplesThisSec=0; 
    //Serial.print("BLE:"); Serial.print(ble.isConnected()); Serial.print(" ");
    //Serial.println(samplesPerSec);  //print debug info
  }
  
  //====BATTERY================================================================/
  //Measure battery level every 5 seconds
  if(measure_battery && millis()-battMillis>=5000){
    battMillis = millis();
    batteryLvl = getBatteryLvl();
    batteryPercent = (int)(batteryLvl*156.25 - 556.25);  //conversion to percent;
    if(batteryPercent > 99){batteryPercent = 99;}
    else if(batteryPercent < 0){batteryPercent = 0;}
  }

  //====MS5611=================================================================/

  int result = MS5611.read();
  if(result != 0){
    Serial.print("Error in read: ");
    Serial.println(result);
  }
  
  //TEMPERATURE:
  if(TEMPERATURE_FILTER_DURATION){
    temperatureF = FILTER4.RUNNING_AVERAGE(
      //(MS5611_I2C.readTemperature()*9/5.0)+32,
      //MS5611.getTemperatureF(D2_OSR), 
      MS5611.getTemperature()*0.01*(9/5.0)+32,
      samplesPerSec, 
      TEMPERATURE_FILTER_DURATION
    );
  }
  else{
    temperatureF = MS5611.getTemperature()*0.01*(9/5.0)+32;
    //temperatureF = MS5611.getTemperatureF(D2_OSR);
    //temperatureF = (MS5611_I2C.readTemperature()*9/5.0)+32;
    //temperatureF = initialTemperature;
  }
  
  //PRESSURE:
  if(PRESSURE_FILTER_DURATION){
    pressurePa = FILTER1.RUNNING_AVERAGE(
      MS5611.getPressure(),
      //MS5611.getPressurePa(D1_OSR),
      //MS5611_I2C.readPressure(), 
      samplesPerSec, 
      PRESSURE_FILTER_DURATION
    );
  }
  else{
    pressurePa = MS5611.getPressure();
    //pressurePa = MS5611.getPressurePa(D1_OSR);
    //pressurePa = MS5611_I2C.readPressure();
  }
  
  //ALTITUDE:
  if(ALTITUDE_FILTER_DURATION){
    altitudeFt = FILTER2.RUNNING_AVERAGE(
      getAltitudeFt(temperatureF, pressurePa),
      //MS5611.getAltitudeFt(temperatureF, pressurePa), 
      samplesPerSec, 
      ALTITUDE_FILTER_DURATION
    );
    AGL = altitudeFt - AGL_offset;
  }
  else{
    //altitudeFt = MS5611.getAltitudeFt(temperatureF, pressurePa);
    altitudeFt = getAltitudeFt(temperatureF, pressurePa);
    AGL = altitudeFt - AGL_offset;
  }
  switch(ALTITUDE_UNITS){
    default: altitude=altitudeFt*1; break;
    case 2: altitude=altitudeFt*0.3048; break;
  }

  //VERTICAL SPEED:
  if(millis()>8000){
    if(VSPEED_FILTER_DURATION){
      velocityFtPerSec = FILTER3.RUNNING_AVERAGE(
        //MS5611.getVelocityFtPerSec(altitudeFt, millis()), 
        getVelocityFtPerSec(altitudeFt, millis()),
        samplesPerSec, 
        VSPEED_FILTER_DURATION
      );
      //velocityFtPerSec -= 0.1;
    }
    else{
      velocityFtPerSec = getVelocityFtPerSec(altitudeFt, millis());
      //velocityFtPerSec = MS5611.getVelocityFtPerSec(altitudeFt, millis());
    }
    switch(VELOCITY_UNITS){
      default: velocity=velocityFtPerSec*1; break;
      case 2: velocity=velocityFtPerSec*0.3048; break;
      case 3: velocity=velocityFtPerSec*60; break;
    }
  }
  else{velocity=0;}

  //DEBUG:
  //Serial.print(samplesPerSec);
  //Serial.print(" ");
  //Serial.print(temperatureF); 
  //Serial.print(" ");
  //Serial.print(pressurePa);
  //Serial.print(" "); 
  //Serial.print(altitude); 
  //Serial.print(" "); 
  Serial.print(AGL);
  Serial.print(" ");
  Serial.println(velocity); 
  

  //====BEEP====================================================================/
  // TODO: add beep routine
  // armed altitude - 7000
  // break off - 5500
  // pull - 4000
  // decision altitude - 2500
  if(AGL>ARMED_ALTITUDE && !armed){
    armed = true;
    tone(BEEP_CTRL, 400, 300); 
  }
  if(AGL<DISARM_ALTITUDE && armed){
    armed = false;
    breakOffBeepInitiated = false;
    pullBeepInitiated = false;
    decisionAltitudeBeepInitiated = false;
    tone(BEEP_CTRL, 400, 300); 
  }
  if(armed){
    if(AGL<BREAK_OFF && !breakOffBeepInitiated){
      beginBreakOffBeep(BEEP_CTRL);
      breakOffBeepInitiated = true;
    }
    if(AGL<PULL && !pullBeepInitiated){
      beginPullBeep(BEEP_CTRL);
      pullBeepInitiated = true;
    }
    if(AGL<DECISION_ALTITUDE /*&& velocity > 70*/ && !decisionAltitudeBeepInitiated){
      beginDecisionAltitudeBeep(BEEP_CTRL);
      decisionAltitudeBeepInitiated = true;
    }
  }
  

  //====BUTTONS=================================================================/
  if(analogRead(VOL_UP)<500 && millis()-volMillis>=volDelay){
    volMillis = millis();
    volumeUp();
  }

  if(analogRead(VOL_DOWN)<500 && millis()-volMillis>=volDelay){
    volMillis = millis();
    volumeDown();
  }
}


void MS5611_init(){
  MS5611.init();

  unsigned int C_read[8];

  uint8_t i;
  unsigned int n_rem = 0;
  unsigned int crc_read;
  unsigned char n_bit;


  // Calculate and check PROM's CRC4
  // 
  int result = MS5611.read();
  for (i = 0; i < 8; i++)
  {
    C_read[i] = MS5611.getPromValue(i);
    //C_read[i] = C_test[i];
  }
  crc_read = C_read[7];
  C_read[7]=(0xFF00 & (C_read[7]));
  for (i = 0; i < 16; i++)
  {
    if (i%2==1) n_rem ^= (unsigned short) ( (C_read[i>>1]) & 0x00FF );
    else n_rem ^= (unsigned short) (C_read[i>>1]>>8);
    for (n_bit = 8; n_bit > 0; n_bit--)
    {
      if (n_rem & (0x8000))
      {
        n_rem = (n_rem << 1) ^ 0x3000;
      }
      else
      {
        n_rem = (n_rem << 1);
      }
    }
  }
  n_rem= (0x000F & (n_rem >> 12));

  Serial.print ("CRC (calculated) : ");
  Serial.println (n_rem,HEX);
  Serial.print ("CRC (read)       : ");
  C_read[7]=crc_read;
  Serial.println (C_read[7] & 15,HEX);
  Serial.println();
}


float getAltitudeFt(float tempF, float pressPa){
  float sLvl = 101325.00;
  //float sLvl = 100680.00;
  float pressPaTemp = pressPa;
  if(pressPaTemp <= 0){pressPaTemp=1.0;}
  return 504.745*((5.00*(tempF - 32.00))/9.00 + 273.15)*(pow((sLvl/pressPaTemp),0.190223) - 1.00);
}


bool firstTimeVelo = true;
float prevAlti = 0;
unsigned long prevTimeVelo = 0;
float getVelocityFtPerSec(float altiFeet, unsigned long currentVeloMillis){
  if(firstTimeVelo){
    firstTimeVelo = false;
    prevAlti = altiFeet; //initializing
    prevTimeVelo = currentVeloMillis; //initializing
    return 0;
  }
  else{
    float velo = (1000.0*((float)altiFeet - (float)prevAlti)) / ((float)currentVeloMillis - (float)prevTimeVelo);
    prevAlti = altiFeet;
    prevTimeVelo = currentVeloMillis;
    return velo; 
  }
}


void beginBreakOffBeep(int _beepCtrl){
  int pitch = 500;
  int beepDuration = 2000;
  tone(_beepCtrl, pitch, beepDuration);
}


void beginPullBeep(int _beepCtrl){
  int pitch = 600;
  int beepDuration = 2000;
  tone(_beepCtrl, pitch, beepDuration);
}


void beginDecisionAltitudeBeep(int _beepCtrl){
  int pitch = 700;
  int beepDuration = 2000;
  tone(_beepCtrl, pitch, beepDuration);
}


void volumeUp(){
  
  //X9C.trimPot(31, X9C_UP, true);
  
  digitalWrite(POT_CS,LOW);
  digitalWrite(POT_UD, HIGH);
  digitalWrite(POT_INC, HIGH);
  digitalWrite(POT_INC, LOW);
  digitalWrite(POT_INC, HIGH);
  digitalWrite(POT_CS,HIGH);
  
  tone(BEEP_CTRL, 400, 100);
  
  Serial.print("VOL_UP: "); 
  estimatedVolume++;
  if(estimatedVolume>32){estimatedVolume=32;}
  Serial.println(estimatedVolume);
}


void volumeDown(){

  //X9C.trimPot(31, X9C_DOWN, true);
  
  digitalWrite(POT_CS,LOW);
  digitalWrite(POT_UD, LOW);
  digitalWrite(POT_INC, HIGH);
  digitalWrite(POT_INC, LOW);
  digitalWrite(POT_INC, HIGH);
  digitalWrite(POT_CS,HIGH); 
  
  tone(BEEP_CTRL, 400, 100);
  
  Serial.print("VOL_DOWN: ");
  estimatedVolume--;
  if(estimatedVolume<0){estimatedVolume=0;}
  Serial.println(estimatedVolume);
}


void adjustVolumeTo(int volLevel){
  
  //RESET VOLUME TO ZERO:
  digitalWrite(POT_CS,LOW);
  digitalWrite(POT_UD, LOW);
  for(int i = 0; i <= 100; i++){
    digitalWrite(POT_INC, LOW);
    digitalWrite(POT_INC, HIGH);
  }
  digitalWrite(POT_CS,HIGH);

  //MOVE UP TO A DESIRED VOLUME:
  digitalWrite(POT_CS,LOW);
  digitalWrite(POT_UD, HIGH);
  for(int i = 0; i <= volLevel; i++){
    digitalWrite(POT_INC, LOW);
    digitalWrite(POT_INC, HIGH);
  }
  digitalWrite(POT_CS,HIGH); 
  Serial.print("VOLUME:"); Serial.println(volLevel);
}


float getBatteryLvl(){  
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}
