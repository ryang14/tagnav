#include <Arduino.h>
#include <atomic>
#include <AceRoutine.h>
using namespace ace_routine;

std::atomic<bool> safe_drive(false);

void safety_setup()
{
  pinMode(23, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(23), []{ safe_drive = true; }, RISING);
}

COROUTINE(safety)
{
  COROUTINE_LOOP()
  {
    safe_drive = digitalRead(23);
    COROUTINE_YIELD();
  }
}
