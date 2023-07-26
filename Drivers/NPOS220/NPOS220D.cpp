/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Driver For NPOS220D
 * 
*********************************************************************/

#include<iostream>

#include<serial/serial.h>


#include<Drivers/NPOS220/NPOS220D.h>

using namespace std;


namespace Drivers{
    static unsigned long CRC32Value(int i) {
        int j;
        unsigned long ulCRC;
        ulCRC = i;
        for ( j = 8 ; j > 0; j-- ) {
            if (ulCRC & 1)
                ulCRC = ( ulCRC >> 1 ) ^ CRC32_POLYNOMIAL;
            else
                ulCRC >>= 1;
        }
        return ulCRC;
    }

    static unsigned long CalculateBlockCRC32( unsigned long ulCount, const char *ucBuffer ){
        unsigned long ulTemp1;
        unsigned long ulTemp2;
        unsigned long ulCRC = 0;
        while ( ulCount-- != 0 ) {
            ulTemp1 = ( ulCRC >> 8 ) & 0x00FFFFFFL;
            ulTemp2 = CRC32Value( ((int) ulCRC ^ *ucBuffer++ ) & 0xFF );
            ulCRC = ulTemp1 ^ ulTemp2;
        }
        return( ulCRC );
    }

    bool NPOS220D_Handler::open(const std::string &port, int BAUDRATE){
        try{
            ser.setPort(port);
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
        if(Msg_temp.size()>NPOS220D_BUFFER_SIZE){
            Msg_temp.erase(0,Msg_temp.size()-NPOS220D_BUFFER_SIZE);
        }
        if(Buffer.size()+Msg_temp.size()>NPOS220D_BUFFER_SIZE){
            Buffer.erase(0,Buffer.size()+Msg_temp.size()-NPOS220D_BUFFER_SIZE);
        }
        Buffer+=Msg_temp;

        const string Header = "#";
        const string Tail   = "\r\n";
        bool ret = false;
        while(1){
            size_t idx1 = Buffer.find(Header);
            if(idx1 == string::npos) break;
            size_t idx2 = Buffer.find(Tail,idx1);
            if(idx2 == string::npos) break;
            idx2+=1;
            string tmpdata = Buffer.substr(idx1,idx2-idx1+1);
            // Check CRC
            {
                int idx = tmpdata.size()-10;
                auto crc = CRC_calcor.crcCompute(tmpdata.c_str()+1,tmpdata.size()-12);
                auto crc2 = CalculateBlockCRC32(tmpdata.size()-12,tmpdata.c_str()+1);
                uint32_t crcdata = 0;
                for(int i = idx;i<idx+8;i++){
                    crcdata <<= 4;
                    auto c = tmpdata[i] - '0';
                    if(c>9) c = tmpdata[i]-'A'+10;
                    if(c>9) c = tmpdata[i]-'a'+10;
                    crcdata += c;
                }
                if(crc == crcdata){
                    ret = true;
                    dataline = tmpdata;
                }
            }
            Buffer.erase(0,idx2+1);
        }

        return ret;
    }


} //namespace Drivers
