@echo off

rmdir /s /q .vs
rmdir /s /q debug
rmdir /s /q serverlib\debug
rmdir /s /q serverlib\release
rem rmdir /s /q release
rem del release\*.exe
del release\*.pdb
del release\*.ipdb
del release\*.iobj
del release\*.lib
del release\*.exp

attrib -r -s -h *.ncb
attrib -r -s -h *.suo
attrib -r -s -h *.opensdf
attrib -r -s -h *.sdf
del *.ncb
del *.suo
del *.opensdf
del *.sdf

rmdir /s /q client\debug
rmdir /s /q client\release

rmdir /s /q server\debug
rmdir /s /q server\release

del client\*.user
del server\*.user
del serverlib\*.user