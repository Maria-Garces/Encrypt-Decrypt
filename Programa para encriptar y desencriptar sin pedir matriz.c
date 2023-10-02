#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>

/* 	Programa que permita encriptar y desencriptar mensajes ingresados por el 
	usuario */
	
void ConvertirNumero(int vector[], int longitud, char v[], int longi);
void Desencriptar(int criptograma[], int longitud, int m[][3], int filas, int determinante);	
void Inversa(int determinante, int matriz[][3], int filas);
int Determinante(int m[][3], int filas);
int Menu();
int ValidarNumero(char str[], int longitud);
int ValidarNegativo(char str[], int longitud);
int ValidarTexto(char str[], int longitud);
void QuitarNuevaLinea(char cadena[], int longitud);
void Encriptar(char texto[], int longitud);
void ConvertirTexto(char texto[], int longitud);
void Multiplicacion(int vector[], int longitud, float matriz[][3], int filas);
void ImprimirVector(int vector[], int longitud);
void ImprimirChar(char texto[], int longitud);
void ReiniciarVector(int vector1[], int vector2[], int vector3[], int vector4[], int vector5[], int longitud);

int letras[15], v1[3]={0,0,0}, v2[3]={0,0,0}, v3[3]={0,0,0}, v4[3]={0,0,0}, v5[3]={0,0,0}, v6[3]={0,0,0};
int vector1[3]={0,0,0}, vector2[3]={0,0,0}, vector3[3]={0,0,0}, vector4[3]={0,0,0}, vector5[3]={0,0,0};
float inversa[3][3], matriz[3][3]={{1, -2, 2}, {-1, 1, 3}, {1, -1, -4}};
char t1[4], t2[4], t3[4], t4[4], t5[4]; 	
int m[3][3]={{1, -2, 2}, {-1, 1, 3}, {1, -1, -4}};
	
