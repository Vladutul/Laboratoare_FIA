#include <stdio.h>
#include <conio.h>
#define modul(x) ( ((x)>=0) ? (x) : (-1*(x)) )
#define max(x,val_reale) ( ((x)>(val_reale)) ? (x) : (val_reale) )
#define min(x,val_reale) ( ((x)<(val_reale)) ? (x) : (val_reale) )
#define nr_esan 101

float reuniune[nr_esan], I[nr_esan]; //xR[nr_esan], xI[nr_esan]
float limita_inferioara=0, limita_superioara=100;

float xA[]={20, 30, 80};
float uA[]={ 0,  1,  0};
int nA=3;

float xB[]={10, 40, 60};
float uB[]={ 0,  1,  0};
int nB=3;

/*float xB[]={5,  7, 13, 22, 32, 40};
float uB[]={0,0.2,0.2,0.7,0.7,  0};
int nB=6; */

//set vechi de date pentru eliminare puncte necoliniare
/*
float val_reale[] ={0,  3, 13, 17, 23, 25, 35,40};
float grad_apart[]={0,0.3,0.3,0.7,0.7,0.5,0.5, 0};
int nr_puncte=8;
*/

//set nou de date pentru eliminare puncte necoliniare
float val_reale[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
float grad_apart[] = {0, 0.2, 0.4, 0.6, 0.8, 1, 0.8, 0.6, 0.4, 0.2, 0};
int nr_puncte = 11;


float val_reale_nou[nr_esan];
float grad_apart_nou[nr_esan];
int nr_puncte_nou;

float calcul_distanta_dintre_puncte(void);
int elimin_puncte_necoliniare(float*, float*, int, float*, float*);
void calcul_intersectie(float*, float*,int, float*, float*,int);
void calcul_reuniune(float*, float*,int, float*, float*,int);
float calcul_grad_apartenenta(float, float*, float*,int);
float calcul_centru_greutate_fuzzy(float*, float*,int);
float calcul_centru_greutate_metoda_trapez(void);

int main(void)
{
/*	float coord_x;
	printf("coord_x="); scanf("%f",&coord_x);
	printf("uA=%.2f\n",calcul_grad_apartenenta(coord_x,xA,uA,nA));
	printf("uB=%.2f",calcul_grad_apartenenta(coord_x,xB,uB,nB));
*/
	printf("\n calcul_centru_greutate_fuzzy = %f \n", calcul_centru_greutate_fuzzy(val_reale, grad_apart, nr_puncte));
	printf("\n nr_puncte_vechi = %d \n", nr_puncte);
	int nr_puncte_nou = elimin_puncte_necoliniare(val_reale, grad_apart, nr_puncte, val_reale_nou, grad_apart_nou);
	printf("\n nr_puncte_nou = %d \n", nr_puncte_nou);
	printf("\n calcul_centru_greutate_fuzzy dupa eliminare = %f \n", calcul_centru_greutate_fuzzy(val_reale_nou, grad_apart_nou, nr_puncte_nou));
//	calcul_intersectie(xA,uA,nA,xB,uB,nB);
	calcul_reuniune(xA,uA,nA,xB,uB,nB);
	printf("\n calcul_centru_greutate_metoda_trapez = %f \n", calcul_centru_greutate_metoda_trapez());
	
	//eliminare_pcte_col(); + calcul_centru_greutate_fuzzy(xR,reuniune,nR);
	printf("Press ENTER to exit...");
	getchar();
}

float calcul_grad_apartenenta(float coord_x, float x[], float u[], int n)
{
	if (coord_x<x[0]) return u[0];
	if (coord_x>x[n-1]) return u[n-1];

	for(int index=0; index<n-1; index++)
		if (coord_x>=x[index] && coord_x<=x[index+1]) //daca coord_x este in intervalul curent
		{	if(u[index]<u[index+1]) //panta crescatoare
				return (coord_x-x[index])/(x[index+1]-x[index])*(u[index+1]-u[index])+u[index];
			else if(u[index]>u[index+1]) //panta descrescatoare
					return (x[index+1]-coord_x)/(x[index+1]-x[index])*(u[index]-u[index+1])+u[index+1];
				else //platou
					return u[index];
		}
}

float calcul_centru_greutate_fuzzy(float val_reale[], float grad_apart[], int nr_puncte)
{
	float suma1, suma2, aria, cg, A2, cg2;
	suma1=0; suma2=0;
	
	for(int index=0; index<nr_puncte-1; index++)
	{	
		if (grad_apart[index] == 0 || grad_apart[index+1] == 0) // triunghi
		{	
            aria= (val_reale[index+1] - val_reale[index]) * modul(grad_apart[index+1] - grad_apart[index]) / 2; 
			cg = (val_reale[index]+val_reale[index+1]+ ((grad_apart[index+1]>grad_apart[index])? val_reale[index+1] : val_reale[index]))/3;
		}


        /*		
        if (grad_apart[index]==0) //triunghi panta crescatoare
		{	aria = (val_reale[index+1]-val_reale[index])*grad_apart[index+1]/2; cg = (val_reale[index]+2*val_reale[index+1])/3; }
		if (grad_apart[index+1]==0) //triunghi panta descrescatoare
		{	aria = (val_reale[index+1]-val_reale[index])*grad_apart[index]/2; cg = (2*val_reale[index]+val_reale[index+1])/3; }
        */

		if (grad_apart[index] == grad_apart[index+1]) // dreptunghi
		{	
			aria = (val_reale[index+1]-val_reale[index])*grad_apart[index];
			cg = (val_reale[index]+val_reale[index+1])/2;  
		}

		if (grad_apart[index]!=0 && grad_apart[index+1]!=0 && grad_apart[index]!=grad_apart[index+1]) //trapez
		{	
			aria = (val_reale[index+1]-val_reale[index]) * modul(grad_apart[index+1]-grad_apart[index]) /2; 
			cg = (val_reale[index]+val_reale[index+1]+ ((grad_apart[index+1]>grad_apart[index])? val_reale[index+1] : val_reale[index]) )/3;
			A2 = (val_reale[index+1]-val_reale[index])*grad_apart[index]; 
			cg2 = (val_reale[index]+val_reale[index+1])/2;
			//printf("A_tri:%f, cg_tri:%f, A_dr:%f cg_dr:%f \n",aria,cg,A2,cg2);
			cg = (cg*aria + cg2*A2)/(aria+A2); 
			aria = aria+A2; 
		}	

		suma1 = suma1+aria*cg;
		suma2 = suma2+aria;
		//printf("aria%d = %f, cg%d = %f \n",index,aria,index,cg);
	}
	return suma1/suma2;
}

void calcul_intersectie(float xA[], float uA[], int nA, float xB[], float uB[], int nB)
{
	int index;
	float pas, coord_x;
	pas = calcul_distanta_dintre_puncte();

	for (index=0,coord_x=limita_inferioara; index<nr_esan; index++, coord_x+=pas)
	{	I[index] = min( calcul_grad_apartenenta(coord_x,xA,uA,nA), calcul_grad_apartenenta(coord_x,xB,uB,nB));
		//printf("(%.1f,%.2f), ",coord_x,I[index]);
	}
	//printf("\n");
}

void calcul_reuniune(float xA[], float uA[], int nA, float xB[], float uB[], int nB)
{
	int index;
	float pas, coord_x;
	pas = calcul_distanta_dintre_puncte();
	
	for (index=0,coord_x=limita_inferioara; index<nr_esan; index++, coord_x+=pas)
		reuniune[index] = max( calcul_grad_apartenenta(coord_x,xA,uA,nA), calcul_grad_apartenenta(coord_x,xB,uB,nB));
}

float calcul_centru_greutate_metoda_trapez(void)
{	int index;
	float pas, coord_x, suma_produs1 = 0, suma_produs2 = 0; // pas // distanta dintre doua puncte consecutive de esantionare

	pas = calcul_distanta_dintre_puncte();

	for (index=0, coord_x = limita_inferioara; index < nr_esan - 1; index++, coord_x += pas)
	{	suma_produs1 += (reuniune[index] + reuniune[index+1])/2 * (coord_x + pas/2); //aproximare arii prin met.trapezului
		suma_produs2 += (reuniune[index] + reuniune[index+1])/2;
	}
	return suma_produs1 / suma_produs2;
}

int elimin_puncte_necoliniare(float x_vechi[], float y_vechi[], int n, float x_nou[], float y_nou[]) {
    if (n < 3) {
        for (int index = 0; index < n; index++) {
            x_nou[index] = x_vechi[index];
            y_nou[index] = y_vechi[index];
        }
        return n;
    }

    int nr_puncte = 0;  // numărul de puncte în noul set
    x_nou[nr_puncte] = x_vechi[0];
    y_nou[nr_puncte] = y_vechi[0];
    nr_puncte++;

    for (int index = 1; index < n-1; index++) {
        float dx1 = x_vechi[index] - x_vechi[index-1];
        float dy1 = y_vechi[index] - y_vechi[index-1];

        float dx2 = x_vechi[index+1] - x_vechi[index];
        float dy2 = y_vechi[index+1] - y_vechi[index];

        if (dy1*dx2 != dy2*dx1) { // punctul nu e coliniar
            x_nou[nr_puncte] = x_vechi[index];
            y_nou[nr_puncte] = y_vechi[index];
            nr_puncte++;
        }
    }

    x_nou[nr_puncte] = x_vechi[n-1];
    y_nou[nr_puncte] = y_vechi[n-1];
    nr_puncte++;

    return nr_puncte;  // returnează numărul de puncte rămase
}


float calcul_distanta_dintre_puncte(void)
{
	float pas;

	pas = (limita_superioara - limita_inferioara) / (nr_esan - 1);
	
	return pas;
}
