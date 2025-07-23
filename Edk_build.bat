@echo off
:: ===========================================================================
:: EDK II 一键构建脚本
:: 功能：自动设置环境并构建EDK II项目
:: 注意：本文件必须保存为GBK编码以保证中文正常显示
:: ===========================================================================

:: 设置控制台编码为GBK（简体中文）
::chcp 936 >nul

:: 启用延迟变量扩展
setlocal enabledelayedexpansion

echo [1/6] 设置工作空间...
:: 使用当前目录作为工作空间
set "WORKSPACE=%CD%"
:: 设置EDK II包路径
set "PACKAGES_PATH=%WORKSPACE%\edk2"
echo   WORKSPACE: %WORKSPACE%
echo   PACKAGES_PATH: %PACKAGES_PATH%

echo [2/6] 进入edk2目录...
:: 注意：此处屏蔽了cd命令的输出（包括错误输出）
cd /d "%WORKSPACE%\edk2" 2>&1 >nul || (
    echo ERROR: edk2目录在%WORKSPACE%中未找到
    exit /b 1
)

echo [3/6] 初始化构建环境...
:: 注意：此处屏蔽了edksetup.bat的所有输出
:: 如需查看详细输出，请移除 "2>&1 >nul"
call edksetup.bat 2>&1 >nul || (
    echo ERROR: edksetup.bat 执行失败
    exit /b 1
)

echo [4/6] 重建基础工具...
:: 注意：此处屏蔽了edksetup.bat rebuild的所有输出
:: 如需查看详细输出，请移除 "2>&1 >nul"
call edksetup.bat rebuild 2>&1 >nul || (
    echo ERROR: 工具重建失败
    exit /b 1
)

:: ===========================================================================
:: 构建参数配置
:: 可修改以下参数以适应不同构建需求
:: ===========================================================================
set BUILD_ARCH=X64
set BUILD_TOOLCHAIN=VS2017
set BUILD_FLAGS=-D DEBUG_ON_SERIAL_PORT

:: ===========================================================================
:: 构建目标选择
:: 支持三种构建目标选择方式
:: ===========================================================================
echo [5/6] 选择构建目标：
echo   1. EmulatorPkg (默认)
echo   2. OvmfPkgX64
echo   3. 自定义 DSC 文件

:: 获取用户输入（使用双引号避免空格问题）
set /p "choice=请选择构建目标 (1-3): "

:: 处理空输入（默认为选项1）
if "!choice!"=="" set choice=1

if "!choice!"=="1" (
    set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
) else if "!choice!"=="2" (
    set DSC_FILE=OvmfPkg\OvmfPkgX64.dsc
) else if "!choice!"=="3" (
    set /p "DSC_FILE=请输入 DSC 文件路径: "
) else (
    echo 无效选择，使用默认构建目标
    set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
)

:: 验证 DSC 文件是否存在
if not exist "!DSC_FILE!" (
    echo ERROR: DSC 文件不存在 - !DSC_FILE!
    exit /b 1
)

:: ===========================================================================
:: 构建执行阶段
:: 此部分输出不会被屏蔽，以便用户查看构建进度
:: ===========================================================================
echo [6/6] 开始构建: !DSC_FILE!
echo   架构: %BUILD_ARCH%
echo   工具链: %BUILD_TOOLCHAIN%
echo   标志: %BUILD_FLAGS%

:: 执行构建命令（注意：此处保留所有输出）
build -a %BUILD_ARCH% -t %BUILD_TOOLCHAIN% -p "!DSC_FILE!" %BUILD_FLAGS% || (
    echo ERROR: 构建失败 !DSC_FILE!
    exit /b 1
)

echo 构建成功完成: !DSC_FILE!
endlocal

:: ===========================================================================
:: 输出屏蔽说明
::
:: 本脚本屏蔽了以下非关键命令的输出：
:: 1. chcp 936 >nul         - 屏蔽代码页更改提示
:: 2. cd ... 2>&1 >nul      - 屏蔽目录切换输出（包括错误）
:: 3. call edksetup.bat ... - 屏蔽环境初始化和工具重建输出
::
:: 如需解除屏蔽，请：
:: 1. 删除 "2>&1 >nul" 重定向
:: 2. 或者改为重定向到日志文件：
::    例: call edksetup.bat > setup.log 2>&1
::
:: 构建命令 (build) 的输出未被屏蔽，以便实时监控进度
:: ===========================================================================