int main(){
	
	int opcion, longitud, texto_valido, cripto_valido, longitud_valida, i, j, criptograma[15];
	char validar_texto[21], validar_criptograma[5], validar_longitud[5], validar_numero[5];
	int longitud_criptograma, matriz_usuario[3][3], numero_valido, determinante;
	
	textcolor(WHITE);
	opcion=Menu();
	
	do{
	
		switch(opcion){
			
			case 1:
				
				do{
				
					printf("\n\nIngrese el mensaje que desea encriptar: ");
					printf("\n\nNota- El mensaje debe tener maximo 15 caracteres (Incluyendo espacios en blanco)\n\n");
					fgets(validar_texto, 21, stdin);
					fflush(stdin);
					longitud=strlen(validar_texto);
					QuitarNuevaLinea(validar_texto, longitud);
					texto_valido=ValidarTexto(validar_texto, longitud-1);
					
					if(longitud>16 && validar_texto[15]!='\n'){
						textcolor(RED); printf("\n\n[!] ");
						textcolor(WHITE);
						printf("Ingrese maximo hasta 15 caracteres, incluyendo espacios en blanco.\n\n");
					}
					
					system("pause");
					system("cls");
					
				}while(texto_valido==1 || (longitud>16 && validar_texto[15]!='\n'));
				
				Encriptar(validar_texto, longitud);
				
				textcolor(GREEN); printf("\n\n[_/] ");
				textcolor(WHITE); printf("El texto ha sido encriptado exitosamente, resultado: ");
				printf("\n\n\t");
				
				if(longitud-1<4){
					ImprimirVector(v2, 3);
				}
				else if(longitud-1>3 && longitud-1<7){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3);
				}
				else if(longitud-1>6 && longitud-1<10){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
				}
				else if(longitud-1>9 &&longitud-1<13){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
					ImprimirVector(v5, 3);
				}
				else if(longitud-1>12 && longitud<17){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
					ImprimirVector(v5, 3); ImprimirVector(v6, 3);
				}
				
				ReiniciarVector(vector1, vector2, vector3, vector4, vector5, 3);
				ReiniciarVector(v2, v3, v4, v5, v6, 3);
				memset(validar_texto, '\0', 21);
				for(i=0; i<15; i++){
					letras[i]=0;
				}
				
				break;
				
			case 2:
				
				do{
					
					printf("Ingrese la longitud del criptograma que desea desencriptar: ");
					printf("\n\nNota- El criptograma debe tener maximo 15 numeros.\n\n");	
					fgets(validar_longitud, 5, stdin);
					fflush(stdin);
					longitud=strlen(validar_longitud);
					QuitarNuevaLinea(validar_longitud, longitud);
					longitud_valida=ValidarNumero(validar_longitud, longitud-1);
					
					if(longitud_valida==0){
						longitud_criptograma=atoi(validar_longitud);
					}
					if(longitud_criptograma!=3 && longitud_criptograma!=6 && longitud_criptograma!=9 && longitud_criptograma!=12 && longitud_criptograma!=15 || longitud_criptograma==0){
						textcolor(RED); printf("\n\n[!] ");
						textcolor(WHITE); 
						printf("Longitud invalida, debe ser maximo hasta 15 y debe ser multiplo de 3.\n\n");
					}
					
					system("pause");
					system("cls");
					
				}while(longitud_valida==1 || longitud_criptograma==0 || (longitud_criptograma!=3 && longitud_criptograma!=6 && longitud_criptograma!=9 && longitud_criptograma!=12 && longitud_criptograma!=15));
				
				printf("\n\nIngrese el criptograma que desea desencriptar:\n\n");
				
				for(i=0; i<longitud_criptograma; i++){
				
					do{
						printf("Ingrese el elemento %d del criptograma: ", i+1);
						fgets(validar_criptograma, 5, stdin);
						fflush(stdin);
						longitud=strlen(validar_criptograma);
						QuitarNuevaLinea(validar_criptograma, longitud);
						cripto_valido=ValidarNegativo(validar_criptograma, longitud-1);
						
						if(cripto_valido==0){
							criptograma[i]=atoi(validar_criptograma);
						}
						if(cripto_valido==1){
							system("pause");
							system("cls");
						}
						
					}while(cripto_valido==1);
				
				}
				system("cls");
				
			
			determinante=Determinante(m, 3);
				
			printf("\n\nDesencriptando...");
			Sleep(3000);
			
			Desencriptar(criptograma, longitud_criptograma, m, 3, determinante);
			
			textcolor(GREEN); printf("\n\n[_/] ");
			textcolor(WHITE); printf("El texto ha sido desencriptado exitosamente, resultado: ");
			printf("\n\n\t");
				
				if(longitud_criptograma==3){
					ImprimirChar(t1, 4);
				}
				else if(longitud_criptograma==6){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4);
				}
				else if(longitud_criptograma==9){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
				}
				else if(longitud_criptograma==12){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
					ImprimirChar(t4, 4);
				}
				else if(longitud_criptograma==15){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
					ImprimirChar(t4, 4); ImprimirChar(t5, 4);
				}
				
				ReiniciarVector(vector1, vector2, vector3, vector4, vector5, 3);
				memset(t1, '\0', 4); memset(t2, '\0', 4); memset(t3, '\0', 4);
				memset(t4, '\0', 4); memset(t5, '\0', 4); memset(validar_criptograma, '\0', 5);
				for(i=0; i<15; i++){
					criptograma[i]=0;
				}
				
				break;
				
			case 3:
				
				do{
				
					printf("\n\nIngrese el mensaje que desea encriptar: ");
					printf("\n\nNota- El mensaje debe tener maximo 15 caracteres (Incluyendo espacios en blanco)\n\n");
					fgets(validar_texto, 21, stdin);
					fflush(stdin);
					longitud=strlen(validar_texto);
					QuitarNuevaLinea(validar_texto, longitud);
					texto_valido=ValidarTexto(validar_texto, longitud-1);
					
					if(longitud>16 && validar_texto[15]!='\n'){
						textcolor(RED); printf("\n\n[!] ");
						textcolor(WHITE);
						printf("Ingrese maximo hasta 15 caracteres, incluyendo espacios en blanco.\n\n");
					}
					
					system("pause");
					system("cls");
					
				}while(texto_valido==1 || (longitud>16 && validar_texto[15]!='\n'));
				
				Encriptar(validar_texto, longitud);
				
				textcolor(GREEN); printf("\n\n[_/] ");
				textcolor(WHITE); printf("El texto ha sido encriptado exitosamente, resultado: ");
				printf("\n\n\t");
				
				if(longitud-1<4){
					ImprimirVector(v2, 3);
					
					for(i=0; i<3; i++){
						criptograma[i]=v2[i];
					}
					longitud_criptograma=3;
				}
				else if(longitud-1>3 && longitud-1<7){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3);
					
					for(i=0; i<3; i++){
						criptograma[i]=v2[i];
					}
					j=0;
					for(i=3; i<6; i++){
						criptograma[i]=v3[j];
						j++;
					}
					longitud_criptograma=6;
				}
				else if(longitud-1>6 && longitud-1<10){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
					
					for(i=0; i<3; i++){
						criptograma[i]=v2[i];
					}
					j=0;
					for(i=3; i<6; i++){
						criptograma[i]=v3[j];
						j++;
					}
					j=0;
					for(i=6; i<9; i++){
						criptograma[i]=v4[j];
						j++;
					}
					longitud_criptograma=9;
				}
				else if(longitud-1>9 &&longitud-1<13){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
					ImprimirVector(v5, 3);
					
					for(i=0; i<3; i++){
						criptograma[i]=v2[i];
					}
					j=0;
					for(i=3; i<6; i++){
						criptograma[i]=v3[j];
						j++;
					}
					j=0;
					for(i=6; i<9; i++){
						criptograma[i]=v4[j];
						j++;
					}
					j=0;
					for(i=9; i<12; i++){
						criptograma[i]=v5[j];
						j++;
					}
					longitud_criptograma=12;
				}
				else if(longitud-1>12 && longitud<17){
					ImprimirVector(v2, 3); ImprimirVector(v3, 3); ImprimirVector(v4, 3);
					ImprimirVector(v5, 3); ImprimirVector(v6, 3);
					
					for(i=0; i<3; i++){
						criptograma[i]=v2[i];
					}
					j=0;
					for(i=3; i<6; i++){
						criptograma[i]=v3[j];
						j++;
					}
					j=0;
					for(i=6; i<9; i++){
						criptograma[i]=v4[j];
						j++;
					}
					j=0;
					for(i=9; i<12; i++){
						criptograma[i]=v5[j];
						j++;
					}
					j=0;
					for(i=12; i<15; i++){
						criptograma[i]=v6[j];
						j++;
					}
					longitud_criptograma=15;
				}
				
				ReiniciarVector(vector1, vector2, vector3, vector4, vector5, 3);
				ReiniciarVector(v2, v3, v4, v5, v6, 3);
				
				determinante=Determinante(m, 3);
				
				printf("\n\nDesencriptando...");
				Sleep(3000);
				
				Desencriptar(criptograma, longitud_criptograma, m, 3, determinante);
			
				textcolor(GREEN); printf("\n\n[_/] ");
				textcolor(WHITE); printf("El texto ha sido desencriptado exitosamente, resultado: ");
				printf("\n\n\t");
				
				if(longitud_criptograma==3){
					ImprimirChar(t1, 4);
				}
				else if(longitud_criptograma==6){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4);
				}
				else if(longitud_criptograma==9){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
				}
				else if(longitud_criptograma==12){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
					ImprimirChar(t4, 4);
				}
				else if(longitud_criptograma==15){
					ImprimirChar(t1, 4); ImprimirChar(t2, 4); ImprimirChar(t3, 4);
					ImprimirChar(t4, 4); ImprimirChar(t5, 4);
				}
				
				ReiniciarVector(vector1, vector2, vector3, vector4, vector5, 3);
				ReiniciarVector(v2, v3, v4, v5, v6, 3);
				memset(t1, '\0', 4); memset(t2, '\0', 4); memset(t3, '\0', 4);
				memset(t4, '\0', 4); memset(t5, '\0', 4); memset(validar_texto, '\0', 21);
				for(i=0; i<15; i++){
					criptograma[i]=0;
					letras[i]=0;
				}
			
				break;
				
			case 4:
			
				textcolor(BLUE); printf("\n\nGracias "); textcolor(GREEN); printf("por ");
				textcolor(RED); printf("usar "); textcolor(YELLOW); printf("el ");
				textcolor(MAGENTA); printf("programa"); textcolor(CYAN); printf("!\n\n");
				textcolor(WHITE);
				system("pause");
				exit(0);
				
				break;		
		}
		
		printf("\n\n");
		system("pause");
		system("cls");
		
		opcion=Menu();
	
	}while(opcion==1 || opcion==2 || opcion==3 || opcion==4);
	
	return 0;
}

