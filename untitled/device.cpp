#include <QThread>

#include "device.h"
#include "bvas.h"

Device::Device()
{

}

void Device::init()
{
  if(init_bvas())
      exit(1);
}

void Device::readData()
{
    /*for (int j = 0; j < 6; j++)
    {
      for (int i = 0; i < BUF_SIZE; i++)
        {
          data_buffer[i][j] = 50;
        }
    }*/
    //QThread::msleep(30);
    if(read_data_block_bvas())
        exit(1);

    memcpy(buf,data_buffer,6400*6*2);
}

void Device::stop()
{
    stop_bvas();
}
