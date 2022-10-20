from concurrent.futures import thread
from time import thread_time
from tokenize import Number
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import serial as sr
import tkinter as tk
import numpy as np
import orjson
import threading


def plot(xAxis,yAxis):
    plt.cla()
    plt.ylim([0,4200])  
    axis[0,0].plot(xAxis[-100:],yAxis[-100:])
    plt.pause(0.001)



s = sr.Serial('COM3', 512000, timeout=0, parity=sr.PARITY_NONE, rtscts=1)
s.reset_input_buffer()
figure, axis = plt.subplots(2, 2)
plt.close("all")
plt.ion()
plt.show()

def main():
    data = []
    xAxis = []
    yAxis = []
    dyAxis = []
    i = 0
    while True:
        try:
            if i>=10:
                i=0
                threading.Thread(target=plot(xAxis,yAxis)).start()
            a = s.readline().decode().strip().split(",")
        except:
            a[0]= None
            print("error: ")
        if a[0] != '':
            yAxis.append(int(a[0]))
            xAxis.append(np.uint(a[1]))
            i += 1

if __name__ == "__main__":
    main() 