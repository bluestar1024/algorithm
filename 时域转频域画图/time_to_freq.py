#!/usr/bin/env python
# -*-coding:utf-8 -*-
"""
Created on Wed Sep 22 22:26:02 2021

@author: DONG
"""

import csv
import numpy as np
import matplotlib.pyplot as plt
from numpy import fft
fileName = r'C:\00.csv'
ts = 0.018

def read_filedata(fileName,row,col):
    data = []
    first_data = []
    with open(fileName, 'r') as f:
        f_csv = csv.reader(f)
        for line in f_csv:
            data.append(line[col - 1])
    data = data[(row - 1):-1]
    data = list(map(float, data))
    for i in range(0,len(data)):
        if(i%3 == 0):
            first_data.append(data[i])
    length = len(first_data)
    return first_data,length

def time_to_freq(data,fs):
    fft_y = fft.fft(data)/length
    abs_y = np.abs(fft_y)
    odd = not int(length/2) == length/2
    if odd == True:
        freq = np.linspace(-fs/2,fs/2,length)
        half_freq = freq[int((length-1)/2):]
        l = int(length/2) + 1
        a = abs_y[l:]
        b = abs_y[0:l]
        abs_y = np.append(a,b)
        part_abs_y = abs_y[int((length+1)/2):] * 2
        half_abs_y = np.append(abs_y[int((length-1)/2)],part_abs_y)
    else:
        freq = np.linspace(-fs/(length-1)*length/2, fs/(length-1)*(length/2-1),length)
        half_freq = np.append(freq[int(length/2):],-freq[0])
        l = int(length/2)
        a = abs_y[l:]
        b = abs_y[0:l]
        abs_y = np.append(a,b)
        part_abs_y = abs_y[int(length/2+1):] * 2
        part1_abs_y = np.append(abs_y[int(length/2)],part_abs_y)
        half_abs_y = np.append(part1_abs_y,abs_y[0])
    return half_freq,half_abs_y

def show_figure(x,y):
    plt.figure()
    plt.clf()
    plt.plot(x,y,'.-')
    plt.grid()

plt.close('all')
data,length = read_filedata(fileName,17,5)
t = np.arange(0,length) * ts
show_figure(t,data)
freq,abs_y = time_to_freq(data,1/ts)
show_figure(freq,abs_y)