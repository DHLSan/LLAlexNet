#!/usr/bin/env python
# coding: UTF-8
'''''''''''''''''''''''''''''''''''''''''''''''''''''
   file name: testModel.py
   create time: 2017年03月31日 星期五 15时48分05秒
   author: Jipeng Huang
   e-mail: huangjipengnju@gmail.com
   github: https://github.com/hjptriplebee
'''''''''''''''''''''''''''''''''''''''''''''''''''''
import os
import urllib.request
import argparse
import sys
import alexnet
import cv2
import tensorflow as tf
import numpy as np
import caffe_classes

parser = argparse.ArgumentParser(description='Classify some images.')
parser.add_argument('-m', '--mode', choices=['folder', 'url'], default='folder')
parser.add_argument('-p', '--path', help='Specify a path [e.g. testModel]', default = 'testModel')
args = parser.parse_args(sys.argv[1:])

if args.mode == 'folder':
    #get testImage
    withPath = lambda f: '{}/{}'.format(args.path,f)
    testImg = dict((f,cv2.imread(withPath(f))) for f in os.listdir(args.path) if os.path.isfile(withPath(f)))
elif args.mode == 'url':
    def url2img(url):
        '''url to image'''
        resp = urllib.request.urlopen(url)
        image = np.asarray(bytearray(resp.read()), dtype="uint8")
        image = cv2.imdecode(image, cv2.IMREAD_COLOR)
        return image
    testImg = {args.path:url2img(args.path)}

# noinspection PyUnboundLocalVariable
if testImg.values():
    #some params
    dropoutPro = 1
    classNum = 1000
    skip = []

    imgMean = np.array([104, 117, 124], np.float)
    x = tf.Variable(tf.zeros([1, 227, 227, 3],dtype=tf.float32))

    model = alexnet.alexNet(x, dropoutPro, classNum, skip)
    score = model.fc3
    konvi = tf.squeeze(model.conv1)
    softmax = tf.nn.softmax(score)

    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        model.loadModel(sess)
        variables = tf.trainable_variables()
       
        np.set_printoptions(threshold=sys.maxsize)
        np.set_printoptions(formatter={'float_kind':'{:.6f}'.format})

        file = open("weight_2_yuvarlama_222.txt", "w")


        file.write("{0}".format(sess.run(variables[2])))




        
        #file.write("{0}".format(sess.run(variables[10][9215][0])))

        #vector = np.vectorize(np.float)
        #x = (sess.run(variables[0]))
        #x = vector(x)
        #file.write("%.7f" % x)
        #file.write("%0.10f" % (sess.run(variables[0])))

        #file.close()

         #print("Weight matrix: {0}".format(sess.run(variables)))
        
        # textfile = open("weight.txt", "w")
        # for element in variables:
        #     textfile.write(element)
        # textfile.close()

        
        # file = open("weight_2.txt", "w")
        # for element in variables:
        #     #str_dictionary = repr(element)
        #     file.write("{0}".format(sess.run(element[2])))
        # file.close()

        # file = open("weight_3.txt", "w")
        # for element in variables:
        #     #str_dictionary = repr(element)
        #     file.write("{0}".format(sess.run(element[3])))
        # file.close()

        
        
       

        # with tf.variable_scope("conv1", reuse=True):
        #     w = tf.get_variable("conv1")
        #     print(w.eval(session=sess))
        #print(sess.run(tf.get_variable('conv1', (None, 11, 11, 96))))
        #print(sess.run(tf.get_variable('fc7', (4096))))
        # var = [v for v in tf.trainable_variables() if v.name == 'conv1']
        # print(var)    

        #print(alexnet.layers[0].weights)
        # 
        #q = tf.Variable("conv1")
        # q = tf.get_variable("conv1", shape = [11, 11, 3, 96])   
        # print(model.eval(session=sess))

        for key,img in testImg.items():
            #img preprocess
            
            #print("image degerleri_img", img)
            resized = cv2.resize(img.astype(np.float), (227, 227)) - imgMean
            maxx = np.argmax(sess.run(softmax, feed_dict = {x: resized.reshape((1, 227, 227, 3))}))
            res = caffe_classes.class_names[maxx]

            font = cv2.FONT_HERSHEY_SIMPLEX
            cv2.putText(img, res, (int(img.shape[0]/3), int(img.shape[1]/3)), font, 1, (0, 255, 0), 2)
            print("{}: {}\n----".format(key,res))
            cv2.imshow("demo", img)
            cv2.waitKey(0)
