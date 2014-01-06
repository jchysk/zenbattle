//
//  SChartLineSeriesStyle.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SChartScatterSeriesStyle.h"

@class SChartPointStyle;

typedef enum {
    SChartLineCrosshairTraceStyleHorizontal,
    SChartLineCrosshairTraceStyleVertical,
} SChartLineCrosshairTraceStyle;

/** SChartLineSeriesStyle manages the appearance of an instance of `SChartLineSeries` on a chart.
 
 @available Standard
 @available Premium
 @sample Area
 @sample LargeDataSet
 @sample LineChart
 */
@interface SChartLineSeriesStyle : SChartScatterSeriesStyle

#pragma mark -
#pragma mark Styling properties
/** @name Styling properties */

/** Defines whether the area between the line and the axis is filled. 
 
 The color of the area fill is defined by `areaColor` or `areaColorBelowBaseline`. */
@property (nonatomic)             BOOL      showFill;

/* DEPRECATED - This will be taken off the public API in a future commit. */
@property (nonatomic)             BOOL      showFillSet;

/** If `showFill` is set to `YES`, this adds a gradient to the area fill.
 
 The gradient starts at `areaColor` and finishes at `areaColorLowGradient`. */
@property (nonatomic)             BOOL      fillWithGradient;

/* DEPRECATED - This will be taken off the public API in a future commit. */
@property (nonatomic)             BOOL      fillWithGradientSet;

/** The color of the line 
 
 This property is used as long as `showFill` isn't set to `YES`.  If the area is filled, `areaLineColor` is used instead.
 */
@property (nonatomic, retain)     UIColor   *lineColor;

/** The color for the line if the area is filled 
 
 If the area isn't filled, `lineColor` is used instead.
 */
@property (nonatomic, retain)     UIColor   *areaLineColor;

/** The color of the line below the baseline 
 
 This property is used as long as `showFill` isn't set to `YES`.  If the area is filled, `areaLineColorBelowBaseline` is used instead.
 */
@property (nonatomic, retain)     UIColor   *lineColorBelowBaseline;

/** The color for the line if the area is filled 
 
 If the area isn't filled, `lineColorBelowBaseline` is used instead.
 */
@property (nonatomic, retain)     UIColor   *areaLineColorBelowBaseline;

/** The width of the line in pixels 
 
 This property is used as long as `showFill` isn't set to `YES`.  If the area is filled, `areaLineWidth` is used instead.
 */
@property (nonatomic, retain)     NSNumber  *lineWidth;

/** The width of the line in pixels, if the area is filled 
 
 If the area isn't filled, `lineWidth` is used instead.
 */
@property (nonatomic, retain)     NSNumber  *areaLineWidth;

/** The color of the area fill between the line and the axis. 
 @see showFill */
@property (nonatomic, retain)     UIColor   *areaColor;

/** The second color which is used to form a gradient area fill. 
 @see fillWithGradient */
@property (nonatomic, retain)     UIColor   *areaColorLowGradient;

/** The color of the fill between the line and the axis, when the line goes below the series baseline. 
 @see showFill */
@property (nonatomic, retain)     UIColor   *areaColorBelowBaseline;

/** The second color which is used to form a gradient area fill when the line goes below the series baseline 
 @see fillWithGradient */
@property (nonatomic, retain)     UIColor   *areaColorGradientBelowBaseline;

/** Updates this style object using the configuration of the passed in style.
 @param style The new style with which to update this style object. */
- (void)supplementStyleFromStyle:(SChartLineSeriesStyle *)style;

#pragma mark -
#pragma mark Crosshair styling
/** @name Crosshair styling */

/** The direction of the line data to allow the crosshair to traverse it smoothly
 
 Line data points my be ordered from left to right (x-value sorted) or top to bottom (y-value sorted). This parameter lets the chart know in order to aid the tracing process.
 
    typedef enum {
        SChartLineCrosshairTraceStyleHorizontal,
        SChartLineCrosshairTraceStyleVertical
    } SChartLineCrosshairTraceStyle;
 */
@property (nonatomic)             SChartLineCrosshairTraceStyle lineCrosshairTraceStyle;

/* DEPRECATED - This will be taken off the public API in a future commit. */
@property (nonatomic)             BOOL                          lineCrosshairTraceStyleSet;
@end
