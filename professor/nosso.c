#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campo.h"

#define MAXSTR 512
// #define MAXINT 16

int main(int argc, char **argv) {
  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  char *pont_bola;
  char pos_saltos[MAXSTR / 2];
  int indPosSalto;
  int pos_meuf;
  int tam_campo;
  int pos_filo;
  int pos_bola;
  int num_saltos;
  int i;
  int podeSaltar;

  // conecta com o controlador do campo
  campo_conecta(argc, argv);

  campo_recebe(buf);

  	// separa os elementos do string recebido
  	sscanf(strtok(buf, " \n"), "%c", &lado_meu);
  	sscanf(strtok(NULL, " \n"), "%d", &tam_campo);
  	sscanf(strtok(NULL, " \n"), "%s", campo);
  	sscanf(strtok(NULL, " \n"), "%c", &lado_adv);
  	sscanf(strtok(NULL, " \n"), "%c", &mov_adv);
  	
 	  if(mov_adv == 'f'){
 	    sscanf(strtok(NULL, " \n"), "%d", &pos_filo);
 	  }

 	  if(lado_meu == 'e'){
 	  	pos_meuf = tam_campo;
 	  } else {
 	  	pos_meuf = 1;
 	  }

 	  if(pos_meuf == pos_filo){
 	  	pos_meuf = tam_campo / 2;
 	  	pos_meuf += (lado_meu == 'e') ? 2 : 0;
 	  }

  	// prepara um string com o movimento
  	// de inserir um filosofo na posicao 1 do campo
  	sprintf(buf, "%c f %d\n", lado_meu, pos_meuf);

  	// envia o movimento para o controlador do campo
  	campo_envia(buf);  


  while(1) {
    campo_recebe(buf);
 
  	// separa os elementos do string recebido
  	sscanf(strtok(buf, " \n"), "%c", &lado_meu);
  	sscanf(strtok(NULL, " \n"), "%d", &tam_campo);
  	sscanf(strtok(NULL, " \n"), "%s", campo);
  	sscanf(strtok(NULL, " \n"), "%c", &lado_adv);
  	sscanf(strtok(NULL, " \n"), "%c", &mov_adv);
 
  	pont_bola = strchr(campo, 'o');
  	indPosSalto = 0;

  	pos_bola = pont_bola - campo;

  	if(lado_meu == 'e'){
  		if(campo[pos_bola + 1] == 'f'){
  			podeSaltar = 1;
  			for(i = pos_bola + 2; ((i <= tam_campo) && podeSaltar); i++){
 					if(campo[i + 1] != 'f'){
 	 					podeSaltar = 0;
 	 					pos_saltos[indPosSalto] = (char) i;
 	 				} else {
 	 					pos_saltos[indPosSalto] = (char) i;
 	 				}
 	 				indPosSalto++;
  			}
  		}
  	}
	

 //  	// prepara um string com o movimento
 //  	// de inserir um filosofo na posicao 1 do campo
 //  	sprintf(buf, "%c f %d\n", lado_meu, 1);



 //  	// envia o movimento para o controlador do campo
  	campo_envia(buf);  
	}
}






