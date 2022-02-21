#include <PS4BT.h>
#include <Servo.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);
Servo s1;Servo s2;
int fre=7,frd=3,frp=4,fld=5,flp=6,bre=13,brd=8,brp=9,bld=11,blp=12;
#define p1 28
#define p2 29
#define d1 30
#define d2 31
int te=38,tp=39,td=40;
int s=100,pos=0;
int s1v=35,s2v=34,s1g=36,s2g=37;
void setup() {
  s1.attach(32);s2.attach(41);
  pinMode(te,OUTPUT); digitalWrite(te,LOW);
  pinMode(tp,OUTPUT);
  pinMode(td,OUTPUT);
  pinMode(s1v,OUTPUT); 
  pinMode(s1g,OUTPUT);
  pinMode(s2v,OUTPUT);
  pinMode(s2g,OUTPUT);
  digitalWrite(s1v,HIGH);
  digitalWrite(s2v,HIGH);
  digitalWrite(s1g,LOW);
  digitalWrite(s2g,LOW);
  pinMode(p1,OUTPUT); 
  pinMode(p2,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(fre,OUTPUT);
  pinMode(frd,OUTPUT);
  pinMode(frp,OUTPUT);
  pinMode(fld,OUTPUT);
  pinMode(flp,OUTPUT);
  pinMode(bre,OUTPUT);
  pinMode(brd,OUTPUT);
  pinMode(brp,OUTPUT);
  pinMode(bld,OUTPUT);
  pinMode(blp,OUTPUT);
  digitalWrite(fre,HIGH);
  digitalWrite(bre,HIGH);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
 while (!Serial);
 #endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if (PS4.connected()) 
  {
      if (PS4.getButtonClick(UP))
      {
        Serial.println("STOP");
        stop();
      }
      
      if (PS4.getAnalogHat(LeftHatX) > 200 && PS4.getAnalogHat(LeftHatY) < 200 && PS4.getAnalogHat(LeftHatY) > 130)
      {
        Serial.println("Right");
        analogWrite(s,map(PS4.getAnalogHat(LeftHatX),200,255,0,150));
        right(s);
      }
      if (PS4.getAnalogHat(LeftHatX) < 80 && PS4.getAnalogHat(LeftHatY) < 200 && PS4.getAnalogHat(LeftHatY) < 150)
      {
        Serial.println("Left");
        analogWrite(s,map(PS4.getAnalogHat(LeftHatX),80,0,0,150));
        left(s);
      }
      if (PS4.getAnalogHat(LeftHatY) < 60 && PS4.getAnalogHat(LeftHatX) > 110 && PS4.getAnalogHat(LeftHatX) < 150)
      {
        Serial.println("Forward");
        analogWrite(s,map(PS4.getAnalogHat(LeftHatY),60,0,0,150));
        forward(s);
      }
      
      if (PS4.getAnalogHat(LeftHatY) > 200 && PS4.getAnalogHat(LeftHatX) > 120 && PS4.getAnalogHat(LeftHatX) < 160)
      {
        Serial.println("Backward");
        analogWrite(s,map(PS4.getAnalogHat(LeftHatY),200,255,0,150));
        backward(s);
      }
      if (PS4.getAnalogHat(LeftHatY) < 200 && PS4.getAnalogHat(LeftHatX) < 160 && PS4.getAnalogHat(LeftHatX) > 70 && PS4.getAnalogHat(LeftHatY) > 70)
      {
        
        stop();
      }
      if (PS4.getAnalogHat(RightHatY) < 60 && PS4.getAnalogHat(RightHatX) > 110 && PS4.getAnalogHat(RightHatX) < 150)
      {
        Serial.println("UP");

        digitalWrite(d1,HIGH);
        digitalWrite(d2,LOW);
        
        digitalWrite(p1,HIGH);
        digitalWrite(p2,LOW);
        delay(1);  
        digitalWrite(p1,LOW);
        digitalWrite(p2,HIGH);
        delay(1);
       }
      if (PS4.getAnalogHat(RightHatY) > 200 && PS4.getAnalogHat(RightHatX) > 120 && PS4.getAnalogHat(RightHatX) < 160)
      {
        Serial.println("DOWN");

        digitalWrite(d1,LOW);
        digitalWrite(d2,HIGH);
        
        digitalWrite(p1,HIGH);
        digitalWrite(p2,LOW); 
        delay(1);  
        digitalWrite(p1,LOW);
        digitalWrite(p2,HIGH);
        delay(1);
      }

      if (PS4.getAnalogHat(RightHatX) > 220 && PS4.getAnalogHat(RightHatY) < 200 && PS4.getAnalogHat(RightHatY) > 130)
      {
        Serial.println("OPENING");
        s1.write(0);
      }
      else if (PS4.getAnalogHat(RightHatX) < 50 && PS4.getAnalogHat(RightHatY) < 200 && PS4.getAnalogHat(RightHatY) < 150)
      {
        Serial.println("CLOSING");
        s1.write(90 );
      }
      else
      {
        s1.write(0);
        }

        if (PS4.getButtonClick(SQUARE))
        {
           digitalWrite(te,HIGH);
           digitalWrite(tp,HIGH);
           delay(500);
           digitalWrite(tp,LOW);
        }

        if (PS4.getAnalogButton(L2)>120)
        {
          s2.write(180);
          }
        else if (PS4.getAnalogButton(R2)>120){
          s2.write(0);
          }
         else
         {
          s2.write(90 );
          }
         
  }
}

void forward(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,HIGH);  digitalWrite(brd,HIGH);  digitalWrite(fld,HIGH);  digitalWrite(bld,HIGH);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void backward(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,LOW);  digitalWrite(brd,LOW);  digitalWrite(fld,LOW);  digitalWrite(bld,LOW);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void right(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,HIGH);  digitalWrite(brd,LOW);  digitalWrite(fld,LOW);  digitalWrite(bld,HIGH);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void left(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,LOW);  digitalWrite(brd,HIGH);  digitalWrite(fld,HIGH);  digitalWrite(bld,LOW);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void rightd(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,HIGH);  digitalWrite(brd,LOW);  digitalWrite(fld,LOW);  digitalWrite(bld,HIGH);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void leftd(int pwm)
{
  digitalWrite(fre,LOW);  digitalWrite(bre,LOW);  
  digitalWrite(frd,LOW);  digitalWrite(brd,HIGH);  digitalWrite(fld,HIGH);  digitalWrite(bld,LOW);
  analogWrite(frp,pwm);  analogWrite(brp,pwm+20);  analogWrite(flp,pwm+20);  analogWrite(blp,pwm);
  }
void stop()
{
  digitalWrite(fre,HIGH);  digitalWrite(bre,HIGH);  
  }
