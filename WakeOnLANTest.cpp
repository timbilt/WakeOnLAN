
#include <string>
#include "boost/regex.hpp"

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
	
private:
	bool bMACParsed;
};

#include "gmock/gmock.h"


TEST(WakeOnLANTest, ParsesValidMACAddresses) {
	WakeOnLAN wol;
	
	ASSERT_THAT(wol.ParseMAC("01:23:45:67:89:AB"), testing::Eq(true));
}

TEST(WakeOnLANTest, ConvertsMACStringToBytes)
{
	WakeOnLAN wol;
	ASSERT_THAT(wol.ParseMAC("01:23:45:67:89:AB"), testing::Eq(true));
	
	ASSERT_THAT(MatchBytes(wol.macBytes), testing::Eq(true));
}