//
//  GameViewController.h
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ShinobiCharts/ShinobiChart.h>
#import "PercentageChart.h"

#define MAIN_ORANGE [UIColor colorWithRed:0.83 green:0.38 blue:0.0 alpha:1.0]
#define LINE_ORANGE [UIColor orangeColor]
#define MAIN_RED [UIColor colorWithRed:0.70 green:0.0 blue:0.0 alpha:1.0]
#define LINE_RED [UIColor redColor]
#define MAIN_GREEN [UIColor colorWithRed:0.47 green:0.7 blue:0.0 alpha:1.0]
#define LINE_GREEN [UIColor colorWithRed:0.0 green:0.7 blue:0.0 alpha:1.0]

@interface GameViewController : UIViewController <SChartDatasource>
{
//    IBOutlet PercentageChart *chart;
//    IBOutlet PercentageChart *chartOpponent;
}
@property(nonatomic, assign) IBOutlet PercentageChart *chart;
@property(nonatomic, assign) IBOutlet PercentageChart *chartOpponent;
@property(nonatomic, assign) CGFloat percentage;
@property(nonatomic, assign) CGFloat percentageOpponent;

-(IBAction) onGo:(id)sender;

-(IBAction) endGame:(id)sender;

@end
