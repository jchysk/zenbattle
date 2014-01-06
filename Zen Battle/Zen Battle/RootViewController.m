//
//  ViewController.m
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import "AppDelegate.h"
#import "RootViewController.h"
#import "ServerConnection.h"
#import "NotConnected.h"
#import "GameViewController.h"

@interface RootViewController ()

@property (weak, nonatomic) IBOutlet UIButton * bttnJoin;

@end

@implementation RootViewController
{
    GameViewController * _gameView;
    NotConnected * _notConnectedView;
    NSTimer * _findGameTimer;
}

@synthesize myCode, wager, opponentCode, connected;

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        _gameView = [[GameViewController alloc] initWithNibName:@"GameViewController" bundle:nil];
    } else {
        _gameView = [[GameViewController alloc] initWithNibName:@"GameViewController_iPad" bundle:nil];
    }
    
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
    NSString *code = [defaults stringForKey:@"user_id"];
    myCode.text = code;
    BOOL rawEnabled = [defaults boolForKey:@"raw_enabled"];
    
    TGAccessoryType accessoryType = (TGAccessoryType)[defaults integerForKey:@"accessory_type_preference"];
    [[TGAccessoryManager sharedTGAccessoryManager] setupManagerWithInterval:5.0 forAccessoryType:accessoryType];
    
    [[TGAccessoryManager sharedTGAccessoryManager] setDelegate: self];
    [[TGAccessoryManager sharedTGAccessoryManager] setRawEnabled:rawEnabled];
    
    logEnabled = [defaults boolForKey:@"logging_enabled"];
    logEnabled = YES;
    if(logEnabled) {
        [self initLog];
        NSLog(@"Logging enabled");
    }
    
    [self requestForPossibleGame];
}

#pragma mark

- (void)setFindGameTimer
{
    [_findGameTimer invalidate];
    _findGameTimer = nil;
    _findGameTimer = [NSTimer scheduledTimerWithTimeInterval:5.0f
                                                      target:self
                                                    selector:@selector(requestForPossibleGame)
                                                    userInfo:nil
                                                     repeats:NO];
}

- (void)requestForPossibleGame
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *uuid = [defaults valueForKey:@"uuid"];
    
    // Send an API call
    NSString *strURL = [NSString stringWithFormat:@"%@/start?uuid=%@", kApiUrl, uuid];
    ServerConnection *APIrequest = [[ServerConnection alloc] initWithURL:strURL method:@"GET"];
    [APIrequest startRequestWithCompletionHandler:^(BOOL success, NSData *data, NSDictionary *json) {
        if (success) {
            RMLog(@"JSON: %@", json);
            if ([AppDelegate sharedDelegate].inGame == NO) {
                RMLog(@"End timer and start game");
                [_findGameTimer invalidate];
                _findGameTimer = nil;
                
                id statusCode = [json objectForKey:@"status_code"];
                if (statusCode == nil) {
                    RMLog(@"No status available");
                    return;
                }
                
                if ([statusCode isKindOfClass:[NSNumber class]]) {
                    statusCode = [statusCode stringValue];
                }
                
                if ([statusCode isEqualToString:@"200"]) {
                    
                    NSDictionary *response = [json objectForKey:@"response"];
                    if (response && [response isKindOfClass:[NSDictionary class]]) {
                        
                        id gameId = [response objectForKey:@"game_id"];
                        [[NSUserDefaults standardUserDefaults] setObject:gameId forKey:@"game_id"];
                        
                        [UIView animateWithDuration:0.2
                                         animations:^{
                                             _bttnJoin.alpha = 1.0f;
                                         }];
                        
                    }
                }
                
            } else {
                // start a new timer to check again
                [self setFindGameTimer];
            }
        } else {
            // start a new timer to check again
            RMLog(@"No result, Response: %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
            [self setFindGameTimer];
        }
    }];
}

#pragma mark

