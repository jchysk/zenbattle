//
//  SChartRadialDataPoint.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SChartData.h"
@class SChartDataPoint;

/** A `ShinobiChart` can contain either cartesian or radial chart series.  To learn more about cartesian chart series, you should look at the documentation for `SChartCartesianSeries`, or one of its subclasses.  Radial chart series are described in `SChartRadialSeries`.  The data points in radial chart series are represented by this class.
 
 A radial data point is made up of a name and a value (magnitude).  Unlike data points in cartesian series, a `SChartRadialDataPoint` can have only one value.
 
 @available Standard
 @available Premium
 @sample PieChart
 */
@interface SChartRadialDataPoint : SChartDataPoint <SChartData>

#pragma mark -
#pragma mark Data
/** @name Data */

/** The name of this data point. */
@property (nonatomic, retain) NSString *name;

/** The value or magnitude of this data point.
 
 All radial data points have a single value. */
@property (nonatomic, retain) NSNumber *value;

@end
