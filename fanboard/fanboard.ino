//new
const int fanPin = 9;                                // pin to connect fan to (O0)
const int boostPin = 8;                              // pin to connect boost to (O1)
const int numOfBoostZones = 1;                       // number of boost zone input pins
const int boostZones[numOfBoostZones] = {0}  ;        // the zone numbers that require boost
const int numOfColdZones = 3;
const int coldZones[numOfColdZones] = {1, 2, 3};
const int numOfZones = 7;                            // the number of input zones
const int zonePins[numOfZones] = {10, 14, 15, 16, 17, 18, 19};   //The input pins of the zones
const int wtwPin = 9999;                                                    
unsigned long fanTimer;                                       // timestamp storage for fan timing
unsigned long boostTimer;                                     // timestamp storage for boost timing
unsigned long offDelay = 5 * 60 * 1000;                        // time the fan should stay on after zone signal
                                                              // goes low, in [ms]

void setup() {
  int i;
  
  for (i = 0; i < numOfZones; i++){
    pinMode(zonePins[i], INPUT_PULLUP);
  }
  
  pinMode(fanPin, OUTPUT);
  pinMode(boostPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("READY");
}

void loop() {
    int i;

    // first check the cold zones
    for (i = 0; i < numOfColdZones; i++){
        if (digitalRead(zonePins[coldZones[i]]))
            fanTimer = millis() + offDelay;
    }

    // now check the boost zones
    for (i = 0; i < numOfBoostZones; i++){
        if (digitalRead(zonePins[boostZones[i]])){
            if(digitalRead(wtwPin))
                boostTimer = millis() + offDelay;
            else
                fanTimer = millis() + offDelay;
        }
    }

    if (fanTimer + offDelay > millis())
        digitalWrite(fanPin, 1);
    else
        digitalWrite(fanPin, 0);

    if (boostTimer + offDelay > millis())
        digitalWrite(boostPin, 1);
    else
        digitalWrite(boostPin, 0);
            
}

