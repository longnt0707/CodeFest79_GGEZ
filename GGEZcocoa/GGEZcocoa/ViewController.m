//
//  ViewController.m
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#import "ViewController.h"
#import "GameManagerWrapper.h"

@implementation ViewController {
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    [self.matchIDText setStringValue:[GameManagerWrapper GetTrainingRoomID]];
    
    [GameManagerWrapper InitMatch];
    
    [self.connectLabel setStringValue:@"OK"];
    [self.connectLabel setTextColor:[NSColor greenColor]];
    
    [self.joinLabel setStringValue:@"OK"];
    [self.joinLabel setTextColor:[NSColor greenColor]];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)connectButton:(id)sender {
//    [self.connectLabel setStringValue:@"OK"];
//    [self.connectLabel setTextColor:[NSColor greenColor]];
}

- (IBAction)joinButton:(id)sender {
//    [self.joinLabel setStringValue:@"OK"];
//    [self.joinLabel setTextColor:[NSColor greenColor]];
}


@end
