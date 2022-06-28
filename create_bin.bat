rd /S /Q .\bin
mkdir .\bin
cd bin
xcopy .\..\birthdays.db
xcopy .\..\..\build-Birthdays-Desktop_Qt_6_2_2_MSVC2019_64bit-Release\release\Birthdays.exe
c:\Qt\6.2.4\msvc2019_64\bin\windeployqt.exe Birthdays.exe
