# LLAlexNet

## **LLAlexNet: CNN Accelerator for Low Latency Cloud Integration**

**A repository of my Xilinx Open Hardware 2021 submission including LLAlexNet on ZEDBOARD ZYNQ-7000 SOC Development Boards, C source code and projects for Vivado HLS and projects for Vivado.**


- _**University Name: Eskisehir Technical University**_

### Participant:

- **Participants:** Arif Berkay Okumuş, Mehmet Selim Nazlı

- **Participants e-mail:** aokumus26@gmail.com ,sesleglinmnz98@hotmail.com

- **Supervisor name:** Asst. Prof. İsmail SAN

- **Supervisor e-mail:** isan@eskisehir.edu.tr

### Link to Youtube Video: 



### Brief description of project:
In this Github repo, it is aimed to write the Alexnet architecture in C code by ourselves and accelerate it using the Zynq-7000 System On Chip device. To write Alexnet architecture in C code, 3 Github folders have been created these are Preparation stages of Alexnet C code, Alexnet Python and Full Alexnet folders. The preparation stages of Alexnet C code folder contains the codes and tests written during the construction of the layers, activation functions and other necessary functions required for the creation of the architecture.

The Alexnet Python folder contains the prepared python code of the Alexnet architecture, and how to run this code is explained in the Readme.md file in the file. In this section, we have transferred the trained weight files to the txt file with a few lines of code that we added to the python file.

In the Full Alexnet folder, there is a completely written version of the Alexnet architecture in C code. In addition, there is a function written to use the weights transferred to the txt file in C code. In the full_alexnet_code.c file, the entire architecture is ready to run, but there is no training in the code. Therefore, the trained weight parameters must be given to the filter, but it can work correctly in this way. As stated before, in order to perform this operation, transferring from python to txt file is performed. However, the Alexnet architecture is divided into 2 parts after the first convolution layer and the operations continue. For this reason, when we try to get the weights, we can only pull half of the weights after the first convolution layer. Despite our great efforts, we could not succeed. Therefore, unfortunately, we could not find the opportunity to test whether the architecture works correctly.

In the future, we aim to test the accuracy of our architecture by overcoming this point where we are stuck. In addition, we aim to have training in C code by adding the necessary operations for the training phase into our C code.

## References
[1]	Bjerge, K., Schougaard, J., & Larsen, D. E. (2020). A generic and efficient convolutional neural network accelerator using HLS for a system on chip design. arXiv preprint arXiv:2004.13075.
[2]	Rongshi, D., & Yongming, T. (2019, June). Accelerator Implementation of Lenet-5 Convolution Neural Network Based on FPGA with HLS. In 2019 3rd International Conference on Circuits, System and Simulation (ICCSS) (pp. 64-67). IEEE.
[3]	Zhang, C., Li, P., Sun, G., Guan, Y., Xiao, B., & Cong, J. (2015, February). Optimizing fpga-based accelerator design for deep convolutional neural networks. In Proceedings of the 2015 ACM/SIGDA international symposium on field-programmable gate arrays (pp. 161-170).

