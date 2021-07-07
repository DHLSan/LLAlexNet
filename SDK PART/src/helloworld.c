/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "xil_io.h"
#include "xparameters.h"
#include "xil_types.h"
#include "xconv_upg2.h"
#include "xconv_upg2_hw.h"

#include "xtime_l.h"
#include "xtmrctr.h"

XConv_upg2 conv;
XConv_upg2_Config *conv_config;
float * bias =      (float *) (0x43C00010);
int * control =     (int *) (0x43C10000);
float * filter  =    (float *) (0x43C20080);
float * input  =     (float *) (0x43C30200);
float * output  =    (float *) (0x43C40080);


float input1[75] = {0.4, 0.75, 0.92, 0.563, 0.326,0.296, 0.561, -0.426, 0.783, 0.512, 0.146, -0.565, -0.672, 0.26, 0.812, 0.912, 0.234, 0.541, 0.145, -0.791, 0.542, -0.671, -0.214, 0.742, 0.971, 0.126, 0.654, 0.767, -0.731, -0.323, 0.121, 0.444, -0.678, 0.742, -0.167, 0.663, -0.769, -0.812, 0.468, 0.641, 0.131, -0.657, 0.127, -0.431, -0.324, 0.655, 0.268, -0.246, -0.267, 0.532, -0.263, 0.656, 0.784, -0.864, 0.123, -0.741, 0.731, -0.217, -0.016, 0.543, -0.154, 0.078, 0.542, -0.045, 0.067 , 0.742, 0.317, -0.555, -0.674, 0.135, 0.01, 0.006, -0.663, 0.176, 0.643};




float filter1 [24] = {  0.250, 0.943, -0.145, 0.136,
						0.521, 0.235, 0.741, -0.631,
						0.706, 0.402, -0.294, 0.707,
						0.843, -0.312, 0.189, 0.576,
						0.542, 0.109, -0.641, 0.403,
						0.410, 0.376, -0.124, -0.265

					 };

float bias1[2] = {0.823, 0.634};







void initialize(){


	int status;

	// Initialize ipcore
	conv_config = XConv_upg2_LookupConfig(XPAR_CONV_UPG2_0_DEVICE_ID);
		if(!conv_config){
			printf("Error loading config\n");
						}
	status= XConv_upg2_CfgInitialize(&conv, conv_config);
		if(status != XST_SUCCESS){
			printf("Error initializing for convolution ýp\n");
							 }

	xil_printf("-- IP Core initialized --\r\n");


}

void value_assign(){
	int i,j,k ;

	for (i=0; i<75; i++){
		input[i]=input1[i];
	}
	for (j=0; j<24; j++){
			filter[j]=filter1[j];
		}
	for (k=0; k<2; k++){
			bias[k]=bias1[k];
		}

}



int main()
{
	//Xil_DCacheDisable();
	float elapsed_time,elapsed_whole;
	XTime tStart,tEnd,twholeStart,twholeEnd;
	XTmrCtr pPerfTimer;
	u32 u32Cycles;
	u32 elapsed;


		//1. Initialize the timer functions:
		XTmrCtr_Initialize(&pPerfTimer, XPAR_TMRCTR_0_DEVICE_ID);

		//2. Set the timer reset value:
		XTmrCtr_SetResetValue(&pPerfTimer, 0, 0x00000000);

	XTime_GetTime(&twholeStart);
	sleep(1);
	XTime_GetTime(&twholeEnd);
	elapsed_whole= (twholeEnd-twholeStart) * 0.000000003;
	printf("elapsed sleep(1) time %f \n",elapsed_whole);

	init_platform();
    initialize();
    value_assign();

    control[0] |= 0x1;

    XTime_GetTime(&tStart);

    while((control[0] & 0x2) != 0x2);

    XTime_GetTime(&tEnd);
    elapsed_time= (tEnd-tStart) * 0.000000003;
    printf("Elapsed time %f \n",elapsed_time);

    for(int a=0; a<32; a++){
    	printf("%f \n",output[a]);
    }



    cleanup_platform();
    return 0;
}
