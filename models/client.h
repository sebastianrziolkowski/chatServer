#ifndef CHATSERVER_CLIENT_H
#define CHATSERVER_CLIENT_H

#include <string>
#include <winsock.h>

using namespace std;

class client {
public:
    client() {
        socket = 0;
        nickname.clear();
        channel.clear();
    };
    SOCKET socket;
    string nickname;
    string channel;
};

#endif //CHATSERVER_CLIENT_H
