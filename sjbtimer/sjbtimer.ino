float vres= 0; // residual voltage test before calibration
// Define the ADC input pin
//const int adcPin = 15;
const int adcPin = 15;
int startTime,fTime,endTime ;
// Variables to store the current and previous ADC values
int currentVal = 0;
int previousVal = 0;
float cv,pv;
char pout[50];
char buffer[50];
void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the ADC

  analogRead(adcPin);
   Serial.println("Start the experiment in 3");
    delay(1000);
    Serial.println("Start the experiment in 2");
    delay(1000);
    Serial.println("Start the experiment in 1");
    delay(1000);
    Serial.println("Start the experiment ");
    delay(1000);

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
   // Read the current ADC value
  currentVal = analogRead(adcPin);
 
  valuerecord();
  
 fTime= startTime-endTime ;
  Serial.print("the time elapsed is");
  Serial.println(fTime);
 // exit(0);
 while (1) {};
}

void valuerecord()
{ startTime = micros();
 while (1) {

     // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 //  float cv = currentVal * (5.0 / 1023.0) - vres;
 cv = currentVal * (3.3 / 4095.0) - vres;
    Serial.print("the voltage is");
    Serial.println(cv);
    if (cv==pv){
    break;
    }
  
else {
    // Store the current value as the previous value
    previousVal = currentVal;
     // pv = currentVal * (5.0 / 1024.0) - vres;
       pv = currentVal * (3.3 / 4095.0) - vres;
      // Wait for a short period of time before reading the ADC again
    delay(1000);
    currentVal = analogRead(adcPin);
    
  }

 }endTime = micros();
}

