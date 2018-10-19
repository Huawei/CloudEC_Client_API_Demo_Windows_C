此目录结构如下：
APP_UI：Demo的界面代码及资源。

CI：拷贝脚本，用于将sdk压缩包中的.dll、.lib、.h文件拷贝Debug和Release目录下。

SDK：包含三个文件夹：dll、include、lib。其中dll文件夹用于存放sdk压缩包中的.dll文件，include文件夹用于存放sdk压缩包中的.h文件，lib文件夹用于存放sdk压缩包中的.lib文件。

Service：业务处理代码。

EC_SDK_Demo_vs2012.sln ： demo的解决方案，使用vs2012编译。

EC_SDK_Demo_vs2015.sln :  demo的解决方案，使用vs2015编译。


Demo运行步骤：
1、先从support网站获取eSDK CloudEC的SDK开发包，并将开发包解压缩后拷贝至SDK文件夹下。
2、选择EC_SDK_Demo_vs2012.sln或者EC_SDK_Demo_vs2015.sln进行代码开发。