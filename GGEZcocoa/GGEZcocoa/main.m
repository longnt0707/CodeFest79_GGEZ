//
//  main.m
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[]) {
    return NSApplicationMain(argc, argv);
}


/*
 direction
     1
 2       4
     3
 corner
 1       4
 2       3
 */



/*
 Wifi FSoft Guest
 Account: CodeFest79
 Password: FPTSOFTWARE
 Server: http://54.255.181.99/
 */

/*
 * Drive elephant
 Data Format: JSON.
 
 Data Structure:
 - Requesting is executed successfully.
 {
     "code": 1,
     "status": "OK"
 }
 
 - Requesting is executed failed.
 {
     "code": xx,
     "status": "Error",
     "message": "xxxxxxxx"
 }
 
 Data Definition:
 - code: The code of execution. Type of Number.
     1: Successful.
     100: The room have not created yet.
     101: Invalide key from client(mid or tid).
 - status: The description of code. Type of String.
 - message: The detail description of code. Type of String.
 */

/*
 * Server incomming cycle
 Data Format: JSON.
 
 Data Structure:
 - Requesting is executed successfully.
 {
     "code": 1,
     "status": "OK",
     "round_status": xx,
     "round_time": xx,
     "map": { horizontal: xx, vertical: yy },
     "speed": xx,
     "players": [
         {
             "id": "xxxxx, name:"xxxxx",
             "direction": xx,
             "segments": [
                 {"x: xxxx", "y": xxxx},
                 {"x: xxxx", "y": xxxx},
                 {"x: xxxx", "y": xxxx},
                 {"x: xxxx", "y": xxxx}, ....
             ],
         "score": xxxx
         },
         ....
     ],
     "foods": [
         {
             "id": "Food_xxxx",
             "coordinate": { "x": xxxx, "y": xxxx },
             "type: "NORMAL"
         },
         ....
     ]
 }
 
 - Requesting is executed failed.
 {
     "code": xx,
     "status": "Error",
     "message": "xxxxxxxx"
 }
 
 Data Definition:
 - code: The code of execution. Type of Number.
     1: Successful.
     100: The room have not created yet.
     101: Invalide key from client(mid or tid).
 - round_status: The state of round. Type of Number.
     0: a round is not started.
     1: a round is playing.
     2: a round is pausing.
     3: a round is ended/closed.
 - round_time: The remaining time of round in seconds.
 - map: The information of map. Include size of map by horizotal and vertical squares.
 - speed: The moving speed information of competitors on map.
 - players: The array list of players(include you) on map.
 - direction: The current direction of elephant.
     The value of moving step is defined as below:
     1: Moving UP.
     2: Moving LEFT.
     3: Moving DOWN.
     4; Moving RIGHT.
 - segments: The array of positions of player's elephant members on map. The first item in array is position of Leader Elephant.
 - score: Current score of player on map.
 - foods: The array list of foods(check point elephants) on map.
 - coordinate: The position of food on map.
 - type: The bonus point of food. There are 3 type of bonus point(NORMAL, SUPER, GOLDEN)
 */
