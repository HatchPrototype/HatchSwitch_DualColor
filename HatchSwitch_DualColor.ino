#include<SoftwareSerial.h>

SoftwareSerial wifi(11,12);

#define S1BL 3
#define S1YL 2
#define S2BL A3
#define S2YL A2
#define S4BL 5
#define S4YL 4
#define S3BL A0
#define S3YL A1
#define L1 6
#define L2 7
#define L3 8
#define L4 9

#define ID1 0xFA
#define ID2 0x20

#define delms 2




bool SW1,SW2,SW3,SW4;

bool h1,h2,h3,h4;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(S1BL, OUTPUT);
  pinMode(S2BL, OUTPUT);
  pinMode(S3BL, OUTPUT);
  pinMode(S4BL, OUTPUT);
  pinMode(S1YL, OUTPUT);
  pinMode(S2YL, OUTPUT);
  pinMode(S3YL, OUTPUT);
  pinMode(S4YL, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  Serial.begin(9600);
  wifi.begin(38400);

  digitalWrite(S1BL,HIGH);
  digitalWrite(S2BL,HIGH);
  digitalWrite(S3BL,HIGH);
  digitalWrite(S4BL,HIGH);
  h1 = LOW;
  h2 = LOW;
  h3 = LOW;
  h4 = LOW;
  SW1 = LOW;
  SW2 = LOW;
  SW3 = LOW;
  SW4 = LOW;
  



  

}

// the loop function runs over and over again forever
void loop() {
  readwifibee();
  getInput();
  writeLED();
  writeOutput();

  wifi.println("Hello");
}

void readwifibee()
{
  byte inbuff[32];
  byte crc = 0x00;
  if(wifi.available()==13)
  {
    for(int i=0;i<=13;i++)
    {
      inbuff[i] = wifi.read();
    }

     
    if((inbuff[0] == 0xCC)&&(inbuff[1] == 0x77)&&(inbuff[2] == 0xCC)&&(inbuff[3] == 0x77)&&(inbuff[4] == ID1)&&(inbuff[5] == ID2))
    {
      for(int j=0;j<=13;j++)
      {
        crc ^= inbuff[j];
      }
      if((inbuff[6] == 0x06)&&(inbuff[7] == 0xAC)&&(inbuff[12] == crc))
      {

        //----------------------------SW1-------------------------//
        if(inbuff[8]== 0x01)
        {
          SW1 = HIGH;
        }
        else if(inbuff[8] == 0x00)
        {
          SW1 = LOW;
        }
        else
        {
          
        }
        //----------------------------SW2-------------------------//
        if(inbuff[9]== 0x01)
        {
          SW2 = HIGH;
        }
        else if(inbuff[9] == 0x00)
        {
          SW2 = LOW;
        }
        else
        {
          
        }

        //----------------------------SW3-------------------------//
        if(inbuff[10]== 0x01)
        {
          SW3 = HIGH;
        }
        else if(inbuff[10] == 0x00)
        {
          SW3 = LOW;
        }
        else
        {
          
        }

        //----------------------------SW4-------------------------//
        if(inbuff[11]== 0x01)
        {
          SW4 = HIGH;
        }
        else if(inbuff[11] == 0x00)
        {
          SW4 = LOW;
        }
        else
        {
          
        }

       ACK();
    
      }
      NAK();
    }
    
  }
}

void doCircle()
{
  
  digitalWrite(S1BL,LOW);
  digitalWrite(S1YL,HIGH);
  delay(50);
  digitalWrite(S1BL,HIGH);
  digitalWrite(S1YL,LOW);
  digitalWrite(S2BL,LOW);
  digitalWrite(S2YL,HIGH);
  delay(50);
  digitalWrite(S2BL,HIGH);
  digitalWrite(S2YL,LOW);
  digitalWrite(S3BL,LOW);
  digitalWrite(S3YL,HIGH);
  delay(50);
  digitalWrite(S3BL,HIGH);
  digitalWrite(S3YL,LOW);
  digitalWrite(S4BL,LOW);
  digitalWrite(S4YL,HIGH);
  delay(50);
  digitalWrite(S4BL,HIGH);
  digitalWrite(S4YL,LOW);
  
}

