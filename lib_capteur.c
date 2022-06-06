#include "lib_capteur.h"

int detecterDistance(int pinTrigger,int pinEcho){
	

// Variables utileh
int duree=0;
int distance; // distance

  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(5);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  // Ã‰coute de l'Ã©cho 
   while(digitalRead(pinEcho)==0 && duree<1540)
   {duree++;
    delayMicroseconds(10);}
   duree=0;
   while(digitalRead(pinEcho)!=0 && duree<154){
     duree++;
       delayMicroseconds(100);
   }
  // Calcul de la distance
  distance = (duree*2.6);
  if (distance!=0){
	return distance;
    }
  else {return detecterDistance(pinTrigger,pinEcho);}
}


int detecterBouton(int pinBouton){
    return digitalRead(pinBouton) ; 

  }

int detecterNiveau(int pinNiveau){
    return digitalRead(pinNiveau) ; 

  }

void allumerLed( int pinLed,int value){
	digitalWrite (pinLed,value) ;
}