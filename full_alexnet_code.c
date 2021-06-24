#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//weightler atamadan önce deðiþkenlerin içi 0 ile doldurulabilinir

void padding_upg(int channel, int size, float input[channel][size][size], int pad, 
				 float out[channel][size+(pad*2)][size+(pad*2)]){
	int x, y, a;
	int pad_yeni = pad;
	int count = 0;
	
	if (pad == 0){
		for (a=0 ; a<channel; a++){
			for (x=0 ; x<size; x++){
				for (y=0 ; y<size; y++){
					out[a][x][y] = input[a][x][y];
				}
			}
		}
	}
	else {
		for(a = 0; a<channel; a++){
			while(pad_yeni > 0){
				for(x=count ; x < (size+(pad_yeni*2)+count); x++){
					out[a][count][x] = 0;
					out[a][x][count] = 0;
					out[a][size+(pad_yeni*2)-1+count][x] = 0;
					out[a][x][size+(pad_yeni*2)-1+count] = 0;
				}
			pad_yeni = pad_yeni -1 ;
			count++;
			}
			for(x=pad ; x<size+(pad*2)-pad ; x++){
				for(y=pad ; y<size+(pad*2)-pad ; y++){
					out[a][x][y] = input[a][x-pad][y-pad];
				}		
			}
			/*
			for (x=0 ; x<size+(pad*2); x++){
				for (y=0 ; y<size+(pad*2); y++){
					printf(" p[%d][%d][%d] = %d ",y+1,x+1,a+1,out[a][x][y]);
				}
				printf("\n");
			}
			*/
		pad_yeni = pad;
		count = 0;
		}	
	}
}


float relu(float deger){
	if(deger < 0){
		return 0;
	}
	else
		return deger;
}


void flatten(int size, int channel, float inp[channel][size][size], float output[channel * size * size]){
	int n, k, l;
	int counter = 0;
	for(n = 0; n< channel; n++){
		for(k = 0; k < size; k++){
			for(l = 0; l < size; l++){
				output[counter++] = inp[n][k][l];			
			}
		}
	}
}


void softmax(int input_len, float input[input_len], float output[input_len]){
    assert (input != NULL);
    assert (input_len != 0);
    int i;
    float m;
    /* Find maximum value from input array */
    m = input[0];
    for (i = 1; i < input_len; i++){
        if (input[i] > m) {
        	m = input[i];
        }
    }
    float sum = 0;
    for (i = 0; i < input_len; i++){
        sum += expf(input[i]-m);
    }
    for (i = 0; i < input_len; i++){
        output[i] = expf(input[i] - m - log(sum));
    }    
}


void fullyconnected_relu(int size, float input[size], int neuron_size, float neuron[neuron_size][size], float output[neuron_size], float bias[neuron_size]){
	int k, l ,m;
	float sum = 0;
	for (k = 0; k < neuron_size; k++){
		for(l = 0; l< size ; l++){
			sum += input[l] * neuron[k][l] ;
		}
		sum = sum + bias[k];
		sum = relu(sum);
		output[k] = sum;
		sum = 0;		
	}
}


void fullyconnected_softmax(int size, float input[size], int neuron_size, float neuron[neuron_size][size], float output[neuron_size], float bias[neuron_size]){
	int k, l ,m;
	float sum = 0;
	float output_1[neuron_size];
	for (k = 0; k < neuron_size; k++){
		for(l = 0; l< size ; l++){
			sum += input[l] * neuron[k][l] ;
		}
		sum = sum + bias[k];
		output_1[k] = sum;
		sum = 0;
	}
	softmax(neuron_size, output_1, output);
}


