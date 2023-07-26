#include<iostream>
#include<csignal>

#include<PNCUtils/SimpleTimer.h>

#include<Drivers/NPOS220/NPOS220D.h>
#include<Protocols/INSPVAXA.h>

using namespace std;

Drivers::NPOS220D_Handler NPOSH;
PNCUtils::SimpleTimer timer;
PNCUtils::SimpleTimer timer2;
serial::Serial ser;

#define DEFAULT_COM ("/dev/ttyCH340")

string data = "123";
Protocols::INSPVAXAData info;

void CallBack(){
    bool a = NPOSH.getline(data);

    if(a){
        printf("%s\n",data.c_str());
        bool b = Protocols::toINSPVAXAData(data,info);
        if(b) return;
    }
    else{
        data = "123";
    }
}

void SendOnce(){
    // ser.write("#INSPVAXA,COM3,0,54.0,FINESTEERING,2060,199947.720,02008000,471d,14970;INS_SOLUTION_GOOD,INS_RTKFIXED,30.48279810362,114.16884102924,32.9221,-15.0000,-0.0016,-0.0011,0.0004,0.744013246,3.969861907,109.516743370,0.0226,0.0219,0.0277,0.0015,0.0015,0.0014,0.0277,0.0270,0.1252,0f0000d7,0*49c32c60\r\n");
    // ser.write("#INSPVAXA,COM3,0,54.0,FINESTEERING,2060,199947.820,02008000,471d,14970;INS_SOLUTION_GOOD,INS_RTKFIXED,30.48279810228,114.16884102911,32.9220,-15.0000,-0.0019,-0.0006,0.0007,0.744543643,3.971140207,109.517149611,0.0226,0.0219,0.0277,0.0015,0.0015,0.0014,0.0277,0.0270,0.1252,0f0000d7,0*b7e2dece\r\n");
    // ser.write("#INSPVAXA,COM3,0,54.0,FINESTEERING,2060,199947.800,02008000,471d,14970;INS_SOLUTION_GOOD,INS_RTKFIXED,30.48279810256,114.16884102912,32.9220,-15.0000,-0.0018,-0.0010,0.0002,0.744883798,3.970798507,109.517423528,0.0226,0.0219,0.0277,0.0015,0.0015,0.0014,0.0277,0.0270,0.1252,0f0000d7,0*e60481c0\r\n");
    // ser.write("#INSPVAA,COM1,0,31.0,FINESTEERING,1264,144088.000,02040000,5615,1541;1264,144088.002284950,51.116827527,-114.037738908,401.191547167,354.846489850,108.429407241,-10.837482850,1.116219952,-3.476059035,7.372686190,INS_ALIGNMENT_COMPLETE*af719fd9\r\n");
    // ser.write("#INSPVAA,USB1,0,67.5,FINESTEERING,2209,490558.000,02000020,18bc,16809;2209,490558.000000000,51.15043714042,-114.03067871718,1080.3548,0.0051,-0.0014,-0.0012,-0.296402993,0.311887972,157.992156267,INS_SOLUTION_GOOD*cc698020\r\n");
    ser.write("#INSPVAXA,USB1,0,65.5,FINESTEERING,2209,490782.000,02000020,46eb,16809;INS_SOLUTION_GOOD,INS_PPP,51.15043710672,-114.03067871892,1097.3598,-17.0001,-0.0016,0.0002,0.0029,-0.308665944,0.297893298,157.960833016,0.1816,0.1816,0.1808,0.0018,0.0018,0.0016,0.0292,0.0292,0.0582,13000045,0*a74644a2\r\n");
}
void SIGNAL_HANDLLER(int a){
    timer.stop();
    timer2.stop();
    cout<<"On Exit"<<endl;
    exit(0);
}

int main(int argc, char** argv){
    if(argc>3){
        cout<<"Invalid ARGs"<<endl;
        return 0;
    }

    std::signal(SIGINT,SIGNAL_HANDLLER);

    bool flag;
    if(argc == 1){
        flag = NPOSH.open(DEFAULT_COM);
    } else if(argc == 2) {
        flag = NPOSH.open(argv[1]);
    } else if(argc == 3){
        flag = NPOSH.open(argv[1]);
        try {
            ser.setPort(argv[2]);
            ser.setBaudrate(115200);
            serial::Timeout to = serial::Timeout::simpleTimeout(1000);
            ser.setTimeout(to);
            ser.open();

        } catch(serial::IOException& e){
            cout<<"OpenFailed"<<endl;
            return 0;
        }
        timer2.startSync(100,SendOnce);
    }

    if(!flag){
        cout<<"OpenFailed"<<endl;
        return 0;
    }

    // NPOSH.getline(data);

    timer.startSync(50,CallBack);

    while(1){
        // CallBack();
    }

}