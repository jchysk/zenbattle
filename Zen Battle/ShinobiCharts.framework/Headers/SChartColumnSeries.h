//
//  SChartColumnSeries.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SChartBarColumnSeries.h"

/** Displays a column series on the chart.  A column series is visualized as a vertical rectangle on the chart, where the height of the rectange equates to the y value of the data point.  The area of the column can be filled, depending on the style of the series.
 
 @available Standard
 @available Premium
 @sa ChartsUserGuide
 @sample ColumnChart
 */
@interface SChartColumnSeries : SChartBarColumnSeries 

#pragma mark -
#pragma mark Styling
/**@name Styling */

/** Returns the style object for this series.
 
 When a series is created, its style is set from the theme.  If you wish to customize the look of the series, you can tweak the properties of the style to configure it correctly, or you can create a new style object and set it on the series.
 
 @see SChartColumnSeriesStyle
 */
-(SChartColumnSeriesStyle *)style;

/** Sets the style object for this series.
 
 You would use this method if you wished to modify the look of the series in its normal state.
 
 @see SChartColumnSeriesStyle
 @param style The new style to use for this series.
 */
-(void)setStyle:(SChartColumnSeriesStyle *)style;

/** Returns the selected style object for this series.
 
 These style settings will be applied when the series is marked as selected (or a datapoint is selected).
 
 When a series is created, its style is set from the theme.  If you wish to customize the look of the series, you can tweak the properties of the style to configure it correctly, or you can create a new style object and set it on the series.
 
 @see SChartColumnSeriesStyle
 */
-(SChartColumnSeriesStyle *)selectedStyle;

/** Sets the selected style object for this series.
 
 These style settings will be applied when the series is marked as selected (or a datapoint is selected).
 
 You would use this method if you wished to modify the look of the series when it is selected.
 
 @see SChartColumnSeriesStyle
 @param selectedStyle The new style to use for this series when it is marked as selected.
 */
-(void)setSelectedStyle:(SChartColumnSeriesStyle *)selectedStyle;

@end