void Inversa(int determinante, int matriz[][3], int filas){
	
	float adj[3][3], trasp[3][3];
	int i, j;
	
	//Adjunta de la matriz con la que se encripto el texto.
	adj[0][0]=(matriz[1][1]*matriz[2][2])-(matriz[2][1]*matriz[1][2]);
	adj[0][1]=((matriz[1][0]*matriz[2][2])-(matriz[2][0]*matriz[1][2]))*-1;
	adj[0][2]=(matriz[1][0]*matriz[2][1])-(matriz[2][0]*matriz[1][1]);
	adj[1][0]=((matriz[0][1]*matriz[2][2])-(matriz[2][1]*matriz[0][2]))*-1;
	adj[1][1]=(matriz[0][0]*matriz[2][2])-(matriz[2][0]*matriz[0][2]);
	adj[1][2]=((matriz[0][0]*matriz[2][1])-(matriz[2][0]*matriz[0][1]))*-1;
	adj[2][0]=(matriz[0][1]*matriz[1][2])-(matriz[1][1]*matriz[0][2]);
	adj[2][1]=((matriz[0][0]*matriz[1][2])-(matriz[1][0]*matriz[0][2]))*-1;
	adj[2][2]=(matriz[0][0]*matriz[1][1])-(matriz[1][0]*matriz[0][1]);
	
	//Se transpone la matriz.
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			trasp[j][i]=adj[i][j];
		}
	}
	
	//Se calcula la inversa.
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			inversa[i][j]=trasp[i][j]/determinante;
		}
	}
	
}

