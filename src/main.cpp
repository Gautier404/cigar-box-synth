#include <Arduino.h>
#include <functions.cpp> //All of the functions used for this project are contained within the functions.cpp in the include folder

double testfreq;
void setup() {
  Serial.begin(9600);
  createFrequencies();

  //print all 84 frequencies to make sure they've been generated properly
  Serial.println("Frequency Generation:"); 
  for (int i = 0; i <= 83; i++){
    Serial.println(frequencies[i]);
  }

  //print the current tuning of the synth to make sure the tuning potentiometer and tuneSynth functions works
  Serial.println("Tuning test");
  tuneSynth(tun);
  for (int i = 0; i <= 23; i++) {
    Serial.print(tuneIndex);
    Serial.print(tuning[i]);
    Serial.println();
  }
}

void loop() {
  readpot(pot);
  tuneSynth(tun);
  pitch(vib, por);
  delay(5);
  //Serial.println(analogRead(currentPitch)); // uncomment this line to test if arduino is producing tones accuratly.
}