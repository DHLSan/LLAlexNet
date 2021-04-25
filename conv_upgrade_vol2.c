#include <stdio.h>

void padding_upg(int channel, int size, int input[size][size][channel], int pad, int out[size+(pad*2)][size+(pad*2)][channel]){
	int x, y, a;
	int pad_yeni = pad;
	int count = 0;
	if (pad == 0){
		for (a=0 ; a<channel; a++){
		for (x=0 ; x<size; x++){
			for (y=0 ; y<size; y++){
				out[x][y][a] = input[x][y][a];
			}
		}
	}
}
	else {
		for(a = 0; a<channel; a++){
			while(pad_yeni > 0){
	for(x=count ; x < (size+(pad_yeni*2)+count); x++){
		out[count][x][a] = 0;
		out[x][count][a] = 0;
		out[size+(pad_yeni*2)-1+count][x][a] = 0;
		out[x][size+(pad_yeni*2)-1+count][a] = 0;
	}
	pad_yeni = pad_yeni -1 ;
	count++;
}

	for(x=pad ; x<size+(pad*2)-pad ; x++){
		for(y=pad ; y<size+(pad*2)-pad ; y++){
			out[x][y][a] = input[x-pad][y-pad][a];
		}		
	}
	
	for (x=0 ; x<size+(pad*2); x++){
			for (y=0 ; y<size+(pad*2); y++){
			printf(" p[%d][%d][%d] = %d ",x+1,y+1,a+1,out[x][y][a]);
			}
			printf("\n");
		}
	}	
}
}

// Bu kodda convolution layer fonksiyonuna bias de�eri ve 3 kanall� image i�in convolution yap�lacakt�r.
// 3 kanall� convoltion i�in �nce tek tek R-G-B kanallar� i�in farkl� kernel filtreleri ile input aras�nda convolution yap�l�r daha sonra 3 tane 2 boyutlu matrix elde edilir.
// Bu 3 matrix birbiriyle toplan�r ve tek bir ��kt� bulunur. En sonda ise bu tek ��kt�ya tek bir bias de�eri toplan�r ve output bulunur. Bias de�eri tek bir say� de�eridir,
// vekt�r veya matrix de�ildir.
// convolution fonksiyonuna input olarak kanal say�s� girilmelidir (RGB i�in veya �nceki convdan ��kan kanal say�s�), filtreye_size a da yeni bir parametre al�nmal�d�r (filtre say�s�), 
// output olarakda 3. boyut eklenmeli (filtre say�s� kadar).
// Bu i�lemleri yapmak i�in yeni fonksiyon a��labilir conv_upg olarak.


void conv_upg (int input_channel, int size_input, int input[size_input][size_input][input_channel], int filtre_channel, int size_filtre, int filtre[size_filtre][size_filtre][filtre_channel * input_channel], int stride, int pad, int output[(size_input + (pad*2) - size_filtre) / stride + 1][(size_input + (pad*2)- size_filtre) / stride +1][filtre_channel]){
	int a, b;
	int y,x,i,j;
	int count_filter = 0;
	int output_temp = 0;
	int padded_size = size_input + (pad*2);
	int padded_input[padded_size][padded_size][input_channel];
	padding_upg(input_channel, size_input, input, pad, padded_input);
	
	for(b = 0; b < filtre_channel; b++){
		
	int temp = 0;
	for (y=0; y < padded_size - size_filtre +1 ; y++){         		
		for (x=0; x< padded_size - size_filtre +1 ;x++){
		
		for(a = 0; a < input_channel; a++){   		
			for (i=0; i<size_filtre; i++){    								   
				for (j=0; j<size_filtre; j++){ 							
					temp += filtre[i][j][count_filter] * padded_input[i+(y * stride)][j+(x * stride)][a];				
				}
			} 		
		//printf(" outputa atanan deger : %d \n", output[y][x][a]);
		//output_temp[y][x] = temp;
		}
		output[y][x][b] = temp;
		printf("outputa atanan deger output[%d][%d][%d] = %d \n",y,x,b, output[y][x][b]);
		count_filter++;
		temp = 0;
	}
		//output_temp += temp;
		
	   
}
	//	output_temp = 0;
}
}


int main(){
int size_im = 3;
int size_fil = 2;
int pad = 0;
int stride = 1;
int inp_channel = 3;
int fil_channel =4 ;

printf("5\n");
int l, m, n;

int out[(size_im + (pad*2) - size_fil) / stride + 1][(size_im + (pad*2) - size_fil) / stride + 1];

int padout[7][7];
int size = 5;

int image[5][5] = {{2, 3, 5, 7, 11}, {12, 8, 4, 6, 1}, {9, 7, 5, 0, 13}, {1, 3, 2, 6, 5}, {4, 6, 8, 8, 1}};

int image_3d[3][3][3] = {
						{{2, 3, 5}, {12, 8, 4}, {9, 7, 5}},
						{{1, 3, 2}, {6, 5, 8}, {4, 6, 8}},
					 	{{7, 5, 1}, {8, 9, 0}, {4, 3, 2}}
					};

int kernel_4d[2][2][4] = {{{1, 4}, {2, 6}},{{5, 9}, {8,2}},{{4, 3}, {3, 1}},{{9, 8}, {0, 3}}};
						  	

int output_3d[(size_im + (pad*2) - size_fil) / stride + 1][(size_im + (pad*2) - size_fil) / stride + 1][4];

conv_upg(inp_channel, size_im, image_3d, fil_channel, size_fil, kernel_4d, stride, pad, output_3d);

        
int kernel[3][3] = {{1, 3, 5}, {2, 7, 6}, {9, 3, 1}};

//convolution2d(size_im, image, size_fil, kernel, stride, pad, out);
 
//for (l=0; l<(size_im + (pad*2) - size_fil) / stride + 1; l++){
//		for (m=0; m<(size_im + (pad*2) - size_fil) / stride + 1; m++){
//			printf(" padout[%d][%d] = %d ",l,m,out[l][m]);
//		}
//			printf("\n");
//	}

for(n = 0; n < 4 ; n++){
	printf("%d katman \n",n);
for(l = 0; l <(size_im + (pad*2) - size_fil) / stride +1; l++){
	for(m = 0; m <(size_im + (pad*2) - size_fil) / stride +1; m++){	
			printf("conv_out[%d][%d][%d] = %d  ", l,m,n,output_3d[l][m][n]);
		}
		printf("\n");
	}

}


}
