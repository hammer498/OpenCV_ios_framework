@ECHO OFF

:: enable command extensions
VERIFY BADVALUE 2>NUL
SETLOCAL ENABLEEXTENSIONS || (ECHO Unable to enable command extensions. & EXIT \B)

:: build environment
SET SOURCE_DIR=%cd%
IF EXIST .\android.toolchain.cmake (SET BUILD_OPENCV=1) ELSE (SET BUILD_OPENCV=0)
IF EXIST .\jni\nul (SET BUILD_JAVA_PART=1) ELSE (SET BUILD_JAVA_PART=0)

:: load configuration
PUSHD %~dp0
SET SCRIPTS_DIR=%cd%
IF EXIST .\wincfg.cmd CALL .\wincfg.cmd
POPD

:: inherit old names
IF NOT DEFINED CMAKE SET CMAKE=%CMAKE_EXE%
IF NOT DEFINED MAKE SET MAKE=%MAKE_EXE%

:: defaults
IF NOT DEFINED BUILD_DIR SET BUILD_DIR=build
IF NOT DEFINED ANDROID_ABI SET ANDROID_ABI=armeabi-v7a
SET OPENCV_BUILD_DIR=%SCRIPTS_DIR%\..\%BUILD_DIR%

:: check that all required variables defined
PUSHD .
IF NOT DEFINED ANDROID_NDK (ECHO. & ECHO You should set an environment variable ANDROID_NDK to the full path to your copy of Android NDK & GOTO end)
(CD "%ANDROID_NDK%") || (ECHO. & ECHO Directory "%ANDROID_NDK%" specified by ANDROID_NDK variable does not exist & GOTO end)

IF NOT EXIST "%CMAKE%" (ECHO. & ECHO You should set an environment variable CMAKE to the full path to cmake executable & GOTO end)
IF NOT EXIST "%MAKE%" (ECHO. & ECHO You should set an environment variable MAKE to the full path to native port of make executable & GOTO end)

IF NOT %BUILD_JAVA_PART%==1 GOTO required_variables_checked

IF NOT DEFINED ANDROID_SDK (ECHO. & ECHO You should set an environment variable ANDROID_SDK to the full path to your copy of Android SDK & GOTO end)
(CD "%ANDROID_SDK%" 2>NUL) || (ECHO. & ECHO Directory "%ANDROID_SDK%" specified by ANDROID_SDK variable does not exist & GOTO end)

IF NOT DEFINED ANT_DIR (ECHO. & ECHO You should set an environment variable ANT_DIR to the full path to Apache Ant root & GOTO end)
(CD "%ANT_DIR%" 2>NUL) || (ECHO. & ECHO Directory "%ANT_DIR%" specified by ANT_DIR variable does not exist & GOTO end)

IF NOT DEFINED JAVA_HOME (ECHO. & ECHO You should set an environment variable JAVA_HOME to the full path to JDK & GOTO end)
(CD "%JAVA_HOME%" 2>NUL) || (ECHO. & ECHO Directory "%JAVA_HOME%" specified by JAVA_HOME variable does not exist & GOTO end)

:required_variables_checked
POPD

:: check for ninja
echo "%MAKE%"|findstr /i ninja >nul:
IF %errorlevel%==1 (SET BUILD_WITH_NINJA=0) ELSE (SET BUILD_WITH_NINJA=1)
IF %BUILD_WITH_NINJA%==1 (SET CMAKE_GENERATOR=Ninja) ELSE (SET CMAKE_GENERATOR=MinGW Makefiles)

:: create build dir
IF DEFINED REBUILD rmdir /S /Q "%BUILD_DIR%" 2>NUL
MKDIR "%BUILD_DIR%" 2>NUL
PUSHD "%BUILD_DIR%" || (ECHO. & ECHO Directory "%BUILD_DIR%" is not found & GOTO end)

:: run cmake
ECHO. & ECHO Runnning cmake...
ECHO ANDROID_ABI=%ANDROID_ABI%
ECHO.
IF NOT %BUILD_OPENCV%==1 GOTO other-cmake
:opencv-cmake
("%CMAKE%" -G"%CMAKE_GENERATOR%" -DANDROID_ABI="%ANDROID_ABI%" -DCMAKE_TOOLCHAIN_FILE="%SOURCE_DIR%"\android.toolchain.cmake -DCMAKE_MAKE_PROGRAM="%MAKE%" %* "%SOURCE_DIR%\..") && GOTO cmakefin
ECHO. & ECHO cmake failed &	GOTO end
:other-cmake
("%CMAKE%" -G"%CMAKE_GENERATOR%" -DANDROID_ABI="%ANDROID_ABI%" -DOpenCV_DIR="%OPENCV_BUILD_DIR%" -DCMAKE_TOOLCHAIN_FILE="%OPENCV_BUILD_DIR%\..\android.toolchain.cmake" -DCMAKE_MAKE_PROGRAM="%MAKE%" %* "%SOURCE_DIR%") && GOTO cmakefin
ECHO. & ECHO cmake failed &	GOTO end
:cmakefin

:: run make
ECHO. & ECHO Building native libs...
IF %BUILD_WITH_NINJA%==0 ("%MAKE%" -j %NUMBER_OF_PROCESSORS% VERBOSE=%VERBOSE%) || (ECHO. & ECHO make failed & GOTO end)
IF %BUILD_WITH_NINJA%==1 ("%MAKE%") || (ECHO. & ECHO ninja failed & GOTO end)

IF NOT %BUILD_JAVA_PART%==1 GOTO end
POPD && PUSHD %SOURCE_DIR%

:: configure java part
ECHO. & ECHO Updating Android project...
(CALL "%ANDROID_SDK%\tools\android" update project --name %PROJECT_NAME% --path .) || (ECHO. & ECHO failed to update android project & GOTO end)

:: compile java part
ECHO. & ECHO Compiling Android project...
(CALL "%ANT_DIR%\bin\ant" debug) || (ECHO. & ECHO failed to compile android project & GOTO end)

:end
POPD
ENDLOCAL
