#pragma once

#include <ArduinoJson.h>

class DeviceInfoStruct {
    public:
        String m_DeviceName;
        String m_DeviceOSVersion;
        String m_IPv4;
        String m_IPv6;
        String m_DeviceMacAddress;
        int m_ServingPort;
        int m_PluginsCount;
        String m_SendTime;
        bool m_IsMainDevice;
        String m_ServerAddress;
        String m_ServerBuildTime;
        int m_DeviceOSType = 0;
        DeviceInfoStruct(String str) {
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, str);
            m_DeviceName = (const char*)doc["DeviceName"];
            m_DeviceOSVersion = (const char*)doc["DeviceOSVersion"];
            m_IPv4 = (const char*)doc["IPv4"];
            m_IPv6 = (const char*)doc["IPv6"];
            m_DeviceMacAddress = (const char*)doc["DeviceMacAddress"];
            m_ServingPort = doc["ServingPort"];
            m_PluginsCount = doc["PluginsCount"];
            m_SendTime = (const char*)doc["SendTime"];
            m_IsMainDevice = doc["IsMainDevice"];
            m_ServerAddress = (const char*)doc["ServerAddress"];
            m_ServerBuildTime = (const char*)doc["ServerBuildTime"];
            m_DeviceOSType = doc["DeviceOSType"];
        }
        DeviceInfoStruct(
            String DeviceName,
            String DeviceOSVersion,
            String IPv4,
            String IPv6,
            String DeviceMacAddress,
            int ServingPort,
            int PluginsCount,
            String SendTime,
            bool IsMainDevice,
            String ServerAddress,
            String ServerBuildTime,
            int DeviceOSType = 0
        ) : 
            m_DeviceName(DeviceName),
            m_DeviceOSVersion(m_DeviceOSVersion),
            m_IPv4(IPv4),
            m_IPv6(IPv6),
            m_DeviceMacAddress(DeviceMacAddress),
            m_ServingPort(ServingPort),
            m_PluginsCount(PluginsCount),
            m_SendTime(SendTime),
            m_IsMainDevice(IsMainDevice),
            m_ServerAddress(ServerAddress),
            m_ServerBuildTime(ServerBuildTime),
            m_DeviceOSType(DeviceOSType)
            {}
        String toJson();
};

String DeviceInfoStruct::toJson() {
    DynamicJsonDocument doc(512);
    String ret;
    doc["DeviceName"] = m_DeviceName;
    doc["DeviceOSVersion"] = m_DeviceOSVersion;
    doc["IPv4"] = m_IPv4;
    doc["IPv6"] = m_IPv6;
    doc["DeviceMacAddress"] = m_DeviceMacAddress;
    doc["ServingPort"] = m_ServingPort;
    doc["PluginsCount"] = m_PluginsCount;
    doc["SendTime"] = m_SendTime;
    doc["IsMainDevice"] = m_IsMainDevice;
    doc["ServerAddress"] = m_ServerAddress;
    doc["ServerBuildTime"] = m_ServerBuildTime;
    doc["DeviceOSType"] = m_DeviceOSType;
    serializeJson(doc, ret);
    return ret;
}


