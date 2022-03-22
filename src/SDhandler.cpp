#include <SDhandler.h>

bool SDhandler::begin(){
  Serial.println("SD Begin");
    if (!SD.begin(SD_PIN)) {
    Serial.println("initialization failed!");
    return 0;
  }
  else{
    Serial.println("initialization Done!");
    myFile = SD.open("/LOG.txt", FILE_WRITE);
    return 1;
  }
}

void SDhandler::write(uint sensNr, float temp, char time[]){
    myFile.print(time);
    myFile.print(" ");
    myFile.print("Sensor Nr: ");
    myFile.print(sensNr);
    myFile.print(" Temperatur: ");
    myFile.println(temp);

    myFile.flush();
}
