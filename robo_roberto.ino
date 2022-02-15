#include<NewPing.h> 

int dist;

#define TRIGGER_PIN 9
#define ECHO_PIN 8 
#define DIST_MAX 20

NewPing sonar(TRIGGER_PIN, ECHO_PIN, DIST_MAX);

int M11 = 48; 
int M12 = 46;
int M21 = 50; 
int M22 = 52;
int M1S = 12;
int M2S = 13;
int spd = 100;
int aux = 0;

// VARIÁVEIS DO SENSOR DE LINHA

int angulo;
int cor0, cor1; 

int lim_pretoE = 1024;
int lim_brancoE = 100; 

int lim_pretoD = 1024; 
int lim_brancoD = 100;

int sensor_esquerda = A7;
int sensor_direita = A6; 

int valor_esquerda = 0;
int valor_direita = 0; 

void setup() {
  // put your setup code here, to run once:
  
  pinMode(M11, OUTPUT); 
  pinMode(M12, OUTPUT); 
  pinMode(M21, OUTPUT); 
  pinMode(M22, OUTPUT);   
  pinMode(M1S, OUTPUT); 
  pinMode(M2S, OUTPUT);   
  
  Serial.begin(9600);
 
 
}
void frente(int spd){
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void para(int spd){
  digitalWrite(M11,LOW);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void desq(int spd){
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void ddir(int spd){
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  analogWrite(M1S,150);
  analogWrite(M2S,150);
}

void monitorar_obstaculo() {  
 //frente(spd); 
 int di = 0;
 di = sonar.ping_cm();
// delay(300);
// di = sonar.ping_cm();
 
 Serial.println(di);
  if(di >= 5 && di <= 15) {
      para(spd);
      delay(1000);
      desq(spd); 
      delay(500); // Giro 90º a velocidade de 100
      frente(spd); 
      delay(1500); // Giro 90º a velocidade de 100
      ddir(spd);
      delay(500); // Giro 90º a velocidade de 100
      frente(spd); 
      delay(2000);
      ddir(spd);
      delay(500);
      frente(spd); 
      delay(1000); // Giro 90º a velocidade de 100
      desq(spd); 
      delay(800);
      //frente(spd); 
     // delay(1500); // Giro 90º a velocidade de 100
//      para(spd);
  }
} 

// TABELA VERDADE PARA OS 2 SENSORES 

void tabela() {

  if(cor0 == 0 && cor1 == 0) {
    frente(spd);
    
  }
  
  if(cor0 == 0 && cor1 == 1) {
    ddir(spd);
    
  }
  
  if(cor0 == 1 && cor1 == 0) {
    desq(spd);
    
  }
  
  if(cor0 == 1 && cor1 == 1) {
    para(spd);
  }
}
 
int lerSensor(int sensor) {   
    
    if(sensor == 0){
      valor_esquerda = analogRead(sensor_esquerda);
      return classificaSensor(valor_esquerda);   
    }

    if(sensor == 1){
      valor_direita = analogRead(sensor_direita);
      return classificaSensor(valor_direita);      
    } 
}

int classificaSensor(int valor){

// CÓDIGO PARA LIMITAR SENSOR DA ESQUERDA  
  
  if(valor > 0 && valor < lim_brancoE){
    return 0;
  }
  
   else if(valor > lim_brancoE && valor < lim_pretoE){
    return 1;
  }

// CÓDIGO PARA LIMITAR SENSOR DA DIREITA 

  if(valor > 0 && valor < lim_brancoD) {
    return 0;
    } 
   else if(valor > lim_brancoD && valor < lim_pretoD) {
    return 1;
  }
   }

void loop() {
  
  cor0 = lerSensor(0);
  cor1 = lerSensor(1);
  tabela();
  
  Serial.print("Cor0: ");
  Serial.print(valor_esquerda);
  Serial.print(" Cor1: ");
  Serial.println(valor_direita); 
   

  monitorar_obstaculo(); 
}


