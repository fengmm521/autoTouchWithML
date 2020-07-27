#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-07-25 11:31:41
# @Author  : mage(gp@woodcol.com)
# @Link    : https://fengmm521.taobao.com
# @Version : $Id$

import os,sys
import shutil
import platform

def getSystype():
    #'Windows','Darwin','Linux'
    systype = platform.system()
    print(systype)
    return systype

#获取脚本路径
def cur_file_dir():
    pathx = sys.argv[0]
    tmppath,_file = os.path.split(pathx)
    if cmp(tmppath,'') == 0:
        tmppath = sys.path[0]
    #判断为脚本文件还是py2exe编译后的文件，如果是脚本文件，则返回的是脚本的目录，如果是py2exe编译后的文件，则返回的是编译后的文件路径
    if os.path.isdir(tmppath):
        return tmppath
    elif os.path.isfile(tmppath):
        return os.path.dirname(tmppath)

def cmp(a,b):
    return ((a>b)-(a<b))

#获取父目录
def GetParentPath(strPath):
    if not strPath:
        return None;
    lsPath = os.path.split(strPath);
    if lsPath[1]:
        return lsPath[0];
    lsPath = os.path.split(lsPath[0]);
    return lsPath[0];

def createTrain():
    trainpth = GetParentPath(os.getcwd()) + os.sep + 'outsource' + os.sep + 'train.txt'
    f = open(trainpth,'r')
    lines = f.readlines()
    f.close()
    outstr = ''
    for i,v in enumerate(lines):
        tmpv = v.replace('\n','').replace('\r','')
        outstr += os.getcwd() + os.sep + 'data' + os.sep + 'images' + os.sep + tmpv + '.jpg\n'
    outstr = outstr[:-1]
    savetrainpth = os.getcwd() + os.sep + 'data' + os.sep + 'train.txt'
    f = open(savetrainpth,'w')
    f.write(outstr)
    f.close()

def createTest():
    trainpth = GetParentPath(os.getcwd()) + os.sep + 'outsource' + os.sep + 'val.txt'
    f = open(trainpth,'r')
    lines = f.readlines()
    f.close()
    outstr = ''
    for i,v in enumerate(lines):
        tmpv = v.replace('\n','').replace('\r','')
        outstr += os.getcwd() + os.sep + 'data' + os.sep + 'images' + os.sep + tmpv + '.jpg\n'
    outstr = outstr[:-1]
    savetrainpth = os.getcwd() + os.sep + 'data' + os.sep + 'val.txt'
    f = open(savetrainpth,'w')
    f.write(outstr)
    f.close()

def getClasses():
    classespth = GetParentPath(os.getcwd()) + os.sep + 'outsource' + os.sep + 'classes.txt'
    f = open(classespth,'r')
    lines = f.readlines()
    f.close()
    ts = []
    for i,v in enumerate(lines):
        tmpv = v.replace('\n','').replace('\r','')
        if len(tmpv) > 0:
            ts.append(tmpv)
    return ts

def createNames():
    topth = os.getcwd() + os.sep + 'data' + os.sep + 'my.names'
    css = getClasses()
    outstr = ''
    for i,v in enumerate(css):
        outstr += v + '\n'
    outstr = outstr[:-1]
    f = open(topth,'w')
    f.write(outstr)
    f.close()

def copyImgAndLabel():
    if getSystype() != 'Windows':
        spth = GetParentPath(os.getcwd()) + os.sep + 'outsource' + os.sep + 'images'
        tpth = os.getcwd() + os.sep + 'data' + os.sep + 'images'
        cmd = '/bin/ln -s %s %s'%(spth,tpth)
        os.system(cmd)
        stph = GetParentPath(os.getcwd()) + os.sep + 'outsource' + os.sep + 'txt'
        tpth = os.getcwd() + os.sep + 'data' + os.sep + 'label'
        cmd = '/bin/ln -s %s %s'%(spth,tpth)
        os.system(cmd)

def backTrainData():
    if getSystype() != 'Windows':
        backuppth = os.getcwd() + os.sep + 'backup'
        backbackpth = os.getcwd() + os.sep + 'backup_back'
        if os.path.exists(backuppth):
            fnum = len(os.listdir(backuppth))
            if  fnum < 2 and fnum > 0:
                shutil.rmtree(backuppth)
                os.mkdir(backuppth)
            elif fnum > 2:
                if os.path.exists(backbackpth):
                    shutil.rmtree(backbackpth)
                cmd = '/bin/mv %s %s'%(backuppth,backbackpth)
                os.system(cmd)
                os.mkdir(backuppth)
        else:
            os.mkdir(backuppth)
    else:
        print('On windows does not with shell to backup data')

def createData():
    dpth = os.getcwd() + os.sep + 'data'
    if os.path.exists(dpth):
        shutil.rmtree(dpth)
    os.mkdir(dpth)
    createTrain()
    createTest()
    createNames()
    copyImgAndLabel()


from yolov3 import getYOLOV3CFG

def createCfgYOLOv3(cnum):
    yolov3cfg = getYOLOV3CFG(cnum)
    yocfgpth = os.getcwd() + os.sep + 'cfg' + os.sep + 'yolov3.cfg'
    f = open(yocfgpth,'w')
    f.write(yolov3cfg)
    f.close()

def createCFGFile():
    cfgdir = os.getcwd() + os.sep + 'cfg'
    if os.path.exists(cfgdir):
        shutil.rmtree(cfgdir)
    os.mkdir(cfgdir)
    cnum = len(getClasses())
    trainpth = os.getcwd() + os.sep + 'data' + os.sep + 'train.txt'
    valpth = os.getcwd() + os.sep + 'data' + os.sep + 'val.txt'
    namepth = os.getcwd() + os.sep + 'data' + os.sep + 'my.names'
    backuppth = os.getcwd() + os.sep + 'backup' + os.sep
    mydatastr = '''classes= %d
train  = %s
valid  = %s
names = %s
backup = %s

'''%(cnum,trainpth,valpth,namepth,backuppth)
    cfgdatapth = os.getcwd() + os.sep + 'cfg' + os.sep + 'my.data'
    f = open(cfgdatapth,'w')
    f.write(mydatastr)
    f.close()
    createCfgYOLOv3(cnum)


def main():
    createCFGFile()
    backTrainData()
    createData()

    

#测试
if __name__ == '__main__':
    main()
    
