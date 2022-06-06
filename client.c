#include "client.h"


void main(){

	gestionGel (PIN_TRIGGER,PIN_ECHO,PIN_BOUTON,PIN_LED,PIN_NIVEAU,ID_GEL); 

}


void gestionGel (int pinTrigger,int pinEcho,int pinBouton,int pinLed,int pinNiveau,int idGel){
	
  //initialisation des ports GPIO
  wiringPiSetup () ;
  pinMode (pinBouton, INPUT) ;
  pinMode (pinLed, OUTPUT) ;
  pinMode(pinTrigger, OUTPUT); // Configuration du port du Trigger comme une SORTIE
  pinMode(pinEcho, INPUT);
  pinMode(pinNiveau,INPUT);
  
  //declaration des variables
  int appui=0,appui1=0, dosesDelivrees=0,dosesNonDelivrees=0,distance=0,niveau=0;
  int tpsPersonne=0;// tps personne > 8 = 4 s
  char sidGel[10];
  char day[10], mois[10], an[10],date[50];
  char requeteSQL[500],requeteSQL2[500], requeteDosesOui[500],requeteDosesNon[500],requeteVide[500],requetePlein[500];

//récupération de la date du jour
  time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );

  //initialisation des variables
  sprintf(sidGel,"%d", idGel);
  sprintf(day,"%02d",timeInfos->tm_mday);          
  sprintf(mois,"%02d",timeInfos->tm_mon+1);     
  sprintf(an,"%04d",timeInfos->tm_year+1900); 
  strcpy(date,strcat(strcat(strcat(an,"-"),strcat(mois,"-")),day));	
  strcpy(requeteSQL,"\0");strcpy(requeteSQL2,"\0");strcpy(requeteDosesOui,"\0");strcpy(requeteDosesNon,"\0");strcpy(requeteVide,"\0");strcpy(requetePlein,"\0");
  
 //requete initiale
  strcpy(requeteSQL,"insert into GEL(`Idgel`,`DateGel`,`NbreDosesDistrib`,`NbreDosesNnDistrib`,`EstVide`) values (");
  strcat(requeteSQL,sidGel); strcat(requeteSQL,",\'");strcat(requeteSQL,date); strcat(requeteSQL,"\',");strcat(requeteSQL,"0,0,0);\0");

//verif necessité requete initiale
strcat(requeteSQL2,"SELECT * FROM GEL WHERE idgel=");strcat(requeteSQL2,sidGel);strcat(requeteSQL2," AND DateGel=\'");strcat(requeteSQL2,date);
strcat(requeteSQL2,"\';");
printf("test:%s\n",requeteSQL2  );

//construction DoseOk
strcat(requeteDosesOui,"Update GEL set NbreDosesDistrib=NbreDosesDistrib+1 Where idgel=");
strcat(requeteDosesOui,sidGel);strcat(requeteDosesOui," and DateGel=\'");strcat(requeteDosesOui,date);strcat(requeteDosesOui,"\';");

//Construction DoseKo
strcat(requeteDosesNon,"Update GEL set NbreDosesNnDistrib=NbreDosesNnDistrib+1 Where idgel=");
strcat(requeteDosesNon,sidGel);strcat(requeteDosesNon," and DateGel=\'");strcat(requeteDosesNon,date);strcat(requeteDosesNon,"\';");

//Construction GelVide
strcat(requeteVide,"Update GEL set EstVide=1 Where idgel=");
strcat(requeteVide,sidGel);strcat(requeteVide," and DateGel=\'");strcat(requeteVide,date);strcat(requeteVide,"\';");

//construction gel plein
strcat(requetePlein,"Update GEL set EstVide=0 Where idgel=");
strcat(requetePlein,sidGel);strcat(requetePlein," and DateGel=\'");strcat(requetePlein,date);strcat(requetePlein,"\';");

 printf( "*******Date:%s ********* \n",date);
 //connexion à la base de donnée
 MYSQL mysql=connexion(IP_SERVER,USER,PASSWORD);
requete(&mysql,USER,PASSWORD,requeteSQL);
printf("connexion au serveur effectué\n");
  //coeur du programme
  for(;;){
	  allumerLed(pinLed,LOW); 
	  appui1=appui;//on donne la valeur de appui à appui -1
	  appui=detecterBouton(pinBouton);// on détecte de appui
	  distance=detecterDistance(pinTrigger,pinEcho);
	  niveau=detecterNiveau(pinNiveau);
	  if(appui==0 && appui!=appui1 && niveau!=0){
		  dosesDelivrees++;
      requete(&mysql,USER,PASSWORD,requeteDosesOui);
		  tpsPersonne=0;
	  }
	  else if(appui==1 && distance<100 && tpsPersonne>8){
		allumerLed(pinLed,HIGH);
		dosesNonDelivrees++;
    requete(&mysql,USER,PASSWORD,requeteDosesNon);
		tpsPersonne=0;
	 }
	else if(niveau!=0 && distance<100){
	   tpsPersonne++;
	 }
	 
	 if (niveau==0){
	   printf("gel vide\n");
     requete(&mysql,USER,PASSWORD,requeteVide);//requete vide= le gel est vide
	 }
   else{
    requete(&mysql,USER,PASSWORD,requetePlein);
   }
	 
	 printf("Nbre de doses delivrees=%d	Nbre de doses nonDelivrees=%d 	distance:%d\n",dosesDelivrees,dosesNonDelivrees,distance);
	 delay(500);
}

deconnexion(&mysql);
}
