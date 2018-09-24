//
//  GameManagerWrapper.m
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/24/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#import "GameManagerWrapper.h"
#import "../../Common/GameManager.h"

GameManager gmShared;

@implementation GameManagerWrapper

+(NSString*)GetTrainingRoomID{
    return [NSString stringWithUTF8String:UNIQUE_MATCH_ID_TRAINING];
}

+(void)InitMatch{
    GameManager::Shared().SocketIOStartConnect(UNIQUE_SERVER_ADDRESS);
    GameManager::Shared().SocketIOJoinRoom(UNIQUE_MATCH_ID_TRAINING);
}

@end
