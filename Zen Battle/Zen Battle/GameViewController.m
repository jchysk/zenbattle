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
{
    ShinobiChart* _chart;
}

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
    
    self.view.backgroundColor = [UIColor whiteColor];
    CGFloat margin = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ? 10.0 : 50.0;
    _chart = [[ShinobiChart alloc] initWithFrame:CGRectInset(self.view.bounds, margin, margin)];
    _chart.title = @"Trigonometric Functions";

    _chart.licenseKey = @"XQHnM4yYvkxXh2jMjAxNDAyMDRpbmZvQHNoaW5vYmljb250cm9scy5jb20=8Ub5sLZAGJmhCHzy53ZwY+wXxYpvfcZf1RrfmK6DE2Q2lgEObUxeO2WeXQSdERASJxFEiuBWjCux4xFsseYn07Ja1VCmdlg8Ndb9k1bJu4vnWGeQEy7LMIZhf7Ryonvx5cAmdZpSWMy4YTBGZtgB/ZgOyVg8=BQxSUisl3BaWf/7myRmmlIjRnMU2cA7q+/03ZX9wdj30RzapYANf51ee3Pi8m2rVW6aD7t6Hi4Qy5vv9xpaQYXF5T7XzsafhzS3hbBokp36BoJZg8IrceBj742nQajYyV7trx5GIw9jy/V6r0bvctKYwTim7Kzq+YPWGMtqtQoU=PFJTQUtleVZhbHVlPjxNb2R1bHVzPnh6YlRrc2dYWWJvQUh5VGR6dkNzQXUrUVAxQnM5b2VrZUxxZVdacnRFbUx3OHZlWStBK3pteXg4NGpJbFkzT2hGdlNYbHZDSjlKVGZQTTF4S2ZweWZBVXBGeXgxRnVBMThOcDNETUxXR1JJbTJ6WXA3a1YyMEdYZGU3RnJyTHZjdGhIbW1BZ21PTTdwMFBsNWlSKzNVMDg5M1N4b2hCZlJ5RHdEeE9vdDNlMD08L01vZHVsdXM+PEV4cG9uZW50PkFRQUI8L0V4cG9uZW50PjwvUlNBS2V5VmFsdWU+"; // TODO: add your trial licence key here!

    chart.autoresizingMask =  ~UIViewAutoresizingNone;

    // add a pair of axes
    SChartNumberAxis *xAxis = [[SChartNumberAxis alloc] init];
    xAxis.title = @"Time";
    _chart.xAxis = xAxis;

    SChartNumberAxis *yAxis = [[SChartNumberAxis alloc] init];
    yAxis.title = @"% of Focus";
    yAxis.rangePaddingLow = @(0.1);
    yAxis.rangePaddingHigh = @(0.1);
    _chart.yAxis = yAxis;

    _chart.legend.hidden = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone);

    // enable gestures
    yAxis.enableGesturePanning = YES;
    yAxis.enableGestureZooming = YES;
    xAxis.enableGesturePanning = YES;
    xAxis.enableGestureZooming = YES;

    _chart.datasource = self;
//    [self.view addSubview:_chart];


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

#pragma - mark
#pragma - Shinob Methods

- (int)numberOfSeriesInSChart:(ShinobiChart *)chart {
    return 2;
}

-(SChartSeries *)sChart:(ShinobiChart *)chart seriesAtIndex:(int)index {

    SChartLineSeries *lineSeries = [[SChartLineSeries alloc] init];
    lineSeries.style.showFill = YES;
    // the first series is a cosine curve, the second is a sine curve
    if (index == 0) {
	lineSeries.title = [NSString stringWithFormat:@"y = cos(x)"];
    } else {
	lineSeries.title = [NSString stringWithFormat:@"y = sin(x)"];
    }

    return lineSeries;
}

- (int)sChart:(ShinobiChart *)chart numberOfDataPointsForSeriesAtIndex:(int)seriesIndex {
    return 100;
}

- (id<SChartData>)sChart:(ShinobiChart *)chart dataPointAtIndex:(int)dataIndex forSeriesAtIndex:(int)seriesIndex {

    SChartDataPoint *datapoint = [[SChartDataPoint alloc] init];

    // both functions share the same x-values
    double xValue = dataIndex / 10.0;
    datapoint.xValue = [NSNumber numberWithDouble:xValue];

    // compute the y-value for each series
    if (seriesIndex == 0) {
	datapoint.yValue = [NSNumber numberWithDouble:cosf(xValue)];
    } else {
	datapoint.yValue = [NSNumber numberWithDouble:sinf(xValue)];
    }

    return datapoint;
}



#pragma - mark
#pragma - Custom Methods

- (IBAction)endGame:(id)sender {
    [AppDelegate sharedDelegate].inGame = NO;
    [self.navigationController popToRootViewControllerAnimated:YES];
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
