
#include "boost/regex.hpp"

#include "WakeOnLAN.h"

WakeOnLAN::WakeOnLAN()
	: bMACParsed{false},
	  bMACBytesSet{false}
{ }

bool WakeOnLAN::ParseMAC(const std::string& sMac)
{
	boost::regex exp ("^([0-9a-fA-F]{2}[:-]){5}([0-9a-fA-F]{2})$");
	
	if ((bMACParsed = boost::regex_match(sMac, exp))) {
		mac = sMac;
		bMACBytesSet = SetMACBytes();
	}
	
	return bMACParsed;
}

bool WakeOnLAN::SetMACBytes()
{
	if (!bMACParsed) return false;
	
	unsigned int macIndex;
	
	for (macIndex = 0; macIndex < MAC_SIZE; macIndex++)
	{
		macBytes[macIndex] = (unsigned char)strtol(mac.substr(macIndex*3, 2).data(), nullptr, 16);
	}
	
	return true;
}

const unsigned char* WakeOnLAN::SetPayloadMarker()
{
	auto vp = memset(payload, MARKER_UNIT, MARKER_SIZE);
	return reinterpret_cast<unsigned char*>(vp);
}

const unsigned char* WakeOnLAN::AppendMACToPayload16Times()
{
	return payload;
}