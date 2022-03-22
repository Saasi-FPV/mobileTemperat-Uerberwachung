#include <Arduino.h>
#include <DS18B20.h>
#include <Adafruit_I2CDevice.h>
#include <AddressList.h>
#include <Display.h>
#include <SDhandler.h>
#include <RTClib.h>
#include <PinDefinition.h>




//Konstanten
#define BAUDRATE          115200   //Baud for SerialMonitor
#define MAXSENSORS            15   //Maximale anzahl an sensoren
#define MESSURINTERFALL       10   //Mess Intervall in Sekunden
#define DISPLAYROTATION        1   //Display Rotation [0-3]
#define DATETIMEASSORT "DD.MM.YY-hh:mm:ss"  //Darstellung des Zeitformats für LOG File




//Globale Variablen
uint numberOfDevices = 0;



//Objekte erstellen
DS18B20 ds(ONEWIREPIN);
AddressList dsAddress(MAXSENSORS);
Display disp(DISPLAYROTATION);
SDhandler SDcard(SD_CS);
RTC_DS3231 rtc;




void setup() {
  Serial.begin(BAUDRATE);
  
  //SPI trouble solver
  pinMode(SD_CS, OUTPUT); pinMode(TS_CS, OUTPUT); pinMode(TFT_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH); digitalWrite(TS_CS, HIGH); digitalWrite(TFT_CS, HIGH);
  
  numberOfDevices = ds.getNumberOfDevices(); Serial.println(ds.getNumberOfDevices());

  disp.begin();
  rtc.begin();
  disp.startScreen();

  delay(3000);

  if (!SDcard.begin()){
    disp.sdNotFound();
    delay(2000);
    while (!disp.JaNein("SD-Karte eingesteckt?"));
    ESP.restart();
  }

  if (numberOfDevices > 0){
    disp.unPlugsensor();
    delay(2000);
    while (!disp.JaNein("Alle Sensoren ausgesteckt?"));
    ESP.restart();
  }

  bool flag1 = 1;
  uint count = 0;
  do{
    bool flag2 = 1;
    uint errorcount = 0;
    bool maxSensorlocal = 0;   
    disp.plugInSensor(count+1);
    delay(2000);
    while (!disp.JaNein("Sensor eingesteckt?"));
    

    while (flag2){
      ds.selectNext();
      uint8_t address[8] = {0};
      ds.getAddress(address);
      if (!dsAddress.addressPresent(address)){
        if (!dsAddress.setAddress(count, address)){
          maxSensorlocal = 1;
          Serial.println("maxSensoren erreicht");
        }
        flag2 = 0;
      }
      else{
        errorcount++;
        if (errorcount > MAXSENSORS * 3){
          if (disp.JaNein("Sensor nicht gefunden. Richtig eingesteckt?")){
          errorcount = 0;
          }
          else{
            flag2 = 0;
          }
        }
      }
    }
    if (maxSensorlocal){   
      break;
    }
    
    if(!disp.JaNein("Weitere Sensor?"))
      flag1 = 0;

    count++;
  }while(flag1);

  numberOfDevices = dsAddress.getNumberOfSensors();
  disp.sensorReadinComplete(numberOfDevices);

}



void loop() {

char DaTim[] = DATETIMEASSORT; //Date Time sortment
DateTime now = rtc.now();


for (int i = 0; i <= numberOfDevices-1; i++){
  uint8_t addresslocal[8];
  dsAddress.getAddress(i, addresslocal);
  ds.select(addresslocal);
  float templocal = ds.getTempC();
  ///////////////////////////////////////////////////////////////
  Serial.println(i+1);
  Serial.print("Address:");
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print(" ");
    Serial.print(addresslocal[i]);
  }
  Serial.println("");
  Serial.println(templocal);
  Serial.println(now.toString(DaTim));
  ///////////////////////////////////////////////////////////////
  SDcard.write(i+1, templocal, now.toString(DaTim));               
  disp.showTempPrep(i, templocal);
}

disp.showTemp();



delay(MESSURINTERFALL * 1000);
}