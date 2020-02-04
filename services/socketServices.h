#ifndef CHATSERVER_SOCKETSERVICES_H
#define CHATSERVER_SOCKETSERVICES_H

#include <string>
#include <iostream>
#include "../resources/static/serverInfo.h"
#include "stringServices.h"
#include "../resources/static/staticSymbols.h"
#include "../resources/properties.h"
#include "../models/client.h"
#include "../resources/static/functionalNames.h"


using namespace std;

class socketService {
public:
    static void sendMessageToUser(int user, const string &message, client clients[]) {
        send(clients[user].socket, message.c_str(), message.length(), 0);
        send(clients[user].socket, "\n\r", 3, 0);
    }

    static void joinChannel(string &b, int user, client clients[]) {
        stringService::trim(b);
        clients[user].channel.assign(b);
        string joinMessage(serverInfo::USER);
        joinMessage.append(clients[user].nickname);
        joinMessage.append(serverInfo::JOINED_CHANEL).append(staticSymbols::NEW_LINE);
        for (int i = 0; i < properties::MAX_SOCKET; i++) {
            if (clients[i].socket > 0 && clients[i].channel == clients[user].channel && i != user) {
                send(clients[i].socket, joinMessage.c_str(), joinMessage.length(), 0);
            }
        }
        sendMessageToUser(user, clients[user].channel, clients);
    }

    static void listChannels(int user, client clients[]) {
        string channelsList;
        channelsList.append(serverInfo::ACTIVE_CHANNELS).append(staticSymbols::NEW_LINE);
        for (int i = 0; i < properties::MAX_SOCKET; i++) {
            if (clients[i].socket > 0 && clients[i].channel.length() > 0) {
                channelsList.append(clients[i].channel);
                channelsList.append(staticSymbols::NEW_LINE);
            }
        }
        channelsList = stringService::removeDupWord(channelsList);
        socketService::sendMessageToUser(user, channelsList, clients);
    }


    static void leaveChannel(int user, client clients[]) {
        if (clients[user].channel.length() > 0) {
            string leaveMessage(serverInfo::LEAVING_CHANNEL);
            leaveMessage.append(clients[user].channel);
            leaveMessage.append(staticSymbols::NEW_LINE);
            string userLeaveMessage(serverInfo::USER);
            userLeaveMessage.append(clients[user].nickname)
                    .append(serverInfo::LEFT_CHANNEL)
                    .append(staticSymbols::NEW_LINE);
            for (int i = 0; i < properties::MAX_SOCKET; i++) {
                if (clients[i].socket > 0 && clients[i].channel == clients[user].channel && i != user)
                    send(clients[i].socket, userLeaveMessage.c_str(), userLeaveMessage.length(), 0);
                send(clients[user].socket, staticSymbols::NEW_LINE, 3, 0);
            }
            socketService::sendMessageToUser(user, leaveMessage, clients);
        }
    }

    static void listUsers(int user, client clients[]) {
        string usersList;
        usersList.append(serverInfo::ACTIVE_USERS)
                .append(staticSymbols::NEW_LINE);
        for (int i = 0; i < properties::MAX_SOCKET; i++) {
            if (clients[i].socket > 0) {
                usersList.append(clients[i].nickname)
                        .append(staticSymbols::NEW_LINE);
            }
        }
        socketService::sendMessageToUser(user, usersList, clients);
    }

    static void nickname(string &b, int user, client clients[]) {
        string message(serverInfo::NEW_NICKNAME);
        message.append(b);
        stringService::trim(b);
        clients[user].nickname.assign(b);
        socketService::sendMessageToUser(user, message, clients);
    }



    static void sendMessage(string &b, int user, client clients[]) {
        string message;
        message.clear();
        message.append(clients[user].nickname);
        message.append(": ");
        message.append(b);
        for (int i = 0; i < properties::MAX_SOCKET; i++) {
            if (clients[i].socket > 0 && clients[i].channel == clients[user].channel && i != user) {
                socketService::sendMessageToUser(i, message, clients);
            }
        }
    }


    static void exitChat(int user, client clients[]) {
        socketService::leaveChannel(user, clients);
        closesocket(clients[user].socket);
        clients[user].socket = 0;

        string byeMessage(serverInfo::DISCONNECT_USER);
        byeMessage.append(clients[user].nickname);

        cout << byeMessage << staticSymbols::NEW_LINE;
    }

    static void viewChatCommands(int user, client clients[]) {
        string commandsList(functionalNames::CHAT_COMMANDS);

        commandsList.append(staticSymbols::NEW_LINE).append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::LIST_OF_CHANNELS_SYMBOL)
                .append(functionalNames::LIST_OF_CHANNELS)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::JOIN_CHANEL_SYMBOL)
                .append(functionalNames::JOIN_CHANEL)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::LEAVE_CHANEL_SYMBOL)
                .append(functionalNames::LEAVE_CHANEL)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::LIST_USER_SYMBOL)
                .append(functionalNames::LIST_USER)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::SEND_MESSAGE_SYMBOL)
                .append(functionalNames::SEND_MESSAGE)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::NICK_NAME_SYMBOL)
                .append(functionalNames::NICK_NAME)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::CHAT_INFO_SYMBOL)
                .append(functionalNames::CHAT_INFO)
                .append(staticSymbols::NEW_LINE);

        commandsList.append(functionalNames::EXIT_SYMBOL)
                .append(functionalNames::EXIT)
                .append(staticSymbols::NEW_LINE);

        socketService::sendMessageToUser(user, commandsList, clients);
    }

};


#endif //CHATSERVER_SOCKETSERVICES_H
