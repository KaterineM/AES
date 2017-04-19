/*
*   Autores: Katerine Muñoz, Sergio Salinas.
*   Programa: simular una fase del sistema de encriptación AES.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM 128

char *aes_sbox[16][16] = {
  {"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76"},
  {"CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0"},
  {"B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15"},
  {"04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75"},
  {"09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84"},
  {"53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF"},
  {"D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8"},
  {"51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2"},
  {"CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73"},
  {"60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB"},
  {"E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79"},
  {"E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08"},
  {"BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A"},
  {"70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E"},
  {"E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF"},
  {"8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"}
};

int matrix[4][4] = {
	{02, 03, 01, 01},
	{01, 02, 03, 01},
	{01, 01, 02, 03},
	{03, 01, 01, 02}
};


void printer(int array[NUM], int n);
void bitGenerator(int b[NUM]);
char* hextobin(char hex);
int check(int n);

void bitGenerator(int b[NUM]){
//  srand ( time(NULL) );
  for(int i=0 ; i<NUM ; i++)
    b[i] = rand() % 2;
}

void printer(int array[NUM], int n){
  for(int i=0 ; i<n ; i++){
    printf("%i", array[i]);
  }
  printf("\n");
}

char* hextobin(char hex){
  switch (hex) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
    case 'a': return "1010";
    case 'b': return "1011";
    case 'c': return "1100";
    case 'd': return "1101";
    case 'e': return "1110";
    case 'f': return "1111";
  }
}

int check(int x){
  if(x != 0){
    x += 1;
  }
  return x;
}



int main() {
  int a[NUM]; 																			//arreglo a codificar
  int b[NUM];  																			//bits Substitution
  int s[NUM]; 																			//shiftrows, guarda los desplazamientos
  //int key[NUM];                                     //Clave
  int aux[NUM];																			//arreglo auxiliar para mixcolumn
  int aux2[144];                                    //arreglo auxiliar para la multiplicación en mixcolumn

  clock_t start;
  clock_t end;
  start = clock();

  bitGenerator(a);                                  //Genera el arreglo a codificar
  //bitGenerator(key);                                //Genera la clave
  printf("\nArreglo a codificar\na: ");
  printer(a,NUM);

  int row, col, piv;
  int k = 0;
  char *hex;
  char *bin;
  char *bin2;


/************************************************************/
  //byte Substitution. Transforma cada 8 bits del array en números decimal, los pasa por la sbox guardando el resultado en hex y al final pasa todo a un arreglo b
  for(int i=0; i<NUM ;i+=8){
    row = a[i]*8 +a[i+1]*4 +a[i+2]*2 +a[i+3]*1;			//convierte el hexadecimal a binario
    col = a[i+4]*8 +a[i+5]*4 +a[i+6]*2 +a[i+7]*1;

    hex=aes_sbox[row][col];													//Captura desde la sbox el hexadecimal al que se convierte Ai

    k=i; 																						//Para que guarde los bits transformados en la posición original que estaban en a
    for (size_t j = 0; j < 4; j++) {
      bin = hextobin(hex[0]);												//Guarda el binario del hexadecimal capturado desde la sbox
      bin2 = hextobin(hex[1]);
      b[k] = bin[j] - '0';
      b[k+4] = bin2[j] - '0';
      k++;
    }
  }

  printf("\nArreglo después de byte Substitution\n ");
  printf("b:  ");
  printer(b,NUM);


/*********************************************************/
  //Shiftrows
  k = 0;
  int shiftRows[16] = {0,5,10,15,4,9,14,3,8,13,2,7,12,1,6,11}; 	//Posiciones en que debe estar los b luego del shiftRows

  for(int i=0 ; i<16 ; i++){
    for (int j = 0; j < 8; j++) {
       s[k] = b[shiftRows[i]*8 + j]; 								// se encarga de mover los 8 valores de b del shifteows a s
       k++; 																				// k va 0 a 128
    }
  }
  printf("\nArreglo después de Shiftrows\n s: " );
  printer(s,NUM);


