#include <Servo.h>
#include <RedBot.h>
RedBotSensor sen_trai = RedBotSensor(A1); //chân S1
RedBotSensor sen_giua = RedBotSensor(A3); //chân S3
RedBotSensor sen_phai = RedBotSensor(A5);//chân S5


int linechuan = 100;
// mach cau H ( tu trai qua phai: day trang so 5, day xam so 10, day tim so 9, day xanh duong so 8 , day xanh la so  7, day vang dam so 6,)
//tren trai mach cau H gom: enA-in1-in2      con ben phai gom:enB-in3-in4    mach cau H hoat dong tu phai sang trai
byte in1 =7; 
byte in2 =8;
byte in3 =9;
byte in4 =10;
int enA = 5;
int enB = 6;
int i,j;
int k,t;
int n,x;
#define trig 11  // khai bao chan 11 la chan trig cua sieu am
#define echo 12  // khai bao chan 12 la chan echo cua sieu am
int  spd=78;// giá trị băm xung=50% cong suat(191/255)
Servo servo1;
void setup() {
pinMode (trig, OUTPUT);
pinMode (echo, INPUT);
Serial.begin(9600);
servo1.attach(3);// Khai báo chân servo
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);

}
void  doline(){
 
 if(sen_trai.read()>linechuan  && sen_giua.read() < linechuan && sen_phai.read()>linechuan){
   motor_thang();
 }else if(sen_trai.read()<linechuan ){
   motor_phai();
 }
 else if( sen_phai.read()<linechuan){
   motor_trai();
 }
 
 else if(sen_trai.read()<linechuan && sen_giua.read()<linechuan && sen_phai.read()<linechuan){
   dunglai();
  
 }
 
 
}

// moto:  di lui la HIGH-LOW, di thuan la LOW-HIGH, di thang la LOW-LOW 
void motor_thang() // chương trình con cho xe chay tới
{
analogWrite(enA,70);
analogWrite(enB,70);
digitalWrite(in1,HIGH);//motor bên trái chạy tới
digitalWrite(in3,HIGH);// motor bên phải chạy tới
//delay(1000);
digitalWrite(in2,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}
void motor_lui()// chương trình con robot chạy lùi
{
analogWrite(enA,65);
analogWrite(enB,65);
digitalWrite(in2,HIGH);
digitalWrite(in4,HIGH);
//delay(1000);
digitalWrite(in1,LOW);
digitalWrite(in3,LOW);
//delay(1000);
}
void motor_trai()
{
analogWrite(enA,70);
analogWrite(enB,80);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
//delay(5000);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(5000);
}
void motor_phai()
{
analogWrite(enA,80);
analogWrite(enB,70);
digitalWrite(in3,HIGH);
digitalWrite(in1,LOW);
//delay(5000);
digitalWrite(in2,LOW);
digitalWrite(in4,LOW);
//delay(5000);
}
void motor_toi()
{
analogWrite(enA,65);
analogWrite(enB,65);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}
void dunglai()
{
analogWrite(enA,0);
analogWrite(enB,0);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}

int khoangcach() // do khoang cach vat can,khong hieu hoi thay
{  
   int dir;
   int time;
   digitalWrite(trig,LOW);
   delayMicroseconds(2);
   digitalWrite(trig,HIGH);
   delayMicroseconds(5);
   digitalWrite(trig,LOW);
   time =pulseIn(echo,HIGH); 
   dir =(time/2/29.412);
   dir = dir;
   if(dir < 255)
   {
  
   return dir;
   }
}
void servo_trai()
{
   for (t=90; t<=135; t=t+3) 
    {      
 
        servo1.write(t);    
        delay(10); // đợi 10 mili dây
    
    }  
    
  
}
 
void servo_vetrai()
{
  for (i=135; i>=90; i=i-3) 
    {      

        servo1.write(i);     
        delay(10); // đợi 10 mili dây
    }


}
 void servo_phai()
 {
    for (k=90; k>=45; k=k-3)
    {
      
        servo1.write(k);
        delay(10); 
      
    }     
     

 }
void servo_vephai()
{
for (j=45; j<=90; j=j+3)
    {
      
        servo1.write(j);
        delay(10);  
    }

}

void robokvc()
{
  while(khoangcach() >= 15)// khoang cach lon hon 15cm
  {
  for (x=49; x<=132; x=x+3)//goc servo quay
   {
      
        servo1.write(x);
        delay(5);
        if (khoangcach() < 15)  break;
  while (khoangcach() >= 15)
  {
    motor_thang();
    break;
   }
  }
  for (x=132; x>=49; x=x-3)// Nếu ta cố điều khiển servo vượt quá những giới hạn cơ học của nó , trục ra của động cơ sẽ đụng vật cản bên trong, dẫn đến các bánh răng bị mài mòn hay bị rơ. 
                           // Hiện tượng này kéo dài hơn vài giây sẽ làm bánh răng của động cơ bị phá hủy
  {
      
        servo1.write(x);
        delay(5);
        if (khoangcach() < 15)  break;
        while (khoangcach() >= 15)
  {
      motor_thang();
    break;
   }
    }
  }
}
void robocvc()
{
 while   (khoangcach() < 15)
  {
    
  
  motor_lui();
 
  servo_trai();
  delay(200);
  float b = (khoangcach());// lay gia tri khoang cach vat ben trai gan vao b
  delay(20);
  servo_vetrai();
  servo_phai();
   delay(200);
  int c = (khoangcach());  //lay gia tri khoang cach vat can ben phai gan vao c
  delay(20);
  servo_vephai();
  
    if (b > 15 &&  c > 15 ) 
    {
   
    motor_lui();
    
    motor_thang();
    
    
    }
    else if (b > 15 && c < 15)
    {
     
    motor_lui();
    
    motor_trai();
    
    }
    else if (b < 15 && c > 15 )
    {
   
    motor_lui();
    motor_phai();
    //delay(500);
    }
    else if (b < 15 && c < 15  )
    {
    
    motor_lui();
    
    motor_phai();
    //delay(500);
  }
 

break;
  }
}

void loop() {
  
 doline();
 
 if((sen_trai.read()>linechuan&&sen_phai.read()>linechuan&&sen_giua.read()>linechuan)&&(khoangcach()<=15)){
         dunglai();
         robokvc();
         robocvc();
 }
/* if(sen_trai.read()>linechuan && sen_giua.read()>linechuan && sen_phai.read()>linechuan){
   motor_thang();
   if(sen_trai.read()<linechuan||sen_phai.read()<linechuan||sen_giua.read()<linechuan ){
     dunglai();
     delay(1000);
     doline();
 }
   
 
 } */
}
