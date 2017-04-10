#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define F 128

static const char aes_sbox[16][16] = {
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

void bitGenerator(int b[128]){
	srand ( time(NULL) );
	for(int i=0 ; i<128 ; i++)
		b[i] = rand() % 2;
}

void printer(int array[F], int n){
  for(int i=0 ; i<n ; i++){
    printf("%u", array[i]);
  }
  printf("\n");
}

void hexadecimal(int bi[j]) {
	int aux;
	for(int i=0 ; i<16 ; i++){
		if(bi[i] < 9){
			aux = binario(bi[i]);
		}else{
			if(bi[i] == 'A')
				aux = '1010';
			}
		
	}	
}

int main(int argc, char const *argv[]) {

  int b[128];
  bitGenerator(b);
  printf("b: \n");
  printer(b,F);
	
  int row, col;
  int j=0;
  for(int i; i< 128 ;i+=8){
	row = b[i]*8 +b[i+1]*4 +b[i+2]*2 +b[i+3]*1;
	col = b[i+4]*8 +b[i+5]*4 +b[i+6]*2 +b[i+7]*1;
	bi[j]=aes_sbox[row][col];
	//printf("%d%d%d%d %d%d%d%d\n", b[i], b[i+1], b[i+2], b[i+3], b[i+4], b[i+5], b[i+6], b[i+7]);
	//printf("row = %d  col = %d\n", row, col);
	printf("\n%0x", bi[j]);
        j++;
  }	
  
        }
//bin to ex
        switch (hexa[i])
        {
        case '0':
            printf("0000"); break;
        case '1':
            printf("0001"); break;
        case '2':
            printf("0010"); break;
        case '3':
            printf("0011"); break;
        case '4':
            printf("0100"); break;
        case '5':
            printf("0101"); break;
        case '6':
            printf("0110"); break;
        case '7':
            printf("0111"); break;
        case '8':
            printf("1000"); break;
        case '9':
            printf("1001"); break;
        case 'A':
            printf("1010"); break;
        case 'B':
            printf("1011"); break;
        case 'C':
            printf("1100"); break;
        case 'D':
            printf("1101"); break;
        case 'E':
            printf("1110"); break;
        case 'F':
            printf("1111"); break;
        case 'a':
            printf("1010"); break;
        case 'b':
            printf("1011"); break;
        case 'c':
            printf("1100"); break;
        case 'd':
            printf("1101"); break;
        case 'e':
            printf("1110"); break;
        case 'f':
            printf("1111"); break;
        default:
            printf("\n Invalid hexa digit %c ", hexa[i]);
            return 0;
        }
	
  return 0;
}
