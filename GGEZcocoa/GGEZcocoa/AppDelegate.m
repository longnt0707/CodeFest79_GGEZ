//
//  AppDelegate.m
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#import "AppDelegate.h"
#import "GameManagerWrapper.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
    [GameManagerWrapper QuitMatch];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}


@end
