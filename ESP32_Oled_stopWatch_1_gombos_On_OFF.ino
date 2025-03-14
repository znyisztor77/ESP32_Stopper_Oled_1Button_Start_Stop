#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define startButton 26

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int hours = 0;
int minutes = 0;
long int seconds = 0;
unsigned long previousMillis = 0;
const long  interval = 1000;

int buttonState;
int lastButtonState = HIGH;
int State = LOW;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(startButton, INPUT_PULLUP); // start button  
  }

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 30);
  
  buttonState = digitalRead(startButton);
  
  unsigned long currentMillis = millis();
  
  if (buttonState != lastButtonState){
    if(buttonState == LOW){
      State = !State;
    }
  }
  lastButtonState = buttonState;
  
  if(State == 1){
    if(currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      seconds++;
      
      if (seconds>59){ 
      seconds=0;   
      minutes++; 
      } 
      if (minutes>59){
      hours++; 
      minutes=0; 
      } 
      if(hours>23){ 
      hours=0; 
      }       
    }
  }
  if(hours<10){
        display.print("0"+String(hours)+ ":");
      }
      
      else{display.print(String(hours)+ ":");
      }
      if(minutes<10){
        display.print("0"+String(minutes)+ ":");
      }
      
      else{display.print(String(minutes)+ ":");
      }
      if(seconds<10){
        display.print("0"+String(seconds));
      }
      
      else{ display.print(String(seconds));
      }
  
  display.display();
}
