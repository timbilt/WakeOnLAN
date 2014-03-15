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
	unsigned char* SetPayloadMarker();
	
	unsigned char macBytes[MAC_SIZE];
	
private:
	
	bool SetMACBytes();
	
	bool bMACParsed;
	bool bMACBytesSet;
	std::string mac;
	unsigned char payload[MARKER_SIZE + MAC_SIZE * 16];
};

#endif // WAKEONLAN_