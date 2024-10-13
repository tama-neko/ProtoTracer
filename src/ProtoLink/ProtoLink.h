// #pragma once

// #include "Arduino.h"
// #include "memory"
// #include "string"
// #include "ArduinoJson.hpp"

// class ProtoLink {
//     public:
//         ProtoLink(HardwareSerial* serial) : hwSerial_(serial);

//         void Update();
//     private:
//         void UpdateSettings();
//         void SyncProtoChanges();
//         bool IsSettingsChanged();

//         JsonDocument inDoc_;
//         JsonDocument outDoc_;

//         HardwareSerial* hwSerial_;

//         // Copy of the Menu class' parameters to keep track of changes
//         uint8_t faceState;
//         uint8_t bright;
//         uint8_t accentBright;
//         uint8_t microphone;
//         uint8_t micLevel;
//         uint8_t boopSensor;
//         uint8_t spectrumMirror;
//         uint8_t faceSize;
//         uint8_t color;
//         uint8_t huef;
//         uint8_t hueb;
//         uint8_t effect;
//         uint8_t fanSpeed;
// }