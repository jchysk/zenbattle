//
//  SChartDataPoint.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SChartData.h"

/** In a `ShinobiChart`, one or more `SChartSeries` are visualised. The data displayed by these series is contained in a data series, `SChartDataSeries`. And, finally, each of these data series contains individual data points. This class represents these data items. 
 
 Each `SChartDataPoint` represents a _simple_ data point in a `SChartDataSeries`. The simple data point is made up of an x and a y object (not multiple x or y objects). It doesn't need to know what these objects are, it merely looks after them. Knowing how to interpet and translate these objects onto a chart is the job of the axis on the chart, which is an instance of `SChartAxis`.
 
 @available Standard
 @available Premium
 @sa ChartsUserGuide
 */
@interface SChartDataPoint : NSObject <SChartData>

#pragma mark -
#pragma mark Data
/** @name Data */

/** The x value for this data point. */
@property (nonatomic, retain) id xValue;

/** The y value for this data point. */
@property (nonatomic, retain) id yValue;

/** Returns the index of this data point in its series.*/
- (NSInteger) index;

#pragma mark -
#pragma mark Selection and Highlighting
/** @name Point selection */

/** Defines whether this point is selected.
 
 When set to `YES` this data point will adopt a selected state. One effect of setting this property is that the style of the data point will change.  The series will apply the selected style to this point, as opposed to the normal style. */
@property (nonatomic, assign) BOOL selected;

@end