int Determinante(int m[][3], int filas){
	
	int det;
	
	det=(m[0][0]*m[1][1]*m[2][2])+(m[0][1]*m[1][2]*m[2][0])+(m[1][0]*m[2][1]*m[0][2])-
	(m[0][0]*m[1][2]*m[2][1])-(m[2][0]*m[1][1]*m[0][2])-(m[1][0]*m[0][1]*m[2][2]);
	
	return det;
	
}

void ReiniciarVector(int vector1[], int vector2[], int vector3[], int vector4[], int vector5[], int longitud){
	
	int i;
	
	for(i=0; i<longitud; i++){
		vector1[i]=0;
		vector2[i]=0;
		vector3[i]=0;
		vector4[i]=0;
		vector5[i]=0;
	}
		
}

void Multiplicacion(int vector[], int longitud, float matriz[][3], int filas){
	
	int i, j;
	
	for(i=0; i<3; i++){
		v1[i]=0;
	}
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			
			v1[i]+=vector[j]*matriz[j][i];
			
		}
	}
		
}

void ImprimirVector(int vector[], int longitud){
	
	int i;
	
	for(i=0; i<longitud; i++){
		printf("%d ", vector[i]);
	}
}

void ImprimirChar(char texto[], int longitud){
	
	int i;
	
	for(i=0; i<longitud; i++){
		printf("%c", texto[i]);
	}
}

