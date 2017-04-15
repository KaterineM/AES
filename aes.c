#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define F 128

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

void printer(int array[F], int n);
void bitGenerator(int b[128]);
char* hextobin(char hex);


void bitGenerator(int b[128]){
	for(int i=0 ; i<128 ; i++)
		b[i] = rand() % 2;
}

void printer(int array[F], int n){
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

int main(int argc, char const *argv[]) {

  int a[128];
	int b[128];
  bitGenerator(a);
  printf("\na: ");
  printer(a,F);

  int row, col;
  int k=0;
	char *hex;
	char *bin;
	char *bin2;

	//Transforma cada 8 bits del array en números decimal, los pasa por la sbox guardando el resultado en hex y al final pasa todo a un arreglo b
  for(int i=0; i< 128 ;i+=8){
		row = a[i]*8 +a[i+1]*4 +a[i+2]*2 +a[i+3]*1;
		col = a[i+4]*8 +a[i+5]*4 +a[i+6]*2 +a[i+7]*1;
		//aux guarda el resultado de la sbox aux[0] contiene el digito de la izq y aux[1] el de la derecha
		hex=aes_sbox[row][col];
		printf("\n%s",hex );
		//convierte el hexadecimal a binario y lo aguarda en el arreglo b
		k=i; // para que guarde los bits transformados en la posición original que estaban en a
		for (size_t j = 0; j < 4; j++) {
			bin = hextobin(hex[0]);
			bin2 = hextobin(hex[1]);
		 	b[k] = bin[j] - '0';
		 	b[k+4] = bin2[j] - '0';
		 	k++;
		}
  }
	printf("\nb:");
	printer(b,F);


  return 0;
}
