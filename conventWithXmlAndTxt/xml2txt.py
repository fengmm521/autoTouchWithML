import xml.etree.ElementTree as ET
import pickle
import os,sys
from os import listdir, getcwd
from os.path import join

import fileTool

# sets=[('2018', 'train')]

# classes = ["s", "r", "f"]


def convert(size, box):
    dw = 1./(size[0])
    dh = 1./(size[1])
    x = (box[0] + box[1])/2.0 - 1
    y = (box[2] + box[3])/2.0 - 1
    w = box[1] - box[0]
    h = box[3] - box[2]
    x = x*dw
    w = w*dw
    y = y*dh
    h = h*dh
    return (x,y,w,h)

def convert_annotation(in_file,out_file,classes,isHeaveClas):
    tree=ET.parse(in_file)
    root = tree.getroot()
    size = root.find('size')
    w = int(size.find('width').text)
    h = int(size.find('height').text)
    ocls = []
    outstr = ''
    for obj in root.iter('object'):
        difficult = obj.find('difficult').text
        cls = obj.find('name').text
        if isHeaveClas:
            if not classes:
                print('the classes is empty...')
                return None
            if cls not in classes or int(difficult)==1:
                continue
            cls_id = classes.index(cls)  
            xmlbox = obj.find('bndbox')
            b = (float(xmlbox.find('xmin').text), float(xmlbox.find('xmax').text), float(xmlbox.find('ymin').text), float(xmlbox.find('ymax').text))
            bb = convert((w,h), b)
            outstr += str(cls_id) + " " + " ".join([str(a) for a in bb]) + '\n'
            # out_file.write(str(cls_id) + " " + " ".join([str(a) for a in bb]) + '\n')
            ocls.append(cls)
        else:
            cls_id = 0
            if cls not in classes and int(difficult) == 0:
                classes.append(cls)
                cls_id = len(classes) - 1
            elif int(difficult) == 1:
                continue
            else:
                cls_id = classes.index(cls)
            xmlbox = obj.find('bndbox')
            b = (float(xmlbox.find('xmin').text), float(xmlbox.find('xmax').text), float(xmlbox.find('ymin').text), float(xmlbox.find('ymax').text))
            bb = convert((w,h), b)
            outstr += str(cls_id) + " " + " ".join([str(a) for a in bb]) + '\n'
            ocls.append(cls)
    f = open(out_file,'a')
    f.write(outstr)
    f.close()
    return ocls


def findClassInXMLFileName(in_file,classes):
    tree=ET.parse(in_file)
    root = tree.getroot()
    for obj in root.iter('object'):
        difficult = obj.find('difficult').text
        cls = obj.find('name').text
        if cls in classes:
            return True
    return False


def main(indir,outdir):
    wd = getcwd()
    # for year, image_set in sets:
    if not os.path.exists(outdir):
        os.makedirs(outdir)
    image_ids = open('VOCdevkit/VOC%s/ImageSets/Main/%s.txt'%(year, image_set)).read().strip().split()
    list_file = open('%s_%s.txt'%(year, image_set), 'w')
    for image_id in image_ids:
        list_file.write('%s/VOCdevkit/VOC%s/JPEGImages/%s.jpg\n'%(wd, year, image_id))
        convert_annotation(year, image_id)
    list_file.close()

def test():
    print(getcwd())

if __name__ == '__main__':
    test()
    args = sys.argv
    indir = None
    outdir = None
    if len(args) == 2:
        indir = args[1]
        outdir = args[1] + os.sep +'out'
    elif len(args) == 3:
        indir = args[1]
        outdir = args[2]
    else:
        print('use pwd dir')
    main(indir,outdir)

# os.system("cat 2007_train.txt 2007_val.txt 2012_train.txt 2012_val.txt > train.txt")
# os.system("cat 2007_train.txt 2007_val.txt 2007_test.txt 2012_train.txt 2012_val.txt > train.all.txt")

