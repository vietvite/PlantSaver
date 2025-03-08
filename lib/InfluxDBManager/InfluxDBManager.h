#ifndef INFLUXDBMANAGER_H
#define INFLUXDBMANAGER_H

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

class InfluxDBManager {
public:
    InfluxDBManager(const char* url, const char* org, const char* bucket, const char* token);
    void init(const char* device, const char* ssid);
    void sendSoilMoistureData(int value, int percentage);
    void sendWiFiData(int32_t rssi, int channel, const char* ip);

private:
    InfluxDBClient client;
    Point sensor;
};

#endif // INFLUXDBMANAGER_H
