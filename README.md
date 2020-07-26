# autoTouchWithML
 
自动将labelImg标注的voc xml数据转换为yolo的txt数据,同时将png或者其他格式的图片转换为jpg格式与xml一起保存为voc格式的数据目录

## labelImg数据转换工具使用方法
``` bash
python3 conventWithXmlAndTxt/createData.py labelImg标注路径 处理结果输出路径 图片后缀 xml文件的后缀(xml)
```
也可以使用下边方式
``` bash 
cd conventWithXmlAndTxt
./cdata labelImg标注文件目录 图片格式后缀字符
```
这个工具来生成yolo或者voc格式数据集在outsource目录下,以供darknet下的工具直接使用

上边的参数最后的xml主要是为了后边做一个把yolo的txt数据转换为voc的xml数据做的,但目前还不支持yolo的txt数据转为voc的xml,所以最后一个参数必须是xml

## darknet的YOLOv3预训练数据生成方法

在darknet目录下有一个python脚本createTrainAndTest.py

运行这个脚本可根据outsource目录下标注文件自动生成用于darknet训练的设置数据

运行
``` bash
cd darknet
python3 createTrainAndTest.py
```
即可生成用于darknet训练的数据

然后运行下边命令开始训练

``` bash
dk train darket项目下编译后的darkey文件路径 网上下载的yolov3的预训练模型文件路径
```

上边用到的darknet项目源码:

darket YOLOv3项目: https://github.com/pjreddie/darknet

darket YOLOV4项目: https://github.com/AlexeyAB/darknet

使用两个项目中的任一个darket编译后的工具都可以

darket的YOLOv3预训练模型文件(文件大小:154M)下载地址:

https://pjreddie.com/media/files/darknet53.conv.74

