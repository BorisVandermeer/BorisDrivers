
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

    bool toINSPVAXAData(std::string const & str, INSPVAXAData & buffer){
        int temp_position = str.find(",");
        string temp_s = str.substr(0,temp_position);
        string data = str;

        if(temp_s != "#INSPVAXA") return false;

        temp_position = str.find(";");
        temp_s = str;
        buffer.header = temp_s;
        vector<string> temp_array;
        do
        {
            temp_position = str.find(",");
            temp_s = str.substr(0,temp_position);
            data.erase(0,temp_position+1);
            temp_array.push_back(temp_s);
        }while(temp_position != -1);

        buffer.header = "#INSPVAXA";
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

    }




}//namespace Protocols