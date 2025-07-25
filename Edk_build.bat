@echo off
:: ========================================================
:: EDK II Smart Build Script
:: Supports both command-line arguments and interactive mode
:: Usage examples:
::   Edk_build.bat                   -> Interactive mode
::   Edk_build.bat 1                 -> Auto-build EmulatorPkg
::   Edk_build.bat 2                 -> Auto-build OvmfPkgX64
::   Edk_build.bat "path\to\custom.dsc" -> Build custom DSC
:: ========================================================

:: Initialization
chcp 65001 >nul
setlocal enabledelayedexpansion

:: Initialize DSC_FILE variable
set DSC_FILE=

:: Argument processing
if not "%~1"=="" (
    if "%~1"=="1" (
        set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
    ) else if "%~1"=="2" (
        set DSC_FILE=OvmfPkg\OvmfPkgX64.dsc
    ) else (
        :: Handle quoted paths
        set DSC_FILE=%~1
    )
)

echo [1/6] Setting workspace...
set "WORKSPACE=%CD%"
set "PACKAGES_PATH=%WORKSPACE%\edk2"
echo   WORKSPACE: %WORKSPACE%
echo   PACKAGES_PATH: %PACKAGES_PATH%

echo [2/6] Entering edk2 directory...
cd /d "%WORKSPACE%\edk2" 2>&1 >nul || (
    echo ERROR: edk2 directory not found in %WORKSPACE%
    exit /b 1
)

echo [3/6] Initializing build environment...
call edksetup.bat 2>&1 >nul || (
    echo ERROR: edksetup.bat failed
    exit /b 1
)

echo [4/6] Rebuilding base tools...
call edksetup.bat rebuild 2>&1 >nul || (
    echo ERROR: Tools rebuild failed
    exit /b 1
)

:: Build configuration
set BUILD_ARCH=X64
set BUILD_TOOLCHAIN=VS2017
set BUILD_FLAGS=-D DEBUG_ON_SERIAL_PORT

:: ========================================================
:: Build target selection
:: Skip interactive mode if command-line argument was provided
:: ========================================================
if defined DSC_FILE (
    echo [5/6] Using build target specified via command-line: %DSC_FILE%
) else (
    echo [5/6] Select build target:
    echo   1. EmulatorPkg (default)
    echo   2. OvmfPkgX64
    echo   3. Custom DSC file
    
    set /p "choice=Select target (1-3): "
    if "!choice!"=="" set choice=1
    
    if "!choice!"=="1" (
        set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
    ) else if "!choice!"=="2" (
        set DSC_FILE=OvmfPkg\OvmfPkgX64.dsc
    ) else if "!choice!"=="3" (
        set /p "DSC_FILE=Enter DSC file path: "
    ) else (
        echo Invalid selection, using default target
        set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
    )
)

:: Verify DSC file exists
if not exist "%DSC_FILE%" (
    echo ERROR: DSC file not found - %DSC_FILE%
    exit /b 1
)

:: ========================================================
:: Build execution
:: ========================================================
echo [6/6] Starting build: %DSC_FILE%
echo   Architecture: %BUILD_ARCH%
echo   Toolchain: %BUILD_TOOLCHAIN%
echo   Flags: %BUILD_FLAGS%

build -a %BUILD_ARCH% -t %BUILD_TOOLCHAIN% -p "%DSC_FILE%" %BUILD_FLAGS% || (
    echo ERROR: Build failed for %DSC_FILE%
    exit /b 1
)

echo Build completed successfully: %DSC_FILE%!
endlocal