#include <iostream>

#include "WakeOnLAN.h"

using namespace std;

#include "gmock/gmock.h"

bool ShowUsage();

int main(int argc, char** argv) {
	
	//testing::InitGoogleMock(&argc, argv);
	
	//RUN_ALL_TESTS();
	
	bool bWake{true};
	
	std::string macFlag{"-m"};
	std::string hostFlag{"-h"};
	std::string portFlag{"-p"};
	
	if (argc % 2 == 0 || (argc != 3 && argc != 7))
	   bWake = !ShowUsage();
	if (argc == 3)
	   if (argv[1] != macFlag)
		   bWake = !ShowUsage();
    if (argc == 7)
		if (argv[1] != macFlag || argv[3] != hostFlag || argv[5] != portFlag)
			bWake = !ShowUsage();
	
	if (!bWake)
		return 1;
	
	WakeOnLAN wol;
	
	if (!wol.ParseMAC(argv[2]))
		cerr << endl << "Invalid MAC address." << endl << endl;
	
	if (argc == 3)
		bWake = wol.SendPayload("255.255.255.255", "9");
	else
		bWake = wol.SendPayload(argv[4], argv[6]);
	
	return (bWake ? 0 : 1);	
}

bool ShowUsage()
{
	cout << endl;
	cout << "WakeOnLAN 1.0 by Delano Cooper" << endl << endl;
	cout << "Usage: wol -m <mac_address> [ -h <host_name_or_ip> -p <port_number> ]";
	cout << endl << endl;
	cout << "Example 1: Wake host with mac address 11-22-33-44-55-66 on your subnet.";
	cout << endl << endl;
	cout << "           wol -m 11-22-33-44-55-66" << endl << endl;
	cout << "Example 2: Wake host with mac address 00:11:22:33:44:55 on a different subnet.";
	cout << endl << endl;
	cout << "           wol -m 00:11:22:33:44:55 -h home.dyndns.org -p 30009" << endl;
	cout << "           wol -m 00:11:22:33:44:55 -h 170.20.1.31 -p 51001" << endl << endl;
	cout << "           You must forward the ports to port 9 for the target host(s)." << endl;
	cout << "           Forward the broadcast IP to enable sending different mac addresses";
	cout << endl;
	cout << "           to target different hosts." << endl << endl;
	
	return true;
}