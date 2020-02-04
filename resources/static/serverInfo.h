#ifndef CHATSERVER_SERVERINFO_H
#define CHATSERVER_SERVERINFO_H

#include <string>

class serverInfo {
    public:
    static constexpr const char* USER = "User ";
    static constexpr const char* ERROR_OCCURED = "Error occured: ";

    static constexpr const char* NEW_NICKNAME = "Your new nickname is ";
    static constexpr const char* NO_NICKNAME = "You should have nickname. Type it here:  ";
    static constexpr const char* HELLO_USER = "Hello on chat ";

    static constexpr const char* JOINED_CHANEL = " joined the channel";
    static constexpr const char* LEFT_CHANNEL = " left channel.";
    static constexpr const char* LEAVING_CHANNEL = "You are leaving channel: ";

    static constexpr const char* ACTIVE_CHANNELS = "Active channels: ";
    static constexpr const char* ACTIVE_USERS = " Active users: ";
    static constexpr const char* DISCONNECT_USER = "Disconnect user ";
    static constexpr const char* CONNECT_USER = "Connect user ";

    static constexpr const char* CREATING_SERVER_SOCKET = "Creating server socket...";
    static constexpr const char* CONNECTING_SERVER_SOCKET = "Connecting server socket...";
    static constexpr const char* RUNNING_LISTEN = "Running listen on port ";
    static constexpr const char* READY = " READY ";
};

#endif //CHATSERVER_SERVERINFO_H
