//This will contain all the setup and memory alocation needed for the synth software

//pin setup:
int pot = A0; //linear potentiometer in
int tun = A1; //tuning potentiometer in
int vib = A2; //vibrato potentiometer in
int por = A3; //portamento potentiometer in
int speaker = 3; //speaker, in my build I ran this wiring through an analog low pass filter and gain control potentiometer

//variables used by the createFrequencies function
double frequencies[84] = {}; //stores the 84 frequencies generated

//variables used by the readpot function that processes input from the potentiometer
int reading; //stores the reading of the potentiometer
const int dataPoints = 10; //number of readings that will be averaged at a time
int readings[dataPoints] = {}; //list that stores datapionts
int readingIndex = 0; //the index of the previouse list (will be used to iterate through the list)
int total = 0; //stores the sum of all the readings in the list
float toneIn = 0; //average of readings 
int toneIndex = 0; //mapped value of toneIn

//variables used by the tuneSynth function
int tuneIndex; //mapped value of the tuning potentiometer
int oldTuneIndex; //used to detect if tune Index has changed
double tuning[24]; //an array that stores the notes the synth will play

//variables used by the pitch function
double desiredPitch; //pitch the player wants to go to
double currentPitch; //current pitch the synth is playing 
int portamento;  //how much slide there should be between notes. Comes from the map of the portamento potentiometer
int vibFreq = 30; //scales how quick the vibrato is
float vibrato; //mapped from the vibrato potentiometer (determines amplitude of vibrato)
float t; //current time in milliseconds(used for vibrato)
