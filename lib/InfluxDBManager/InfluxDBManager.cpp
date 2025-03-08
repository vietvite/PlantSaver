#include "InfluxDBManager.h"

InfluxDBManager::InfluxDBManager(const char* url, const char* org, const char* bucket, const char* token)
    : client(url, org, bucket, token), sensor("soil_moisture") {}

void InfluxDBManager::init(const char* device, const char* ssid) {
    sensor.addTag("device", device);
    sensor.addTag("SSID", ssid);
}

void InfluxDBManager::sendSoilMoistureData(int value, int percentage) {
    sensor.clearFields();
    sensor.addField("value", value);
    sensor.addField("percentage", percentage);

    if (!client.writePoint(sensor)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    } else {
        Serial.println("Soil moisture data submitted successfully");
    }
}

void InfluxDBManager::sendWiFiData(int32_t rssi, int channel, const char* ip) {
    sensor.addField("wifi_signal_strength", rssi);
    sensor.addField("wifi_channel", channel);
    sensor.addField("wifi_ip_address", ip);

    if (!client.writePoint(sensor)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    } else {
        Serial.println("WiFi data submitted successfully");
    }
}
