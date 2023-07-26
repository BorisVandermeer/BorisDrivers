
/*********************************************************************
 * Author : BorisVandermeer
 * 
 * Discription ：
 *      A Implement For INSPVAXA Protocols
 * 
*********************************************************************/

#pragma once

#include<string>

namespace Protocols{
    struct INSPVAXAData{
        int stamp;
        std::string header;
        std::string ins_status;
        std::string position_type;
        double latitude;
        double longitude;
        double altitude;
        float  undulation;
        double north_velocity;
        double east_velocity;
        double up_velocity;
        double roll;
        double pitch;
        double azimuth;
        float  latitude_std;
        float  longitude_std;
        float  altitude_std;
        float  north_velocity_std;
        float  east_velocity_std;
        float  up_velocity_std;
        float  roll_std;
        float  pitch_std;
        float  azimuth_std;
        uint32_t extended_status;
        uint16_t seconds_since_update;
    };

    bool toINSPVAXAData(std::string const & str, INSPVAXAData & buffer);

    bool INSPVAXACheckCRC(std::string const & str);
    

}//namespace Protocols

