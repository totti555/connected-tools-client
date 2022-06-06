all : lib_mySql.o lib_capteur.o client.c client.h
	gcc -Wall lib_capteur.o lib_mySql.o -o client.exe client.c -lwiringPi -lmysqlclient -I/usr/include/mariadb/

lib_capteur.o : lib_capteur.c lib_capteur.h
	gcc -Wall -Wextra -c lib_capteur.c -lwiringPi -lmysqlclient -I/usr/include/mariadb/

lib_mySql.o : lib_mySql.c lib_mySql.h
	gcc -Wall -Wextra -c lib_mySql.c -lwiringPi -lmysqlclient -I/usr/include/mariadb/
