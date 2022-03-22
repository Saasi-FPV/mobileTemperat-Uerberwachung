#ifndef SDHANDLER_H
#define SDHANDLER_H

#include <SPI.h>
#include <SD.h>

class SDhandler{
    

    public:
        SDhandler(uint SD_PINin){
            SD_PIN = SD_PINin;
        }

        
        bool begin();
        void write(uint sensNr, float temp, char time[]);


    
    private:
        File myFile;
        uint SD_PIN;


};





#endif