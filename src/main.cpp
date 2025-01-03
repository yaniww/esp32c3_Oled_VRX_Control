#include <Arduino.h>
#include <AlfredoCRSF.h>
#include <EncButton.h>
#include <U8g2lib.h>

#include <Wire.h>

#define SDA_PIN 5
#define SCL_PIN 6

#define BUTTON_PIN GPIO_NUM_9

#define S1 GPIO_NUM_0
#define CS1 GPIO_NUM_1
#define CS2 GPIO_NUM_2
#define CS3 GPIO_NUM_3

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /*clock*/ SCL_PIN, /*data*/ SDA_PIN); // EastRising 0.42" OLED
Button but(BUTTON_PIN);

AlfredoCRSF crsf;
crsfLinkStatistics_t crsfLink;

uint16_t channel12Value=1000;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(S1, OUTPUT);
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);
  pinMode(CS3, OUTPUT);


  delay(500);
  u8g2.begin();
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1, GPIO_NUM_4);
  crsf.begin(Serial1);

  but.tick();

  u8g2.setContrast(8);
  u8g2.setBusClock(400000);
  u8g2.setFont(u8g2_font_ncenB08_te);
  u8g2.enableUTF8Print();
  u8g2.setDisplayRotation(&u8g2_cb_r2);
  u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  u8g2.setFont(u8g2_font_5x7_mf);
  //u8g2.setCursor(0, 8);
  u8g2.sendBuffer();
}

void loop()
{
  //static uint8_t i = 0;
  but.tick();
  //u8g2.setDisplayRotation(++i % 2 == 0 ? &u8g2_cb_r2 : &u8g2_cb_r0);
  crsf.update();
  channel12Value=crsf.getChannel(12);
  channel12Value=channel12Value>1000?channel12Value:1000;
  //u8g2.setCursor(0, 8);
  u8g2.setCursor(0,32);
  u8g2.print("12: ");
  u8g2.print(channel12Value);
  u8g2.setCursor(0, 40);
  u8g2.print("RSSI: ");
  u8g2.print( crsf.getLinkStatistics()->downlink_RSSI);
  u8g2.print(" QTY: ");
  u8g2.print(crsf.getLinkStatistics()->downlink_Link_quality);
  u8g2.sendBuffer();
  
  u8g2.setCursor(0, 8);
  u8g2.print("Freq: ");
  if(channel12Value>=1000&& channel12Value<1075){
    digitalWrite(S1, HIGH);
    digitalWrite(CS3, LOW);
    digitalWrite(CS2,LOW);
    digitalWrite(CS1,LOW);
    u8g2.print("1080");
  }
  else if(channel12Value>1075 && channel12Value <= 1150){
    digitalWrite(S1, HIGH);
    digitalWrite(CS3, LOW);
    digitalWrite(CS2,LOW);
    digitalWrite(CS1,HIGH);
    u8g2.print("1120");
  }
  else if(channel12Value>1150 && channel12Value <= 1275){
    digitalWrite(S1, HIGH);
    digitalWrite(CS3, LOW);
    digitalWrite(CS2,HIGH);
    digitalWrite(CS1,LOW);
    u8g2.print("1160");
  }
  else if(channel12Value>1275 && channel12Value <= 1425){
    digitalWrite(S1, HIGH);
    digitalWrite(CS3, LOW);
    digitalWrite(CS2, HIGH);
    digitalWrite(CS1, HIGH);
    u8g2.print("1200");
  }
  else if(channel12Value>1425 && channel12Value <= 1550){
    digitalWrite(S1, HIGH);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS2, LOW);
    digitalWrite(CS1, LOW);
    u8g2.print("1240");
  }
  else if(channel12Value>1550 && channel12Value <= 1675){
    digitalWrite(S1, LOW);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS2, LOW);
    digitalWrite(CS1, LOW);
    u8g2.print("1258");
  }
  else if(channel12Value>1675 && channel12Value <= 1825){
    digitalWrite(S1, LOW);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS2, LOW);
    digitalWrite(CS1, HIGH);
    u8g2.print("1280");
  }
else if(channel12Value>1825 && channel12Value <= 1950){
    digitalWrite(S1, LOW);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS2 ,HIGH);
    digitalWrite(CS1, LOW);
    u8g2.print("1320");
  }
  else if(channel12Value>1950 && channel12Value <= 2100){
    digitalWrite(S1, LOW);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS2, HIGH);
    digitalWrite(CS1, HIGH);
    u8g2.print("1360");
  }


  u8g2.sendBuffer();
  
  
  
}
