#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#include "Arduino.h"



class AddressList{
    public:

        AddressList(uint8_t maxSensorsin){
            maxSensors = maxSensorsin;
        }
        bool setAddress(int sensNr,uint8_t address[]);
        void getAddress(int sensNr, uint8_t address[]);
        uint getNumberOfSensors();
        bool addressPresent(uint8_t address[]);
    
    
    private:
        uint8_t addresslist[100][8];
        uint8_t numberOfSensors = 0;
        uint8_t maxSensors;

};

#endif