void ConvertirTexto(char texto[], int longitud){
	
	int i;
	
	for(i=0; i<longitud-1; i++){
		if(isspace(texto[i])){
			letras[i]=0;
		}
		if(texto[i]=='A' || texto[i]=='a'){
			letras[i]=1;
		}
		if(texto[i]=='B' || texto[i]=='b'){
			letras[i]=2;
		}
		if(texto[i]=='C' || texto[i]=='c'){
			letras[i]=3;
		}
		if(texto[i]=='D' || texto[i]=='d'){
			letras[i]=4;
		}
		if(texto[i]=='E' || texto[i]=='e'){
			letras[i]=5;
		}
		if(texto[i]=='F' || texto[i]=='f'){
			letras[i]=6;
		}
		if(texto[i]=='G' || texto[i]=='g'){
			letras[i]=7;
		}
		if(texto[i]=='H' || texto[i]=='h'){
			letras[i]=8;
		}
		if(texto[i]=='I' || texto[i]=='i'){
			letras[i]=9;
		}
		if(texto[i]=='J' || texto[i]=='j'){
			letras[i]=10;
		}
		if(texto[i]=='K' || texto[i]=='k'){
			letras[i]=11;
		}
		if(texto[i]=='L' || texto[i]=='l'){
			letras[i]=12;
		}
		if(texto[i]=='M' || texto[i]=='m'){
			letras[i]=13;
		}
		if(texto[i]=='N' || texto[i]=='n'){
			letras[i]=14;
		}
		if(texto[i]=='O' || texto[i]=='o'){
			letras[i]=15;
		}
		if(texto[i]=='P' || texto[i]=='p'){
			letras[i]=16;
		}
		if(texto[i]=='Q' || texto[i]=='q'){
			letras[i]=17;
		}
		if(texto[i]=='R' || texto[i]=='r'){
			letras[i]=18;
		}
		if(texto[i]=='S' || texto[i]=='s'){
			letras[i]=19;
		}
		if(texto[i]=='T' || texto[i]=='t'){
			letras[i]=20;
		}
		if(texto[i]=='U' || texto[i]=='u'){
			letras[i]=21;
		}
		if(texto[i]=='V' || texto[i]=='v'){
			letras[i]=22;
		}
		if(texto[i]=='W' || texto[i]=='W'){
			letras[i]=23;
		}
		if(texto[i]=='X' || texto[i]=='x'){
			letras[i]=24;
		}
		if(texto[i]=='Y' || texto[i]=='y'){
			letras[i]=25;
		}
		if(texto[i]=='Z' || texto[i]=='z'){
			letras[i]=26;
		}
	}
	
}

void ConvertirNumero(int vector[], int longitud, char v[], int longi){
	
	int i;
	
	for(i=0; i<longitud; i++){
		if(vector[i]==0){
			v[i]=' ';
		}
		if(vector[i]==1){
			v[i]='a';
		}
		if(vector[i]==2){
			v[i]='b';
		}
		if(vector[i]==3){
			v[i]='c';
		}
		if(vector[i]==4){
			v[i]='d';
		}
		if(vector[i]==5){
			v[i]='e';
		}
		if(vector[i]==6){
			v[i]='f';
		}
		if(vector[i]==7){
			v[i]='g';
		}
		if(vector[i]==8){
			v[i]='h';
		}
		if(vector[i]==9){
			v[i]='i';
		}
		if(vector[i]==10){
			v[i]='j';
		}
		if(vector[i]==11){
			v[i]='k';
		}
		if(vector[i]==12){
			v[i]='l';
		}
		if(vector[i]==13){
			v[i]='m';
		}
		if(vector[i]==14){
			v[i]='n';
		}
		if(vector[i]==15){
			v[i]='o';
		}
		if(vector[i]==16){
			v[i]='p';
		}
		if(vector[i]==17){
			v[i]='q';
		}
		if(vector[i]==18){
			v[i]='r';
		}
		if(vector[i]==19){
			v[i]='s';
		}
		if(vector[i]==20){
			v[i]='t';
		}
		if(vector[i]==21){
			v[i]='u';
		}
		if(vector[i]==22){
			v[i]='v';
		}
		if(vector[i]==23){
			v[i]='w';
		}
		if(vector[i]==24){
			v[i]='x';
		}
		if(vector[i]==25){
			v[i]='y';
		}
		if(vector[i]==26){
			v[i]='z';
		}
	}
}

