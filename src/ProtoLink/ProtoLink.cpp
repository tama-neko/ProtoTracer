#include <ProtoLink/ProtoLink.h>

void ProtoLink::Initialize(HardwareSerial* serial) {
    if (initialized_) return;

    hwSerial_ = serial;
    hwSerial_->begin(115200);

    // Initialize class variables to the menu's to have a reference to refer to for changes
    faceState = Menu::GetFaceState();
    bright = Menu::GetBrightness();
    accentBright = Menu::GetAccentBrightness();
    microphone = Menu::UseMicrophone();
    micLevel = Menu::GetMicLevel();
    boopSensor = Menu::UseBoopSensor();
    faceSize = Menu::GetFaceSize();
    color = Menu::GetFaceColor();
    huef = Menu::GetHueF();
    hueb = Menu::GetHueB();
    effect = Menu::GetEffectS();
    fanSpeed = Menu::GetFanSpeed();

    initialized_ = true;
}

void ProtoLink::Update() {
    if (!initialized_) return;

    if (IsSettingsChanged()) SyncProtoChanges();

    if (hwSerial_->available()) {
        DeserializationError err = deserializeJson(inDoc_, *hwSerial_);

        if (err == DeserializationError::Ok) {
            UpdateSettings();
        } else {
            // Flush bytes
            while (hwSerial_->available() > 0) {
                hwSerial_->read();
            }
        }
    }
}

void ProtoLink::UpdateSettings() {
    uint8_t inFaceState = inDoc_["faceState"].as<uint8_t>();
    if (inFaceState != Menu::GetFaceState()) Menu::SetFaceState(inFaceState);
    faceState = inFaceState;

    uint8_t inBrightness = inDoc_["brightness"].as<uint8_t>();
    if (inBrightness != Menu::GetBrightness()) Menu::SetBrightness(inBrightness);
    bright = inBrightness;

    uint8_t inAccentBrightness = inDoc_["accentBrightness"].as<uint8_t>();
    if (inAccentBrightness != Menu::GetAccentBrightness()) Menu::SetAccentBrightness(inAccentBrightness);
    accentBright = inAccentBrightness;

    uint8_t inUseMicrophone = inDoc_["useMicrophone"].as<uint8_t>();
    if (inUseMicrophone != Menu::UseMicrophone()) Menu::SetUseMicrophone(inUseMicrophone);
    microphone = inUseMicrophone;

    uint8_t inMicLevel = inDoc_["micLevel"].as<uint8_t>();
    if (inMicLevel != Menu::GetMicLevel()) Menu::SetMicLevel(inMicLevel);
    micLevel = inMicLevel;

    uint8_t inUseBoopSensor = inDoc_["useBoopSensor"].as<uint8_t>();
    if (inUseBoopSensor != Menu::UseBoopSensor()) Menu::SetUseBoopSensor(inUseBoopSensor);
    boopSensor = inUseBoopSensor;

    uint8_t inFaceSize = inDoc_["faceSize"].as<uint8_t>();
    if (inFaceSize != Menu::GetFaceSize()) Menu::SetFaceSize(inFaceSize);
    faceSize = inFaceSize;

    uint8_t inFaceColor = inDoc_["faceColor"].as<uint8_t>();
    if (inFaceColor != Menu::GetFaceColor()) Menu::SetFaceColor(inFaceColor);
    color = inFaceColor;

    uint8_t inHueF = inDoc_["hueF"].as<uint8_t>();
    if (inHueF != Menu::GetHueF()) Menu::SetHueF(inHueF);
    huef = inHueF;

    uint8_t inHueB = inDoc_["hueB"].as<uint8_t>();
    if (inHueB != Menu::GetHueB()) Menu::SetHueB(inHueB);
    hueb = inHueB;

    uint8_t inEffectS = inDoc_["effectS"].as<uint8_t>();
    if (inEffectS != Menu::GetEffectS()) Menu::SetEffectS(inEffectS);
    effect = inEffectS;

    uint8_t inFanSpeed = inDoc_["fanSpeed"].as<uint8_t>();
    if (inFanSpeed != Menu::GetFanSpeed()) Menu::SetFanSpeed(inFanSpeed);
    fanSpeed = inFanSpeed;
}

void ProtoLink::SyncProtoChanges() {
    faceState = Menu::GetFaceState();
    outDoc_["faceState"] = faceSize;

    bright = Menu::GetBrightness();
    outDoc_["brightness"] = bright;

    accentBright = Menu::GetAccentBrightness();
    outDoc_["accentBrightness"] = accentBright;

    microphone = Menu::UseMicrophone();
    outDoc_["useMicrophone"] = microphone;

    micLevel = Menu::GetMicLevel();
    outDoc_["micLevel"] = micLevel;

    boopSensor = Menu::UseBoopSensor();
    outDoc_["useBoopSensor"] = boopSensor;

    faceSize = Menu::GetFaceSize();
    outDoc_["faceSize"] = faceSize;

    color = Menu::GetFaceColor();
    outDoc_["faceColor"] = color;

    huef = Menu::GetHueF();
    outDoc_["hueF"] = huef;

    hueb = Menu::GetHueB();
    outDoc_["hueb"] = hueb;

    effect = Menu::GetEffectS();
    outDoc_["effectS"] = effect;

    fanSpeed = Menu::GetFanSpeed();
    outDoc_["fanSpeed"] = fanSpeed;

    serializeJson(outDoc_, *hwSerial_);
}

bool ProtoLink::IsSettingsChanged() {
    return (    
        faceState != Menu::GetFaceState() &&
        bright != Menu::GetBrightness() &&
        accentBright != Menu::GetAccentBrightness() &&
        microphone != Menu::UseMicrophone() &&
        micLevel != Menu::GetMicLevel() &&
        boopSensor != Menu::UseBoopSensor() &&
        faceSize != Menu::GetFaceSize() &&
        color != Menu::GetFaceColor() &&
        huef != Menu::GetHueF() &&
        hueb != Menu::GetHueB() &&
        effect != Menu::GetEffectS() &&
        fanSpeed != Menu::GetFanSpeed()
    );
}