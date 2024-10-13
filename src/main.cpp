#include "Examples/UserConfiguration.h"

#ifdef TESTHARDWARE
#include "Examples/Protogen/ProtogenHardwareTest.h"
#endif

//#include "Examples\Commissions\UnicornZhenjaAnimation.h"
#include "Examples/Protogen/ProtogenHUB75SenseProject.h"
#include <memory>
#include "ProtoLink/ProtoLink.h"
//#include "Examples\Protogen\ProtogenWS35Project.h"
//#include "Examples\VerifyEngine.h"


//#include "Examples/Commissions/ArrowAnimation.h"
//#include "../lib/ProtoTracer/Examples/Protogen/BetaProject.h"

ProtogenHUB75SenseProject project;
ProtoLink pl;


void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    #ifndef TESTHARDWARE
    project.Initialize();
    pl.Initialize(&Serial4);
    delay(100);
    #else
    while(true){
        HardwareTest::ScanDevices();
        HardwareTest::TestNeoTrellis();
        HardwareTest::TestBoopSensor();
        HardwareTest::TestHUD();
    }
    #endif
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;

    // Call update
    pl.Update();

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
}