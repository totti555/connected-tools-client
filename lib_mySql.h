//Inclusion des librairies
#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mysql.h>

//Définition des fonctions
MYSQL connexion(char server[100],char name[100],char password[100]);
int deconnexion(MYSQL *con);
int requete(MYSQL *con,char name[100],char password[100],char requete[100]);