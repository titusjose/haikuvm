@echo off
echo %1 %2 %3 %4 %5

set "NXJ_COMMAND=%~n0"
set "NXJ_HOME=%~dp0\..\..\..\.."

cd %NXJ_HOME%
if not exist junitCProject cd junitCProject
cd junitCProject
if exist haikuVM rmdir /s /q haikuVM
if exist haikuJava rmdir /s /q haikuJava
if exist utility rmdir /s /q utility
if exist target rmdir /s /q target
if exist haikuC rmdir /s /q haikuC
if exist tutorials rmdir /s /q tutorials
if not exist tutorials mkdir tutorials
copy ..\myCProject\tutorials\* tutorials


goto %1
goto eof

:experiment 
call %NXJ_HOME%\bin\haiku --Config %2 --Mode %3 %5
goto eof

:develop_link_upload
set TJAVAFILE=%5
call SET TJAVAFILE=%%TJAVAFILE:.=/%%

if exist %NXJ_HOME%\haikuBench\src\main\java\%TJAVAFILE%.java ( 
  set JAVAFILE=%NXJ_HOME%\haikuBench\src\main\java\%TJAVAFILE%
) else if exist %NXJ_HOME%\examples\src\main\java\%TJAVAFILE%.java (
  set JAVAFILE=%NXJ_HOME%\examples\src\main\java\%TJAVAFILE%
) else (
  set JAVAFILE=%TJAVAFILE%
)
 
if "%2" == "junit.cygwin" (
	set PATH=D:\cygwin\usr\local\bin;D:\cygwin\usr\bin;D:\cygwin\bin;%PATH%
	%NXJ_HOME%\bin\haiku -v --Config %2 --Mode %3 %JAVAFILE%
) else (
	call %NXJ_HOME%\bin\haiku -v --Config %2 --Mode %3 %JAVAFILE%
)

goto eof

:xdevelop_link_upload 
call %NXJ_HOME%\bin\haikulink --Config %2 --Mode %3 -o junitCProject.hex --bootclasspath ../bootstrap/bin;../haikuRT\bin;../lib/nxt/classes.jar --classpath ../haikuBench/bin;../examples/bin;../gattaca/bin %5
call %NXJ_HOME%\bin\haikuupload                      junitCProject.hex
goto eof

:link_upload 

rem call %NXJ_HOME%\bin\haikulink -v --Config %2 --Mode %3 -o junitCProject.hex C:\haikuVM\examples\src\main\java\arduino\tutorial\BlinkWithThread
call %NXJ_HOME%\bin\haikulink -v --Config %2 -o junitCProject.hex --bootclasspath D:\Entwicklung\haikuVM\lib\haikuvm\bootstrap.jar;D:\Entwicklung\haikuVM\lib\haikuvm\haikuRT.jar;D:\Entwicklung\haikuVM\lib\nxt\classes.jar --classpath ../haikuBench/bin;../examples/bin;../gattaca/bin %5
call %NXJ_HOME%\bin\haikuupload                      junitCProject.hex
goto eof

:link_upload_InternalExceptionThrow 

call %NXJ_HOME%\bin\haikulink -v --Config %2 --Mode %3 --Config:InternalExceptionThrow 1 --Config:InternalExceptionEnable "NullPointerException|NoSuchMethodError|OutOfMemoryError|ClassCastException|VirtualMachineError|ArrayIndexOutOfBoundsException|StackOverflowError" -o junitCProject.hex --bootclasspath ../bootstrap/bin;../haikuRT\bin;../lib/nxt/classes.jar --classpath ../haikuBench/bin;../examples/bin;../gattaca/bin %5
call %NXJ_HOME%\bin\haikuupload                      junitCProject.hex
goto eof


:optimize_link_upload 

java -jar %NXJ_HOME%\lib\pc\proguard.jar -keep class %5 { public static void main(java.lang.String[]);} @%NXJ_HOME%\lib\pc\myproguard.conf

call %NXJ_HOME%\bin\haikulink -v --Config %2 --Mode %3 -o junitCProject.hex --bootclasspath ..\lib\pc\optimized.jar %5
call %NXJ_HOME%\bin\haikuupload                      junitCProject.hex
goto eof


:eof
