//
//  GameViewController.m
//  Zen Battle
//
//  Created by @geomon on 1/4/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import "GameViewController.h"

@interface GameViewController ()

@end

@implementation GameViewController

@synthesize chart, chartOpponent, percentage, percentageOpponent;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    percentage = 10.0;
    percentageOpponent = 10.0;
    
    [chart setMainColor:MAIN_ORANGE];
    [chart setLineColor:LINE_ORANGE];
    [chart setSecondaryColor:[UIColor darkGrayColor]];
    [chart setFontName:@"Helvetica-Bold"];
    [chart setFontSize:30.0];
    [chart setText:@"Focus"];
    
    [chart setPercentage:73.5];
    
    [chartOpponent setMainColor:MAIN_ORANGE];
    [chartOpponent setLineColor:LINE_ORANGE];
    [chartOpponent setSecondaryColor:[UIColor darkGrayColor]];
    [chartOpponent setFontName:@"Helvetica-Bold"];
    [chartOpponent setFontSize:30.0];
    [chartOpponent setText:@"Focus"];
    
    [chartOpponent setPercentage:65.5];

}

-(void) onGo:(id)sender
{
    [chart setPercentage:percentage];
    if( [chart percentage] > 85 )
    {
        [chart setMainColor:MAIN_GREEN];
        [chart setLineColor:LINE_GREEN];
    }
    else if( [chart percentage] > 65 )
    {
        [chart setMainColor:MAIN_ORANGE];
        [chart setLineColor:LINE_ORANGE];
    }
    else
    {
        [chart setMainColor:MAIN_RED];
        [chart setLineColor:LINE_RED];
    }
    percentage +=20;
    if( percentage > 100.0 )
        percentage -= 101.0;
    
    [chartOpponent setPercentage:percentageOpponent];
    if( [chartOpponent percentage] > 85 )
    {
        [chartOpponent setMainColor:MAIN_GREEN];
        [chartOpponent setLineColor:LINE_GREEN];
    }
    else if( [chartOpponent percentage] > 65 )
    {
        [chartOpponent setMainColor:MAIN_ORANGE];
        [chartOpponent setLineColor:LINE_ORANGE];
    }
    else
    {
        [chartOpponent setMainColor:MAIN_RED];
        [chartOpponent setLineColor:LINE_RED];
    }
    percentageOpponent +=20;
    if( percentageOpponent > 100.0 )
        percentageOpponent -= 101.0;
    
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
