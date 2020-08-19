#ifndef DEVICE_H
#define DEVICE_H

#define BUF_SIZE 6400

class Device
{
public:
    Device();
    void init();
    void readData();
    void stop();

    uint16_t buf[BUF_SIZE][6];
};

#endif // DEVICE_H
