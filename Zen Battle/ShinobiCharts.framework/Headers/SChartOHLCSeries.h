//
//  SChartOHLCSeries.h
//  ShinobiControls_Source
//
//  Copyright (c) 2012 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SChartBarColumnSeries.h"
#import "SChartOHLCSeriesStyle.h"

/** `SChartOHLCSeries` is a type of `SChartSeries` which displays Open-High-Low-Close (OHLC) data on a chart.
 
 Each data point in an OHLC series is visualised as a line between the high and low values, with short perpendicular bars indicating the open and close positions.
 
 Data points in an OHLC series will contain multiple values.  This means that they will be instances of `SChartMultiXDataPoint` or `SChartMultiYDataPoint`, depending on the orientation of the series.  The keys for the values in each data point will be `SChartOHLCKeyOpen`, `SChartOHLCKeyHigh`, `SChartOHLCKeyLow` and `SChartOHLCKeyClose`.
 
 In order to provide the Open, High, Low, and Close values to the chart, the data points in the OHLC series should implement either the `[SChartData sChartXValueForKey:]` method or the `[SChartData sChartYValueForKey:]` method on the `SChartData` protocol, depending on the series orientation.
 
 The series contains an instance of `SChartOHLCSeriesStyle`, which manages the appearance of the series on the chart.
 
 @available Premium
 @sa ChartsUserGuide
 @sample FinancialChart
 */
@interface SChartOHLCSeries : SChartBarColumnSeries

#pragma mark -
#pragma mark Styling
/**@name Styling */

/** Manages the appearance of the OHLC series on the chart.
 
 The default settings of the style are inherited from the chart theme.  You can tweak the appearance of the series by modifying the style.
 
 @see SChartOHLCSeriesStyle
 */
-(SChartOHLCSeriesStyle *)style;

/** Sets the style object for the OHLC series.
 
 @param style The new style object to use for the OHLC series.
 @see style
 */
-(void)setStyle:(SChartOHLCSeriesStyle *)style;

/** Manages the appearance of the OHLC series when it is selected.
 
 Style settings in this object will be applied when the series is marked as selected (or a point is selected).
 
 The default settings of the style are inherited from the chart theme.  You can tweak the appearance of the series by modifying the style.
 
 @see SChartOHLCSeriesStyle
 */
-(SChartOHLCSeriesStyle *)selectedStyle;

/** Sets the style object for the OHLC series when it is selected.
 
 @param selectedStyle The new style object to use.
 @see selectedStyle
 */
-(void)setSelectedStyle:(SChartOHLCSeriesStyle *)selectedStyle;

@end
