
#include "WakeOnLAN.h"

#include "gmock/gmock.h"
#include <algorithm>

using namespace testing;

class WakeOnLANTest : public Test
{
public:
	WakeOnLAN wol;
	
	unsigned char DefaultBytes[MAC_SIZE] { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };
	std::string DefaultMAC{"01:23:45:67:89:AB"};
	
	bool MatchesDefaultBytes(const unsigned char* const pBytes) const
	{		
		for (int index = 0; index < MAC_SIZE; index++)
		{
			if (*(pBytes + index) != DefaultBytes[index])
				return false;
		}
		
		return true;
	}
	
	bool PayloadMarkerInitialized(const unsigned char* const pMarker) const
	{
		return MARKER_SIZE == std::count(pMarker, pMarker + MARKER_SIZE, MARKER_UNIT);
	}
	
	bool MatchesMACAppended16Times(const unsigned char* const pMACBytes) const
	{
		for (int counter = 0; counter < 16; counter++)
		{
			if (memcmp(pMACBytes + MAC_SIZE * counter, wol.macBytes, MAC_SIZE) != 0)
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

TEST_F(WakeOnLANTest, InitializesPayloadMarker)
{
	auto payload = wol.SetPayloadMarker();
	
	ASSERT_THAT(PayloadMarkerInitialized(payload), Eq(true));
}

TEST_F(WakeOnLANTest, AppendsMAC16TimesToPayload)
{
	auto pMACBytes = wol.AppendMACToPayload16Times();
	
	ASSERT_THAT(MatchesMACAppended16Times(pMACBytes), Eq(true));
}

TEST_F(WakeOnLANTest, SendPayloadData)
{
	ASSERT_THAT(wol.SendPayload("www.google.com", "50009"), Eq(true));
}