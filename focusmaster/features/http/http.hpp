#include <windows.h>
#include <winhttp.h>

#include "../crypto/crypto.hpp"

#pragma comment(lib, "winhttp.lib")

class http {

public:
	std::string postReq(std::string jsonBody, LPCWSTR path, bool localhost);
};