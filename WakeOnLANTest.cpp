
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
		
		bMACParsed = boost::regex_match(sMac, exp);
		
		return bMACParsed;
	}
	
	unsigned char macBytes[MAC_SIZE];
	
private:
	bool bMACParsed;
};

#include "gmock/gmock.h"

using namespace testing;

class WakeOnLANTest : public Test
{
public:
	WakeOnLAN wol;
	
	unsigned char DefaultBytes[MAC_SIZE] { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };
	
	bool MatchesDefaultBytes(const unsigned char* const pBytes)
	{		
		for (int index = 0; index < MAC_SIZE; index++)
		{
			if (*(pBytes + index) != DefaultBytes[index])
				return false;
		}
		
		return false;
	}
};

TEST_F(WakeOnLANTest, ParsesValidMACAddresses) {	
	ASSERT_THAT(wol.ParseMAC("01:23:45:67:89:AB"), Eq(true));
}

TEST_F(WakeOnLANTest, ConvertsMACStringToBytes)
{
	ASSERT_THAT(wol.ParseMAC("01:23:45:67:89:AB"), Eq(true));
	
	ASSERT_THAT(MatchesDefaultBytes(wol.macBytes), Eq(true));
}