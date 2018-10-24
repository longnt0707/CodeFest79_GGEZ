//
//  SocketIOManager.h
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#ifndef SocketIOManager_h
#define SocketIOManager_h

//#ifdef __cplusplus

#include <string>
#include "../socketio_headers/sio_socket.h"

typedef void(*SocketIOIncommingEventHandler) (sio::event& event);

void socketioStartConnect(std::string server);
void socketioJoinRoom(std::string teamID, std::string roomID, std::string eventName);
void socketioRegisterEvent(std::string eventName, SocketIOIncommingEventHandler callback);
void socketioSendElephentArmy(std::string teamID, std::string matchID, std::string direction, std::string eventName);
void socketioClose();

//#endif

//#ifdef __OBJC__
//
//#import <Cocoa/Cocoa.h>
//
//#endif


#endif /* SocketIOManager_hpp */
