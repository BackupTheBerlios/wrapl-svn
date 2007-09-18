@echo off
mkdir bin
copy ..\..\..\bin\riva.exe bin\riva.exe
copy ..\..\..\bin\libconfuse.dll bin\libconfuse.dll
copy ..\..\..\bin\libgc.dll bin\libgc.dll
mkdir lib
xcopy /S ..\..\..\lib\* lib\*
makensis /DVERSION=%1 package.nsi
rmdir /Q /S bin
rmdir /Q /S lib