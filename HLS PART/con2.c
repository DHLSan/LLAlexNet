#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define input_channel 3
#define size_input 5
#define filtre_sayisi 2  // number of filters
#define size_filtre  2   // size of filter
#define stride  1
#define pad 0



float relu(float deger){
	if(deger < 0){
		return 0;
	}
	else
		return deger;
}

void conv_upg2 (float input[input_channel][size_input][size_input],
				float bias[filtre_sayisi], float filtre[filtre_sayisi][input_channel][size_filtre][size_filtre],
				  float output[filtre_sayisi][(size_input + (pad*2) - size_filtre) / stride + 1][(size_input + (pad*2)- size_filtre) / stride +1]){

#pragma HLS INTERFACE s_axilite port=input bundle=inputport
#pragma HLS INTERFACE s_axilite port=bias bundle=biasport
#pragma HLS INTERFACE s_axilite port=filtre bundle=filtreport
#pragma HLS INTERFACE s_axilite port=output bundle=outputport

#pragma HLS INTERFACE s_axilite port=return bundle=control


	int a, b;
	int y,x,i,j;
	int count_filter = 0;
	//int output_temp = 0;
	int padded_size = size_input + (pad*2);

	int n, l, m, chan;
	


	for(b = 0; b < filtre_sayisi; b++){	
		float temp = 0;
		for (y=0; y < size_input - size_filtre +1 ; y++){
			for (x=0; x< size_input - size_filtre +1 ;x++){
				for(a = 0; a < input_channel; a++){   		
					for (i=0; i<size_filtre; i++){    								   
						for (j=0; j<size_filtre; j++){ 
							//printf("yapilan islem: filtre[%d][%d][%d][%d] = %d -- input[%d][%d][%d] = %d \n", j, i, count_filter, b, filtre[b][count_filter][i][j], j+(x * stride), i+(y * stride), a, padded_input[a][i+(y * stride)][j+(x * stride)]);							
							temp += filtre[b][count_filter][i][j] * input[a][i+(y * stride)][j+(x * stride)];
						}
					} 		
				//printf(" outputa atanan deger : %d \n", output[y][x][a]);
				//output_temp[y][x] = temp;
				count_filter++;
				}
			temp = temp + bias[b];
			temp = relu(temp);
			output[b][y][x] = temp;
			//printf("outputa atanan deger output[%d][%d][%d] = %d \n",x,y,b, output[b][y][x]);
			count_filter = 0;
			temp = 0;
			}
			//output_temp += temp; 
		}
	//	output_temp = 0;
	}
}

					
	
