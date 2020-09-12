#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os,sys
import serial
import time
import json

def readcom(t):
    n = t.inWaiting()
    while n<=0:
        time.sleep(0.001)
        n = t.inWaiting()
    pstr = t.read(n)
    print(str(pstr) + ':' + str(time.time()))

def sendcmd(t,cmd):
    sendstr = cmd
    if cmd[-1] != '\r':
        sendstr += '\r'
    print(sendstr)
    s = t.write(sendstr)
    t.flush()


def test():
    # dev = 'com5'  #这里请写你电脑正确的串口,windows请写"com数字"这样的端口
    dev = '/dev/cu.usbserial-14120'
    # t = serial.Serial('com5',115200,timeout=1) #115200
    # t.open()
    t = serial.Serial(dev,'115200',timeout=1)
    if t:
        print(t.name)
        print(t.port)
        print(t.baudrate)           #波特率
        print(t.bytesize)           #字节大小
        print(t.parity)             #校验位N－无校验，E－偶校验，O－奇校验
        print(t.stopbits)           #停止位
        print(t.timeout)            #读超时设置
        print(t.writeTimeout)       #写超时
        print(t.xonxoff)            #软件流控
        print(t.rtscts)             #硬件流控
        print(t.dsrdtr)             #硬件流控
        print(t.interCharTimeout)   #字符间隔超时
        print('-'*10)
        # n = t.write('x')
        time.sleep(5)
        readcom(t)
        while True:
            readcom(t)   
        t.close()
    else:
        print('串口不存在')
if __name__ == '__main__':
    # comtool()
    test()