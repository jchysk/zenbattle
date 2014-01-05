//
//  ViewController.h
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TGAccessoryManager.h"
#import "TGAccessoryDelegate.h"
#import <ExternalAccessory/ExternalAccessory.h>

// the eSense values
typedef struct {
    int attention;
    int meditation;
} ESenseValues;

// the EEG power bands
typedef struct {
    int delta;
    int theta;
    int lowAlpha;
    int highAlpha;
    int lowBeta;
    int highBeta;
    int lowGamma;
    int highGamma;
} EEGValues;

@interface RootViewController : UIViewController <TGAccessoryDelegate> {
    short rawValue;
    int rawCount;
    int buffRawCount;
    int blinkStrength;
    int poorSignalValue;
    int heartRate;
    float respiration;
    int heartRateAverage;
    int heartRateAcceleration;
    
    ESenseValues eSenseValues;
    EEGValues eegValues;
    
    bool logEnabled;
    NSFileHandle * logFile;
    NSString * output;
    
    UIView * loadingScreen;
    
    NSThread * updateThread;
}

@property (nonatomic) BOOL connected;
@property (weak, nonatomic) IBOutlet UILabel * myCode;
@property (weak, nonatomic) IBOutlet UITextField * opponentCode;
@property (weak, nonatomic) IBOutlet UITextField * wager;

// TGAccessoryDelegate protocol methods
- (void)accessoryDidConnect:(EAAccessory *)accessory;
- (void)accessoryDidDisconnect;
- (void)dataReceived:(NSDictionary *)data;

- (UIImage *)updateSignalStatus;

- (void)initLog;
- (void)writeLog;


@end

