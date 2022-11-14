// Importem les llibreries necessaries.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Definim N = 512.
#define N 512 
// Declarem les Matrius.
float Mat[N][N], MatDD[N][N]; 
// Declarem els Vectors.
float V1[N], V2[N], V3[N], V4[N]; 

// Inicialització Matrius i Vectors.
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
	int i; // Declarem i com a int.
	for (i = from; i < numel + from; i++){ // Igualem la variable i al valor introduit from per començar a imprimir per pantalla desde aquella posició amb la condicio que i no passi del valor from + numel, la variable numel es la cantitat de valors que imprimira a partir del from.
		printf ("%f\n", vect[i]); // Imprimim el valor que hi ha a vect[i].
	}
	printf("\n"); // Salt de linea per llegir millor el resultat.
}

void PrintRow(float mat[N][N],int row, int from, int numel ){
	int i; // Declarem la variable i com a int.
	for (i = from; i < numel + from; i++){ // Igualem la variable i al valor introduit from per començar a imprimir per pantalla desde aquella posició amb la condicio que i no passi del valor from + numel, la variable numel es la cantitat de valors que imprimira a partir del from.
		printf ("%f\n", mat[row][i]); // Imprimim el valor que hi ha a mat[row][i].
	}
	printf("\n"); // Salt de linea per llegir millor el resultat.
}

void MultEscalar(float vect[N], float vectres[N], float alfa){
	int i; // Declarem la variable i com a int.
	for (i = 0; i < N; i++){ // Per cada valor del vect amb mida N.
		vectres[i] = vect[i]*alfa; // Es multiplica el valor a vect[i] per alfa i es guarda a la mateixa posició i en un altre vector.
	}
}

float Scalar(float vect1[N], float vect2[N]){
	int suma, i; // Declarem les variables suma i "i" com a int.
	for (i = 0; i < N; i++){ // Per cada valor del vect amb mida N.
		suma += vect1[i]*vect2[i]; // Es multiplica el valor a vect1[i] per el valor a vect2[i] i es fa un sumatori de tots els valors.
	}
	return suma; // Retorna el resultat del sumatori.
}

float Magnitude(float vect[N] ){
	int suma, i; // Declarem les variables suma i "i" com a int.
	for (i = 0; i < N; i++){ // Per cada valor del vect amb mida N.
		suma += vect[i]*vect[i]; // S'eleva al quadrat el valor a vect[i] i es fa un sumatori de tots els valors.
	}
	return suma; // Retorna el resultat del sumatori.
}

int Ortogonal(float vect1[N], float vect2[N]){
	if (Scalar(vect1, vect2) == 0){ // Si el valor retornat per la funció Scalar() és 0.
		return 1; // Retorna 1 (True).
	}
	else{ // Si no és el cas.
		return 0;// Retorna 0 (False).
	}
}

void Projection( float vect1[N], float vect2[N], float vectres[N] ){
	float uv, v, div; // Declarem les variables uv, v, i div com a float.
	uv = Scalar(vect1, vect2); // Calculem el producte escalar entre els dos vectors amb la funció Scalar() i guardem el resultat a la variable uv.
	v = Magnitude(vect2); // Calculem la magnitud del segon vector amb la funció Magnitude() i la guardem a la variable v.
	div = uv / v; // Dividim el producte escalar dels dos vectors entre la magnitud del segon i ho guardem a la variable div.
	MultEscalar(vect2, vectres, div); // Amb la funció MultEscalar() fem la multiplicació del segon vector per un escalar, que en aquest cas és el valor guardat a div.
}

float Infininorm(float M[N][N]){
	float max = 0.0, sum; // Declarem les variables max i sum com a float, inicialitzant també max a 0.0. 
	int i, j; // Declarem les variables "i" i j com a int.
	for (i = 0; i < N; i++){
		sum = 0.0;
		for (j = 0; j < N-1; j++){
			sum += fabs(M[i][j]); // Es suma cada valor absolut d'una fila.
		}
		if (sum > max){ // Si la suma d'una fila és més gran que el maxim (la suma d'una fila més alta fins ara). 
		max = sum; // La suma d'aquella fila és el nou máxim.
		}
	}
	return max; // Retorna el valor max.
}

float Onenorm(float M[N][N]){
	float max = 0.0, sum; // Declarem les variables max i sum com a float, inicialitzant també max a 0.0.
	int i, j; // Declarem les variables "i" i j com a int.
	for (j = 0; j < N; j++){
		sum = 0.0;
		for (i = 0; i < N-1; i++){
			sum += fabs(M[i][j]); // Es suma cada valor absolut d'una columna.
		}
		if (sum > max){ // Si la suma d'una columna és més gran que el maxim (la suma d'una columna més alta fins ara).
		max = sum; // La suma d'aquella columna és el nou máxim.
		}
	}
	return max; // Retorna el valor max.
}

float NormFrobenius(float M[N][N]){
	float sum; // Declarem la variable sum com a float.
	int i, j; // Declarem les variables "i" i j com a int.
	for (i = 0; i < N; i++){
		for (j = 0; j < N-1; j++){
			sum += M[i][j] * M[i][j]; // Es fa un sumatori de cada valor de la matriu elavat al quadrat.
		}
	}
	float arrel = sqrt(sum); // Declarem la variable arrel com a float i la igualem a l'arrel quadrada del sumatori anterior.
	return arrel; // Retornem el valor que hi ha a arrel.
}

int DiagonalDom(float M[N][N]){
	float ediag, sum_no_diag; // Declarem les variables ediag(Element de la diagonal) i sum_no_diag(suma elements que no son de la diagonal).
	int i, j; // Declarem les variables "i" i j com a int.
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (i == j){
				ediag = fabs(M[i][j]); // S'iguala a ediag el valor del element de la diagonal de la fila i.
			}
			else{
				sum_no_diag += fabs(M[i][j]); // Es sumen tots els valors que no son de la diagonal a la variable sum_no_diag.
			}
		}
		if (ediag < sum_no_diag){ // Si el valor de la diagonal és més petit que la suma de tots els altres valors de la fila.
			return 0; // Retorna 0 (False)
		} // Només cal que una fila compleixi la condició per fer que la matriu no sigui diagonal dominant.
		
	}
	return 1; // Retorna 1 (True)
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
	printf("Mat:\n");
	printf("Infini-norma: %f\n", Infininorm(Mat));
	printf("Norma ú: %f\n", Onenorm(Mat));
	printf("Norma de Frobenius: %f\n", NormFrobenius(Mat));
	printf("Es Mat diagonal dominant? %d\n\n",DiagonalDom(Mat));
	
	printf("MatDD:\n");
	printf("Infini-norma: %f\n", Infininorm(MatDD));
	printf("Norma ú: %f\n", Onenorm(MatDD));
	printf("Norma de Frobenius: %f\n", NormFrobenius(MatDD));
	printf("Es Mat diagonal dominant? %d\n\n",DiagonalDom(MatDD));
	
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
	
	// F.
	printf("V4 = V3·2.0:\n");
	MultEscalar(V3, V4, 2.0);
	printf("V4 de 0 a 9:\n");
	PrintVect(V4, 0, 9);
	printf("V4 de 256 a 265:\n");
	PrintVect(V4, 256, 9);
	
	// G.
	Projection(V2, V3, V4);
	printf("Projecció del V2 sobre V3 (10 primers):\n");
	PrintVect(V4, 0, 10);
	Projection(V1, V2, V4);
	printf("Projecció del V1 sobre V2 (10 primers):\n");
	PrintVect(V4, 0, 10);
}
