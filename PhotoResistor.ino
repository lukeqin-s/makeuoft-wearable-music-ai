// arduino tutorials:
// https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-an-arduino

// automatic "night light"
// turn LED on when light levels drop too low

const int led = 22;          // led pin
const int sensor_pin = A0;  // sensor pin
int sensor;					// sensor reading
const int threshold = 500;  // threshold to turn LED on

void setup(){  // setup code that only runs once
  pinMode(led, OUTPUT);  // set LED pin as output
  Serial.begin(9600);    // initialize serial communication
}

void loop(){   // code that loops forever
  sensor = analogRead(sensor_pin);   // read sensor value
  Serial.println(sensor);			 // print sensor value
  if(sensor>threshold){  // if sensor reading is less than threshold
    digitalWrite(led,HIGH);  // turn LED on
  }  
  else{  // else, if sensor reading is greater than threshold
    digitalWrite(led,LOW);    // turn LED off
  }
}