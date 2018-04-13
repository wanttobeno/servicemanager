#ifndef _SERVICETOOLS_H
#define _SERVICETOOLS_H

bool createService(const char* serviceName, const char* executablePath);
bool startService(const char* serviceName);
bool stopService(const char* serviceName);
bool deleteService(const char* serviceName);

#endif // _SERVICETOOLS_H
