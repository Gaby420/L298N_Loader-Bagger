#include <Arduino.h>
//Linker L298N
//#include <L298NX2.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <L298N_Gaby.h>

const char *ssid        = "Linker_L298N";
const char *password    = "Linker_L298N";

WiFiServer server(80);

const int CCW   = 2;
const int CW    = 1;

#define ENA 14
#define IN1 35
#define IN2 32
#define CHA 0

#define ENB 12
#define IN3 25
#define IN4 26
#define CHB 1

#define motor1 1
#define motor2 2

L298N_Gaby robot_1(ENA, IN1, IN2, CHA, ENB, IN3, IN4, CHB);

/*
const unsigned int EN_A   =34; ////34 existiert nicht 
const unsigned int IN1_A  =35;
const unsigned int IN2_A  =32;

const unsigned int IN1_B  =25;
const unsigned int IN2_B  =26;
const unsigned int EN_B   =27; //27 existiert nicht 

L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

int speedness   = 0;
int speedAmount = 1;
*/
void setup(){
    Serial.begin(115200);
    Serial.println();
    Serial.println("Konfiguriere Wlan...");

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP Address ");
    Serial.println(myIP);
    server.begin();

    Serial.println("Wlan konfiguriert und Server gestartet");
}
void loop(){
    WiFiClient client = server.available();
    
    if (client){
        Serial.println("New Client");
        String currentLine = "";
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character
        
                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0) {
                    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                    // and a content-type so the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println();
        
                
                    // the content of the HTTP response follows the header:
                    //             Motor1_Unterarm
                    client.print("Klicken <a href=\"/A\">here</a> um Schaufel zu bewegen.<br>");
                    client.println("_.<br>");
                    client.print("Klicken <a href=\"/B\">here</a> um Schaufel STOPPT.<br>");
                    client.println("_.<br>");
                    client.print("Klicken <a href=\"/C\">here</a> um Schaufel zu bewegen.<br>");
                    client.println("_.<br>");
                    //              Motor2_Oberarm
                    client.println("_.<br>");
                    client.print("Klicken <a href=\"/D\">here</a> um Getriebe umzustellen.<br>");
                    client.println("_.<br>");
                    client.print("Klicken <a href=\"/E\">here</a> um Getriebe STOPPT.<br>");
                    client.println("_.<br>");
                    client.print("Klicken <a href=\"/F\">here</a> um Getriebe umzustellen.<br>");

                    client.println();
                    // break out of the while loop:
                    break;
                } else {    // if you got a newline, then clear currentLine:
                    currentLine = "";
                }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
        
                // Check to see if the client request was "GET /H" or "GET /L":
                
                //                              UNTERARM

                if (currentLine.endsWith("GET /A")) {
                  robot_1.rotate(motor1, 100, CW);                // GET Unterarm ?
    //            motors.forwardA();
                }
                if (currentLine.endsWith("GET /B")) {
                    robot_1.brake(1);               // GET /L Unterarm STOPPT
    //              motors.stopA();
                }
                if(currentLine.endsWith("GET /C")){
                  robot_1.rotate(motor1, 100, CCW);                // GET Unterarm ?
    //              motors.backwardA();
                } 

                //                              GET /D OBERARM
                
                if(currentLine.endsWith("GET /D")){
                    robot_1.rotate(motor2, 100, CW);                // GET Oberarm ?
//                  motors.forwardB();
                }            
                if(currentLine.endsWith("GET /E")){
                    robot_1.brake(2);                // GET /H Oberarm STOPPT
//                  motors.stopB();
                }
                if(currentLine.endsWith("GET /F")){
                    robot_1.rotate(motor2, 100, CCW);                // GET Oberarm ?
//                  motors.backwardB();
                }           
    
            }

        }
        client.stop();
        Serial.print("Verbindung gestoppt...");
    }
}
