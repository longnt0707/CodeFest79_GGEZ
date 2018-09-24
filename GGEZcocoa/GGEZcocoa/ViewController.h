//
//  ViewController.h
//  GGEZcocoa
//
//  Created by Nguyen The Long on 9/13/18.
//  Copyright © 2018 Nguyen The Long. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController

@property (weak) IBOutlet NSTextField *connectLabel;
@property (weak) IBOutlet NSTextField *joinLabel;
@property (weak) IBOutlet NSTextField *matchIDText;


- (IBAction)connectButton:(id)sender;
- (IBAction)joinButton:(id)sender;

@end

