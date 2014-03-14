
#include <string>

class WakeOnLAN
{
public:
	bool ParseMAC(const std::string& sMac)
	{
		return false;
	}
};

#include "gmock/gmock.h"


TEST(WakeOnLANTest, ParsesValidMACAddresses) {
	WakeOnLAN wol;
	
	ASSERT_THAT(wol.ParseMAC(""), testing::Eq(true));
}