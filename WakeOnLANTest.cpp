
#include <string>

class WakeOnLAN
{
public:
	
	WakeOnLAN()
	: bMACParsed{false}
	{ }
	
	bool ParseMAC(const std::string& sMac)
	{
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