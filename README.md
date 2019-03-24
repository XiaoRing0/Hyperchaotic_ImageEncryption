# Hyperchaotic_ImageEncryption
基于openCV与MFC的超混沌图像加密软件，openCV提供图像读取、存储功能，通过MFC构建人机交互界面

编译环境为Visual Studio Community 2017 版本号: 15.9.8

OpenCV库版本为: opencv-3.4.1-vc14_vc15

## 概览
<!-- vim-markdown-toc GFM -->
* [使用说明](#使用说明)
* [算法原理](#算法原理)
* [展望](#展望)
* [题外之言](#题外之言)
<!-- vim-markdown-toc -->


## 使用说明
* 若用户想使用该项目直接编译
  * Download全部文件，将vs项目文件Encryption_MFC.sln关于openCV的配置，例如包含目录等修改为自身openCV所在的目录。关于openCV的配置，在此不再赘述
  * 主目录提供了一张标准测试图，编译运行之后，可直接使用该图进行测试
![Image text](https://github.com/XiaoRing0/Hyperchaotic_ImageEncryption/raw/master/lena512color.tiff"lena_512*512")
* 若用户想自行构建MFC项目，配置openCV，那理解代码即可
 * 该项目核心代码为`Hyperchaotic_ImageEncryption/Encryption_MFC/`目录下，三个核心文件：`Encryption_MFC.h`, `Encryption_MFCDlg.h`, `Encryption_MFCDlg.cpp`
  * `Encryption_MFC.h`包含了openCV头文件，宏定义
  * `Encryption_MFCDlg.h`包含了对话框类中的图像数据成员变量、进度条成员变量、所有控件按钮的响应成员函数的声明及行变换的移位函数模板
  * `Encryption_MFCDlg.cpp`包含了默认的MFC初始化函数以及所有成员函数的实现、相关按钮的逻辑控制
* 若用户想直接使用该软件，不想繁琐地配置openCV
 * 直接将openCV的动态链接库复制到`C:\Windows\System32`目录下
 * 受于GitHub文件大小限制，两个动态链接库的网盘地址为：[](https://pan.baidu.com/s/11jDEUONrjLs1iKbO1iwVxg), 提取码：`ejgj`  


## 算法原理
* 该算法的混沌序列有一定的数学背景，主要利用混沌的伪随机、非周期及确定性

* 此处使用的是超混沌系统，相较于混沌，其拓扑更为复杂

* 结合混沌的基础上，考虑图像的空间分布，采用图像的置乱与扩散，并将置乱与扩散同时进行

* 算法简要流程为：采集图像信息与密钥一起作为超混沌迭代初值，迭代超混沌序列

* 加密时，遍历3维图像矩阵，利用超混沌序列进行行变换（置乱），异或像素值（扩散），再次列变换与异或

* 解密的过程为加密的反操作

## 展望
* 此项目操作的是RGB彩色图像，可简化为二维灰度图像（灰度图像过于简单，但能较好地进行算法性能评估）

* 该项目可进行下一步拓展，通过RGB与YUV色彩空间转换原理，将视频传输的YUV数据转换成RGB数据进行加密

* C，C++良好的跨平台兼容性可使其能够拓展至嵌入式等平台，拓展适用于实时、非实时的视频加密



## 题外之言

总想透过你眼睛

去找寻

最深处的坚冰

没想到 

最后却闯进

一整本

诗书的宁静
