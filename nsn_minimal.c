// NSN (Network Security Navigator) - Minimal Prototype
// Windows: gcc nsn_minimal.c -o nsn.exe -lws2_32
// Linux/Termux: gcc nsn_minimal.c -o nsn

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Platform-specific headers
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
    #define SOCKET_ERROR_CODE WSAGetLastError()
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <errno.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define CLOSE_SOCKET close
    #define SOCKET_ERROR_CODE errno
#endif

#define VERSION "0.1.0-prototype"

// Execute ping command
void nsn_ping(const char* target) {
    char cmd[256];
#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "ping -n 4 %s", target);
#else
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", target);
#endif
    system(cmd);
}

// Execute port scan
void nsn_scan(const char* target, int port) {
    printf("Scanning %s:%d...\n", target, port);
    
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return;
    }
#endif
    
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Could not create socket : %d\n", SOCKET_ERROR_CODE);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(target);
    
    // Set timeout
#ifdef _WIN32
    int timeout = 1000; // 1 second
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
#else
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif
    
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == 0) {
        printf("✓ Port %d is OPEN\n", port);
    } else {
        printf("✗ Port %d is CLOSED\n", port);
    }
    
    CLOSE_SOCKET(s);
#ifdef _WIN32
    WSACleanup();
#endif
}

// Execute NSN script
void execute_nsn(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error: Could not open file '%s'\n", filename);
        return;
    }
    
    char line[1024];
    int line_num = 0;
    
    printf("Executing: %s\n\n", filename);
    
    while (fgets(line, sizeof(line), f)) {
        line_num++;
        
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        // Skip empty lines and comments
        if (line[0] == '\0' || line[0] == '#') continue;
        
        // Parse commands
        if (strncmp(line, "print ", 6) == 0) {
            // Print statement
            char* text = line + 6;
            // Remove quotes if present
            if (text[0] == '"' && text[strlen(text)-1] == '"') {
                text[strlen(text)-1] = '\0';
                text++;
            }
            printf("%s\n", text);
        }
        else if (strncmp(line, "ping ", 5) == 0) {
            // Ping command
            char* target = line + 5;
            nsn_ping(target);
        }
        else if (strncmp(line, "scan ", 5) == 0) {
            // Scan command - format: scan target:port
            char* args = line + 5;
            char target[256];
            int port;
            
            if (sscanf(args, "%[^:]:%d", target, &port) == 2) {
                nsn_scan(target, port);
            } else {
                printf("Error: Invalid scan syntax at line %d\n", line_num);
                printf("Usage: scan <target>:<port>\n");
            }
        }
        else if (strncmp(line, "resolve ", 8) == 0) {
            // DNS resolve
            char* hostname = line + 8;
            printf("Resolving %s...\n", hostname);
            
#ifdef _WIN32
            WSADATA wsa;
            WSAStartup(MAKEWORD(2,2), &wsa);
#endif
            
            struct addrinfo hints, *result;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            
            if (getaddrinfo(hostname, NULL, &hints, &result) == 0) {
                struct sockaddr_in* addr = (struct sockaddr_in*)result->ai_addr;
                printf("✓ %s -> %s\n", hostname, inet_ntoa(addr->sin_addr));
                freeaddrinfo(result);
            } else {
                printf("✗ Failed to resolve %s\n", hostname);
            }
            
#ifdef _WIN32
            WSACleanup();
#endif
        }
        else {
            printf("Warning: Unknown command at line %d: %s\n", line_num, line);
        }
    }
    
    fclose(f);
    printf("\nExecution complete.\n");
}

// Interactive REPL
void repl() {
    char line[1024];
    printf("NSN v%s - Interactive Mode\n", VERSION);
    printf("Type 'exit' to quit, 'help' for commands\n\n");
    
    while (1) {
        printf("nsn> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        
        line[strcspn(line, "\r\n")] = 0;
        
        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
            break;
        }
        if (strcmp(line, "help") == 0) {
            printf("Available commands:\n");
            printf("  print <text>       - Print text\n");
            printf("  ping <target>      - Ping a host\n");
            printf("  scan <ip>:<port>   - Scan a port\n");
            printf("  resolve <hostname> - DNS lookup\n");
            printf("  help               - Show this help\n");
            printf("  exit               - Exit REPL\n");
            continue;
        }
        
        // Create temp file and execute
        FILE* tmp = fopen("_nsn_temp.nsn", "w");
        fprintf(tmp, "%s\n", line);
        fclose(tmp);
        execute_nsn("_nsn_temp.nsn");
        remove("_nsn_temp.nsn");
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("NSN (Network Security Navigator) v%s\n", VERSION);
        printf("Usage:\n");
        printf("  nsn <script.nsn>   - Run NSN script\n");
        printf("  nsn -i             - Interactive mode\n");
        printf("  nsn --version      - Show version\n");
        printf("  nsn --help         - Show this help\n");
        return 0;
    }
    
    if (strcmp(argv[1], "--version") == 0) {
        printf("NSN v%s\n", VERSION);
        return 0;
    }
    
    if (strcmp(argv[1], "--help") == 0) {
        printf("NSN (Network Security Navigator) v%s\n\n", VERSION);
        printf("A lightweight language for network analysis and security.\n\n");
        printf("Usage: nsn [options] <script.nsn>\n\n");
        printf("Options:\n");
        printf("  -i, --interactive  Start interactive REPL\n");
        printf("  --version          Show version\n");
        printf("  --help             Show this help\n");
        return 0;
    }
    
    if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0) {
        repl();
        return 0;
    }
    
    // Execute script file
    execute_nsn(argv[1]);
    
    return 0;
}
