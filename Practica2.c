#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512
float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N], V4[N];

void InitData(){
	int i,j;
	srand(8824553);
	for( i = 0; i < N; i++ )
		for( j = 0; j < N; j++ ){
			Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
			if ( (abs(i - j) <= 3) && (i != j))
				MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
			else if ( i == j )
				MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
			else MatDD[i][j] = 0.0;
		}
		for( i = 0; i < N; i++ ){
			V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
			V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
			V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
		}
}

void PrintVect(float vect[N], int from, int numel ){
	int i;
	for (i = from; i < numel + from; i++){
		printf ("%f\n", vect[i]);
	}
	printf("\n");
}

void PrintRow(float mat[N][N],int row, int from, int numel ){
	int i;
	for (i = from; i < numel + from; i++){
		printf ("%f\n", mat[row][i]);
	}
	printf("\n");
}

void MultEscalar(float vect[N], float vectres[N], float alfa){
	int i;
	for (i = 0; i < N; i++){
		vectres[i] = vect[i]*alfa;
	}
}

float Scalar(float vect1[N], float vect2[N]){
	int suma, i;
	for (i = 0; i < N; i++){
		suma += vect1[i]*vect2[i];
	}
	return suma;
}

float Magnitude(float vect[N] ){
	int suma, i;
	for (i = 0; i < N; i++){
		suma += vect[i]*vect[i];
	}
	return suma;
}

int Ortogonal(float vect1[N], float vect2[N]){
	if (Scalar(vect1, vect2) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

void Projection( float vect1[N], float vect2[N], float vectres[N] ){
	float uv, v, div;
	uv = Scalar(vect1, vect2);
	v = Magnitude(vect2);
	div = uv / v;
	MultEscalar(vect2, vectres, div);
}
float Infininorm( float M[N][N] ){
	float max= 0.0,sum;
	int i,j;
	for( i = 0;i < N;i++){
		sum=0.0;
		for(j=0;j<N-1;j++){
			sum = fabs(M[i][j]);
		}	
	
		if (sum>max){
			max=sum;
		}
	}
	return max;

}
float Onenorm( float M[N][N] ){
	float max= 0.0,sum;
	int i,j;
	for( j = 0;j < N;j++){
		sum=0.0;
		for(i=0;i<N-1;i++){
			sum = fabs(M[i][j]);
		}	
	
		if (sum>max){
			max=sum;
		}
	}
	return max;

}
float NormFrobenius( float M[N][N] ){
	float sum,mul,arrel;
	int i,j;
	for( j = 0;j < N;j++){
		for(i=0;i<N-1;i++){
			sum += (M[i][j]);
	
		}
	mul=sum*sum;
	arrel =sqrt(mul);
	return arrel;	
		
}
}
int main(){
	InitData();
	// A.
	printf("V1 de 0 a 9:\n");
	PrintVect(V1, 0, 9);
	printf("V2 de 0 a 9:\n");
	PrintVect(V2, 0, 9);
	printf("V3 de 0 a 9:\n");
	PrintVect(V3, 0, 9);
	
	printf("V1 de 256 a 265:\n");
	PrintVect(V1, 256, 9);
	printf("V2 de 256 a 265:\n");
	PrintVect(V2, 256, 9);
	printf("V3 de 256 a 265:\n");
	PrintVect(V3, 256, 9);
	
	printf("Mat fila 0 de 0 a 9:\n");
	PrintRow(Mat, 0, 0, 9);
	printf("Mat fila 100 de 0 a 9:\n");
	PrintRow(Mat, 100, 0, 9);
	
	printf("MatDD fila 0 de 0 a 9:\n");
	PrintRow(MatDD, 0, 0, 9);
	printf("MatDD fila 100 de 90 a 99:\n");
	PrintRow(MatDD, 100, 90, 9);
	// B.
	
	// C.
	printf("Producte escalar V1·V2: %f \n", Scalar(V1,V2));
	printf("Producte escalar V1·V3: %f \n", Scalar(V1,V3));
	printf("Producte escalar V2·V3: %f \n\n", Scalar(V2,V3));
	
	// D.
	printf("Magnitud V1; %f \n", Magnitude(V1));
	printf("Magnitud V2; %f \n", Magnitude(V2));
	printf("Magnitud V3; %f \n\n", Magnitude(V3));
	
	// E.
	printf("V1 i V2 son ortogonals? %d \n", Ortogonal(V1,V2));
	printf("V1 i V3 son ortogonals? %d \n", Ortogonal(V1,V3));
	printf("V2 i V3 son ortogonals? %d \n\n", Ortogonal(V2,V3));
	// F,
	MultEscalar(V3,V4,2.0);
	printf("V4 de 0 a 9:\n");	
	PrintVect(V4, 0, 9);
	printf("V4 de 256 a 265:\n");	
	PrintVect(V4, 256, 9);
	
}