void conv_upg2 (int input_channel, int size_input, float input[input_channel][size_input][size_input], int filtre_sayisi,
				float bias[filtre_sayisi], int size_filtre, float filtre[filtre_sayisi][input_channel][size_filtre][size_filtre], 
				 int stride, int pad, float output[filtre_sayisi][(size_input + (pad*2) - size_filtre) / stride + 1][(size_input + (pad*2)- size_filtre) / stride +1]){
	int a, b;
	int y,x,i,j;
	int count_filter = 0;
	//int output_temp = 0;
	int padded_size = size_input + (pad*2);
	float padded_input[input_channel][padded_size][padded_size];
	int n, l, m, chan;
	
	padding_upg(input_channel, size_input, input, pad, padded_input);
	/*
	for(n = 0; n < 3 ; n++){
		printf("%d channel \n",n);
		for(l = 0; l <7; l++){
			for(m = 0; m <7; m++){	
				printf("padding_in[%d][%d][%d] = %d ", m,l, n, padded_input[n][l][m]);
			}
		printf("\n");
		}
	}
	*/
	for(b = 0; b < filtre_sayisi; b++){	
		float temp = 0;
		for (y=0; y < padded_size - size_filtre +1 ; y++){         		
			for (x=0; x< padded_size - size_filtre +1 ;x++){		
				for(a = 0; a < input_channel; a++){   		
					for (i=0; i<size_filtre; i++){    								   
						for (j=0; j<size_filtre; j++){ 
							//printf("yapilan islem: filtre[%d][%d][%d][%d] = %d -- input[%d][%d][%d] = %d \n", j, i, count_filter, b, filtre[b][count_filter][i][j], j+(x * stride), i+(y * stride), a, padded_input[a][i+(y * stride)][j+(x * stride)]);							
							temp += filtre[b][count_filter][i][j] * padded_input[a][i+(y * stride)][j+(x * stride)];				
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


void maxpool(int input_size,int channel, int filtre_size, int stride, float input[channel][input_size][input_size], float output[channel][(input_size - filtre_size) / stride +1][(input_size - filtre_size) / stride +1]){
	int x, y, i, j, k, n;
	int count=0;
	float max = 0;
	float temp[filtre_size * filtre_size];
	for(n = 0 ; n < channel; n++){
		for(x=0 ; x<(input_size -filtre_size) / stride +1 ; x++){
			for(y=0 ; y<(input_size -filtre_size) / stride +1 ; y++){
				for(i=0 ; i<filtre_size; i++){
					for(j=0 ; j<filtre_size; j++){
						temp[count] = input[n][(x*stride)+i][(y*stride)+j];
						printf("temp[%d] = %f ", count, temp[count]);
						count++ ;
					}
				}
				count = 0;
				for(k=0 ; k< filtre_size * filtre_size; k++){
					printf("maximum deger = %f \n", max);
					if(max < temp[k]){
						max = temp[k];
					}
				}
				output[n][x][y] = max;
				max = 0;			
			}
		}
	}
}


int main(){
	int a, b, c, d, e;
	
	
	float input[3][5][5] = {
							{{0.4, 0.75, 0.92, 0.563, 0.326}, {0.296, 0.561, -0.426, 0.783, 0.512}, {0.146, -0.565, -0.672, 0.26, 0.812}, {0.912, 0.234, 0.541, 0.145, -0.791}, {0.542, -0.671, -0.214, 0.742, 0.971}},
							{{0.126, 0.654, 0.767, -0.731, -0.323}, {0.121, 0.444, -0.678, 0.742, -0.167}, {0.663, -0.769, -0.812, 0.468, 0.641}, {0.131, -0.657, 0.127, -0.431, -0.324}, {0.655, 0.268, -0.246, -0.267, 0.532}},
							{{-0.263, 0.656, 0.784, -0.864, 0.123}, {-0.741, 0.731, -0.217, -0.016, 0.543}, {-0.154, 0.078, 0.542, -0.045, 0.067}, {0.742, 0.317, -0.555, -0.674, 0.135}, {0.01, 0.006, -0.663, 0.176, 0.643}}
							};
							
	// pythona göre input deðeri
	//float input_py[3][5][5] = {
	//						   {{0.4, }
	//						   }
	//}
	/*
	float filtre_1[2][3][2][2] = {
								{{{0.250, -0.145}, {0.943, 0.136}},
								 {{0.843, 0.189}, {-0.312, 0.576}},
								 {{0.521, 0.741}, {0.235, -0.631}}
								},
								{{{0.542, -0.641}, {0.109, 0.403}},
								 {{0.706, -0.294}, {0.402, 0.707}},
								 {{0.410, -0.124}, {0.376, -0.265}}
								}
							};
	*/
	
	//filtre python koduna göre yeniden yazýldý
	float filtre_1 [2][3][2][2] = {
									{{{0.250, 0.943}, {-0.145, 0.136}},
									 {{0.521, 0.235}, {0.741, -0.631}},
									 {{0.706, 0.402}, {-0.294, 0.707}}
									 },
									{{{0.843, -0.312}, {0.189, 0.576}},
									 {{0.542, 0.109}, {-0.641, 0.403}},
									 {{0.410, 0.376}, {-0.124, -0.265}}
									  }
								};						
    
    float bias_1[2] = {0.823, 0.634};
	
	float filtre_2[1][2][2][2] = {
									{{{0.647, -0.421}, {0.39, 0.873}},
									 {{-0.479, 0.802}, {-0.362, 0.289}}}
									};
	
	int channel = 3, size = 5, filt_sayisi = 2, filt_size = 2, stride = 1, pad = 0;
	float output_1[filt_sayisi][(size + (pad*2) - filt_size) / stride + 1][(size + (pad*2) - filt_size) / stride + 1];
	conv_upg2(channel, size, input, filt_sayisi, bias_1, filt_size, filtre_1, stride, pad, output_1);
	
	int max_stride = 2;
	int max_size = (size + (pad*2) - filt_size) / max_stride + 1;
	int max_filt_size = 2;
	float output_2[filt_sayisi][(max_size - max_filt_size) / max_stride + 1][(max_size - max_filt_size) / max_stride + 1];
	maxpool(max_size, filt_sayisi, max_filt_size, max_stride, output_1, output_2);
	
	for(a = 0; a < filt_sayisi; a++){
		for(b = 0; b < (max_size - max_filt_size) / max_stride + 1; b++){
			for(c = 0; c < (max_size - max_filt_size) / max_stride + 1; c++){
				printf("output[%d][%d][%d] = %f     ", c,b,a,output_2[a][b][c]);
			}
			printf("\n");
		} 
	}
	
	/*
	for(a = 0; a < filt_sayisi; a++){
		for(b = 0; b < max_size; b++){
			for(c = 0; c < max_size; c++){
				printf("output[%d][%d][%d] = %f     ", c,b,a,output_1[a][b][c]);
			}
			printf("\n");
		} 
	}
	*/
	
	
	
	int inp_channel = 3, inp_size = 227, conv1_filtre_num = 96, conv1_size = 11, conv1_stride = 4, conv1_pad = 0;
	float input[inp_channel][inp_size][inp_size];
	float conv1_bias[conv1_filtre_num];
	float conv1_filtre[conv1_filtre_num][inp_channel][conv1_size][conv1_size];
	int output1_size = (inp_size + (conv1_pad*2) - conv1_size) / conv1_stride + 1;
	float conv1_output[conv1_filtre_num][output1_size][output1_size];
	//alexnet mimari baþlangiç
	//1.convolution layer
	// 11x11 filtre stride = 4 96 tane kernel, input 3 kanallý, padding yok
	conv_upg2(inp_channel, inp_size, input, conv1_filtre_num, conv1_bias, conv1_size, conv1_filtre, conv1_stride
			 conv1_pad, conv1_output);
			 
	int maxpool_filtre_size1 = 3;
	int maxpool1_stride = 2;
	int maxpool1_output_size = (output1_size - maxpool_filtre_size1) / maxpool1_stride +1 ;
	float maxpool1_output[conv1_filtre_num][maxpool1_output_size][maxpool1_output_size];
	// maxpool filtre 3x3 stride = 2
	maxpool(output1_size, conv1_filtre_num, maxpool_filtre_size1, maxpool1_stride, conv1_output, maxpool1_output);
	
	int conv2_filtre_num = 256, conv2_size = 5, conv2_stride = 1, conv2_pad = 2;
	float conv2_bias[conv2_filtre_num];
	float conv2_filtre[conv2_filtre_num][conv1_filtre_num][conv2_size][conv2_size];
	int output2_size = (maxpool1_output_size + (conv2_pad*2) - conv2_size) / conv2_stride + 1;
	float conv2_output[conv2_filtre_num][output2_size][output2_size];
	//2. convolution layer
	//5x5 filtre stride = 1 256 tane kernel, input 96 kanallý, padding = 2
	conv_upg2(conv1_filtre_num, maxpool1_output_size, maxpool1_output, conv2_filtre_num, conv2_bias, conv2_size,
	          conv2_filtre, conv2_stride, conv2_pad, conv2_output);
	        
	int maxpool_filtre_size2 = 3;
	int maxpool2_stride = 2;
	int maxpool2_output_size = (output2_size - maxpool_filtre_size2) / maxpool2_stride +1;
	float maxpool2_output[conv2_filtre_num][maxpool2_output_size][maxpool2_output_size];
	// maxpool filtre 3x3 stride = 2
	maxpool(output2_size, conv2_filtre_num, maxpool_filtre_size2, maxpool2_stride, conv2_output, maxpool2_output);
	
	int conv3_filtre_num = 384, conv3_size = 3, conv3_stride = 1, conv3_pad = 1;
	float conv3_bias[conv3_filtre_num];
	float conv3_filtre[conv3_filtre_num][conv2_filtre_num][conv3_size][conv3_size];
	int output3_size = (maxpool2_output_size + (conv3_pad*2) - conv3_size) / conv3_stride +1;
	float conv3_output[conv3_filtre_num][output3_size][output3_size];
	//3. convolution layer
	//3x3 filtre stride = 1 384 tane kernel, input 256 kanallý, padding = 1
	conv_upg2(conv2_filtre_num, maxpool2_output_size, maxpool2_output, conv3_filtre_num, conv3_bias, conv3_size,
			  conv3_filtre, conv3_stride, conv3_pad, conv3_output);
			  
	int conv4_filtre_num = 384, conv4_size = 3, conv4_stride = 1, conv4_pad = 1;
	float conv4_bias[conv4_filtre_num];
	float conv4_filtre[conv4_filtre_num][conv3_filtre_num][conv4_size][conv4_size];
	int output4_size = (output3_size + (conv4_pad*2) - conv4_size) / conv4_stride +1;
	float conv4_output[conv4_filtre_num][output4_size][output4_size];
	//4. convolution layer
	//3x3 filtre stride = 1 384 tane kernel, input 384 kanallý, padding = 1
	conv_upg2(conv3_filtre_num, output3_size, conv3_output, conv4_filtre_num, conv4_bias, conv4_size,
			  conv4_filtre, conv4_stride, conv4_pad, conv4_output);
	
	int conv5_filtre_num = 256, conv5_size = 3, conv5_stride = 1, conv5_pad = 1;
	float conv5_bias[conv5_filtre_num];
	float conv5_filtre[conv5_filtre_num][conv4_filtre_num][conv5_size][conv5_size];
	int output5_size = (output4_size + (conv5_pad*2) - conv5_size) / conv5_stride +1;
	float conv5_output[conv5_filtre_num][output5_size][output5_size];
	//5. convolution layer
	//3x3 filtre stride = 1 256 tane kernel, input 384 kanallý, padding = 1
	conv_upg2(conv4_filtre_num, output4_size, conv4_output, conv5_filtre_num, conv5_bias, conv5_size,
		 	  conv5_filtre, conv5_stride, conv5_pad, conv5_output);
	
	int maxpool_filtre_size3 = 3;
	int maxpool3_stride = 2;
	int maxpool3_output_size = (output5_size - maxpool_filtre_size3) / maxpool3_stride +1;
	float maxpool3_output[conv5_filtre_num][maxpool3_output_size][maxpool3_output_size];
	// maxpool filtre 3x3 stride = 2
	maxpool(output5_size, conv5_filtre_num, maxpool_filtre_size3, maxpool3_stride, conv5_output, maxpool3_output);
	//dropout varmýþ sonra
	
	
	//önce flatten, sonra fully connected
	float flatten_output[conv5_filtre_num * maxpool3_output_size * maxpool3_output_size];
	flatten(maxpool3_output_size, conv5_filtre_num, maxpool3_output, flatten_output);
	
	//1. fully connected layer
	//4096 neuron
	int fully1_size = conv5_filtre_num * maxpool3_output_size * maxpool3_output_size;
	int fully1_neuron_size = 4096;
	float fully1_neuron[fully1_neuron_size][fully1_size];
	float fully1_output[fully1_neuron_size];
	float fully1_bias[fully1_neuron_size];
	fullyconnected_relu(fully1_size, flatten_output, fully1_neuron_size, fully1_neuron, fully1_output, fully1_bias);
	//dropout varmýþ burdada
	
	//2. fully connected layer
	//4096 neuron
	int fully2_neuron_size = 4096;
	float fully2_neuron[fully2_neuron_size][fully1_neuron_size];
	float fully2_output[fully2_neuron_size];
	float fully2_bias[fully2_neuron_size];
	fullyconnected_relu(fully1_neuron_size, fully1_output, fully2_neuron_size, fully2_neuron, fully2_output, fully2_bias);
	
	//3. fully connected layer
	//1000 neuron böylece en son 1000 class tahmini yapar
	int fully3_neuron_size = 1000;
	float fully3_neuron[fully3_neuron_size][fully2_neuron_size];
	float fully3_output[fully3_neuron_size];
	float fully3_bias[fully3_neuron_size];
	fullyconnected_softmax(fully2_neuron_size, fully2_output, fully3_neuron_size, fully3_neuron, fully3_output, fully3_bias);
	
	
	
	
}
