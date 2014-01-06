//
//  SChartRadialChartSeries.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SChartSeries.h"

/** `SChartRadialSeries` represents all radial series within a `ShinobiChart`.  This is the base class for radial series, typically you would use one of its subclasses in your chart.  Currently the following subclasses are available:
 
 - `SChartDonutSeries` - represents donut series.
 - `SChartPieSeries` - represents pie series.
 
 Whereas datapoints for cartesian series require an x and a y value, radial series require a name and a value.
 The x value of a datapoint within a radial series is set as the name of the slice, and the y value is set as its magnitude.  See `SChartRadialDataPoint` for more information.
 
 @available Standard
 @available Premium
 @sa ChartsUserGuide
 @sample PieChart
 */
@interface SChartRadialSeries : SChartSeries

/** @name Label Format */

/** A format string to use for the labels which annotate data within a radial series.
 
 A typical example of the labels would be the labels on each slice in a pie chart.
 
 This defaults to @"%.2f"
 */
@property (nonatomic, retain) NSString               *labelFormatString;

@end
