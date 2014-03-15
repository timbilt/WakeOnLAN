#ifndef WAKEONLAN_
#define WAKEONLAN_

#include <string>

#define MAC_SIZE 6
#define MARKER_UNIT 0xFF
#define MARKER_SIZE 6

class WakeOnLAN
{
public:
	
	WakeOnLAN();	
	bool ParseMAC(const std::string& sMac);
	
	unsigned char macBytes[MAC_SIZE];
	
private:
	
	bool SetMACBytes();
	
	bool bMACParsed;
	bool bMACBytesSet;
	std::string mac;
};

#endif // WAKEONLAN_