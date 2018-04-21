//New Automated watering system software, Replace delays() with milis()

int sensorPin = 0;    
// select the input pin for the potentiometer (Humidity sensor Analog Output to this analog pin in Arduino)

int sensorValue = 0;  // variable to store the value coming from the sensor

int hum_thresh = 800; 
// Humidity Threshold. If sensor value is above, then soil is dry. A read below stands for a damp soil.

int sensorVCC = 13; // Pin that gives power to run current through soil humidity sensor. Vcc from sensor goes to this pin.

int out_pin = 11; // Pint that to relay; current pases when high

unsigned long wait_t = 28800000UL; // Time to wait between consecutive meassurments in miliseconds 
        // ( currently set to 8 hours)

unsigned long start_time;

unsigned long water_t = 300000UL; // Time to water the plants in miliseconds
        // (Currently set to 5 minutes)

//Don't forget to connect ground from sensor to ground from arduino!
 
void setup() {
    // declare the ledPin as an OUTPUT:
    Serial.begin(9600);  
    pinMode(out_pin,OUTPUT);
    pinMode(sensorVCC, OUTPUT); 
    digitalWrite(sensorVCC, LOW);
    digitalWrite(out_pin, LOW); 
    
    // Sense Humidity
            // power the sensor  
        digitalWrite(sensorVCC, HIGH); //Now there is current passing through soil sensor
        
        delay(100); //make sure the sensor is powered
        
        // read the value from the sensor:
        sensorValue = analogRead(sensorPin); 
        
        delay(100); //make sure the sensor is powered
         
        //stop power 
        digitalWrite(sensorVCC, LOW); 

      Serial.print(sensorValue);
      Serial.print("\n");
      
      if( sensorValue > hum_thresh ) // Check wether sensor give value below treshold
    {
    // Make it rain during 10 s
    digitalWrite(out_pin, HIGH);
    delay(10000);
    digitalWrite(out_pin, LOW);       
    }
    start_time = millis(); // Initial time when turned on
}
 
void loop() {
 
    if( millis() - start_time > wait_t) // If time elapsed since start_time is longer than wait_t
        {
        // power the sensor  
        digitalWrite(sensorVCC, HIGH); //Now there is current passing through soil sensor
        
        delay(100); //make sure the sensor is powered
        
        // read the value from the sensor:
        sensorValue = analogRead(sensorPin); 
        
        delay(100); //make sure the sensor is powered
         
        //stop power 
        digitalWrite(sensorVCC, LOW);  
        
        // print the humidity value of read 1024 is dry, 1 is wet 
        //Serial.print("sensor = " );                       
        //Serial.println(sensorValue);  
        
        if( sensorValue > hum_thresh ) // Check wether sensor give value below treshold
            {
            digitalWrite(out_pin, HIGH);
            delay(water_t);
            digitalWrite(out_pin, LOW);      
            }
 
        start_time = millis(); //Restart Timer
        }   

// Here I could put a push-button activatation for the watering system. 

                     
}
