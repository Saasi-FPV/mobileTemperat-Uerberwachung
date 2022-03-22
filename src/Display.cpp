#include <Display.h>


void Display::begin(){
    tft.begin();    Serial.println("tft Begin");
    ts.begin();     Serial.println("ts Begin");
    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(DISPLAYROTATION);
    ts.setRotation(DISPLAYROTATION);
}


void Display::startScreen(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(50, 3);
    tft.println("Temperatur");
    tft.setCursor(20, 50);
    tft.println("Ueberwachung");
    tft.setTextSize(2);
    tft.setCursor(0, 222);
    tft.println("Jan.J & Leon.V");
    tft.setCursor(270, 222);
    tft.println("2022");
}

void Display::sdNotFound(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(0, 0);
    tft.println("SD-Karte nicht gefunden.");
}

void Display::unPlugsensor(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(0, 0);
    tft.println("Alle Sensoren ausstecken.");
}

void Display::plugInSensor(uint sensNr){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(0, 0);
    tft.print("Sensor ");
    tft.print(sensNr);
    tft.println(" einstecken.");
}

void Display::sensorReadinComplete(uint numberOfSensors){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(0, 0);
    tft.print("Fertig! ");
    tft.println(numberOfSensors);
    tft.println(" Sensoren wurden eingelesen"); 
}

bool Display::JaNein(String q){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.print(q);
    tft.println("");
    tft.drawRoundRect(40, 160, 100, 60, 5, ILI9341_GREEN);
    tft.fillRoundRect(40, 160, 100, 60, 5, ILI9341_GREEN);
    tft.drawRoundRect(180, 160, 100, 60, 5, ILI9341_RED);
    tft.fillRoundRect(180, 160, 100, 60, 5, ILI9341_RED);
    tft.setCursor(65, 175);
    tft.setTextSize(4);
    tft.print("JA");
    tft.setCursor(183, 175);
    tft.print("Nein");

    
    while (1){
        if (ts.touched()){
            TS_Point p = ts.getPoint();
            p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
            p.y = map(p.y, TS_MAXY, TS_MINY, 240, 0);

            if(p.x > 40 && p.x < 140 && p.y > 160 && p.y < 220){
                Serial.println("JA");
                tft.fillScreen(ILI9341_GREEN);
                delay(500);
                tft.fillScreen(ILI9341_BLACK);
                return 1;
            }
            else if(p.x > 180 && p.x < 280 && p.y > 160 && p.y < 220){
                Serial.println("Nein");
                tft.fillScreen(ILI9341_RED);
                delay(500);
                tft.fillScreen(ILI9341_BLACK);
                return 0;
            }   
        }
    }
}

void Display::showTempPrep(uint position, float temp){
    temperature[position] = {temp};
    counter++;
}

void Display::showTemp(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    for (int i = 0; i < counter; i++){
        if (i+1 < 10){
            if (i % 2 == 0){
                tft.print("S");
                tft.print(i+1);
                if (temperature[i] < 100.0){
                    tft.print("   ");
                    tft.print(temperature[i]);
                }
                else{
                    tft.print("  ");
                    tft.print(temperature[i]);
                }
            }
            else{
                tft.print("     S");
                tft.print(i+1);
                if (temperature[i] < 100.0){
                    tft.print("   ");
                    tft.println(temperature[i]);
                }
                else{
                    tft.print("  ");
                    tft.println(temperature[i]);
                }               
            }
        }
        else{
            if (i % 2 == 0){
                tft.print("S");
                tft.print(i+1);
                if (temperature[i] < 100.0){
                    tft.print("  ");
                    tft.print(temperature[i]);
                }
                else{
                    tft.print(" ");
                    tft.print(temperature[i]);
                }
            }
            else{
                tft.print("     S");
                tft.print(i+1);
                if (temperature[i] < 100.0){
                    tft.print("  ");
                    tft.println(temperature[i]);
                }
                else{
                    tft.print(" ");
                    tft.println(temperature[i]);
                }               
            }                        
        }
    }
    counter = 0;
}
