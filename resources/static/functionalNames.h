#ifndef CHATSERVER_FUNCTIONALNAMES_H
#define CHATSERVER_FUNCTIONALNAMES_H


#include <string>

class functionalNames {
public:
    static constexpr const char* CHAT_COMMANDS = "Chat commands: ";

    static constexpr const char* LIST_OF_CHANNELS_SYMBOL = "C:";
    static constexpr const char* LIST_OF_CHANNELS = "list of channels";

    static constexpr const char* JOIN_CHANEL_SYMBOL = "J:";
    static constexpr const char* JOIN_CHANEL = "join chanel";

    static constexpr const char* LEAVE_CHANEL_SYMBOL = "L:";
    static constexpr const char* LEAVE_CHANEL = "leave chanel";

    static constexpr const char* LIST_USER_SYMBOL = "U:";
    static constexpr const char* LIST_USER = "list user";

    static constexpr const char* SEND_MESSAGE_SYMBOL = "S:";
    static constexpr const char* SEND_MESSAGE = "send message";

    static constexpr const char* EXIT_SYMBOL = "E:";
    static constexpr const char* EXIT = "exit";

    static constexpr const char* NICK_NAME_SYMBOL = "N:";
    static constexpr const char* NICK_NAME = "nick name";

    static constexpr const char* CHAT_INFO_SYMBOL = "I:";
    static constexpr const char* CHAT_INFO = "chat commands";
};

#endif //CHATSERVER_FUNCTIONALNAMES_H
