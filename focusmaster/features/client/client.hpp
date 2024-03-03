#include <nlohmann/json.hpp>

#include "../http/http.hpp"

using json = nlohmann::json;

class client {
	
public:
	void debugtest();
	std::string generateKey(int length, std::string alias);
	std::string banID(std::string identifier, std::string id);
	std::string rsHwid(std::string id);

private:
	std::string key = "ASNFZ4mrze8BI0VniavN7wEjRWeJq83vASNFZ4mrze8=";
	std::string masterkey = "SxF+zweVKbY30jcGmqi8n0XnhIEY/S61KQOcVPBbxbY=";
};