void getInput()
{
  int i1,i2,i3,i4;
  i1=analogRead(A4);
  delay(delms);
  i2=analogRead(A5);
  delay(delms);
  i3=analogRead(A6);
  delay(delms);
  i4=analogRead(A7);
  delay(delms);
  
  //-----------------------------H1----------------------------------//
  if(i1<=512)
  {
    if((h1==LOW)&&(SW1 == LOW))
    {
      SW1 = HIGH;
      h1 = HIGH;
    }
    else if((h1 == LOW)&&(SW1 == HIGH))
    {
      SW1 = LOW;
      h1 = HIGH;
    }
    
  }
  else
  {
    h1 = LOW;
  }

  //-----------------------------H2----------------------------------//
  if(i2<=512)
  {
    if((h2==LOW)&&(SW2 == LOW))
    {
      SW2 = HIGH;
      h2 = HIGH;
    }
    else if((h2 == LOW)&&(SW2 == HIGH))
    {
      SW2 = LOW;
      h2 = HIGH;
    }
    
  }
  else
  {
    h2 = LOW;
  }

  
  //-----------------------------H3----------------------------------//

  if(i3<=512)
  {
    if((h3==LOW)&&(SW3 == LOW))
    {
      SW3 = HIGH;
      h3 = HIGH;
    }
    else if((h3 == LOW)&&(SW3 == HIGH))
    {
      SW3 = LOW;
      h3 = HIGH;
    }
    
  }
  else
  {
    h3 = LOW;
  }


  
  //-----------------------------H4----------------------------------//
  if(i4<=512)
  {
    if((h4==LOW)&&(SW4 == LOW))
    {
      SW4 = HIGH;
      h4 = HIGH;
    }
    else if((h4 == LOW)&&(SW4 == HIGH))
    {
      SW4 = LOW;
      h4 = HIGH;
    }
    
  }
  else
  {
    h4 = LOW;
  }
  
}


void writeLED()
{
  //-----------------------SW1------------------------//
  if(SW1 == HIGH)
  {
    digitalWrite(S1BL,LOW);
    digitalWrite(S1YL,HIGH);
   }
   else
   {
    digitalWrite(S1BL,HIGH);
    digitalWrite(S1YL,LOW);
   }

   //-----------------------SW2------------------------//
   if(SW2 == HIGH)
  {
    digitalWrite(S2BL,LOW);
    digitalWrite(S2YL,HIGH);
   }
   else
   {
    digitalWrite(S2BL,HIGH);
    digitalWrite(S2YL,LOW);
   }

   //-----------------------SW3------------------------//
   if(SW3 == HIGH)
  {
    digitalWrite(S3BL,LOW);
    digitalWrite(S3YL,HIGH);
   }
   else
   {
    digitalWrite(S3BL,HIGH);
    digitalWrite(S3YL,LOW);
   }

   //-----------------------SW4------------------------//

   if(SW4 == HIGH)
  {
    digitalWrite(S4BL,LOW);
    digitalWrite(S4YL,HIGH);
   }
   else
   {
    digitalWrite(S4BL,HIGH);
    digitalWrite(S4YL,LOW);
   }

   
}

void writeOutput()
{
  digitalWrite(L1,SW1);
  digitalWrite(L2,SW2);
  digitalWrite(L3,SW3);
  digitalWrite(L4,SW4);
}

void ACK()
{
  wifi.write(0xCC);
  wifi.write(0x77);
  wifi.write(0xCC);
  wifi.write(0x77);
  wifi.write(0xDA);
  wifi.write(0xDA);
  wifi.write(0x02);
  wifi.write(0x0A);
  wifi.write(0x08);
}

void NAK()
{
  wifi.write(0xCC);
  wifi.write(0x77);
  wifi.write(0xCC);
  wifi.write(0x77);
  wifi.write(0xDA);
  wifi.write(0xDA);
  wifi.write(0x02);
  wifi.write(0x01);
  wifi.write(0x03);
}

