// Data file name on the SD Card
#define DATAFILE "/data.csv"

// Pin definition as per domino4.com/CWA
// I2C pins needed for xChips:
#define I2C_SDA 17
#define I2C_SCL 18
// BuiltIn pins needed for SD Card:
#define SPI_SCK  36
#define SPI_MISO 38
#define SPI_MOSI 37
#define SD_CS     3

// Libraries

/// SD Card Libraries
#include "FS.h"
#include "SD.h"
#include "SPI.h"

/// domino4 Libraries
#include <ArduinoJson.h>  // Needed for xChips - Has to be version 7+
#include <Wire.h>         // Needed for xChips
#include "IWA.h"          // Weather xChip       : https://github.com/domino4com/IWA
#include "IIA.h"          // Accelerometer xChip : https://github.com/domino4com/IIA

// xChip Instantiations and global variable
IWA iwa;
IIA iia;
bool iwa_found = false, iia_found = false;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(1000);
  Serial.printf("\nSD Card Example\n");

  // Initialize xChips
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.begin();
  if (iwa.begin()) {
    Serial.println("IWA initialized successfully.");
    iwa_found = true;
  } else {
    Serial.println("Failed to initialize IWA");
  }
  if (iia.begin()) {
    Serial.println("IIA initialized successfully.");
    iia_found = true;
  } else {
    Serial.println("Failed to initialize IIA");
  }

  // Initialise the SD Card
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_CS);
  if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed.");
    Serial.println("Increase log level to see more info: Tools > Core Debug Level > Verbose");
    exit(0);
  }

  // Check a SD Card has been inserted otherwise exit. If inserted, show card info
  switch (SD.cardType()) {
    case CARD_NONE: Serial.println("No SD card inserted!"); exit(0);
    case CARD_MMC: Serial.println("SD Card Type: MMC"); break;
    case CARD_SD: Serial.println("SD Card Type: SD"); break;
    case CARD_SDHC: Serial.println("SD Card Type: SDHC"); break;
    case CARD_UNKNOWN: Serial.println("SD Card Type: Unknown!"); break;
  }
  Serial.printf("SD Card Size: %lluGB\n", SD.cardSize() / (1024 * 1024 * 1024));
}

void loop() {
  // Variable to hold the comma seperated values
  char buffer[200];

  // Start with milli seconds in the buffer
  sprintf(buffer, "%ld", millis());

  // If the IWA is plugged in, then add temperature and humidity to the buffer after the milli seconds
  float t, h;
  if (iwa_found && iwa.getData(t, h)) {
    sprintf(buffer, "%s,%.2f,%.2f", buffer, t, h);
  } else {
    Serial.println("Failed to get IWA data.");
  }

  // If the IIA is plugged in, then add x, y and z to the buffer after the IWA data
  float x, y, z;
  if (iia_found && iia.getData(x, y, z)) {
    sprintf(buffer, "%s,%.2f,%.2f,%.2f", buffer, x, y, z);
  } else {
    Serial.println("Failed to get IIA data.");
  }

  // Write data to SD Card:
  // Open file...
  File file = SD.open(DATAFILE, FILE_APPEND);  // Open file with filename defined at the top. Open for appending, meaning it creates a file if it doesn't exist and add data to the end of the file
  if (!file) {
    Serial.println("Failed to open file for appending");
    exit(0);
  }
  // Write to file...
  if (!file.println(buffer)) {
    Serial.println("Append failed");
    exit(0);
  }
  // Close file...
  file.close();

  // Print the data to the Serial Port
  // The CSV data format makes it viable to see live data using Microsoft Datastreamer (an Excel function): https://support.microsoft.com/en-us/office/what-is-data-streamer-1d52ffce-261c-4d7b-8017-89e8ee2b806f
  Serial.println(buffer);
}