- (void)viewDidAppear:(BOOL)animated {
    if([[TGAccessoryManager sharedTGAccessoryManager] accessory] != nil) {
        [[TGAccessoryManager sharedTGAccessoryManager] startStream];
        NSLog(@"starting stream");
        connected = YES;
    } else {
        NSLog(@"accessory not found");
        connected = NO;
        
        if (_notConnectedView == nil) {
            if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
                _notConnectedView = [[NotConnected alloc] initWithNibName:@"NotConnected" bundle:nil];
                [self presentViewController:_notConnectedView animated:YES completion:nil];
            } else {
                _notConnectedView = [[NotConnected alloc] initWithNibName:@"NotConnected_iPad" bundle:nil];
                [self presentViewController:_notConnectedView animated:YES completion:nil];
            }
        }
    }
    
    if(updateThread == nil) {
        //        updateThread = [[NSThread alloc] initWithTarget:self selector:@selector(updateTable) object:nil];
        [updateThread start];
    }
    
    //NSLog(@"TGAccessory version: %d", [[TGAccessoryManager sharedTGAccessoryManager] getVersion]);

}

- (IBAction)startGame:(id)sender {
    
    [AppDelegate sharedDelegate].inGame = YES;
    
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    // Set the UUID
    [dict setValue:[[NSUserDefaults standardUserDefaults] valueForKey:@"uuid"] forKey:@"uuid"];
    [dict setValue:wager.text forKey:@"wager"];
    [dict setValue:opponentCode.text forKey:@"user_id"];
    
    // Setup the JSON and URL
	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:nil];
    NSString *strURL = [NSString stringWithFormat:@"%@/start", kApiUrl];
    NSString* jsonString = [[NSString alloc] initWithBytes:[jsonData bytes] length:[jsonData length] encoding:NSUTF8StringEncoding];
    NSLog(@"jsonData: %@", jsonString );
    
    // Send an API call
    ServerConnection *APIrequest = [[ServerConnection alloc] initWithURL:strURL method:@"POST"];
    [APIrequest setDataJSON:jsonData];
    [APIrequest startRequestWithCompletionHandler:^(BOOL success, NSData *data, NSDictionary *json) {
        if (success) {
            if ([[json objectForKey:@"status_code"] intValue] < 400 ) {
                [RMUtils logWithNamespace:@"startGame" withMessage:@"Starting Game: %@", json];
		[[NSUserDefaults standardUserDefaults] setValue:[[json objectForKey:@"response"] objectForKey:@"game_id"] forKey:@"game_id"];
            } else {
                [RMUtils logWithNamespace:@"startGame" withMessage:@"ERROR SENDING DATA", json];
            }
        }
	[self.navigationController pushViewController:_gameView animated:YES];
    }];
}

- (IBAction)joinExistingGame:(id)sender
{
    [AppDelegate sharedDelegate].inGame = YES;
    [self.navigationController pushViewController:_gameView animated:YES];
}

- (UIImage *)updateSignalStatus {
    
    if(poorSignalValue == 0) {
        return [UIImage imageNamed:@"Signal_Connected"];
    }
    else if(poorSignalValue > 0 && poorSignalValue < 50) {
        return [UIImage imageNamed:@"Signal_Connecting3"];
    }
    else if(poorSignalValue > 50 && poorSignalValue < 200) {
        return [UIImage imageNamed:@"Signal_Connecting2"];
    }
    else if(poorSignalValue == 200) {
        return [UIImage imageNamed:@"Signal_Connecting1"];
    }
    else {
        return [UIImage imageNamed:@"Signal_Disconnected"];
    }
}

#pragma mark -
#pragma mark TGAccessoryDelegate protocol methods

//  This method gets called by the TGAccessoryManager when a ThinkGear-enabled
//  accessory is connected.
- (void)accessoryDidConnect:(EAAccessory *)accessory {
    // toss up a UIAlertView when an accessory connects
    UIAlertView * a = [[UIAlertView alloc] initWithTitle:@"Accessory Connected"
                                                 message:[NSString stringWithFormat:@"A ThinkGear accessory called %@ was connected to this device.", [accessory name]]
                                                delegate:nil
                                       cancelButtonTitle:@"Okay"
                                       otherButtonTitles:nil];
    [a show];
    
    // start the data stream to the accessory
    [[TGAccessoryManager sharedTGAccessoryManager] startStream];
    
    // set up the current view
    [self setLoadingScreenView];
}

