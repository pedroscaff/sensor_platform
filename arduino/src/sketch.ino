#include <DHT.h>
#include <TimerOne.h>

#define MQ7PIN A0
#define MQ2PIN A1
#define MQ135PIN A2
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float hum = 0;
float tmp = 0;
float hid = 0;

int mq7 = 0;
int mq2 = 0;
int mq135 = 0;

char fmt [64];

int readMQ7() {
    int value;
    value = analogRead(MQ7PIN);
    if (isnan(value)) {
        return -1;
    } else {
        return value;
    }
}

int readMQ2() {
    int value;
    value = analogRead(MQ2PIN);
    if (isnan(value)) {
        return -1;
    } else {
        return value;
    }
}

int readMQ135() {
    int value;
    value = analogRead(MQ135PIN);
    if (isnan(value)) {
        return -1;
    } else {
        return value;
    }

}

void serialize(char* fmt) {
    sprintf(fmt, "mq7:%i,mq2:%i,mq135:%i,hum:%i,tmp:%i,hid:%i;", mq7, mq2, mq135, (int)hum, (int)tmp, (int)(hid+0.5));
}

void callback() {
    mq7 = readMQ7();
    mq2 = readMQ2();
    mq135 = readMQ135();
    hid = dht.computeHeatIndex(tmp, hum, false);

    serialize(fmt);
    if (Serial.available()) {
        Serial.println(fmt);
    }
}

void setup() {
    Serial.begin(9600);
    dht.begin();
    Timer1.initialize(1000000);
    Timer1.attachInterrupt(callback);
}

void loop() {
    hum = dht.readHumidity();
    tmp = dht.readTemperature();
    if (isnan(tmp) || isnan(hum)) {
        /* Serial.println("Failed to read from DHT"); */
    }
}
