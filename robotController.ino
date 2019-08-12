#include <AceRoutine.h>
using namespace ace_routine;

int lastCycleTime = 0;
int maxCycleTime = 0;

void setup() {
  Serial.begin(9600);

  CoroutineScheduler::setup();
}

void loop() {
  int cycleTime = millis();
  CoroutineScheduler::loop();
  lastCycleTime = millis() - cycleTime;
  if(lastCycleTime > maxCycleTime) maxCycleTime = lastCycleTime;
}
