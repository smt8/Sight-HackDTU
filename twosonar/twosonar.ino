// Hardware used: Arduino UN), 2 Ultrasonic SONAR Sensor - HC-SR04 sensors, 2 Pager(Vibration) Motors//
// Aim of the code is to //
float distance1;  // Distance measured by 1st SONAR Sensor
float distance2;  // Distance measured by 2ND SONAR Sensor
float diffrence; // Diffrence of distance measured by SONAR Sensors


int trigPin1 = 3;
int echoPin1 = 4;

int trigPin2 = 6;
int echoPin2 = 7;

int motorLeft = 8;
int motorRight = 9;

void setup() {

  pinMode(trigPin1, OUTPUT);  // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input

  pinMode(motorLeft, OUTPUT); // Sets the LEFT Motor as an Output
  pinMode(motorRight, OUTPUT); // Sets the RIGHT Motor as an Output

}

void loop() {

  distance1 = calculateDistance(trigPin1, echoPin1);
  distance2 = calculateDistance(trigPin2, echoPin2);
  delay(300);
  diffrence = distance2 - distance1;

  if (distance1 < 300 ||  distance2 < 300) {

    if (diffrence < 30 && diffrence > -30) {
      digitalWrite(motorLeft, HIGH);
      digitalWrite(motorRight, HIGH);
      delay(1000);
    }

    else if (diffrence > 30 && distance1 < distance2) {

      digitalWrite(motorLeft, HIGH);
      digitalWrite(motorRight, LOW);
      delay(1000);
    }

    else if (diffrence > 30 && distance1 > distance2) {

      digitalWrite(motorLeft, LOW);
      digitalWrite(motorRight, HIGH);
      delay(1000);
    }


  }

  else {
    digitalWrite(motorLeft, LOW);
    digitalWrite(motorRight, LOW);
    
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
float calculateDistance(int trigPin, int echoPin) {

  float distance;

  unsigned long T1 = micros();
  digitalWrite(trigPin, LOW); // trigPin needs a fresh LOW pulse before sending a HIGH pulse that can be detected from echoPin
  delayMicroseconds(2);//DELAY #2:time for which low trig pulse is maintained before making it high
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);//DELAY #3:Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  //distance= duration*0.034/2;
  distance = (duration / 2) / 29.1; //in cm,  datasheet gives "duration/58" as the formula

  //To avoid sending data at variable time intervals due to varying time duration taken between execution of above code inside this function depending on distance of obstacle
  //if no object, echo pulse is 38ms long HIGH
  while (micros() - T1 < 38000)
  {
    ;
  }

  return distance;
}
