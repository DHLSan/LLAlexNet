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
	/*
	int channel1 = 96, channel2 = 3, size = 11;
	float nums[channel1][channel2][size][size];
	memset(nums, 0, channel1 * channel2 * size * size * sizeof(float));
	float kontrol[1] = {0};
    int i = 0;
    int j = 0;
    int k = 0;  
    int l = 0;
    int count = 0;
    int temp = 0;
    int temp2 = 0;
    FILE * fp;
 	char ch;
 	int sayac = 0;
 	
 	char f_open[23] = "weight_0_yuvarlama.txt";
 	
    if(fp = fopen(f_open, "r")) {
        while ((ch = fgetc(fp)) != EOF ) {
        //printf("%f\n", ch);	
		fscanf(fp, "%f", &kontrol[0]) != EOF;     // kontrol e atama yap�ld�
        	//printf("%d \n",ch);
		if(kontrol[0] != 0){                      // kontrol de�eri 0 dan farkl� ise
            nums[i][j][k][l] = kontrol[0];
			++count;                // nums de�erine aktar�l�r say�
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
        else            // txt dosyas�nda 0 say�s� oldu�unda hata olmamas� i�in
        {
        	if(ch == 32){            			// say� 0 ise ve "[" karakterine e�it de�ilse
        		nums[i][j][k][l] = kontrol[0];	// i�eri girer ve 0 say�s�n� atama yapar
        		++count;                // nums de�erine aktar�l�r say�
			++i;
			if(i == 96){
				i = 0;
				j = j +1 ;
				if(j == 3){
					j = 0;
					k = k+1;
					if(k == 11){
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
    */
    
	//temp = j;
	//temp2 = k;
	//printf("k = %d && j = %d  &&  count = %d\n", k,j,count);
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

