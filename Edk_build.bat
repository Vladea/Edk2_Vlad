@echo off
:: ===========================================================================
:: EDK II һ�������ű�
:: ���ܣ��Զ����û���������EDK II��Ŀ
:: ע�⣺���ļ����뱣��ΪGBK�����Ա�֤����������ʾ
:: ===========================================================================

:: ���ÿ���̨����ΪGBK���������ģ�
::chcp 936 >nul

:: �����ӳٱ�����չ
setlocal enabledelayedexpansion

echo [1/6] ���ù����ռ�...
:: ʹ�õ�ǰĿ¼��Ϊ�����ռ�
set "WORKSPACE=%CD%"
:: ����EDK II��·��
set "PACKAGES_PATH=%WORKSPACE%\edk2"
echo   WORKSPACE: %WORKSPACE%
echo   PACKAGES_PATH: %PACKAGES_PATH%

echo [2/6] ����edk2Ŀ¼...
:: ע�⣺�˴�������cd�����������������������
cd /d "%WORKSPACE%\edk2" 2>&1 >nul || (
    echo ERROR: edk2Ŀ¼��%WORKSPACE%��δ�ҵ�
    exit /b 1
)

echo [3/6] ��ʼ����������...
:: ע�⣺�˴�������edksetup.bat���������
:: ����鿴��ϸ��������Ƴ� "2>&1 >nul"
call edksetup.bat 2>&1 >nul || (
    echo ERROR: edksetup.bat ִ��ʧ��
    exit /b 1
)

echo [4/6] �ؽ���������...
:: ע�⣺�˴�������edksetup.bat rebuild���������
:: ����鿴��ϸ��������Ƴ� "2>&1 >nul"
call edksetup.bat rebuild 2>&1 >nul || (
    echo ERROR: �����ؽ�ʧ��
    exit /b 1
)

:: ===========================================================================
:: ������������
:: ���޸����²�������Ӧ��ͬ��������
:: ===========================================================================
set BUILD_ARCH=X64
set BUILD_TOOLCHAIN=VS2017
set BUILD_FLAGS=-D DEBUG_ON_SERIAL_PORT

:: ===========================================================================
:: ����Ŀ��ѡ��
:: ֧�����ֹ���Ŀ��ѡ��ʽ
:: ===========================================================================
echo [5/6] ѡ�񹹽�Ŀ�꣺
echo   1. EmulatorPkg (Ĭ��)
echo   2. OvmfPkgX64
echo   3. �Զ��� DSC �ļ�

:: ��ȡ�û����루ʹ��˫���ű���ո����⣩
set /p "choice=��ѡ�񹹽�Ŀ�� (1-3): "

:: ��������루Ĭ��Ϊѡ��1��
if "!choice!"=="" set choice=1

if "!choice!"=="1" (
    set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
) else if "!choice!"=="2" (
    set DSC_FILE=OvmfPkg\OvmfPkgX64.dsc
) else if "!choice!"=="3" (
    set /p "DSC_FILE=������ DSC �ļ�·��: "
) else (
    echo ��Чѡ��ʹ��Ĭ�Ϲ���Ŀ��
    set DSC_FILE=EmulatorPkg\EmulatorPkg.dsc
)

:: ��֤ DSC �ļ��Ƿ����
if not exist "!DSC_FILE!" (
    echo ERROR: DSC �ļ������� - !DSC_FILE!
    exit /b 1
)

:: ===========================================================================
:: ����ִ�н׶�
:: �˲���������ᱻ���Σ��Ա��û��鿴��������
:: ===========================================================================
echo [6/6] ��ʼ����: !DSC_FILE!
echo   �ܹ�: %BUILD_ARCH%
echo   ������: %BUILD_TOOLCHAIN%
echo   ��־: %BUILD_FLAGS%

:: ִ�й������ע�⣺�˴��������������
build -a %BUILD_ARCH% -t %BUILD_TOOLCHAIN% -p "!DSC_FILE!" %BUILD_FLAGS% || (
    echo ERROR: ����ʧ�� !DSC_FILE!
    exit /b 1
)

echo �����ɹ����: !DSC_FILE!
endlocal

:: ===========================================================================
:: �������˵��
::
:: ���ű����������·ǹؼ�����������
:: 1. chcp 936 >nul         - ���δ���ҳ������ʾ
:: 2. cd ... 2>&1 >nul      - ����Ŀ¼�л��������������
:: 3. call edksetup.bat ... - ���λ�����ʼ���͹����ؽ����
::
:: ���������Σ��룺
:: 1. ɾ�� "2>&1 >nul" �ض���
:: 2. ���߸�Ϊ�ض�����־�ļ���
::    ��: call edksetup.bat > setup.log 2>&1
::
:: �������� (build) �����δ�����Σ��Ա�ʵʱ��ؽ���
:: ===========================================================================