//  This method gets called by the TGAccessoryManager when a ThinkGear-enabled
//  accessory is disconnected.
- (void)accessoryDidDisconnect {
    // toss up a UIAlertView when an accessory disconnects
    UIAlertView * a = [[UIAlertView alloc] initWithTitle:@"Accessory Disconnected"
     message:@"The ThinkGear accessory was disconnected from this device."
     delegate:nil
     cancelButtonTitle:@"Okay"
     otherButtonTitles:nil];
     [a show];

    
    // set up the appropriate view
    
    [self setLoadingScreenView];
}

//  This method gets called by the TGAccessoryManager when data is received from the
//  ThinkGear-enabled device.
- (void)dataReceived:(NSDictionary *)data {

    [self sendData:(NSDictionary *)data];
    
    NSString * temp = [[NSString alloc] init];
    NSDate * date = [NSDate date];
    
    if([data valueForKey:@"blinkStrength"])
        blinkStrength = [[data valueForKey:@"blinkStrength"] intValue];
    
    if([data valueForKey:@"raw"]) {
        rawValue = [[data valueForKey:@"raw"] shortValue];
    }
    
    if([data valueForKey:@"heartRate"])
        heartRate = [[data valueForKey:@"heartRate"] intValue];
    
    if([data valueForKey:@"poorSignal"]) {
        poorSignalValue = [[data valueForKey:@"poorSignal"] intValue];
        temp = [temp stringByAppendingFormat:@"%f: Poor Signal: %d\n", [date timeIntervalSince1970], poorSignalValue];
        //NSLog(@"buffered raw count: %d", buffRawCount);
        buffRawCount = 0;
    }
    
    if([data valueForKey:@"respiration"]) {
        respiration = [[data valueForKey:@"respiration"] floatValue];
    }
    
    if([data valueForKey:@"heartRateAverage"]) {
        heartRateAverage = [[data valueForKey:@"heartRateAverage"] intValue];
    }
    if([data valueForKey:@"heartRateAcceleration"]) {
        heartRateAcceleration = [[data valueForKey:@"heartRateAcceleration"] intValue];
    }
    
    if([data valueForKey:@"rawCount"]) {
        rawCount = [[data valueForKey:@"rawCount"] intValue];
    }
    
    
    // check to see whether the eSense values are there. if so, we assume that
    // all of the other data (aside from raw) is there. this is not necessarily
    // a safe assumption.
    if([data valueForKey:@"eSenseAttention"]){
        
        eSenseValues.attention =    [[data valueForKey:@"eSenseAttention"] intValue];
        eSenseValues.meditation =   [[data valueForKey:@"eSenseMeditation"] intValue];
        temp = [temp stringByAppendingFormat:@"%f: Attention: %d\n", [date timeIntervalSince1970], eSenseValues.attention];
        temp = [temp stringByAppendingFormat:@"%f: Meditation: %d\n", [date timeIntervalSince1970], eSenseValues.meditation];
        
        eegValues.delta =       [[data valueForKey:@"eegDelta"] intValue];
        eegValues.theta =       [[data valueForKey:@"eegTheta"] intValue];
        eegValues.lowAlpha =    [[data valueForKey:@"eegLowAlpha"] intValue];
        eegValues.highAlpha =   [[data valueForKey:@"eegHighAlpha"] intValue];
        eegValues.lowBeta =     [[data valueForKey:@"eegLowBeta"] intValue];
        eegValues.highBeta =    [[data valueForKey:@"eegHighBeta"] intValue];
        eegValues.lowGamma =    [[data valueForKey:@"eegLowGamma"] intValue];
        eegValues.highGamma =   [[data valueForKey:@"eegHighGamma"] intValue];
        
    }
    
    _gameView.percentage = eSenseValues.attention;
    [_gameView.chart setPercentage:eSenseValues.attention];
    _gameView.percentageOpponent = 100 - eSenseValues.attention;
    [_gameView.chartOpponent setPercentage:eSenseValues.attention];
    
    if(logEnabled) {
        output = [NSString stringWithString:temp];
        [self performSelectorOnMainThread:@selector(writeLog) withObject:nil waitUntilDone:NO];
    }
    

}

