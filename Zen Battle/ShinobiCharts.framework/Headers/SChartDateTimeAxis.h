//
//  SChartDateTimeAxis.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SChartDateRange;

/** 
 An SChartDateTimeAxis is a subclass of `SChartAxis` designed to work with data points that use `NSDate`. 
 
  The frequency values for tick marks are expected to be `SChartDateFrequency` objects.
 
 @available Standard
 @available Premium
 
 @sa ChartsUserGuide
 
 @sample FinancialChart
 
 */
@interface SChartDateTimeAxis : SChartAxis

#pragma mark - 
#pragma mark Initialization
/** @name Initialization */
/** Init with a NSDate specific range */
- (id)initWithRange:(SChartDateRange *)range;

@end
