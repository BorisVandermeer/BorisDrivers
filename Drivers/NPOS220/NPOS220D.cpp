/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Driver For NPOS220D
 * 
*********************************************************************/

#include<serial/serial.h>

#include<Drivers/NPOS220/NPOS220D.h>

using namespace std;

namespace Drivers{


    bool NPOS220D_Handler::open(const std::string &port, int BAUDRATE){
        try{
            ser.setPort("/dev/ttyS0");
            ser.setBaudrate(115200);
            serial::Timeout to = serial::Timeout::simpleTimeout(1000);
            ser.setTimeout(to);
            ser.open();
        }
        catch(serial::IOException& e){
            return false;
        }

        Buffer.reserve(NPOS220D_BUFFER_SIZE);

        if(ser.isOpen()) return true;
        return false;
    }

    bool NPOS220D_Handler::getline(std::string & dataline){
        string Msg_temp = ser.read(ser.available());
        if(Buffer.size()+Msg_temp.size()>NPOS220D_BUFFER_SIZE){
            Buffer.erase(0,Buffer.size()+Msg_temp.size()-NPOS220D_BUFFER_SIZE);
        }
        Buffer+=Msg_temp;

        const string Header = "#INSPVAXA";
        const string Tail   = "\r\n";
        bool ret = false;
        while(1){
            int idx1 = Buffer.find(Header);
            if(idx1 == string::npos) break;
            int idx2 = Buffer.find(Tail,idx1);
            if(idx2 == string::npos)  break;
            idx2+=1;
            ret = true;
            dataline = Buffer.substr(idx1,idx2-idx1+1);
            Buffer.erase(0,idx2+1);
        }
        return ret;
    }


} //namespace Drivers
