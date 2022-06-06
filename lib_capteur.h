//inclusion de librairies
#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mysql.h>

//Définition des fonctions
int detecterDistance(int pinTrigger,int pinEcho);
int detecterBouton(int pinBouton);
int detecterNiveau(int pinBouton);
void allumerLed( int pinLed,int value);