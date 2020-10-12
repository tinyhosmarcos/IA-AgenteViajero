#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<time.h> 
#include "conio.h"
#include <windows.h>
using namespace std;  
void gotoxy(int x,int y){  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}  

float normal(){
	int hora = time(NULL);  
	srand(hora);  
	int i,j;
	float x=0,ft=0,n=0;
	ft=0;
	for(i=0;i<12;i++){
		x=(rand()% (int)(100) );
		ft=ft+(int)(x/100);
	}
	n=ft-6;
	return n;
}

int ale(int min, int max){
	int a=0;
	a=(rand()% (int)(max-min)+min );
	return a;
}

float pide(){
	float a=0;
	do{/// porcentaje de mutacion
		gotoxy(0,9);
		cout<<"Ingrese datos: "<<endl;
		cin>>a;
	}while(a<0 || a>1);
	return a;
}


int menu(){
	int a=2;
	return a;
}

int main(){
	
	float a,b,acum=0,r,m,infx,supx,infy,supy,ft,tempfit=0;
	int hora = time(NULL); 
	int j,i,mu,mug=0,lam,op,muta,v,nfit[300],pos=0,ban=0,cruza=0,ban1=0,temp,temp1,x,y,cop[300],contador=0,inv,aumenta=0,p[300][300],prueba[300][300],pn[300][300],fit[300],costos[300][300],k,glo=0,pf[300][300],fitf[300],min=0,ar[300],max,emp,final;
	srand(hora);  
	FILE *arch;
	FILE *base;
	arch = fopen("Agente_viajero.txt","w+");
	base = fopen("minimo.txt","w+");
	
	for (i=0;i<  300 ;i++){
		for (j=0; j < 300  ;j++){
			p[i][j]=0;
			pf[i][j]=0;
			pn[i][j]=0;
			prueba[i][j]=0;
		} 
		fit[i]=0;
		fitf[i]=0;
		cop[i]=0;	      
		ar[i]=0;
	}
	cout<<"------------------------Agente viajero------------------------"<<endl;
	
	
	op=menu();gotoxy(0,4); 
	do{
		cout<<"Cantidad de ciudades:"<<endl;
		cin>>lam;
	}while(lam<5 );
	
	gotoxy(0,6); 
	
	do{
		
		cout<<"En que ciudad empieza:"<<endl;
		cin>>emp;
	}while(emp<1  || emp >lam-1);
	
	cout<<"Porcentaje de la poblacion elegida para generacion: "<<endl;
	m=pide();
	mu=lam;		
	mug=mu;
	cout<<"Cantidad de Ciclos: 30000"<<endl;
	cout<<"===================================="<<endl;
	cout<<"El mejor camino es: "<<endl;
	//Iniciar la poblaci?n P con mu individuos generados 
	ban=0;
	for(i=0;i<mu;i++){//filas
		do{
			for(j=0;j<lam;j++){//filas
				p[i][j]=j;
				ban++;
			}
		}while(ban<3);
		ban=0;
		
	}
	for(i=0;i<600;i++){
		pos=ale(0,lam);	
		inv=ale(1,mu);
		ban=ale(0,lam);
		temp1=p[inv][ban];
		temp=p[inv][pos];
		p[inv][ban]=temp;
		p[inv][pos]=temp1;
	}
	for(i=0;i<mu;i++){//filas
		if( emp!=p[i][0]){			
			for(j=0;j<lam;j++){//filas
				if(p[i][j]==emp ) {
					temp=p[i][j]; 
					ban=p[i][0];
					p[i][j]=ban;
					p[i][0]=temp;
				}//condicon
			}//se busca el valor pa intercambiarlo
		}//ciera condicion
	}//cierra for 
	
	for(i=0;i<mu;i++){//filas revuelvo
		p[i][lam]=p[i][0];//el primer camino llev
	}
	
	//calculo costos
	for(i=0;i<lam;i++){//filas
		for(j=0;j<lam;j++){//filas
			costos[i][j]=ale(2,11);
			//costos[i][j]=1;
		}
	}//cierra for 
	
	//PRUEBA/*
	
	if(op==1){
		ban=ale(1,mug);//escojo individuo
		for(k=0;k<lam;k++){//filas	
			costos[p[ban][k]][p[ban][k+1]]=1 ;//ahago el cmaino
		}
	}
	final=0;
	for(k=0;k<lam;k++){	
		final+=costos[p[ban][k]][p[ban][k+1]];
	}
	
	if(op==1){
		for(k=0;k<=lam;k++){
			printf("%d  ", p[ban][k] );
			fprintf(arch,"%d ",p[ban][k]);	
		}
		fprintf(arch,"\n ");	
	}
	printf("\n ");
	inv=ban;
	for(i=0;i<1;i++){
		pos=ale(1,lam);	
		k=ale(1,lam);
		temp1=p[inv][k];
		temp=p[inv][pos];
		p[inv][k]=temp;
		p[inv][pos]=temp1;
	}
	
	j=0;
	for(k=0;k<lam;k++){
		costos[k][j]=0;	
		j++;
	}
	v=0;
	do{	
		if(v==0  )  {
			getchar();
		}
		muta=rint(m*mu);
		
		for(i=0;i<muta;i++){
			ban=ale(1,lam);	
			temp1=p[i][ban];
			pos=ale(1,lam);	
			temp=p[i][pos];
			for(x=0;x<=lam;x++){  
				p[mu+i][x]=p[i][x];
			}
			p[mu+i][ban]=temp;
			p[mu+i][pos]=temp1;
			ban=ale(1,lam);
			temp1=p[mu+i][ban];
			pos=ale(1,lam);
				temp=p[mu+i][pos];
			p[mu+i][ban]=temp;
			p[mu+i][pos]=temp1;
		}
		mu+=muta;
		for(i=0;i<100;i++){
			fit[i]=0;
			cop[i]=0;	
		}
		for(i=0;i<mu;i++){
			for(j=0;j<lam;j++){    
				fit[i]+=   costos[p[i][j]][p[i][j+1]];
			}
		}
		for (i=0;i<mu;i++){
			cop[i]=i;
		} 
		for (i=1;i<  mu ;i++){
			for (j=0; j < mu  ;j++){
				if (fit[j] > fit[j+1]){
					temp=fit[j];
					fit[j]=fit[j+1];            
					fit[j+1]=temp;
					ban=cop[j];
					cop[j]=cop[j+1];
					cop[j+1]=ban;
				}
			}
		}
		
		fprintf(base,"%d\n",fit[0]   );
		mu-=(cruza+muta);
		ft=0;
		for(i=0;i<mu;i++){//filas	
			for(j=0;j<=lam;j++){
				pn[i][j]=p[cop[i]][j];//copiax	
			}
			ft+=fit[i];
		}//cierra for 
		ft=ft/mu;
		for(i=0;i<mu;i++){//filas
			for(j=0;j<=lam;j++){//filas	
				p[i][j]=pn[i][j];
			}
		}
		ban=fit[0];
		
		for(i=0;i<100;i++){//filas
			for(j=0;j<=lam;j++){//filas
				pn[i][j]=0;
				fit[i]=0;
				cop[i]=0;
			}
		}//cierra for 
		gotoxy(0,13);
		for(j=0;j<=lam;j++){//filas	
			printf("%d  ",p[0][j]);	
		}
		printf("\n ");
		gotoxy(0,17);  printf("ciclo %d\n ",v);
		v++;
		fprintf(arch,"%.2f\n",ft);	
		if(v==0){
			tempfit=ft;	
			v=1;
		}
		
		if(v%100==0 && ft==tempfit) {
			m+=.6;
			contador++;
		}
		if(v%300==0  && ft<tempfit) {
			tempfit=ft;
			m-=.6;	
		}
		else if(contador==3) {
			break;
		}
	}while(v<30000 );
	
	printf("\n Ponderado Final: =%d \n",ban);
	
	gotoxy(0,20); 
	
	system("pause");
}



