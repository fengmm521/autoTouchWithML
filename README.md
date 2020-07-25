# autoTouchWithML
 
自动将labelImg标注的voc xml数据转换为yolo的txt数据,同时将png或者其他格式的图片转换为jpg格式与xml一起保存为voc格式的数据目录

## 使用方法
``` bash
python3 conventWithXmlAndTxt/createData.py labelImg标注路径 处理结果输出路径 图片后缀 xml文件的后缀(xml)
```

上边的参数最后的xml主要是为了后边做一个把yolo的txt数据转换为voc的xml数据做的,但目前还不支持yolo的txt数据转为voc的xml,所以最后一个参数必须是xml