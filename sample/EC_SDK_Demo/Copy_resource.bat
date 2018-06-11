@echo off

rem -----------------------------------------------------
rem         拷贝resource到Bin_vs2012\Debug目录下
rem -----------------------------------------------------
rmdir /s/q .\Bin_vs2012\Debug\audio
rmdir /s/q .\Bin_vs2012\Debug\face
rmdir /s/q .\Bin_vs2012\Debug\image

mkdir .\Bin_vs2012\Debug\audio
mkdir .\Bin_vs2012\Debug\face
mkdir .\Bin_vs2012\Debug\image

xcopy .\APP_UI\res\audio\*    .\Bin_vs2012\Debug\audio\   /s /y
xcopy .\APP_UI\res\face\*     .\Bin_vs2012\Debug\face\    /s /y
xcopy .\APP_UI\res\image\*    .\Bin_vs2012\Debug\image\   /s /y

rem -----------------------------------------------------
rem         拷贝resource到Bin_vs2015\Debug目录下
rem -----------------------------------------------------
rmdir /s/q .\Bin_vs2015\Debug\audio
rmdir /s/q .\Bin_vs2015\Debug\face
rmdir /s/q .\Bin_vs2015\Debug\image

mkdir .\Bin_vs2015\Debug\audio
mkdir .\Bin_vs2015\Debug\face
mkdir .\Bin_vs2015\Debug\image

xcopy .\APP_UI\res\audio\*    .\Bin_vs2015\Debug\audio\   /s /y
xcopy .\APP_UI\res\face\*     .\Bin_vs2015\Debug\face\    /s /y
xcopy .\APP_UI\res\image\*    .\Bin_vs2015\Debug\image\   /s /y

rem -----------------------------------------------------
rem         拷贝resource到Bin_vs2012\Release目录下
rem -----------------------------------------------------
rmdir /s/q .\Bin_vs2012\Release\audio
rmdir /s/q .\Bin_vs2012\Release\face
rmdir /s/q .\Bin_vs2012\Release\image

mkdir .\Bin_vs2012\Release\audio
mkdir .\Bin_vs2012\Release\face
mkdir .\Bin_vs2012\Release\image

xcopy .\APP_UI\res\audio\*    .\Bin_vs2012\Release\audio\   /s /y
xcopy .\APP_UI\res\face\*     .\Bin_vs2012\Release\face\    /s /y
xcopy .\APP_UI\res\image\*    .\Bin_vs2012\Release\image\   /s /y

rem -----------------------------------------------------
rem         拷贝resource到Bin_vs2012\Release目录下
rem -----------------------------------------------------
rmdir /s/q .\Bin_vs2015\Release\audio
rmdir /s/q .\Bin_vs2015\Release\face
rmdir /s/q .\Bin_vs2015\Release\image

mkdir .\Bin_vs2015\Release\audio
mkdir .\Bin_vs2015\Release\face
mkdir .\Bin_vs2015\Release\image

xcopy .\APP_UI\res\audio\*    .\Bin_vs2015\Release\audio\   /s /y
xcopy .\APP_UI\res\face\*     .\Bin_vs2015\Release\face\    /s /y
xcopy .\APP_UI\res\image\*    .\Bin_vs2015\Release\image\   /s /y