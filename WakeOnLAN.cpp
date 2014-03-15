
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

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
	unsigned char* pTemp, * pOrigin;
	
	pTemp = pOrigin = payload + MARKER_SIZE;
	
	for (int counter = 0; counter < 16; counter++)
	{
		memcpy(pTemp + MAC_SIZE * counter, macBytes, MAC_SIZE); 
	}
	
	return pOrigin;
}

bool WakeOnLAN::SendPayload(const std::string& sHost, const std::string& sPort)
{
	int sockFD, ret, numBytesSent;
    struct addrInfo hints, *pHostAddrInfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((ret = getaddrinfo(sHost.data(), sPort.data(), &hints, &pHostAddrInfo)) != 0) {
        std::cerr << "\nError: getaddrinfo => " << gai_strerror(ret) << std::endl;
        
		return false;
    }

    for(p = pHostAddrInfo; p != nullptr; p = p->ai_next) {
        if ((sockFD = socket(p->ai_family, 
							  p->ai_socktype,
							  p->ai_protocol)) == -1) 
		{
            std::cerr << "\nError: socket => unable to get file descriptor" << std::endl;
            
			continue;
        }
        else
		{
			break;
		}
    }

    if (p == nullptr) {
        std::cerr << "\nError: Failed to bind to a socket" << std::endl;
		
        return false;
    }

    if ((numBytesSent = sendto(sockFD, 
								payload, 
							    sizeof payload, 
							    0,
								p->ai_addr, 
							    p->ai_addrlen)) == -1) 
	{
        std::cerr << "\nError: sendto => Unable to send data" << std::endl;
		
		return false;
    }

    freeaddrinfo(pHostAddrInfo);
	
    close(sockFD);

    return true;
}