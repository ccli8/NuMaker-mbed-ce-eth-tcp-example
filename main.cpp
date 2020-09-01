#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"

#define USE_HTTP_1_1
//#define LOCAL_LAN

namespace {
    // Test connection information
#ifndef LOCAL_LAN
const char *HTTP_SERVER_NAME = "www.ifconfig.io"; 
#else
const char *HTTP_SERVER_NAME = "pt22_winserver2.nuvoton.com";
#endif

#ifndef LOCAL_LAN
const char *HTTP_SERVER_FILE_PATH = "/method";
const int HTTP_SERVER_PORT = 80;
#else
const char *HTTP_SERVER_FILE_PATH = "/examples/arm_mbed/method.txt";
const int HTTP_SERVER_PORT = 8080;
#endif

    const int RECV_BUFFER_SIZE = 512;

    // Test related data
    const char *HTTP_OK_STR = "200 OK";
    const char *HTTP_EXPECT_STR = "GET";

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

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif
    printf("Start TCP test \r\n");

    bool result = true;

    EthernetInterface eth;

    eth.connect(); //Use DHCP

#if (MBED_MAJOR_VERSION == 6)
    static SocketAddress sa;
    eth.get_ip_address(&sa);
    printf("TCP client IP Address is %s\r\n", sa.get_ip_address());
    TCPSocket sock;
    sock.open(&eth);

    eth.gethostbyname(HTTP_SERVER_NAME, &sa);
    sa.set_port(HTTP_SERVER_PORT);
    if (sock.connect(sa) == 0) {    
        printf("HTTP: Connected to %s:%d\r\n", HTTP_SERVER_NAME, HTTP_SERVER_PORT);    
#else        
    printf("TCP client IP Address is %s\r\n", eth.get_ip_address());

    TCPSocket sock(&eth);
   
    if (sock.connect(HTTP_SERVER_NAME, HTTP_SERVER_PORT) == 0) {
        printf("HTTP: Connected to %s:%d\r\n", HTTP_SERVER_NAME, HTTP_SERVER_PORT);
#endif
        // We are constructing GET command like this:
#ifndef USE_HTTP_1_1
        // GET http://www.ifconfig.io/method HTTP/1.0\n\n
        strcpy(buffer, "GET http://");
        strcat(buffer, HTTP_SERVER_NAME);
        strcat(buffer, HTTP_SERVER_FILE_PATH);
        strcat(buffer, " HTTP/1.0\n\n");
#else
       // GET /method HTTP/1.1\r\nHost: ifconfig.io\r\nConnection: close\r\n\r\n"
        strcpy(buffer, "GET ");
        strcat(buffer, HTTP_SERVER_FILE_PATH);   
        strcat(buffer, " HTTP/1.1\r\nHost: ");
        strcat(buffer, HTTP_SERVER_NAME);
        strcat(buffer, "\r\nConnection: close\r\n\r\n");
#endif
        
        // Send GET command
        sock.send(buffer, strlen(buffer));

        // Server will respond with HTTP GET's success code
        const int ret = sock.recv(buffer, sizeof(buffer) - 1);
        buffer[ret] = '\0';

        // Find 200 OK HTTP status in reply
        bool found_200_ok = find_substring(buffer, buffer + ret, HTTP_OK_STR, HTTP_OK_STR + strlen(HTTP_OK_STR));
        // Find "deny" string in reply
        bool found_expect = find_substring(buffer, buffer + ret, HTTP_EXPECT_STR, HTTP_EXPECT_STR + strlen(HTTP_EXPECT_STR));

        if (!found_200_ok) result = false;
        if (!found_expect) result = false;

        printf("HTTP: Received %d chars from server\r\n", ret);
        printf("HTTP: Received 200 OK status ... %s\r\n", found_200_ok ? "[OK]" : "[FAIL]");
        printf("HTTP: Received '%s' status ... %s\r\n", HTTP_EXPECT_STR, found_expect ? "[OK]" : "[FAIL]");
        printf("HTTP: Received massage:\r\n\r\n");
        printf("%s", buffer);
    }

    sock.close();
    eth.disconnect();

#if MBED_HEAP_STATS_ENABLED
    mbed_stats_heap_get(&heap_stats);
    printf("Current heap: %lu\r\n", heap_stats.current_size);
    printf("Max heap size: %lu\r\n", heap_stats.max_size);
#endif
}
