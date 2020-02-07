#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <credentials.h>
#include <ThingsBoard.h>
//#include <ArduinoHttpClient.h>


#define DOUT1 15 // load cell 1
#define DOUT2 4 // load cell 2
#define DOUT3 33 // load cell 3
#define DOUT4 27 // load cell 4

#define CLK  32 //CLK was on pin 33 in original code

//const char* mqttServer = "192.168.0.203";
//const int mqttPort = 1883;

float lastValues; 

WiFiClient espClient;
ThingsBoard tb(espClient);
// the Wifi radio's status
//int status = WL_IDLE_STATUS;

HX711 scale1; 
HX711 scale2;
HX711 scale3; 
HX711 scale4;
//WiFiClient espClient;
//PubSubClient client(espClient);



void setup() {
  Serial.begin(115200);
  rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
  Serial.println("IKEA");

  //Connecting to wifi
  WiFi.begin(mySSID, myPASSWORD);

  Serial.println("Connecting to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network");

 // Reconnect to ThingsBoard, if needed
  if (!tb.connected()) {
    Serial.println("Not connected to Thingsboard");

    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  // MQTT Setup 
 /*
  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", "admin", "admin" )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      Serial.println(" ");
    }
  }
*/

  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library


  //Setup for scale1
  scale1.begin(DOUT1, CLK);  //  DO,CK(was 33 before)


  
    // uncomment if you want to calibrate the bowl
    /*
    scale. set_scale();
    scale.tare();
    Serial.println("Put known weight on ");
    delay(2500);
    Serial.print(scale.get_units(10));
    Serial.print(" Divide this value to the weight and insert it in the scale.set_scale() statement");
    while(1==1);
    */
  
    //uncomment until here

  Serial.println("Before setting up scale1:");
  Serial.print("read: \t\t");
  Serial.println(scale1.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale1.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale1.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale1.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale1.tare();				        // reset the scale to 0

  Serial.println("After setting up scale1:");

  Serial.print("read: \t\t");
  Serial.println(scale1.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale1.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale1.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  //client.publish("ikea/service", "Hello from ESP32");

//Setup for scale2
 scale2.begin(DOUT2, CLK);  //  DO,CK(was 33 before)


  
    // uncomment if you want to calibrate the bowl
    /*
    scale. set_scale();
    scale.tare();
    Serial.println("Put known weight on ");
    delay(2500);
    Serial.print(scale.get_units(10));
    Serial.print(" Divide this value to the weight and insert it in the scale.set_scale() statement");
    while(1==1);
    */
  
    //uncomment until here

  Serial.println("Before setting up scale2:");
  Serial.print("read: \t\t");
  Serial.println(scale2.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale2.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale2.tare();				        // reset the scale to 0

  Serial.println("After setting up scale2:");

  Serial.print("read: \t\t");
  Serial.println(scale2.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  //client.publish("ikea/service", "Hello from ESP32");

//Setup for scale3
 scale3.begin(DOUT3, CLK);  //  DO,CK(was 33 before)


  
    // uncomment if you want to calibrate the bowl
    /*
    scale. set_scale();
    scale.tare();
    Serial.println("Put known weight on ");
    delay(2500);
    Serial.print(scale.get_units(10));
    Serial.print(" Divide this value to the weight and insert it in the scale.set_scale() statement");
    while(1==1);
    */
  
    //uncomment until here

  Serial.println("Before setting up scale3:");
  Serial.print("read: \t\t");
  Serial.println(scale3.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale3.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale3.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale3.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale3.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale3.tare();				        // reset the scale to 0

  Serial.println("After setting up scale3:");

  Serial.print("read: \t\t");
  Serial.println(scale3.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale3.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale3.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale3.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  //client.publish("ikea/service", "Hello from ESP32");

//Setup for scale4
 scale4.begin(DOUT4, CLK);  //  DO,CK(was 33 before)


  
    // uncomment if you want to calibrate the bowl
    /*
    scale. set_scale();
    scale.tare();
    Serial.println("Put known weight on ");
    delay(2500);
    Serial.print(scale.get_units(10));
    Serial.print(" Divide this value to the weight and insert it in the scale.set_scale() statement");
    while(1==1);
    */
  
    //uncomment until here

  Serial.println("Before setting up scale4:");
  Serial.print("read: \t\t");
  Serial.println(scale4.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale4.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale4.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale4.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale4.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale4.tare();				        // reset the scale to 0

  Serial.println("After setting up scale4:");

  Serial.print("read: \t\t");
  Serial.println(scale4.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale4.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale4.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale4.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  //client.publish("ikea/service", "Hello from ESP32");
}
void loop() {

//scale 1
 // float averageWeight1 = (char)scale1.get_units(10);
  Serial.print("Scale1 reading:\t");
  Serial.print(scale1.get_units(),1);
  Serial.print("\t");
  //Serial.print("\t| average:\t");
  //Serial.println(averageWeight1);
//scale 2
 // float averageWeight2 = (char)scale2.get_units(10);
  Serial.print("Scale2 reading:\t");
  Serial.print(scale2.get_units(),1);
   Serial.print("\t");
 // Serial.print("\t| average:\t");

 //Scale 3
 // Serial.println(averageWeight2);
  Serial.print("Scale3 reading:\t");
  Serial.print(scale3.get_units(),1);
  Serial.print("\t");

  //Scale 4
  Serial.print("Scale4 reading:\t");
  Serial.print(scale4.get_units(),1);
  Serial.print("\t");
  Serial.println();
  delay(200);

  // Uploads new telemetry to ThingsBoard using MQTT. 
  // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api 
  // for more details
  
  tb.sendTelemetryFloat("scale 1", scale1.get_units()); 
    //else tb.sendTelemetryFloat("scale1", '0');
  tb.sendTelemetryFloat("scale 2", scale2.get_units()); 
    //else tb.sendTelemetryFloat("scale2", '0');
  tb.sendTelemetryFloat("scale 3", scale3.get_units()); 
    //else tb.sendTelemetryFloat("scale3", '0');
  tb.sendTelemetryFloat("scale 4", scale4.get_units()); 
    //else tb.sendTelemetryFloat("scale4", '0');
    

/*
  char buf[20];
  sprintf(buf, "%04.02f", averageWeight);
  client.publish("ikea/weight", buf);

  client.loop();

  scale.power_down();			        // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
  */
}