-(void)sendData:(NSDictionary *)data {
    
    if ([AppDelegate sharedDelegate].inGame) {
        
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict addEntriesFromDictionary:data];
        // Set the UUID
        [dict setValue:[[NSUserDefaults standardUserDefaults] valueForKey:@"uuid"] forKey:@"uuid"];
        [dict setValue:[[NSUserDefaults standardUserDefaults] valueForKey:@"game_id"] forKey:@"game_id"];
        
        // Setup the JSON and URL
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:nil];
        NSString *strURL = [NSString stringWithFormat:@"%@/eeg", kApiUrl];
        NSString* jsonString = [[NSString alloc] initWithBytes:[jsonData bytes] length:[jsonData length] encoding:NSUTF8StringEncoding];
        NSLog(@"jsonData: %@", jsonString );

        // Send an API call
        ServerConnection *APIrequest = [[ServerConnection alloc] initWithURL:strURL method:@"POST"];
        [APIrequest setDataJSON:jsonData];
        [APIrequest startRequestWithCompletionHandler:^(BOOL success, NSData *data, NSDictionary *json) {
            if (success) {
                if ([[json objectForKey:@"status_code"] intValue] < 400 ) {
                    [RMUtils logWithNamespace:@"sendData" withMessage:@"Data Received", json];
                    
                    // {"status_code": 200, "response": {"status": "finished", "1": 0.0, "2": 0.0}}
                    if ([[[[json objectForKey:@"response"] objectForKey:@"status"] stringValue] isEqualToString:@"finished"]) {
                    
                        [RMUtils logWithNamespace:@"sendData" withMessage:@"FINISHED"];
                        
                    }
                } else {
                    [RMUtils logWithNamespace:@"sendData" withMessage:@"ERROR SENDING DATA", json];
                }
            }
        }];
    }
}

#pragma mark -
#pragma mark Internal helper methods

- (void)initLog {
    //get the documents directory:
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    //make a file name to write the data to using the documents directory:
    NSString *fileName = [NSString stringWithFormat:@"%@/log.txt", documentsDirectory];
    
    //check if the file exists if not create it
    if(![[NSFileManager defaultManager] fileExistsAtPath:fileName])
        [[NSFileManager defaultManager] createFileAtPath:fileName contents:nil attributes:nil];
    
    logFile = [NSFileHandle fileHandleForWritingAtPath:fileName];
    [logFile seekToEndOfFile];
    
    output = [[NSString alloc] init];
}

- (void)writeLog {
    if (logEnabled && logFile) {
        [logFile writeData:[output dataUsingEncoding:NSUTF8StringEncoding]];
    }
}

//  Determine whether to display the blank "Please connect an accessory" screen or the TableView.
- (void)setLoadingScreenView {

    if([[TGAccessoryManager sharedTGAccessoryManager] accessory] == nil){
        connected = NO;
        if (_notConnectedView == nil) {
            if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
                _notConnectedView = [[NotConnected alloc] initWithNibName:@"NotConnected" bundle:nil];
                [self presentViewController:_notConnectedView animated:YES completion:nil];
            } else {
                _notConnectedView = [[NotConnected alloc] initWithNibName:@"NotConnected_iPad" bundle:nil];
                [self presentViewController:_notConnectedView animated:YES completion:nil];
            }
        }
    }
    else {
        if(!connected) {
            [_notConnectedView dismissViewControllerAnimated:YES completion:nil];
            _notConnectedView = nil;
        }
        [loadingScreen removeFromSuperview];
    }
}

//- (void)updateTable {
//    while(1) {
//        NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//        [[self tableView] performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
//        [NSThread sleepForTimeInterval:0.15];
//        [pool drain];
//        
//    }
//}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
