
/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Implement For INSPVAXA Protocols
 * 
*********************************************************************/

#include<vector>
#include <sstream>

#include<Protocols/INSPVAXA.h>

#define CRC32_POLYNOMIAL 0xEDB88320L

using namespace std;

namespace Protocols{
namespace 
{
    template <class Type>
    Type stringToNum(const string str){
        istringstream iss(str);
        Type num;
        iss >> num;
        return num;
    }
} // namespace <void>

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

    bool toINSPVAXAData(std::string const & str, INSPVAXAData & buffer){
        int temp_position = str.find(",");
        string temp_s = str.substr(0,temp_position);
        string data = str;

        if(temp_s != "#INSPVAXA") return false;

        vector<string> temp_array;
        temp_position = data.find(";");
        buffer.header = data.substr(0,temp_position+1);
        data.erase(0,temp_position+1);
        do
        {
            temp_position = data.find(",");
            temp_s = data.substr(0,temp_position);
            data.erase(0,temp_position+1);
            temp_array.push_back(temp_s);
        }while(temp_position != -1);

        // buffer.header = "#INSPVAXA";
        buffer.ins_status = temp_array[0];
        buffer.position_type = temp_array[1];
        buffer.latitude = stringToNum<double>(temp_array[2]);
        buffer.longitude = stringToNum<double>(temp_array[3]);
        buffer.altitude = stringToNum<double>(temp_array[4]);
        buffer.undulation = stringToNum<double>(temp_array[5]);
        buffer.north_velocity = stringToNum<double>(temp_array[6]);
        buffer.east_velocity = stringToNum<double>(temp_array[7]);
        buffer.up_velocity = stringToNum<double>(temp_array[8]);
        buffer.roll = stringToNum<double>(temp_array[9]);
        buffer.pitch = stringToNum<double>(temp_array[10]);
        buffer.azimuth = stringToNum<double>(temp_array[11]);
        buffer.latitude_std = stringToNum<double>(temp_array[12]);
        buffer.longitude_std = stringToNum<double>(temp_array[13]);
        buffer.altitude_std = stringToNum<double>(temp_array[14]);
        buffer.north_velocity_std = stringToNum<double>(temp_array[15]);
        buffer.east_velocity_std = stringToNum<double>(temp_array[16]);
        buffer.up_velocity_std = stringToNum<double>(temp_array[17]);
        buffer.roll_std = stringToNum<double>(temp_array[18]);
        buffer.pitch_std = stringToNum<double>(temp_array[19]);
        buffer.azimuth_std = stringToNum<double>(temp_array[20]);
        buffer.extended_status = stringToNum<double>(temp_array[21]);
        buffer.seconds_since_update = stringToNum<double>(temp_array[22]);
        return true;
    }

    bool INSPVAXACheckCRC(std::string const & str){
        auto crc = CalculateBlockCRC32(str.size()-12,str.c_str()+1);
        int idx = str.size()-10;
        uint32_t crcdata = 0;
        for(int i = idx;i<idx+8;i++){
            crcdata <<= 4;
            auto c = str[i] - '0';
            if(c>9) c = str[i]-'A'+10;
            if(c>9) c = str[i]-'a'+10;
            crcdata += c;
        }
        if(crc == crcdata) return true;
        return false;
    }




}//namespace Protocols