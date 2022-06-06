//Inclusion des librairies
#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mysql.h>
#include "lib_capteur.h"
#include "lib_mySql.h"

//Définition des constantes
#define PIN_TRIGGER 22
#define PIN_ECHO 21
#define PIN_BOUTON 7
#define PIN_LED 27
#define PIN_NIVEAU 25
#define ID_GEL 1
#define IP_SERVER "192.168.194.55"
#define PORT_SERVER 3306
#define USER "distant"
#define PASSWORD "password"


//Définition des fonctions
void gestionGel (int pinTrigger,int pinEcho,int pinBouton,int pinLed,int pinNiveau,int idGel);
