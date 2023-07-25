/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Driver For NPOS220D
 * 
*********************************************************************/
#pragma once

#include<string>

#include<serial/serial.h>

#define NPOS220D_BAUDRATE_DEFAULT (115200)
#define NPOS220D_BUFFER_SIZE      (1000)

namespace Drivers{

    class NPOS220D_Handler{
    public:
        NPOS220D_Handler() = default;
        
        bool open(const std::string &port){return open(port,NPOS220D_BAUDRATE_DEFAULT);}
        bool open(const std::string &port, int BAUDRATE);
        // return true, if Some Data is Set to " line "
        bool getline(std::string & dataline);

    private:
        serial::Serial ser;
        std::string Buffer;
    };

} //namespace Drivers
