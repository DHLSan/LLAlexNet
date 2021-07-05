#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void take_weight_convolution(int channel1, int channel2, int size, 
							 float filtre[channel1][channel2][size][size], char txt_name[23]){
	memset(filtre, 0, channel1 * channel2 * size * size * sizeof(float));
	float kontrol[1] = {0};
	int i = 0, j = 0, k = 0, l = 0, count = 0, temp = 0, temp2 = 0, sayac = 0;
	FILE * fp;
	char ch;
	
	if(fp = fopen(txt_name, "r")) {
        while ((ch = fgetc(fp)) != EOF ) {
			fscanf(fp, "%f", &kontrol[0]) != EOF;     // Assignment to kontrol
			if(kontrol[0] != 0){                      // if kontrol value is different from 0
            	filtre[i][j][k][l] = kontrol[0];
				++count;                			  // number transfer to nums value
				++i;
				if(i == channel1){
					i = 0;
					j = j +1 ;
					if(j == channel2){
						j = 0;
						k = k+1;
						if(k == size){
							k = 0;
							l = l+1;
						}
					}
				}
            	kontrol[0] = 0;
        	}
        	else{            // To avoid errors when the number 0 in the .txt file
        		if(ch == 32){            			// if the number is 0 and not equal to the character "["
        			filtre[i][j][k][l] = kontrol[0];	// goes in and assigns the number 0
        			++count;                // number transfer to nums value
					++i;
					if(i == channel1){
						i = 0;
						j = j +1 ;
						if(j == channel2){
							j = 0;
							k = k+1;
							if(k == size){
								k = 0;
								l = l+1;
							}
						}
					}
            		kontrol[0] = 0;
				}		
			}
		}
        fclose(fp);
    }	
}


int main(void)
{

	int l = 0, k = 0, j = 0, i = 0, sayac = 0;
	
	int channel1 = 256, channel2 = 48, size = 5;
	int channel1_1 = 96, channel2_1 = 3, size_1 = 11;
	float nums[channel1][channel2][size][size];
	char f_open[23] = "weight_2_yuvarlama.txt";
	
	take_weight_convolution(channel1, channel2, size, nums, f_open);
	
	printf("num = %f", nums[0][0][0][0] );
for(l = 0; l <= 4; l++){
	for(k = 0; k <= 4 ; k++){
    	for(j = 0; j <= 47 ; j++){
    		for (i = 0; i <=255; i++){
        		printf("num[%d][%d][%d][%d] = %f     ", i,j,k,l, nums[i][j][k][l]);
        		sayac++;
        		if(sayac == 3){
        			sayac = 0;
        			printf("\n");
				}
			}
		}
	}
}

	
}

