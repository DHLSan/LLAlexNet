#include <stdio.h>
#include <math.h>
#include <assert.h>

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

float relu(float deger){
	if(deger < 0){
		return 0;
	}
	else
		return deger;
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

int main(){
	int size_im = 3;
	int size_fil = 2;
	int pad = 0;
	int stride = 1;
	int inp_channel = 3;
	int fil_channel = 4 ;
	int l, m, n, chan, k;
	float out[(size_im + (pad*2) - size_fil) / stride + 1][(size_im + (pad*2) - size_fil) / stride + 1];
	float image[5][5] = {{2, 3, 5, 7, 11}, {12, 8, 4, 6, 1}, {9, 7, 5, 0, 13}, {1, 3, 2, 6, 5}, {4, 6, 8, 8, 1}};

	float image_3d[3][3][3] = {
							{{2, 3, 5}, {12, 8, 4}, {9, 7, 5}},
							{{1, 3, 2}, {6, 5, 8}, {4, 6, 8}},
					 		{{7, 5, 1}, {8, 9, 0}, {4, 3, 2}}
							};

	float kernel_4d[4][3][2][2] = {{{{1, 4}, {2, 6}},{{5, 9}, {8,2}},{{4, 3}, {3, 1}}},
							  	{{{-2, -5}, {-3, -7}},{{-4, -8}, {-5,-9}},{{-1, 0}, {-3, -7}}},
							  	{{{6, 6}, {7, 2}},{{8, 2}, {9,1}},{{7, 8}, {0, 3}}},
							  	{{{1, 4}, {2, 6}},{{5, 9}, {8,2}},{{4, 3}, {3, 1}}}};

	float output_3d[4][(size_im + (pad*2) - size_fil) / stride + 1][(size_im + (pad*2) - size_fil) / stride + 1];
	float output_flat[size_im * size_im * inp_channel];  
	int fully_size = 4;
	int neuron_size = 3;	
	float soft[7] = {1, 2, 3, 4, 1, 2, 3} ;
	float outout[3];
	float bias[3] = {1, 2, 3};
	float fully[3][4] = {{1, 3, 5, 8}, {1, 3, 5, 8}, {0, 3, 1, 0}};
	float inp_fully[4] = {24, 10, 15, 1};
	float output_fully[neuron_size] ;
	fullyconnected_softmax(fully_size, inp_fully, neuron_size, fully, output_fully, bias);

	for ( k = 0; k < neuron_size; k++)
		printf(" neuron %d = %f \n", k, output_fully[k]);
	
	float output2_fully[3] = {5, 3, 2};
	
	softmax(neuron_size, output2_fully, outout);
	
	for(k = 0; k< neuron_size; k++)
		printf("softmax sonucu %d = %f ", k, outout[k]);
	printf("\n");

	flatten(size_im, inp_channel,  image_3d, output_flat);

	for(l = 0; l< size_im * size_im * inp_channel; l++)
		printf(" flatten[%d] = %f\n", l, output_flat[l]);

}
	
		