/********************************************************/
  //MixColumn

  //Toma de a 8-bit y los transforma en sus respectivos coeficientes polimoniales
  int raised = 7;
  piv = 7;
  for(int i=0 ; i<NUM ; i++){
  	if(i % 8 == 0){                                //raised vuelve a 7 cuando ya ha tomado los 8-bit correspondientes para mixcolumn
  		raised = 7;
  	}else if(i == piv){                            //Se guarda un {0,1} en x^0 en vez de su grado, para saber si es que hay o no componente en esa posición
      aux[i] = s[i];                               //ya que si se guarda el grado, siempre sería cero y se perdería ese dato.
      piv+=8;
      raised--;
      continue;
    }
  	aux[i] = s[i]*raised;                          //transforma los binarios en sus grados respectivos
  	raised--;
  }

  /*
  La estructura de aux[NUM] es:
  - De 0 a 6 primeras posiciones de bits de aux, se guarda el grado correspondiente segun posicion de acuerdo a s.
  - En la posición 7 se guarda el mismo valor de s para saber si es que x⁰ existe. Si se guardara el valor de su grado, siempre sería 0.
  */
  printf("\nP: ");
  printer(aux,NUM);

  //Multiplicacion por matriz
  row = 0, col = 0, piv = 0;
  for(int i=0 ; i<NUM ; i+=32){
    k = i;
    for(int j=i ; j<k+32 ; j+=8){
      if(matrix[row][col] == 01){                 //Sólo se suma uno a x⁰ y se utiliza el XOR para que
        aux2[piv] = 0;                            //cumpla con GL(2⁸)
        aux2[piv+1] = aux[j];
        aux2[piv+2] = aux[j+1];
        aux2[piv+3] = aux[j+2];
        aux2[piv+4] = aux[j+3];
        aux2[piv+5] = aux[j+4];
        aux2[piv+6] = aux[j+5];
        aux2[piv+7] = aux[j+6];
        aux2[piv+8] = aux[j+7]^1;
      }else if(matrix[row][col] == 02){           //Check verifica si es que x^n existe y devuelve n+1
        aux2[piv] = check(aux[j]);
        aux2[piv+1] = check(aux[j+1]);
        aux2[piv+2] = check(aux[j+2]);
        aux2[piv+3] = check(aux[j+3]);
        aux2[piv+4] = check(aux[j+4]);
        aux2[piv+5] = check(aux[j+5]);
        aux2[piv+6] = check(aux[j+6]);
        aux2[piv+7] = aux[j+7];                   //No se hace el check porque corresponde a x⁰ porque el valor guardado en esa posición es {0,1} siendo 0 si existe y 1 si no.
        aux2[piv+8] = 0;                          //Se pone 0 por default ya que el polinomio se está multiplicando por x¹, por lo tanto, no hay x⁰
      }else{
        aux2[piv] = check(aux[j]);                //Se suma 1 a cada grado (funcion check) y se les aplica XOR con el polinomio original (ya que es x + 1)
        aux2[piv+1] = check(aux[j+1])^aux[j];     //
        aux2[piv+2] = check(aux[j+2])^aux[j+1];   //
        aux2[piv+3] = check(aux[j+3])^aux[j+2];   //
        aux2[piv+4] = check(aux[j+4])^aux[j+3];
        aux2[piv+5] = check(aux[j+5])^aux[j+4];
        aux2[piv+6] = check(aux[j+6])^aux[j+5];
        aux2[piv+7] = aux[j+7]^aux[j+6];
        aux2[piv+8] = aux[j+7];
      }
      piv+=9;
      col++;
    }
    row++;
    col = 0;
  }

  printf("\nM: ");
  printer(aux2,144);

  //Se reducen los polinomios que sean de grado 8 con el Polinomio irreductible, diviendo el polinomios con el PI y guardando el resto
  printf("\n" );
  int PI[9]= {8,0,0,0,4,3,0,1,1}; // polinomio irreductible del aes
  for (size_t i = 0; i < 144; i+=9)
    if(aux2[i] == 8)
      for (size_t j = 0; j < 9; j++)
        aux2[i+j] = aux2[i+j]^PI[j]; //Hace un xor con cada polinomio de grado 8 con el PI
  printf("M: " );
  printer(aux2,144);

  //se crea un nuevo arreglo de largo 128 con polinomios de grado 7
  int t=0;
  for (size_t i = 0; i < 144; i+=9) //Corta el arreglo en segmentos de polinomios de largo 8
    for (size_t j = i+1; j < i+9; j++) { //quita el primer elemento del polinomio bajandole el grado a 7
      s[t] = aux2[j] == 0 ? 0 : 1; // Guarda el nuevo polinomio en s.
      t++;
    }

    printf("\nEl arreglo después de MixColumn y finalmente codificado es:\n" );
    printer(s,128);

  //for (size_t i = 0; i < 128; i++) { // se hace un xor con la clave
  //  a[i] = s[i]^ key[i];
  //}

  end = clock();




  printf("\n time: %f", (double)(end - start));

  return 0;
}
