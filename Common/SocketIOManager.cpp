//
//  SocketIOManager.cpp
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#include "SocketIOManager.h"

#include "../socketio_headers/sio_client.h"

#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#define HIGHLIGHT(__O__) std::cout<<"\e[1;31m"<<__O__<<"\e[0m"<<std::endl
#define EM(__O__) std::cout<<"\e[1;30;1m"<<__O__<<"\e[0m"<<std::endl

using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
bool connect_finish = false;
bool joined_room = false;

class connection_listener
{
    sio::client &handler;
    
public:
    
    connection_listener(sio::client& h):
    handler(h)
    {
    }
    
    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
        std::cout<<"[debug]----- SIO on_connected "<<std::endl;
    }
    
    void on_close(client::close_reason const& reason)
    {
        std::cout<<"[debug]----- SIO closed "<<std::endl;
        exit(0);
    }
    
    void on_fail()
    {
        std::cout<<"[debug]----- SIO failed "<<std::endl;
        exit(0);
    }
};


// Socket
sio::client h;
socket::ptr current_socket;
SocketIOIncommingEventHandler EventCallback;

void OnMessage(sio::event& event) {
    _lock.lock();
    if (!joined_room) {
        _cond.notify_all();
        joined_room = true;
    }
    _lock.unlock();
    
    EventCallback(event);
}

void socketioRegisterEvent(std::string eventName, SocketIOIncommingEventHandler callback)
{
    //Room state returned each cycle (200ms for speed 5: 1000ms/5)
    current_socket->on(eventName, OnMessage);
    EventCallback = callback;
}

void socketioSendElephentArmy(std::string teamID, std::string matchID, std::string direction, std::string eventName) {
    sio::message::list msgList;
    msgList.push(teamID);
    msgList.push(matchID);
    msgList.push(direction);
    
    current_socket->emit(eventName, msgList, NULL);
    HIGHLIGHT("[debug]----- SIO Sent Move   : " << direction);
}


//Start connect to server
void socketioStartConnect(std::string server)
{
    connection_listener l(h);
    
    h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
    h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
    h.connect(server);
    _lock.lock();
    if(!connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
    current_socket = h.socket();
    
    HIGHLIGHT("[debug]----- Start ..." << server);
    
//    HIGHLIGHT("[debug]----- Closing...");
//    h.sync_close();
//    h.clear_con_listeners();
}

//Start Room
void socketioJoinRoom(std::string teamID,std::string roomID, std::string eventName)
{
    message::list msgList;
    msgList.push(teamID);
    msgList.push(roomID);
    current_socket->emit(eventName, msgList, NULL);
    
    _lock.lock();
    if(!joined_room)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
}




