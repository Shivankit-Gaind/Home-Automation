int calibrationTime = 30;
int counter=0;


long unsigned int lowIn1;      
long unsigned int lowIn2;            


long unsigned int pause = 100;  

boolean lockLow1 = true;
boolean takeLowTime1;  
boolean lockLow2 = true;
boolean takeLowTime2; 

int pirPin2 = A1;
int pirPin1 = A0;    
int ledPin = 13;
int flag1=0;
int flag2=0;
int ctr=0;

/////////////////////////////

void setup(){
 Serial.begin(9600);
 pinMode(pirPin1, INPUT);
 pinMode(pirPin2, INPUT);
 pinMode(ledPin, OUTPUT);
 digitalWrite(pirPin1, LOW);
 digitalWrite(pirPin2, LOW);

 Serial.print("calibrating sensor ");
   for(int i = 0; i < calibrationTime; i++){
     Serial.print(".");
     delay(1000);
     }
   Serial.println(" done");
   Serial.println("SENSOR ACTIVE");
   delay(50);
 }

////////////////////////////
//LOOP
void loop(){
 static int relayVal = 0;

    if(digitalRead(pirPin1) == HIGH){
  
      if(lockLow1){  
       
        lockLow1 = false;            
        Serial.println("---");
        Serial.print("motion detected at1 ");
        Serial.print(millis()/1000);
        Serial.println(" sec"); 
       
        delay(50);
        flag1=1;
        if(flag2==1)
        {
         ctr=ctr+1;
         Serial.println("ctr  at 1= ");
         Serial.println(ctr);
         flag1=0;
         flag2=0;
         if(ctr<=0)
                 digitalWrite(ledPin, LOW);
                   if(ctr>0)
                 digitalWrite(ledPin, HIGH);
        }
     
        }         
        takeLowTime1 = true;
      }

//*************8

    if(digitalRead(pirPin2) == HIGH){
      
      if(lockLow2){  
        
        lockLow2 = false;            
        Serial.println("---");
        Serial.print("motion detected at2 ");
        Serial.print(millis()/1000);
        Serial.println(" sec"); 
         
        delay(50);
         flag2=1;
        if(flag1==1)
        {
         ctr=ctr-1;
         Serial.println("ctr at 2 = ");
         Serial.println(ctr);
         flag1=0;
         flag2=0;
         if(ctr<=0)
                 digitalWrite(ledPin, LOW);
                   if(ctr>0)
                 digitalWrite(ledPin, HIGH);
        }
      
        }         
        takeLowTime2 = true;
      }
//************

    if(digitalRead(pirPin1) == LOW){       

      if(takeLowTime1){
       lowIn1 = millis();         
       takeLowTime1 = false;       
       }
      //if the sensor is low for more than the given pause, 
      //we assume that no more motion is going to happen
      if(!lockLow1 && millis() - lowIn1 > pause){  
          //makes sure this block of code is only executed again after 
          //a new motion sequence has been detected
          lockLow1 = true;                        
          Serial.print("motion ended at1 ");      //output
          Serial.print((millis() - pause)/1000);
          Serial.println(" sec");
          delay(50);
          }
      }
//#####
if(digitalRead(pirPin2) == LOW){       
    

      if(takeLowTime2){
       lowIn2 = millis();         
       takeLowTime2 = false;       //make sure this is only done at the start of a LOW phase
       }

      if(!lockLow2 && millis() - lowIn2 > pause){  
         
          lockLow2 = true;                        
          Serial.print("motion ended at2 ");      
          Serial.print((millis() - pause)/1000);
          Serial.println(" sec");
          delay(50);
          }
      }
//#####
if(ctr<=0)
{
  digitalWrite(ledPin, LOW);
}
else{
digitalWrite(ledPin, HIGH);
}


}