void Desencriptar(int criptograma[], int longitud, int m[][3], int filas, int determinante){
	
	int i, j;
	
	if(longitud==3){
		for(i=0; i<3; i++){
			vector1[i]=criptograma[i];
		}
		
		Inversa(determinante, m, 3);
		Multiplicacion(vector1, 3, inversa, 3);
		ConvertirNumero(v1, 3, t1, 4);
	}
	else if(longitud==6){
		for(i=0; i<3; i++){
			vector1[i]=criptograma[i];
		}
		
		Inversa(determinante, m, 3);
		Multiplicacion(vector1, 3, inversa, 3);
		ConvertirNumero(v1, 3, t1, 4);
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, inversa, 3);
		ConvertirNumero(v1, 3, t2, 4);
	}
	else if(longitud==9){
		for(i=0; i<3; i++){
			vector1[i]=criptograma[i];
		}
		
		Inversa(determinante, m, 3);
		Multiplicacion(vector1, 3, inversa, 3);
		ConvertirNumero(v1, 3, t1, 4);
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, inversa, 3);
		ConvertirNumero(v1, 3, t2, 4);
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, inversa, 3);
		ConvertirNumero(v1, 3, t3, 4);
	}
	else if(longitud==12){
		for(i=0; i<3; i++){
			vector1[i]=criptograma[i];
		}
		
		Inversa(determinante, m, 3);
		Multiplicacion(vector1, 3, inversa, 3);
		ConvertirNumero(v1, 3, t1, 4);
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, inversa, 3);
		ConvertirNumero(v1, 3, t2, 4);
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, inversa, 3);
		ConvertirNumero(v1, 3, t3, 4);
		
		j=0;
		for(i=9; i<12; i++){
			vector4[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector4, 3, inversa, 3);
		ConvertirNumero(v1, 3, t4, 4);
	}
	else if(longitud==15){
		for(i=0; i<3; i++){
			vector1[i]=criptograma[i];
		}
		
		Inversa(determinante, m, 3);
		Multiplicacion(vector1, 3, inversa, 3);
		ConvertirNumero(v1, 3, t1, 4);
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, inversa, 3);
		ConvertirNumero(v1, 3, t2, 4);
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, inversa, 3);
		ConvertirNumero(v1, 3, t3, 4);
		
		j=0;
		for(i=9; i<12; i++){
			vector4[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector4, 3, inversa, 3);
		ConvertirNumero(v1, 3, t4, 4);
		
		j=0;
		for(i=12; i<15; i++){
			vector5[j]=criptograma[i];
			j++;
		}
		
		Multiplicacion(vector5, 3, inversa, 3);
		ConvertirNumero(v1, 3, t5, 4);
	}
	
}

