import time
from typing import Counter
import serial
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
from matplotlib import animation


port = serial.Serial(port="COM7", baudrate=115200)
iter = 0
vect = []
while 1:
    iter += 1
    now = datetime.now()
    output = b""
    while((datetime.now()-now).seconds < 1):
        output = output + port.read()
    global s
    # print(output)
    s = 0
    for i in output:
        s = s+i
    print(s)
    s = s/100
    if(s > 210):
        print(s)
    elif(s < 210):
        print("0")
        s = 0
    plt.scatter(iter, s)
    plt.pause(0.01)
plt.show()
