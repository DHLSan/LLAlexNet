#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define input_channel 3
#define size 5
#define filt_sayisi 2  // number of filters
#define filt_size  2   // size of filter
#define stride  1
#define pad 0

int main(){


	float input[3][5][5] = {
							{{0.4, 0.75, 0.92, 0.563, 0.326}, {0.296, 0.561, -0.426, 0.783, 0.512}, {0.146, -0.565, -0.672, 0.26, 0.812}, {0.912, 0.234, 0.541, 0.145, -0.791}, {0.542, -0.671, -0.214, 0.742, 0.971}},
							{{0.126, 0.654, 0.767, -0.731, -0.323}, {0.121, 0.444, -0.678, 0.742, -0.167}, {0.663, -0.769, -0.812, 0.468, 0.641}, {0.131, -0.657, 0.127, -0.431, -0.324}, {0.655, 0.268, -0.246, -0.267, 0.532}},
							{{-0.263, 0.656, 0.784, -0.864, 0.123}, {-0.741, 0.731, -0.217, -0.016, 0.543}, {-0.154, 0.078, 0.542, -0.045, 0.067}, {0.742, 0.317, -0.555, -0.674, 0.135}, {0.01, 0.006, -0.663, 0.176, 0.643}}
							};
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


    // int channel = 3, size = 5, filt_sayisi = 2, filt_size = 2, stride = 1, pad = 0;
	float output_1[filt_sayisi][(size + (pad*2) - filt_size) / stride + 1][(size + (pad*2) - filt_size) / stride + 1];
	conv_upg2(input, bias_1, filtre_1, output_1);

	int i,j,k ;
	
	for (i=0;i<filt_sayisi;i++){
		for(j=0;j<(size + (pad*2) - filt_size) / stride + 1;j++){
			for(k=0;k<(size + (pad*2) - filt_size) / stride + 1;k++){
				printf("%f \n",output_1[i][j][k]);
			}
		}
	}
}
