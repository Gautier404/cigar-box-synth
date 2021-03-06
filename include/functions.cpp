#include <Arduino.h>
#include <synth.h>

//createFrequncies creates a array of frequencies that will be used to tune the synth to different scales.
void createFrequencies () {
  for (int i = 0; i <= 83; i++) 
  frequencies[i] = 440*pow(2, double (i-49)/12); //adds a frequency to an array according to the function for equal temperment (from wikipedia)
}

//readpot takes in the soft pot reading, smooths it out and then maps the tone to 12//
void readpot (int pot) {
  reading = analogRead(pot);
  total = total - readings[readingIndex]; //subtract last reading from readings

  if (reading < 5) {
    //if the player isn't depressing the linear potentiometer we don't want to be adding 0 to the current tone
    readings[readingIndex] = toneIn; 
  } else {
    //Since I'm using a pull down on the linear potentiometer, the potentiometer is no longer linear.
    //To fix this I used excel and some testing to create a polynomial that makes the readings more linear.
    readings[readingIndex] = -.0007*pow(reading, 2) + 1.7227*reading - 40.462; //take in the linearlized reading and add it to the readings array
  }
  total = total + readings[readingIndex]; //add new reading to the total

  readingIndex = readingIndex + 1; //shift index up one
  if (readingIndex >= dataPoints) { //if index is above the number of data points shift it back to 0
    readingIndex = 0;
  }
  toneIn = total / dataPoints; //take average of datapoints
  toneIndex = map(toneIn, 5, 1000, 24, 0); //map average to 24 keys
}

//tune the synth to the correct scale from the tuning potentiometer
void tuneSynth(int tun) {
  tuneIndex = map(analogRead(tun), 0, 1024, 0, 6); //map tuning potentiometer to 6 values
  if (tuneIndex != oldTuneIndex) { 
    for (int i = 0; i <= 23; i++) {
      tuning[i] = frequencies[12*tuneIndex + i]; //if the tune Index has changed iterate through the tuning array and add in the new tuned frequencies
    }
  }
  oldTuneIndex = tuneIndex;
}

//generate a tone to be played based on portamento, vibrato, and input from the soft pot
void pitch (int vib, int por) {
  portamento = map(analogRead(por), 0, 1024, 0, 10);
  desiredPitch = tuning[toneIndex]; //calculate the pitch the player wants
  
  //if the portamento potentiometer is off just set the current pitch to the desired pitch. If it's on add in portamento effect.
  if (portamento == 10) {
    currentPitch = desiredPitch;
  } else {
  currentPitch = (desiredPitch - currentPitch)*portamento/10 + currentPitch; //the higher the portamento the faster notes slide to each other
  }

  //create and regulate vibrato based on a sinusoidal function and the time
  t = millis();
  vibrato = analogRead(vib)*cos(t/vibFreq)/500;

  //if the linear potentiometer isn't reading anything don't play any noise. If it is generate a tone to be played.
  if (reading < 5) {
    noTone(speaker); 
  } else {
  tone(speaker, currentPitch + vibrato); 
  }
}