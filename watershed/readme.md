#### 图像分割处理流程

（1）将白色背景编程黑色，为后面变换做准备；

（2）使用filter2D与拉普拉斯算子实现图像对比度提高；

（3）转为二值图像通过threshold；

（4）距离变换；

（5）对距离变换结果进行归一化到[0-1]之间；

（6）使用阈值，再次二值化，得到标记；

（7）腐蚀得到每个peak；

（8）发现轮廓；

（9）绘制轮廓；

（10）分水岭变换；

（11）对每个分割区域着色输出结果；

![原图](https://github.com/cheerTT/python-project-practise/raw/master/watershed/img/1550387581921.png)
![分割图](https://github.com/cheerTT/python-project-practise/raw/master/watershed/img/1550387601131.png)