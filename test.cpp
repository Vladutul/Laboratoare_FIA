#include <stdio.h>
#include <conio.h>
#define modul(x) ( ((x)>=0) ? (x) : (-1*(x)) )
#define max(x,y) ( ((x)>(y)) ? (x) : (y) )
#define min(x,y) ( ((x)<(y)) ? (x) : (y) )
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

float val_reale[] ={0,  3, 13, 17, 23, 25, 35,40};
float grad_apart[]={0,0.3,0.3,0.7,0.7,0.5,0.5, 0};
int ny=8;



float calcul_centru_greutate_fuzzy(float val_reale[], float grad_apart[], int ny)
{
	float suma1, suma2, aria, cg, A2, cg2;
	suma1=0; suma2=0;
	
	for(int index=0; index<ny-1; index++)
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
			printf("A_tri:%f, cg_tri:%f, A_dr:%f cg_dr:%f \n",aria,cg,A2,cg2);
			cg = (cg*aria + cg2*A2)/(aria+A2); 
			aria = aria+A2; 
		}	

		suma1 = suma1+aria*cg;
		suma2 = suma2+aria;
		printf("aria%d = %f, cg%d = %f \n",index,aria,index,cg);
	}
	return suma1/suma2;
}



int main(void)
{
   printf("calcul_centru_greutate_fuzzy = %f \n", calcul_centru_greutate_fuzzy(val_reale, grad_apart, ny));
   getchar();
}
