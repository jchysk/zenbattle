//
//  AppDelegate.m
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import "AppDelegate.h"
#import "TGAccessoryManager.h"
#import "RootViewController.h"
#import "KeychainItemWrapper.h"
#import "ServerConnection.h"

@implementation AppDelegate
@synthesize inGame;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    inGame = NO;
    
    // Generate our own UUID so we don't anger Apple
	NSString *uuid = [self getUUID];
    
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
    [defaults setValue:uuid forKey:@"uuid"];
    [defaults synchronize];
    
    NSDictionary *dictSave = @{@"uuid" : uuid};

    // Setup the JSON and URL
	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictSave options:NSJSONWritingPrettyPrinted error:nil];
    NSString *strURL = [NSString stringWithFormat:@"%@/device", kApiUrl];
    
    
    // Send an API call
    ServerConnection *APIrequest = [[ServerConnection alloc] initWithURL:strURL method:@"POST"];
    [APIrequest setDataJSON:jsonData];
    [APIrequest startRequestWithCompletionHandler:^(BOOL success, NSData *data, NSDictionary *json) {
        if (success) {
            if ([[json objectForKey:@"status_code"] intValue] < 400 ) {
                [defaults setValue:[[json objectForKey:@"response"] objectForKey:@"user_id"] forKey:@"user_id"];

                [RMUtils showAlertViewWithTitle:@""
                                        message:@"Device Registered"
                                  cancelMessage:@"OK"];
                
            } else {
                
                [RMUtils showAlertViewWithTitle:@""
                                        message:@"Oh no, we suck again! Had a little problem. Please restart me."
                                cancelMessage:@"Sure thing"];
            }
        }
    }];
    
    return YES;
}

+ (AppDelegate *)sharedDelegate {
	return (AppDelegate *)[[UIApplication sharedApplication] delegate];
}

- (NSString *)getUUID
{
    NSString *keychainUuid = [Keychain getStringForKey:@"com.zenbattle.uuid"];
    if (keychainUuid) {
        return keychainUuid;
    }
    
    // Create the UUID
    CFUUIDRef theUuid = CFUUIDCreate(NULL);
    NSString *deviceUuid = (__bridge_transfer NSString *)CFUUIDCreateString(NULL, theUuid);
    [Keychain setString:deviceUuid forKey:@"com.zenbattle.uuid"];
    CFRelease(theUuid);
    
    return deviceUuid;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
