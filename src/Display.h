#ifndef DISPLAY_H
#define DISPLAY_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <PinDefinition.h>


#define TS_MINX 449
#define TS_MINY 214
#define TS_MAXX 3946
#define TS_MAXY 3837



class Display{
    public:
        Display(uint DISPLAYROTATIONin){
            DISPLAYROTATION = DISPLAYROTATIONin;
        }

        void begin();
        void startScreen();
        void sdNotFound();
        void unPlugsensor();
        void plugInSensor(uint sensNr);
        bool nextSensor();
        void sensorReadinComplete(uint numberOfSensors);
        bool JaNein(String q);
        void showTempPrep(uint sensorNr, float temp);
        void showTemp();
    
    
    private:
        uint DISPLAYROTATION;
        uint counter = 0;
        float temperature[100];

        
        Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
        XPT2046_Touchscreen ts = XPT2046_Touchscreen(TS_CS);

};

#endif