//
//  SChartPointSeries.h
//  ShinobiControls_Source
//
//  Copyright (c) 2013 Scott Logic Ltd. All rights reserved.
//
//

#import "SChartCartesianSeries.h"

/** An SChartPointSeries acts as the base class for both SChartScatterSeries and SChartBubbleSeries and concerns itself with drawing data points. SChartScatterSeries adds the drawing of inner points, whereas SChartBubbleSeries adds the ability to control the drawn datapoint size via SChartBubbleDataPoints. It is therefore unlikely that you will ever want to directly instantiate a series of this type, but should you wish to do so note that the corresponding point style is SChartBasePointStyle.*/

@class SChartPointSeriesStyle;
@class SChartBasePointStyle;

@interface SChartPointSeries : SChartCartesianSeries

/**@name Styling */
/** Override any default settings or theme settings on a _per series_ basis by editing the values in these style objects.
 
 The `SChartScatterSeriesStyle` contains all of the objects relevant to styling a scatter series. */
-(SChartPointSeriesStyle *)style;
-(void)setStyle:(SChartPointSeriesStyle *)style;

/** Style settings in this object will be applied when the series is marked as selected (or a datapoint is selected).*/
-(SChartPointSeriesStyle *)selectedStyle;
-(void)setSelectedStyle:(SChartPointSeriesStyle *)selectedStyle;

@end
