#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    Serial.print("\nStart LittleFS_Test on ");

 
}

SettingsManager::~SettingsManager() {
}

void SettingsManager::readCharsFromFile(const char * path)
{
  Serial.print("readCharsFromFile: ");
  Serial.print(path);

  FILE *file = fopen(path, "r");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  char c;

  while (true)
  {
    c = fgetc(file);

    if ( feof(file) )
    {
      break;
    }
    else
      Serial.print(c);
  }

  fclose(file);
}

void SettingsManager::readFile(const char * path)
{
  Serial.print("Reading file: ");
  Serial.print(path);

  FILE *file = fopen(path, "r");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  char c;
  uint32_t numRead = 1;

  while (numRead)
  {
    numRead = fread((uint8_t *) &c, sizeof(c), 1, file);

    if (numRead)
      Serial.print(c);
  }

  fclose(file);
}

void SettingsManager::writeFile(const char * path, const char * message, size_t messageSize)
{
  Serial.print("Writing file: ");
  Serial.print(path);

  FILE *file = fopen(path, "w");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file))
  {
    Serial.println("* Writing OK");
  }
  else
  {
    Serial.println("* Writing failed");
  }

  fclose(file);
}

void SettingsManager::appendFile(const char * path, const char * message, size_t messageSize)
{
  Serial.print("Appending file: ");
  Serial.print(path);

  FILE *file = fopen(path, "a");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file))
  {
    Serial.println("* Appending OK");
  }
  else
  {
    Serial.println("* Appending failed");
  }

  fclose(file);
}

void SettingsManager::deleteFile(const char * path)
{
  Serial.print("Deleting file: ");
  Serial.print(path);

  if (remove(path) == 0)
  {
    Serial.println(" => OK");
  }
  else
  {
    Serial.println(" => Failed");
    return;
  }
}

void SettingsManager::saveSettings(int timeNow, int dispenseTime, bool backlight) {
    if (!initialized) return;

    Serial.println("- writing" );

    // char message[]  = "Hello from " BOARD_NAME "\n";

    
    Serial.println("File written ... " );

}

void SettingsManager::loadSettings(int &timeNow, int &dispenseTime, bool &backlight) {
    if (!initialized) return;




    Serial.println("Settings loaded successfully.");
   
}
