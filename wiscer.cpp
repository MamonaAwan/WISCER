#include <SoftwareSerial.h>
#include <Servo.h> 
Servo servowhite;        // create servo object to control a servo 
Servo servoblack;        // create servo object to control a servo
int count;
int pos = 0;
char check = 0;
SoftwareSerial mySerial(10, 11);
void setup() 
{ 
  Serial.begin(9600);
  delay(1000);
  mySerial.begin(9600);
  delay(1000);
  pinMode(10, INPUT);
  servowhite.attach(8); // attaches the servo on pin 8 to the servo object 
  servoblack.attach(9); // attaches the servo on pin 9 to the servo object 
  while(!Serial)
  {
    ;
  }
} 
void loop()
{
      mySerial.write('u');
      delay(100);
      unpack();

      mySerial.write('t');  
      delay(100);
      count=1;
      two_leg();
  
      mySerial.write('w');
      delay(100);
      count=0;    
      worm();
    
      mySerial.write('l');  
      delay(100);
      count=1;
      leg_walk();
      
      mySerial.write('p');
      delay(100);  
      pack();
      
      while(true)
      {
        continue;
      }
}

void pack()
{
    servowhite.write(180);
    servoblack.write(180);
    delay(1000);
    mySerial.write('a');
    delay(100);
    while(!mySerial.available())
    {
      ;                 //wait untill data is recieved by serial   
    }
    if (mySerial.available())
    {
      char x = mySerial.read();
      if(x=='b')
      {
        servowhite.write(180);
        servoblack.write(180);
        delay(1000);
      }
    } 
}

void unpack()
{
    servowhite.write(90);
    servoblack.write(90);
    delay(1000);
    mySerial.write('c');
    delay(100);
}

void worm()
{
  while(count < 10)
  {
    mySerial.write('a');
    delay(100);
    while(!mySerial.available())
    {
      ;
    }
    if (mySerial.available())
    {
      char x = mySerial.read();
      if (x=='a')
       {
        for(pos = 45; pos < 105; pos += 1)  // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
           servowhite.write(pos);          // tell servo to go to position in variable 'pos'  
           delay(10);                      // waits 10ms for the servo to reach the position 
        }  
        for (pos = 100; pos > 10; pos -= 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
           servoblack.write(pos);         // tell servo to go to position in variable 'pos'  
           delay(10);                    // waits 10ms for the servo to reach the position 
        }
       }
       mySerial.write('a');
       delay(1000);
     }
     count+=1;
   }
  mySerial.write('z');
  delay(1000);
}

void two_leg()
{
  while(count==1)
  {
    servowhite.write(135);
    servoblack.write(90);
    delay(1000);
    mySerial.write('a');
    delay(100);
    count=count+1;
  }
    while(!mySerial.available())
    {
      ;                 //wait untill data is recieved by serial comm    
    }
 
    if (mySerial.available())
    {
      char x = mySerial.read();
      while(x!='z')
      {
         if(x=='b')
        {
          servowhite.write(90);
          servoblack.write(0);
          delay(1000);
          mySerial.write('c');
          delay(100);
        }
        if(x=='d')
        {
          servowhite.write(45);
          servoblack.write(45);
          delay(1000);
          mySerial.write('e');
          delay(100);
        }
        if (x=='f')
        {
          servowhite.write(0);
          servoblack.write(90);
          delay(1000);
          mySerial.write('g');
          delay(100);
        }
        if (mySerial.available())
        {
           x = mySerial.read();
        }
      }
      mySerial.write('z');
      delay(100);
    } 
}
void leg_walk()
{
   while(count < 11)
   {
      mySerial.write('a');
      delay(100);
      while(!mySerial.available())
      {
        ;
      }
      if (mySerial.available())
      {
        char x = mySerial.read();
        if (x=='a')
        {
          for(pos = 90; pos > 0; pos -= 1)  // goes from 90 degrees to 0 degrees 
          {                                 // in steps of 1 degree 
            servowhite.write(pos);          // tell servo to go to position in variable 'pos'  
            servoblack.write(90);
            delay(10);                      // waits 10ms for the servo to reach the position 
          }
        }
        delay(100);
        mySerial.write('a');
        delay(100);
      }
      count=count+1;
    }
   mySerial.write('z');
  delay(100); 
}


