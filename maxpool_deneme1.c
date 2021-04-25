#include <stdio.h>

void maxpool(int input_size, int filtre_size, int stride, int input[input_size][input_size], int output[(input_size - filtre_size) / stride +1][(input_size - filtre_size) / stride +1]){
	int x, y, i, j, k;
	int count=0;
	int max = 0;
	int temp[filtre_size * filtre_size];
	for(x=0 ; x<(input_size -filtre_size) / stride +1 ; x++){
		for(y=0 ; y<(input_size -filtre_size) / stride +1 ; y++){
			for(i=0 ; i<filtre_size; i++){
				for(j=0 ; j<filtre_size; j++){
					temp[count] = input[(x*stride)+i][(y*stride)+j];
					printf("temp[%d] = %d ", count, temp[count]);
					count++ ;
				}
			}
			count = 0;
			for(k=0 ; k< filtre_size * filtre_size; k++){
				printf("maximum deger = %d \n", max);
				if(max < temp[k]){
					max = temp[k];
				}
			}
			output[x][y] = max;
			max = 0;
				
		}
	}
}


int main(){
	
	
	int image[4][4] = {{2, 3, 5, 7}, {12, 8, 4, 6}, {9, 7, 5, 0}, {1, 3, 2, 6}};
	int size = 4;
	int filtre = 2;
	int stride = 2;
	int output[(size - filtre) / stride +1][(size - filtre) / stride +1];
	
	int i, j;
	
	maxpool(size, filtre, stride, image, output);
	
	for(i = 0; i <(size - filtre) / stride +1 ; i++)
		for(j= 0; j<(size - filtre) / stride +1; j++)
			printf("output[%d][%d] = %d \n", i,j,output[i][j]);	
	
	
}
