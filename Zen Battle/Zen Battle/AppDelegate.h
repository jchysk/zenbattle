//
//  AppDelegate.h
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TGAccessoryManager.h"
#import "RMUtils.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, assign) id <TGAccessoryDelegate> delegate;

@property (nonatomic, assign) BOOL inGame;

- (NSString *)getUUID;

+ (AppDelegate *) sharedDelegate;

@end
