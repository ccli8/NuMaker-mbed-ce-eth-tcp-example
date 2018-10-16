//#if !FEATURE_IPV4
//    #error [NOT_SUPPORTED] IPV4 not supported for this target
//#endif

#include <algorithm>
#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"
#include "greentea-client/test_env.h"
#include "unity/unity.h"

//#define LOCAL_LAN

namespace {
    // Test connection information
#ifndef LOCAL_LAN
const char *HTTP_SERVER_NAME = "os.mbed.com";
#else
const char *HTTP_SERVER_NAME = "pt22_winserver2.nuvoton.com";
#endif

#ifndef LOCAL_LAN
const char *HTTP_SERVER_FILE_PATH = "/media/uploads/mbed_official/hello.txt";
const int HTTP_SERVER_PORT = 80;
#else
const char *HTTP_SERVER_FILE_PATH = "/examples/arm_mbed/hello.txt";
const int HTTP_SERVER_PORT = 8080;
#endif

#if defined(TARGET_VK_RZ_A1H)
    const int RECV_BUFFER_SIZE = 300;
#else
    const int RECV_BUFFER_SIZE = 512;
#endif

    // Test related data
    const char *HTTP_OK_STR = "200 OK";
    const char *HTTP_HELLO_STR = "Hello world!";

    // Test buffers
    char buffer[RECV_BUFFER_SIZE] = {0};
}

bool find_substring(const char *first, const char *last, const char *s_first, const char *s_last) {
    const char *f = std::search(first, last, s_first, s_last);
    return (f != last);
}

int main() {
#if MBED_HEAP_STATS_ENABLED
    mbed_stats_heap_t heap_stats;
#endif

    printf(" Start TCP test \r\n");
//    GREENTEA_SETUP(20, "default_auto");

    bool result = true;

    EthernetInterface eth;

    eth.connect(); //Use DHCP
        
    printf("TCP client IP Address is %s\r\n", eth.get_ip_address());

    TCPSocket sock(&eth);
   
    if (sock.connect(HTTP_SERVER_NAME, HTTP_SERVER_PORT) == 0) {
        printf("HTTP: Connected to %s:%d\r\n", HTTP_SERVER_NAME, HTTP_SERVER_PORT);

        // We are constructing GET command like this:
        // GET http://developer.mbed.org/media/uploads/mbed_official/hello.txt HTTP/1.0\n\n
        strcpy(buffer, "GET http://");
        strcat(buffer, HTTP_SERVER_NAME);
        strcat(buffer, HTTP_SERVER_FILE_PATH);
        strcat(buffer, " HTTP/1.0\n\n");
        // Send GET command
        sock.send(buffer, strlen(buffer));

        // Server will respond with HTTP GET's success code
        const int ret = sock.recv(buffer, sizeof(buffer) - 1);
        buffer[ret] = '\0';

        // Find 200 OK HTTP status in reply
        bool found_200_ok = find_substring(buffer, buffer + ret, HTTP_OK_STR, HTTP_OK_STR + strlen(HTTP_OK_STR));
        // Find "Hello World!" string in reply
        bool found_hello = find_substring(buffer, buffer + ret, HTTP_HELLO_STR, HTTP_HELLO_STR + strlen(HTTP_HELLO_STR));

        if (!found_200_ok) result = false;
        if (!found_hello) result = false;

        printf("HTTP: Received %d chars from server\r\n", ret);
        printf("HTTP: Received 200 OK status ... %s\r\n", found_200_ok ? "[OK]" : "[FAIL]");
        printf("HTTP: Received '%s' status ... %s\r\n", HTTP_HELLO_STR, found_hello ? "[OK]" : "[FAIL]");
        printf("HTTP: Received massage:\r\n\r\n");
        printf("%s", buffer);
    }

    sock.close();
    eth.disconnect();
//    GREENTEA_TESTSUITE_RESULT(result);

#if MBED_HEAP_STATS_ENABLED
    mbed_stats_heap_get(&heap_stats);
    printf("Current heap: %lu\r\n", heap_stats.current_size);
    printf("Max heap size: %lu\r\n", heap_stats.max_size);
#endif
}
