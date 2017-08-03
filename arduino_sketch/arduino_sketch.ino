 int led = 13;
 int pinA = 3;  // Connected to CLK on KY-040
 int pinB = 4;  // Connected to DT on KY-040
 int pinC = 5;  // Connected to CLK on KY-040
 int pinD = 6;  // Connected to DT on KY-040
 int encoderPosCount = 0; 
 int pinALast;  
 int aVal;
 int pinCLast;  
 int cVal;
 boolean bCW;

 void setup() { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
   pinMode(led, OUTPUT);


   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   pinALast = digitalRead(pinA);   
   Serial.begin (9600);
 } 

void loop() {
  boolean p1 = false;
  boolean p2 = false;
  boolean p3 = false;
  boolean p4 = false;
  
  //Serial.println("--start--");
   //int buttonState = digitalRead(button);
   //digitalWrite(led, buttonState);
   aVal = digitalRead(pinA);
   if (aVal != pinALast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     if (bCW){
       p1 = true;
       //Serial.println ("1");
       //digitalWrite(led, HIGH);
     }else{
       p2 = true;
       //Serial.println("2");
     }
     
   } 
   pinALast = aVal;
   
   cVal = digitalRead(pinC);
   if (cVal != pinCLast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinD) != cVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     if (bCW){
       p3 = true;
       //Serial.println ("3");
       //digitalWrite(led, HIGH);
     }else{
       p4 = true;
       //Serial.println("4");
     }
     
   } 
   pinCLast = cVal;
   
   if(p1||p2||p3||p4){
     //Serial.println("--start--");
     if(p1){
       Serial.println("1");
     }
     if(p2){
       Serial.println("2");
     }
     if(p3){
       Serial.println("3");
     }
     if(p4){
       Serial.println("4");
     }
     //Serial.println("--end--");
   }
 } 
