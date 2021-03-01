const int sensorPin = 0;           // select the input pin for the potentiometer
const int buttonPin = 2;            // the number of the pushbutton pin
const int ledRed =  5;              // D0-l3 the number of the LED pin
const int ledGreen =  16;           // D1-l1 the number of the LED pin
const int ledYellow =  4;           // D2-l2 the number of the LED pin
const long minGlobInterval = 5000;  // Minim work general interval 
const long maxGlobInterval = 10000; // Maxim work general interval 

// variables will change:
int blink = 0;               // variable for blinking green light
int buttonState = 0;         // variable for reading the pushbutton status
int colourState = 0;         // variable to know current colour
long currentTime = 0;        // variable to know current time
long previousMillis = 0;     // Will store last time LED was updated
long interval = 1000;        // Interval at which to blink (milliseconds)
long sensorValue;            // variable to store the value coming from the sensor
long globalInterval = minGlobInterval;

void setup() {    
    pinMode(ledGreen, OUTPUT);      // Declaring ledPins as an OUTPUT:
    pinMode(ledRed, OUTPUT);
    pinMode(buttonState, INPUT);    // Declaring button as an Input

    digitalWrite(ledGreen, HIGH);   // Turn off green light
    digitalWrite(ledRed, LOW);      // Turn on red light
    colourState = ledRed;           // Active Colour
    Serial.begin(9600);             // Enabled print
}


void loop(){
    unsigned long currentMillis;
    currentMillis = millis();
    
    currentTime = currentMillis - previousMillis;
    if( currentTime >  globalInterval) {
        if( colourState == ledRed ){
            digitalWrite(ledGreen, LOW); 
            digitalWrite(ledRed, HIGH);
            colourState = ledGreen;
        }else{
            digitalWrite(ledGreen, HIGH);
            digitalWrite(ledRed, LOW);
            colourState = ledRed; 
            blink = 0; 
        }
            
        Serial.print("CHANGING COLOURSTATE: " );        
        printDebugger();
        previousMillis = currentMillis;     // restart clock
    }

    
    sensorValue = SensorRead();

    // If 1s
    if( currentTime % interval == 0 ) {
        // debo ver cada cuanto preguntar para saber cual va a ser mi intervalo
        // me d la impresion que se cambia a cada rato
        // Serial.print("BEFORE SENSOR -> " );
        // printDebugger();
        globalInterval = intervalRange(sensorValue, globalInterval, colourState);        
        Serial.print("AFTER INTERVAL -> " );        
        printDebugger();
        pushButton();    // Check button status
    }

    if( (colourState == ledGreen) && (currentTime % (interval/2) == 0 )) {
        handlerGreen(globalInterval, currentTime);
    }

}

long SensorRead(){
    long sensorVal = analogRead(sensorPin);
    sensorVal = map(sensorVal, 0, 1023, 0, 1);
    return sensorVal;
}

long intervalRange(long sensorLect, int interval, int colour){
    // Converge -> 0  morning
    // Converge -> valorAlto  night
    Serial.print("BEFORE INTERVAL -> " );
    printDebugger();
    if (colour ==ledGreen) { // Green light        
        interval = changeInterval(sensorLect, interval, 700);
    }else{ // Red light
        interval = changeInterval(sensorLect, interval, 7000);
    }
    return interval;
}

long changeInterval(int sensorLect, int interval, int condit){
    sensorLect = SensorRead();
    if (sensorLect == 1) {
        Serial.println("IF changeInterval= " );
        Serial.println(sensorLect );
        Serial.println(condit );
        interval = maxGlobInterval;
    }else{
        Serial.println("ELSE changeInterval= " );
        Serial.println(sensorLect );
        Serial.println(condit );
        interval = minGlobInterval;
    }
    return interval;
}


void pushButton(){
    buttonState = digitalRead(buttonPin);    // read the state of the pushbutton value:
    if (buttonState == 0) {
        digitalWrite(ledRed, HIGH);          // Turn off red light
        digitalWrite(ledGreen, LOW);         // Turn on green light
        colourState = ledGreen;              // Set colour
    }
    // printDebugger();
    return;
}

void handlerGreen(int interval, int currentTime){
    // Serial.println("handlerGreen" );
    if (interval == minGlobInterval && currentTime > 2000 ) {
        blinkGreen();
    }else if(interval == maxGlobInterval && currentTime > 6000 ){
        blinkGreen();
    }
    return ;
}

void blinkGreen(){
    if( blink == 0){
        digitalWrite(ledGreen, LOW);
        blink = 1; 
    }else{
        digitalWrite(ledGreen, HIGH);
        blink = 0; 
    }
    Serial.print("BLINK -> " );
    printDebugger();
    return;
}

void printDebugger(){
    Serial.print("currentTime=");
    Serial.print( currentTime );
    Serial.print(", colourState[ledRed=5,ledGreen=16]=" );
    Serial.print( colourState );
    Serial.print(", sensorValue=" );
    Serial.print( sensorValue );
    Serial.print(", globalInterval=" );
    Serial.print( globalInterval );
    Serial.print(", blink=" );
    Serial.println( blink );

}