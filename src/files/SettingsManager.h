#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <LittleFS_Mbed_RP2040.h>
#include <Arduino.h>

class SettingsManager {
public:
    SettingsManager();
    ~SettingsManager();

    void saveSettings(int timeNow, int dispenseTime, bool backlight);
    void loadSettings(int &timeNow, int &dispenseTime, bool &backlight);
    bool initialized;

private:
    void deleteFile(const char * path);
    void appendFile(const char * path, const char * message, size_t messageSize);
    void writeFile(const char * path, const char * message, size_t messageSize);
    void readFile(const char * path);
    void readCharsFromFile(const char * path);
    
    LittleFS_MBED *myFS;


    const char* settingsFilePath = MBED_LITTLEFS_FILE_PREFIX "/settings.dat";
    
};

#endif 