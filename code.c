#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h>

Servo servo;  

LiquidCrystal_I2C lcd(0x27, 20, 4);

const uint8_t ROWS = 4;

const uint8_t COLS = 4;



char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 }; 
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 }; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


int lungime_parola=4;

char parola[20]={'7','6','3','A'};
char vector[20];

int incercari=3;

int i=0;
int cond=0;
int j=0;
int ok=0;
int new_pass=0;
int nr=0;

char resetare[20];

void setup() {
  //Serial.begin(10);

lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Introdu o parola :");
lcd.setCursor(7,1);
pinMode(12,INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
servo.attach(10);
servo.write(90);
}

void loop() {
  
  
 int new_pass=digitalRead(12);
//Serial.print(new_pass);
 int force_open=digitalRead(11);

 if(force_open==0)
 {
   deschidere();
   exit(0);
 }

if(new_pass==0){
  ok=1;
  nr=2;
  
}
 
 if(ok!=0){

   reset();

 }

else{
 

 if(i==lungime_parola)
  {
    int k=0;

    for(int j=0;j<lungime_parola;j++)
      {
        if(vector[j]!=parola[j])
        {
          k=1;
          break;
        } 
      }

    if(k==1)
      incorect();
    
    else if(k==0)
      corect();
    
    
  }

   char key = keypad.getKey();
  
  if (key != NO_KEY) {
    
    vector[i++]=char(key);
    lcd.print(key);
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);
    delay(100);
    digitalWrite(0, HIGH);
  }
 
}
}

void incorect()
{
  pinMode(1, OUTPUT);
      digitalWrite(1, LOW);
      lcd.setCursor(0,3);
      lcd.print("Parola incorecta !!");
      delay(1000);
      digitalWrite(1, HIGH);
      incercari_ramase(); 

}

void corect()
{
  pinMode(0, OUTPUT);
      digitalWrite(0,LOW);
      lcd.setCursor(0,2);
      lcd.print("--------------------");
      lcd.setCursor(1,3);
      servo.write(0);
      lcd.print("Parola corecta !!");
      exit(0);
}

void incercari_ramase()
{
  if(incercari>0){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Introdu o parola:");
  lcd.setCursor(0,1);
  const char mesaj[20];
  sprintf(mesaj,"Incercari ramase %d ",incercari);
  lcd.print(mesaj);
  i=0;
  lcd.setCursor(6,3);
  incercari--;
  loop();
  
}
else 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("--------------------");
  lcd.setCursor(0,2);
  lcd.print("LOCKER BLOCAT");
  lcd.setCursor(0,3);
  lcd.print("--------------------");
  digitalWrite(1, LOW);
  
  exit(0);
}
}

void reset(){

  
    if(cond==0){
    //char *resetare=(char*)calloc(1,sizeof(char));
    char resetare[20];
    
    pinMode(1, OUTPUT);
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("--------------------");
    lcd.setCursor(0,1);
    lcd.print("RESETARE PAROLA");
    servo.write(0);
    lcd.setCursor(0,3);
    lcd.print("--------------------");
    delay(2000);
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Parola noua");
    //delay(2000);
    lcd.setCursor(0,1);
    lcd.print("minim 4 caractere");
    lcd.setCursor(0,2);
    lcd.print("*# pentru setare");
    lcd.setCursor(0,3);
    cond=1;
    }
     
    if(cond==1){

      char key_new= keypad.getKey();
      //resetare=(char*)realloc(resetare,j+1);
     
      
      if(key_new!=NO_KEY){
       lcd.print(key_new);
        resetare[j]=key_new;
      j  ++;
      
      if(resetare[j-1]=='#' && resetare[j-2]=='*')
       cond=2;

      if(j==20)
      cond=2;
      
      }

     
    }

    
    
    if(cond==2){
    
      if(j<4)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Setare incorecta!");
        lcd.setCursor(0,1);
        lcd.print("Minim 4 caractere!");
        lcd.setCursor(0,2);
        lcd.print("APASA BUTOANELE");
        lcd.setCursor(0,3);
        lcd.print("RESET->NEW PASS");
        servo.write(90);
        delay(200);
        exit(0);
        
      }
      resetare[j-2]=0;
      strcpy(parola,resetare);
      lungime_parola=j-2;
      cond=3;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("--------------------");
      lcd.setCursor(0,1);
      lcd.print("Parola este resetata:");
      servo.write(90);
      lcd.setCursor(0,2);
      lcd.print(parola);
      lcd.setCursor(0,3);
      lcd.print("--------------------");
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
      delay(3000);
      digitalWrite(0, HIGH);
      digitalWrite(1, HIGH);
      lcd.clear();
      ok=0;
     cond=0;
     digitalWrite(0,LOW);
     //delay(5000);
     lcd.print("Introdu o parola:");
     
      lcd.setCursor(7,1);
    
      
    }

    
    

}

void deschidere()
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DESCHIDERE FORTATA");
      servo.write(0);
      digitalWrite(0,LOW);
      digitalWrite(1,LOW);
      lcd.setCursor(0,1);
      lcd.print("--------------------");
      lcd.setCursor(0,2);
      lcd.print("--------------------");
      lcd.setCursor(0,3);
      lcd.print("APASA RESET");
      delay(200);
    }

