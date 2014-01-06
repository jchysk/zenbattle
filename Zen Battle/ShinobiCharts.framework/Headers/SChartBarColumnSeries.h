//
//  SChartBarColumnSeries.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SChartCartesianSeries.h"
#import "SChartBarColumnSeriesStyle.h"

/** This is the base class for column and bar series - containing all of the common functions between the two. To display a bar or column series on the chart init and use one of the classes `SChartBarSeries` or `SChartColumnSeries` respectively. 
 
 @available Standard
 @available Premium
 @sample BarChart
 @sample ColumnChart
 @sa ChartsUserGuide
 */
@interface SChartBarColumnSeries : SChartCartesianSeries

#pragma mark -
#pragma mark Config settings

/** The orientation of the axis with which this series is associated.
 
 SChartSeriesOrientation is defined as follows:
 
    typedef enum {
        SChartSeriesOrientationHorizontal,
        SChartSeriesOrientationVertical
    } SChartSeriesOrientation;
 
 The orientation for bar series is vertical, and the orientation for column series is horizontal.
 */
@property (nonatomic, assign) SChartSeriesOrientation orientation;

@end
