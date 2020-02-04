#include <iostream>
#include <string>

#include "resources/static/serverInfo.h"
#include "models/client.h"
#include "resources/properties.h"
#include "services/socketServices.h"

using namespace std;

int main() {

    client clients[properties::MAX_SOCKET];
    SOCKET new_socket, cs = 0, s;


    WSADATA wsa;
    struct sockaddr_in server{}, address{};

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cout << serverInfo::ERROR_OCCURED << WSAGetLastError();
        return 1;
    }

    cout << serverInfo::CREATING_SERVER_SOCKET;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << serverInfo::ERROR_OCCURED << WSAGetLastError();
    }
    cout << serverInfo::READY << endl;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(properties::CONNECT_PORT);

    cout << serverInfo::CONNECTING_SERVER_SOCKET;
    if (bind(s, (struct sockaddr *) &server,
             sizeof(server)) == SOCKET_ERROR) {
        cout << serverInfo::ERROR_OCCURED << WSAGetLastError();
    }
    cout << serverInfo::READY << endl;

    int activity, addRLen, valRead;
    fd_set readFds;
    char *buffer;

    buffer = new char[properties::MAX_BUFFER_SIZE + 1];
    addRLen = sizeof(struct sockaddr_in);

    cout << serverInfo::RUNNING_LISTEN << properties::CONNECT_PORT << staticSymbols::ELLIPSIS;
    listen(s, 3);
    cout << serverInfo::READY << endl;

    for (;;) {

        FD_ZERO(&readFds);
        FD_SET(s, &readFds);

        for (auto &client : clients) {
            cs = client.socket;
            if (cs > 0) {
                FD_SET(cs, &readFds);
            }
        }
        activity = select(0, &readFds, nullptr, nullptr, nullptr);

        if (activity == SOCKET_ERROR) {
            cout << serverInfo::ERROR_OCCURED << WSAGetLastError();
            return 1;
        }
        if (FD_ISSET(s, &readFds)) {
            if ((new_socket = accept(s, (struct sockaddr *) &address, (int *) &addRLen)) < 0) {
                cout << serverInfo::ERROR_OCCURED << WSAGetLastError();
                return 1;
            } else {
                getpeername(cs, (struct sockaddr *) &address, (int *) &addRLen);
                cout << serverInfo::CONNECT_USER << inet_ntoa(address.sin_addr) << endl;
            }


            for (int j = 0; j < properties::MAX_SOCKET; j++) {
                if (clients[j].socket == 0) {
                    clients[j].socket = new_socket;
                    socketService::sendMessageToUser(j, serverInfo::NO_NICKNAME, clients);
                    break;
                }
            }
        }
        for (int k = 0; k < properties::MAX_SOCKET; k++) {
            cs = clients[k].socket;
            if (FD_ISSET(cs, &readFds)) {
                getpeername(cs, (struct sockaddr *) &address,
                            (int *) &addRLen);
                memset(buffer, 0, properties::MAX_BUFFER_SIZE + 1);
                valRead = recv(cs, buffer, properties::MAX_BUFFER_SIZE, 0);
                if (valRead == SOCKET_ERROR) {
                    int error_code = WSAGetLastError();
                    if (error_code == WSAECONNRESET) {
                        closesocket(cs);
                        clients[k].socket = 0;
                        cout << serverInfo::DISCONNECT_USER << endl;

                    } else {
                        cout << serverInfo::ERROR_OCCURED << error_code << endl;
                    }
                }
                if (valRead == 0) {
                    closesocket(cs);
                    clients[k].socket = 0;
                    cout << serverInfo::DISCONNECT_USER << endl;
                } else {
                    string strBuffer(buffer);
                    strBuffer.erase(0, 1);
                    if (clients[k].nickname.empty()) {
                        clients[k].nickname = buffer;
                        string nicknameMessage(serverInfo::HELLO_USER);
                        nicknameMessage.append(buffer);
                        socketService::sendMessageToUser(k, nicknameMessage, clients);
                        socketService::viewChatCommands(k, clients);
                    } else {
                        switch (buffer[0]) {
                            case 'i':
                            case 'I':
                                socketService::viewChatCommands(k, clients);
                                break;
                            case 'C':
                            case 'c':
                                socketService::listChannels(k, clients);
                                break;
                            case 'J':
                            case 'j':
                                socketService::joinChannel(strBuffer, k, clients);
                                break;
                            case 'L':
                            case 'l':
                                socketService::leaveChannel(k, clients);
                                break;
                            case 'U':
                            case 'u':
                                socketService::listUsers(k, clients);
                                break;
                            case 'S':
                            case 's':
                                socketService::sendMessage(strBuffer, k, clients);
                                break;
                            case 'E':
                            case 'e':
                                socketService::exitChat(k, clients);
                                break;
                            case 'N':
                            case 'n':
                                socketService::nickname(strBuffer, k, clients);
                                break;
                        }
                    }
                }
            }
        }
    }
}
