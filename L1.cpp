#include <stdio.h>
#include <conio.h>
#define modul(x) ( ((x)>=0) ? (x) : (-1*(x)) )
#define max(x,y) ( ((x)>(y)) ? (x) : (y) )
#define min(x,y) ( ((x)<(y)) ? (x) : (y) )
#define N 101

float R[N], I[N]; //xR[N], xI[N]
float inf_x=0, sup_x=100;

float xA[]={20, 30, 80};
float uA[]={ 0,  1,  0};
int nA=3;

float xB[]={10, 40, 60};
float uB[]={ 0,  1,  0};
int nB=3;

/*float xB[]={5,  7, 13, 22, 32, 40};
float uB[]={0,0.2,0.2,0.7,0.7,  0};
int nB=6; */

float y[] ={0,  3, 13, 17, 23, 25, 35,40};
float uy[]={0,0.3,0.3,0.7,0.7,0.5,0.5, 0};
int ny=8;

void intersectie(float*, float*,int, float*, float*,int);
void reuniune(float*, float*,int, float*, float*,int);
float grad_apart(float, float*, float*,int);
float cog(float*, float*,int);
float cog2(void);

int main(void)
{
/*	float xc;
	printf("xc="); scanf("%f",&xc);
	printf("uA=%.2f\n",grad_apart(xc,xA,uA,nA));
	printf("uB=%.2f",grad_apart(xc,xB,uB,nB));
*/
	printf("cog = %f \n", cog(y, uy, ny));
//	intersectie(xA,uA,nA,xB,uB,nB);
	reuniune(xA,uA,nA,xB,uB,nB);
	printf("cog2 = %f \n", cog2());
	
	//eliminare_pcte_col(); + cog(xR,R,nR);
	
	getch();
}
float grad_apart(float xc, float x[], float u[], int n)
{
	if (xc<x[0]) return u[0];
	if (xc>x[n-1]) return u[n-1];
	for(int i=0; i<n-1; i++)
		if (xc>=x[i] && xc<=x[i+1]) //daca xc este in intervalul curent
		{	if(u[i]<u[i+1]) //panta crescatoare
				return (xc-x[i])/(x[i+1]-x[i])*(u[i+1]-u[i])+u[i];
			else if(u[i]>u[i+1]) //panta descrescatoare
					return (x[i+1]-xc)/(x[i+1]-x[i])*(u[i]-u[i+1])+u[i+1];
				else //platou
					return u[i];
		}
		
}
float cog(float y[], float uy[], int ny)
{
	float S1, S2, A, cg, A2, cg2;
	S1=0; S2=0;
	
	for(int i=0; i<ny-1; i++)
	{	
		if (uy[i]==0 || uy[i+1]==0) // triunghi
		{	A= (y[i+1]-y[i])*modul(uy[i+1]-uy[i])/2; 
			cg = (y[i]+y[i+1]+ ((uy[i+1]>uy[i])? y[i+1] : y[i]) )/3;
		}
/*		if (uy[i]==0) //triunghi panta crescatoare
		{	A = (y[i+1]-y[i])*uy[i+1]/2; cg = (y[i]+2*y[i+1])/3; }
		if (uy[i+1]==0) //triunghi panta descrescatoare
		{	A = (y[i+1]-y[i])*uy[i]/2; cg = (2*y[i]+y[i+1])/3; }
*/
		if (uy[i]==uy[i+1]) // dreptunghi
		{	A = (y[i+1]-y[i])*uy[i]; cg = (y[i]+y[i+1])/2;  }
		if (uy[i]!=0 && uy[i+1]!=0 && uy[i]!=uy[i+1]) //trapez
		{	A = (y[i+1]-y[i]) * modul(uy[i+1]-uy[i]) /2; 
			cg = (y[i]+y[i+1]+ ((uy[i+1]>uy[i])? y[i+1] : y[i]) )/3;
			A2 = (y[i+1]-y[i])*uy[i]; 
			cg2 = (y[i]+y[i+1])/2;
			printf("A_tri:%f, cg_tri:%f, A_dr:%f cg_dr:%f \n",A,cg,A2,cg2);
			cg = (cg*A + cg2*A2)/(A+A2); 
			A = A+A2; 
		}	
		S1 = S1+A*cg;
		S2 = S2+A;
		printf("A%d = %f, cg%d = %f \n",i,A,i,cg);
	}
	return S1/S2;
}

void intersectie(float xA[], float uA[], int nA, float xB[], float uB[], int nB)
{
	int i;
	float delta, xc;
	delta = (sup_x - inf_x)/(N-1);
	
	for (i=0,xc=inf_x; i<N; i++, xc+=delta)
	{	I[i] = min( grad_apart(xc,xA,uA,nA), grad_apart(xc,xB,uB,nB));
		printf("(%.1f,%.2f), ",xc,I[i]);
	}
	printf("\n");
}
void reuniune(float xA[], float uA[], int nA, float xB[], float uB[], int nB)
{
	int i;
	float delta, xc;
	delta = (sup_x - inf_x)/(N-1);
	
	for (i=0,xc=inf_x; i<N; i++, xc+=delta)
		R[i] = max( grad_apart(xc,xA,uA,nA), grad_apart(xc,xB,uB,nB));
}
float cog2(void)
{	int i;
	float delta, xc, S1, S2;
	delta = (sup_x - inf_x)/(N-1);
	S1=0; S2=0;
	
	for (i=0,xc=inf_x; i<N-1; i++, xc+=delta)
	{	S1 += (R[i]+R[i+1])/2 * (xc+delta/2); //aproximare arii prin met.trapezului
		S2 += (R[i]+R[i+1])/2;
	}
	return S1/S2;
}
