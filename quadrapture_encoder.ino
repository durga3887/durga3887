//Welcome to Durga prasad coding
/*These codes is used to calculate the Direction of the Motor*/

 #define dir 9
 #define pwm 7

const byte interruptPin_r_a = 47;       //2, 3, 18, 19, 20, 21 interrupt pins
const byte interruptPin_f_a = 49;
const byte interruptPin_r_b = 51;
const byte interruptPin_f_b = 53;
long tc=0,tp=0;
volatile byte state = LOW;
int count=0;
int en_a_state=0,en_b_state=0,en_a_las_state=0,en_b_las_state=0;

void setup() {Serial.begin(9600);
 pinMode (pwm,OUTPUT);
 pinMode (dir,OUTPUT);

  pinMode(interruptPin_r_a, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_r_a), rais_a, RISING);
  pinMode(interruptPin_f_a, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_f_a), fall_a, FALLING);
  pinMode(interruptPin_r_b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_r_b), rais_b, RISING);
  pinMode(interruptPin_f_b, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_f_b), fall_b, FALLING);
 
}

void loop() {
  if(tp==0)
  {Serial.println("tp");
  tc=millis();
  tp++;}
 if(tc+10000>=millis())
 {Serial.println("pwm_h");
 analogWrite(pwm,15);
 } 
 else
 {
 analogWrite(pwm,0); 
 Serial.println("pwm_L");
 }
 digitalWrite(dir,HIGH);
 Serial.print("count:");
 Serial.println(count);
}

void rais_a() {
  en_a_state=HIGH;
  calculataion();
}
void fall_a() {
  
  en_a_state=LOW;
  calculataion();
}
void rais_b() {
 en_b_state=HIGH;
 calculataion();
}
void fall_b() {
  
 en_b_state=LOW;
 calculataion();
}
void calculataion()
{
  if (en_a_state != en_a_las_state)           // If the previous and the current state of the encoderA are different, that means a Pulse has occured
       {   
          if (en_b_state == en_a_state) // If the encoderB state is different to the encoderA state, that means the encoder is rotating clockwise
        {
           count--;   
          } 
          else
          {
            count++;
            }     

         }  
   else if (en_a_state == en_a_las_state)           // If the previous and the current state of the encoderA are different, that means a Pulse has occured
    { 
     
      if (en_b_state != en_b_las_state)   
      {
         if (en_b_state != en_a_state) // If the encoderB state is different to the encoderA state, that means the encoder is rotating clockwise
           {
           count--; 
          } 
          else
          {
            count++;   
            }
      }
      
    }
   en_a_las_state= en_a_state;
    en_b_las_state=en_b_state;   
}