void Encriptar(char texto[], int longitud){
	
	//cambio de matriz int por float, ahora es global
	//float matriz[3][3]={{1, -2, 2}, {-1, 1, 3}, {1, -1, -4}};
	int i, j;
	
	ConvertirTexto(texto, longitud);
	
	if(longitud-1<4){
		for(i=0; i<longitud-1; i++){
			vector1[i]=letras[i];
		}
		
		Multiplicacion(vector1, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v2[i]=v1[i];
		}

	}
	else if(longitud-1>3 && longitud-1<7){
		for(i=0; i<3; i++){
			vector1[i]=letras[i];
		}
		
		Multiplicacion(vector1, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v2[i]=v1[i];
		}
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v3[i]=v1[i];
		}
	}
	else if(longitud-1>6 &&longitud-1<10){
		for(i=0; i<3; i++){
			vector1[i]=letras[i];
		}
		
		Multiplicacion(vector1, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v2[i]=v1[i];
		}
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v3[i]=v1[i];
		}
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v4[i]=v1[i];
		}
	}
	else if(longitud-1>9 &&longitud-1<13){
		for(i=0; i<3; i++){
			vector1[i]=letras[i];
		}
		
		Multiplicacion(vector1, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v2[i]=v1[i];
		}
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v3[i]=v1[i];
		}
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v4[i]=v1[i];
		}
		
		j=0;
		for(i=9; i<12; i++){
			vector4[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector4, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v5[i]=v1[i];
		}
	}
	else if(longitud-1>12 && longitud<17){
		for(i=0; i<3; i++){
			vector1[i]=letras[i];
		}
		
		Multiplicacion(vector1, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v2[i]=v1[i];
		}
		
		j=0;
		for(i=3; i<6; i++){
			vector2[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector2, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v3[i]=v1[i];
		}
		
		j=0;
		for(i=6; i<9; i++){
			vector3[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector3, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v4[i]=v1[i];
		}
		
		j=0;
		for(i=9; i<12; i++){
			vector4[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector4, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v5[i]=v1[i];
		}
		
		j=0;
		for(i=12; i<15; i++){
			vector5[j]=letras[i];
			j++;
		}
		
		Multiplicacion(vector5, 3, matriz, 3);
		
		for(i=0; i<3; i++){
			v6[i]=v1[i];
		}
	}
		
}

int Menu(){
	
	int opcion, longitud, n_valido;
	char cadena[5];
	
	do{
	
		printf("\tBienvenido al programa para encriptar y desencriptar mensajes.\n");
		printf("\nIngrese la opcion numerica que desea realizar: ");
		printf("\n1.-Encriptar un mensaje.");
		printf("\n2.-Desencriptar un mensaje.");
		printf("\n3.-Encriptar y luego desencriptar un mismo mensaje.");
		printf("\n4.-Salir.\n\n");
		fgets(cadena, 8, stdin);
		fflush(stdin);
		longitud=strlen(cadena);
		QuitarNuevaLinea(cadena, longitud);
		n_valido=ValidarNumero(cadena, longitud-1);
			
		if(n_valido==0){
			opcion=atoi(cadena);
		}
		if(opcion != 1 && opcion != 2 && opcion!=3 && opcion!=4){
			textcolor(RED); printf("\n\n[!]");
			textcolor(WHITE);
			printf(" Error, por favor ingrese una opcion valida.\n");
		}
		printf("\n");
		system("pause");
		system("cls");
		
	}while(n_valido==1 || (opcion !=1 && opcion!=2 && opcion!=3 && opcion!=4));
	
	return opcion;
}

int ValidarTexto(char str[], int longitud){
	
	int i;
	for(i=0; i<longitud-1; ++i){
		if(!(isalpha(str[i]) || isspace(str[i]) || ispunct(str[i]))){
			
			textcolor(RED); printf("\n\n[!] ");
			textcolor(WHITE);
			printf("Por favor, ingrese solo letras o simbolos.\n");
			return 1;
		}
	}
	return 0;
}

int ValidarNegativo(char str[], int longitud){
	
	int i;
	for(i=0; i<longitud; ++i){
		if(str[0]=='-' && i == 0){
			i++;	
		}
		if(str[i]=='-' && i>0){
			printf("\nPor favor, ingrese solo numeros enteros validos.\n");
			return 1;
		}
		if(!(isdigit(str[i])) && str[0]=='-'){
			printf("\nPor favor, ingrese solo numeros enteros validos.\n");
			return 1;
		}
		else if(!(isdigit(str[i])) && str[0]!='-'){
				printf("\nPor favor, ingrese solo numeros enteros.\n");
				return 1;
			
		}
	}
	
	return 0; 
}

int ValidarNumero(char str[], int longitud){
	
	int i;
	for(i=0; i<longitud; ++i){
		if(!(isdigit(str[i]))){
			
			printf("\nPor favor, ingrese solo numeros positivos enteros.\n");
			return 1;
		}
	}
	return 0;
}

void QuitarNuevaLinea(char cadena[], int longitud){
	if(longitud>1 && cadena[longitud-1]=='\n'){
		cadena[longitud-1]='\0';
	}
}
