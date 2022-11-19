#include <Arduino.h>

#include "struct/DeviceInfoStruct.h"
#include <esp_sntp.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
#include <WiFi.h>

WiFiUDP UDPClient;
DeviceInfoStruct info(
    /*DeviceName*/ "ESP32",
    /*DeviceOSVersion*/"ESP32",
    /*IPv4*/"",
    /*IPv6*/"",
    /*DeviceMacAddress*/"111",
    /*ServingPort*/0,
    /*PluginsCount*/0,
    /*SendTime*/"",
    /*IsMainDevice*/false,
    /*ServerAddress*/"",
    /*ServerBuildTime*/"",
    /*DeviceOSType*/9
);

uint16_t UDPPortSend = 23404;
uint16_t UDPPortReceive = 24040;

unsigned long time1;
unsigned long time2;

time_t now;
char strftime_buf[64];
struct tm timeinfo;

void setup() {
    #pragma region Smartconfig 智能配网
    Serial.begin(115200);
    delay(100);
    Serial.print("");
    Serial.print("Connection WIFI.");
    WiFi.begin();
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
        if (count > 10)
        {
            Serial.println("WIFI Wait for Smartconfig");
            WiFi.mode(WIFI_STA);
            WiFi.beginSmartConfig();
            while (1)
            {
                if (WiFi.smartConfigDone())
                {
                    WiFi.setAutoConnect(true);
                    count = 0;
                    break;
                }
            }
        }
        count++;
    }
    #pragma endregion

    // 打印WIFI信息
    Serial.println("");
    Serial.println("WIFI SmartConfig Success");
    Serial.printf("SSID:%s", WiFi.SSID().c_str());
    Serial.printf(", PSW:%s\r\n", WiFi.psk().c_str());
    Serial.print("LocalIP:");
    Serial.print(WiFi.localIP());
    Serial.print(" ,GateIP:");
    Serial.println(WiFi.gatewayIP());
    info.m_IPv4 = WiFi.localIP().toString();
    info.m_IPv6 = WiFi.localIPv6().toString();
    info.m_DeviceMacAddress = WiFi.macAddress();

    UDPClient.begin(UDPPortSend);
    // UDPClient.begin(UDPPortReceive);
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "1.cn.pool.ntp.org");
    sntp_setservername(1, "210.72.145.44");
    sntp_setservername(2, "2.cn.pool.ntp.org");
    sntp_init();

    // 将时区设置为中国标准时间
    setenv("TZ", "CST-8", 1);
    tzset();
}
void loop() {
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%FT%T%z", &timeinfo);
    info.m_SendTime = strftime_buf;
    // Serial.println(info.toJson());
    delay(1000);
}