MODULE 2:

#include <SoftwareSerial.h>
#include <Servo.h> 
Servo servowhite;        // create servo object to control a servo 
Servo servoblack;        // create servo object to control a servo
int pos =0;
int count;
char check = 0;
SoftwareSerial mySerial(10, 11);
void setup() 
{ 
  mySerial.begin(9600);
  delay(1000);
  pinMode(10, INPUT);
  servowhite.attach(8);   // attaches the servo on pin 8 to the servo object 
  servoblack.attach(9);   // attaches the servo on pin 9 to the servo object 
  while(!mySerial.available())
  {
    ;
  }
} 
void loop()
{
  while(!mySerial.available())
  {
    continue;
  }
  if (mySerial.available())
  {
    check= mySerial.read();
  }
  switch(check)
  { 
    case 'u':
      unpack();
      break;
      
    case 'p':
      pack();
      break;

    case 'w':  
      worm();
      break;

    case 't':
      count=1;
      two_leg();
      break;

    case 'l':
      break;
  }  
}
void pack()
{
   while(!mySerial.available())
   {
    ;                     //wait untill data is recieved by serial   
   }
   if (mySerial.available())
    {
      char x = mySerial.read();
      if (x=='a')
      {
        servowhite.write(90);
        servoblack.write(20);
        delay(1000);
        servowhite.write(0);
        servoblack.write(20);
        delay(1000);
        mySerial.write('b');
        delay(100);
      }
    }
}
void unpack()
{
   while(!mySerial.available())
   {
    ;                     //wait untill data is recieved by serial    
   }
   if (mySerial.available())
    {
      char x = mySerial.read();
      if (x=='c')
      {
        servowhite.write(90);
        servoblack.write(90);
        delay(1000);
      }
    }
}
void worm()
{
    while(!mySerial.available())
    {
      ;
    }
     char x = mySerial.read();
     while(x!='z')
     {
       if (x=='a')
        {
          for(pos = 30; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            servoblack.write(pos);           // tell servo to go to position in variable 'pos'  
            delay(10);                       // waits 10ms for the servo to reach the position 
          }
          for(pos = 10; pos < 120; pos += 1) // goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            servowhite.write(pos);           // tell servo to go to position in variable 'pos'  
            delay(10);                       // waits 10ms for the servo to reach the position 
          } 
          mySerial.write('a');
          delay(1000);
        }
        x=mySerial.read();
     }
}

void two_leg()
{
  while(count==1)
  {
    servowhite.write(90);
    servoblack.write(90);
    count=count+1;
  }
    
   while(!mySerial.available())
   {
    ;                     //wait untill data is recieved by serial    
   }
      char x = mySerial.read();
      while(x!='z')
      { 
        if (x=='a')
        {
          servowhite.write(90);
          servoblack.write(45);
          delay(1000);
          mySerial.write('b');
          delay(100);
        }
        if (x=='c')
        {
          servowhite.write(180);
          servoblack.write(90);
          delay(1000);
          mySerial.write('d');
          delay(100);
        }
        if (x=='e')
        {
          servowhite.write(135);
          servoblack.write(135);
          delay(1000);
          mySerial.write('f');
          delay(100);
        }
        if (x=='g')
        {
          servowhite.write(90);
          servoblack.write(180);
          delay(1000);
          mySerial.write('z');
          delay(100);
        }
        if (mySerial.available())
        {
           x = mySerial.read();
        }
    }
}

void leg_walk()
{
   while(!mySerial.available())
  {
    ;
  }
    char x = mySerial.read();
    while(x!='z')
    {
      if (x=='a')
      {
       for(pos = 135; pos <180; pos += 1)  // goes from 180 degrees to 135 degrees 
        {                                  // in steps of 1 degree 
          servoblack.write(pos);           // tell servo to go to position in variable 'pos'  
          servowhite.write(90);
          delay(10);                       // waits 10ms for the servo to reach the position 
        }
       delay(100);
       mySerial.write('a');
       delay(100);
      }
      x=mySerial.read();
    } 
}
