#ifndef SDCard_h
#define SDCard_h

#include <SD.h>

class SDCard {
    public:
        SDCard(int pin);
        int begin();
        int writeToFile(char const* fileName, char const* data);
        int readFromFile(char const*);
    private:
        int _cs;
};

#endif