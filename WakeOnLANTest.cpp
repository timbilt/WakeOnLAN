
#include <string>
#include "boost/regex.hpp"

#define MAC_SIZE 6

class WakeOnLAN
{
public:
	
	WakeOnLAN()
	: bMACParsed{false}
	{ }
	
	bool ParseMAC(const std::string& sMac)
	{
		boost::regex exp ("^([0-9a-fA-F]{2}[:-]){5}([0-9a-fA-F]{2})$");
		
		if ((bMACParsed = boost::regex_match(sMac, exp))) {
			mac = sMac;
			bMACBytesSet = SetMACBytes();
		}
		
		return bMACParsed;
	}
	
	unsigned char macBytes[MAC_SIZE];
	
private:
	
	bool SetMACBytes()
	{
		if (!bMACParsed) return false;
		
		unsigned int macIndex;
		
		for (macIndex = 0; macIndex < MAC_SIZE; macIndex++)
		{
			macBytes[macIndex] = (unsigned char)strtol(mac.substr(macIndex*3, 2).data(), nullptr, 16);
		}
		
		return true;
	}
	
	bool bMACParsed;
	bool bMACBytesSet;
	std::string mac;
};

#include "gmock/gmock.h"

using namespace testing;

class WakeOnLANTest : public Test
{
public:
	WakeOnLAN wol;
	
	unsigned char DefaultBytes[MAC_SIZE] { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };
	std::string DefaultMAC{"01:23:45:67:89:AB"};
	
	bool MatchesDefaultBytes(const unsigned char* const pBytes)
	{		
		for (int index = 0; index < MAC_SIZE; index++)
		{
			if (*(pBytes + index) != DefaultBytes[index])
				return false;
		}
		
		return true;
	}
};

TEST_F(WakeOnLANTest, ParsesValidMACAddresses) {	
	ASSERT_THAT(wol.ParseMAC(DefaultMAC), Eq(true));
}

TEST_F(WakeOnLANTest, ConvertsMACStringToBytes)
{
	ASSERT_THAT(wol.ParseMAC(DefaultMAC), Eq(true));
	
	ASSERT_THAT(MatchesDefaultBytes(wol.macBytes), Eq(true));
}