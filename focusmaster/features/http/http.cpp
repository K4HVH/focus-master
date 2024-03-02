#include "http.hpp"

std::string http::postReq(std::string jsonBody, LPCWSTR path, bool localhost) {

    // Initialize WinHTTP
    HINTERNET hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        std::cout << "Error initializing WinHTTP." << std::endl;
        return "";
    }

    HINTERNET hConnect;
    HINTERNET hRequest;

    if (localhost) {
        // Connect to the server
        hConnect = WinHttpConnect(hSession, L"localhost", 3000, 0);
        if (!hConnect) {
            std::cout << "Error connecting to the server." << std::endl;
            WinHttpCloseHandle(hSession);
            return "";
        }

        // Create the request
        hRequest = WinHttpOpenRequest(hConnect, L"POST", path, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
        if (!hRequest) {
            std::cout << "Error creating the request." << std::endl;
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return "";
        }
    }
    else {
        // Connect to the server
         hConnect = WinHttpConnect(hSession, L"fls.k4tech.net", INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (!hConnect) {
            std::cout << "Error connecting to the server." << std::endl;
            WinHttpCloseHandle(hSession);
            return "";
        }

        // Create the request
        hRequest = WinHttpOpenRequest(hConnect, L"POST", path, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
        if (!hRequest) {
            std::cout << "Error creating the request." << std::endl;
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return "";
        }
    }

    // Define additional headers for specifying the content type as JSON
    LPCWSTR additionalHeaders = L"Content-Type: application/json\r\n";
    DWORD headersLength = -1; // Use -1 to indicate that the string is null-terminated

    // Send the encrypted message as the request
    if (!WinHttpSendRequest(hRequest, additionalHeaders, headersLength, (LPVOID)jsonBody.c_str(), jsonBody.length(), jsonBody.length(), 0)) {
        std::cout << "Error sending the request." << std::endl;
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "";
    }

    // Receive the response
    if (!WinHttpReceiveResponse(hRequest, NULL)) {
        std::cout << "Error receiving the response." << std::endl;
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "";
    }

    ////////////////////////////////////////  RESPONSE

    // Read the response
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    DWORD dwBytesWritten = 0;

    std::string response;

    do {
        // Keep checking for data until there is nothing left.
        dwSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
            std::cout << "Error querying data." << std::endl;
            break;
        }

        // Allocate memory for the buffer.
        pszOutBuffer = new char[dwSize + 1];
        if (!pszOutBuffer) {
            std::cout << "Error out of memory." << std::endl;
            break;
        }

        // Read the data.
        ZeroMemory(pszOutBuffer, dwSize + 1);
        if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
            std::cout << "Error reading data." << std::endl;
        }
        else if (dwDownloaded > 0) { // Check if data was actually read
            // Append the read data to the response string
            response.append(pszOutBuffer, dwDownloaded);
        }

        // Free the memory allocated to the buffer.
        delete[] pszOutBuffer;
    } while (dwSize > 0);

    // Close any open handles.
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    if (!response.empty()) {
        return response;
    }
}