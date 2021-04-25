#include <stdio.h>

void convolution2d (int size_input, int input[size_input][size_input], int size_filtre, int filtre[size_filtre][size_filtre],int stride, int pad, int output[(size_input + (pad*2) - size_filtre) / stride + 1][(size_input + (pad*2)- size_filtre) / stride +1]){             
	int y,x,i,j;
	int padded_size = size_input + (pad*2);
	int padded_input[padded_size][padded_size];
	padding(size_input, input, pad, padded_input);
	int temp = 0;
	for (y=0; y < padded_size - size_filtre +1 ; y++){         					    // burasý input sütunlarý için döner
		for (x=0; x< padded_size - size_filtre +1 ;x++){   						   // burasý input satýrlarý için döner
			for (i=0; i<size_filtre; i++){    								   	  // burasý filtre sütunlarý için döner
				for (j=0; j<size_filtre; j++){ 									 // burasý filtre satýrlarý için döner
					temp += filtre[i][j] * padded_input[i+(y * stride)][j+(x * stride)];				
				}
			} 
		output[y][x] = temp;
		printf(" outputa atanan deger : %d \n", output[y][x]);
		temp = 0;
		}
	}
}

void padding (int size, int input[size][size], int pad, int out[size+(pad*2)][size+(pad*2)]){
	int x, y;
	int pad_yeni = pad;
	int count = 0;
	if (pad == 0){
		for (x=0 ; x<size; x++){
			for (y=0 ; y<size; y++){
				out[x][y] = input[x][y];
			}
		}
	}
	else {
	while(pad_yeni > 0){
	for(x=count ; x < (size+(pad_yeni*2)+count); x++){
		out[count][x] = 0;
		out[x][count] = 0;
		out[size+(pad_yeni*2)-1+count][x] = 0;
		out[x][size+(pad_yeni*2)-1+count] = 0;
	}
	pad_yeni = pad_yeni -1 ;
	count++;
}

	for(x=pad ; x<size+(pad*2)-pad ; x++){
		for(y=pad ; y<size+(pad*2)-pad ; y++){
			out[x][y] = input[x-pad][y-pad];
		}		
	}
	
	for (x=0 ; x<size+(pad*2); x++){
			for (y=0 ; y<size+(pad*2); y++){
			printf(" p[%d][%d] = %d ",x+1,y+1,out[x][y]);
			}
			printf("\n");
		}
	}
}


int main(){
int size_im = 5;
int size_fil = 3;
int pad = 3;
int stride = 1;

printf("5\n");
int l, m;

int out[(size_im + (pad*2) - size_fil) / stride + 1][(size_im + (pad*2) - size_fil) / stride + 1];

int padout[7][7];
int size = 5;

int image[5][5] = {{2, 3, 5, 7, 11}, {12, 8, 4, 6, 1}, {9, 7, 5, 0, 13}, {1, 3, 2, 6, 5}, {4, 6, 8, 8, 1}};
        
int kernel[3][3] = {{1, 3, 5}, {2, 7, 6}, {9, 3, 1}};

convolution2d(size_im, image, size_fil, kernel, stride, pad, out);

for (l=0; l<(size_im + (pad*2) - size_fil) / stride + 1; l++){
		for (m=0; m<(size_im + (pad*2) - size_fil) / stride + 1; m++){
			printf(" padout[%d][%d] = %d ",l,m,out[l][m]);
		}
			printf("\n");
	}

}


