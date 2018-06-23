#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campo.h"

#define MAXSTR 512
#define MAXINT 16

int main(int argc, char **argv) {
  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  char *pont_bola;
  char pos_saltos[MAXSTR / 2];
  int vetorVazios[MAXSTR / 2];
  char pulo[MAXSTR];
  int pos_meuf, qtdePulos, gol_e, gol_d;
  int tam_campo;
  int pos_filo;
  int pos_bola;
  int num_saltos;
  int i, j, z, podePular;
  char str[MAXINT];

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

  	pos_bola = (pont_bola - campo) + 1;

  	// Verifica se pode saltar
   	j = 0;
   	qtdePulos = 0;
   	gol_e = tam_campo + 1;
   	gol_d = 0;

   	if(lado_meu == 'e'){
   		pos_meuf = pos_bola + 1;
   		if(campo[pos_bola] == 'f'){
   			podePular = 1;
   			for(i = pos_bola; i < tam_campo; i++){
   				if(campo[i] == '.'){
						vetorVazios[j] = i;   				
	   				j++;
   				}
   			}

   			j++;
   			vetorVazios[j] = gol_e;

   			z = 0;
   			while((z < j) && (campo[vetorVazios[z]] != pos_bola + 1)){
   				qtdePulos++;
   				sprintf(str, "%d", vetorVazios[z]);
   				strcat(pulo, str);
   				strcat(pulo, " ");
   				pos_bola = vetorVazios[z];
   				z++;
   			}
  		}

  	} else {
  		
  		pos_meuf = pos_bola - 1;
  		
  		if(campo[pos_bola - 2] == 'f'){
   			podePular = 1;
   			for(i = pos_bola - 2; i > 0; i--){
   				if(campo[i] == '.'){
						vetorVazios[j] = i;   				
	   				j++;
   				}
   			}

   			j++;
   			vetorVazios[j] = gol_d;

   			z = 0;
   			while((z < j) && (campo[vetorVazios[z]] != pos_bola - 1)){
   				qtdePulos++;
   				sprintf(str, "%d", vetorVazios[z]);
   				strcat(pulo, str);
   				strcat(pulo, " ");
   				pos_bola = vetorVazios[z];
   				z++;
   			}
  		}
		}

  	if(podePular){
  		sprintf(buf, "%c o %s\n", lado_meu, pulo);
		} else {
			sprintf(buf, "%c f %d\n", lado_meu, pos_meuf);
		}

		podePular = 0;
		strcpy(pulo, "");
	
  	// envia o movimento para o controlador do campo
		printf("%s\n", buf);
  	campo_envia(buf);  
	}
}






