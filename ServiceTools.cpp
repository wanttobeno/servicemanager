#include "serviceTools.h"
#include <windows.h>
#include <stdio.h>

bool createService(const char* serviceName, const char* executablePath)
{
    SC_HANDLE hManager=OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
    if(hManager==INVALID_HANDLE_VALUE)
        return false;
    SC_HANDLE hService=CreateService(hManager, serviceName, serviceName,
                                     SERVICE_ALL_ACCESS,
                                     SERVICE_KERNEL_DRIVER,
                                     SERVICE_DEMAND_START,
                                     SERVICE_ERROR_NORMAL,
                                     executablePath,
                                     0, 0, 0, 0, 0);
    CloseServiceHandle(hManager);
    if(!hService)
        return false;
    CloseServiceHandle(hService);
    return true;
}

bool startService(const char* serviceName)
{
    SC_HANDLE hManager=OpenSCManager(0, 0, STANDARD_RIGHTS_REQUIRED);
    if(!hManager)
        return false;
    SC_HANDLE hService=OpenService(hManager, serviceName, SERVICE_START);
    CloseServiceHandle(hManager);
    if(!hService)
        return false;
    if(!StartService(hService, 0, 0))
    {
        CloseServiceHandle(hService);
        return false;
    }
    CloseServiceHandle(hService);
    return true;
}

bool stopService(const char* serviceName)
{
    SC_HANDLE hManager=OpenSCManager(0, 0, STANDARD_RIGHTS_REQUIRED);
    if(!hManager)
        return false;
    SC_HANDLE hService=OpenService(hManager, serviceName, SERVICE_STOP);
    CloseServiceHandle(hManager);
    if(!hService)
        return false;
    SERVICE_STATUS srvStatus;
    if(!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        CloseServiceHandle(hService);
        return false;
    }
    CloseServiceHandle(hService);
    return true;
}

bool deleteService(const char* serviceName)
{
    SC_HANDLE hManager=OpenSCManager(0, 0, STANDARD_RIGHTS_REQUIRED);
    if(!hManager)
        return false;
    SC_HANDLE hService=OpenService(hManager, serviceName, DELETE);
    CloseServiceHandle(hManager);
    if(!hService)
        return false;

    if(!DeleteService(hService))
    {
        CloseServiceHandle(hService);
        return false;
    }
    CloseServiceHandle(hService);
    return true;
}
