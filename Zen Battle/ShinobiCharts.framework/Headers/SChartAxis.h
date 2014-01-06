//
//  SChartAxis.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class SChartGLView;
@class SChartInternalDataPoint;
@class SChartRange;
@class SChartCanvasUnderlay;
@class ShinobiChart;
@class SChartTickMark;
@class SChartSeries;
@class SChartAxisStyle;
@class SChartTitle;
@class SChartCartesianSeries;
@class SChartBarColumnSeries;
@class SChartAxis;
@class SChartTickLabel;
@class SChartTickLabelFormatter;
@class SChartSkipList;
@protocol SChartData;

typedef enum {
    SChartOrientationHorizontal,
    SChartOrientationVertical
} SChartOrientation;

typedef enum {
    SChartAxisPositionNormal,
    SChartAxisPositionReverse,
} SChartAxisPosition;

typedef enum {
    SChartAxisZoomLevelOriginal,
    SChartAxisZoomLevelDouble,
    SChartAxisZoomLevelHalf
} SChartAxisZoomLevel;

typedef  enum {
    TickLabelOrientationHorizontal,
    TickLabelOrientationDiagonal,
    TickLabelOrientationVertical
} TickLabelOrientation;

typedef enum {
    SChartAxisPanToStart,
    SChartAxisPanToEnd,
    SChartAxisPanToCenter
} SChartAxisPanTo;

typedef enum {
    SChartTickLabelClippingModeTicksAndLabelsPersist,
    SChartTickLabelClippingModeTicksPersist,
    SChartTickLabelClippingModeNeitherPersist
} SChartTickLabelClippingMode;

typedef enum
{
    SChartDiscontinuousTickLabelClippingLow,
    SChartDiscontinuousTickLabelClippingHigh,
} SChartDiscontinuousTickLabelClipping;

/** 
 The SChartAxis is responsible for managing the coordinate space of the chart. It is the link between the set of real data in a series and the laying down of that series on a chart in a desired manner. Each series on the chart is linked to an axis and this SChartAxis is responsible for managing all of the series linked to it.
 
 For cartesian series, it is expected that you will provide instances of <i>a subclass of</i> SChartAxis each for the `xAxis` and `yAxis` of the chart. If not set, both axes will default to instances of `SChartNumberAxis`.
 
 The axis range can be set to a desired range or left to calculate its own minimum and maximum. When auto-calculating the range, it will consider all data series associated with it.
 
 The axis is also the home of the tick marks and their labels. These can be auto-calculated or set to specific values.
 
 
 @available Standard
 @available Premium
 
 @sa ChartsUserGuide
 
 @see SChartNumberAxis
 @see SChartDateTimeAxis
 @see SChartDiscontinuousNumberAxis
 @see SChartDiscontinuousDateTimeAxis
 @see SChartCategoryAxis
 @see SChartLogarithmicAxis
 
 @see SChartAxisStyle
 
 @sample Area
 @sample BarChart
 @sample ColumnChart
 @sample FinancialChart
 @sample LargeDataSet
 @sample LineChart
 
 */
@interface SChartAxis : NSObject

#pragma mark -
#pragma mark Initializing and managing the axis
/** @name Initializing the axis */
/** Create an axis for a given chart area.*/
- (id)init;

/** Create an axis for a given chart area with a default range.
 
 See `defaultRange` for the implications of setting this type of range. */
- (id)initWithRange:(SChartRange *)range;

#pragma mark -
#pragma mark Chart
/** A pointer to the parent chart
 
 The axis retains a handle on the chart using it so that it can access user-set drawing parameters. */
@property (nonatomic, assign) ShinobiChart *chart;

#pragma mark -
#pragma mark Position
/** @name Positioning the Axis */
/** The `SChartAxisPosition` defines whether the axis will be positioned at the normal or reverse location.
 For xAxes, the 'normal' position is below the plot area, with the 'reverse' location above.
 For yAxes, the 'normal' position is to the left of the plot area and the 'reverse' position is to the right.
 Often, it is a good idea when adding a secondary axis, using `addXAxis` or `addYAxis`, to position one axis in each position.

    typedef enum {
    SChartAxisPositionNormal,
    SChartAxisPositionReverse,
    } SChartAxisPosition 
*/

@property (nonatomic) SChartAxisPosition axisPosition;

/** The value at which an axis intersects with the opposite axis. For example, if this is set to 0 on a yAxis, it will intersect with the xAxis at the point which corresponds to a value of 0 in data terms.
 
 If there is more than one axis of the other orientation on the chart, the primary axis will be used.
 */
@property (nonatomic, retain) NSNumber *axisPositionValue;

/** This property determines whether the axis labels will move with the axis lines and tick marks when an axis position value has been set.
 
    If this is set to YES, labels will stay fixed at the bottom/left or top/right of the chart depending on the axisPosition parameter.
 */
@property (nonatomic) BOOL axisLabelsAreFixed;


#pragma mark -
#pragma mark Styling
/** @name Styling */
/** The `SChartAxisStyle` object that manages the appearance of the axis.
 
 Setting these values will override any values set by the theme.
 Calling applyTheme on the chart, though, will reapply the theme style.
 */
@property (nonatomic, retain) SChartAxisStyle *style;

/** Specifies a fixed width for the axis area that won't change.
 
 This is useful to fix the axis in position to align multiple charts. However, it may restrict the options for labelling the chart. */
@property (nonatomic, retain) NSNumber *width;

/** The text to display in the axis title 
 
 @see SChartTitle. */
@property (nonatomic, retain) NSString *title;

/** The title for the axis 
 
 @see SChartTitle
 @see SChartAxisTitleStyle
 */
@property (nonatomic, retain) SChartTitle *titleLabel;

#pragma mark -
#pragma mark Range
/** @name Ranges */

/** The current _displayed_  range of the axis.
 
 This property is the actual range currently displayed on the visible area of the chart- which may not be the range that was explicitly set. The axis may make small adjustments to the range to make sure that whole bars are displayed etc. This is a `readonly` property - explicit requests to change the axis range should be made through the method `setRangeWithMinimum:andMaximum:` 
 
 @see SChartRange
 @see SChartNumberRange
 @see SChartDateRange */
@property (nonatomic, retain, readonly) SChartRange *axisRange;

/** A readonly property indicating the total data range across all series represented by this axis.
 
 These are absolute minimum and absolute maximum values from the data series represented by this axis.
 This range does not necessarily represent exactly the range of what is drawn on the axis, depending on how the data is visualised - for this see `visibleRange`. 
 
 @see SChartRange
 @see SChartNumberRange
 @see SChartDateRange 
 */
@property (nonatomic, readonly) SChartRange *dataRange;

/** This is the range that will be displayed after the chart initially loads - and if the zoom is reset.
 
 By default it is set to be the `dataRange`, but can be set to custom values.
 
 @see SChartRange
 @see SChartNumberRange
 @see SChartDateRange 
 */
@property (nonatomic, retain) SChartRange *defaultRange;

/** In data terms, the amount by which the lower limit of the axis range will be lowered past the range of the data.
 
 By default, this is set to 0. */
@property (nonatomic, retain) id rangePaddingLow;

/** In data terms, the amount by which the upper limit of the axis range will be raised past the range of the data.
 
 By default, this is set to 0. */
@property (nonatomic, retain) id rangePaddingHigh;

/** Whether or not the user is permitted to pan outside of the user-set default range.
 
 With a user-set default range this can be used to either limit panning and zooming to a subset of the data or to allow panning or zooming outside of the data range but whilst still setting limits. If the default range is not set, it defaults to `dataRange` and `allowPanningOutOfMaxRange' should be used instead. */
@property (nonatomic) BOOL    allowPanningOutOfDefaultRange;

/** Whether or not the user is permitted to pan outside of the union of the data range and the default range 
 
 If this is enabled but `allowPanningOutOfDefaultRange` is disabled, panning will still be restricted to the data range*/
@property (nonatomic) BOOL    allowPanningOutOfMaxRange;

/** Whether or not the axis allows the range to temporarily go past the limit specified before bouncing back in
 
 If this is enabled, the range will bounce back into the given limit. If there is no range limit, this option does nothing */
@property (nonatomic) BOOL    animationEdgeBouncing;

/** Whether or not the axis animates when zooming programmatically, or via double-tap on box gesture. 
 
 If this is enabled, the axis will zoom smoothly from starting to target zoom levels. */
@property (nonatomic) BOOL    animationEnabled;

/** The frame bounding the area where the axis is drawn.
 
 This area in terms of the chart frame within which the axis line, tickmarks and ticklabels are drawn. It can have a fixed width if the `width` property is set, otherwise it wil be dynamic and affected by the tickmarks and their labels.  */
@property (nonatomic)         CGRect axisFrame;

/** The orientation of the axis. 
 
 Axis objects are universal and may be used as an xAxis (horizontal) or as a yAxis (vertical). This property is determined when the axis is assigned to the chart.  
 
    typedef enum {
    SChartOrientationHorizontal,
    SChartOrientationVertical
    } SChartOrientation;
 */
@property (nonatomic, readonly) SChartOrientation axisOrientation;

/** The offset to the axis object from the edge of the canvas, in points.
 
 For xAxes, this is from the bottom edge of the canvas frame for axes at the 'normal' `axisPosition` and from the top for axes at the 'reverse' `axisPosition`.
 For yAxes, this is from the left edge of the canvas frame for axes at the 'normal' `axisPosition` and from the right for axes at the 'reverse' `axisPosition`.
 */
@property (nonatomic, assign) float secondaryAxisOffset;

/** Attempts to set the current visible range `axisRange` to a range with the given minimum and maximum values.
 
 Given any restrictions on setting the range, such as `allowPanningOutOfMaxRange` etc, this method will attempt to set the current axis range.
 
 @param minimum - the minimum value to be displayed, in data terms.
 @param maximum - the maximum value to be displayed, in data terms.
 @return Whether or not the operation was successful. 
 
 The permissable types of minimum and maximum will vary depending on the type of axis in use. The range of an `SChartNumberAxis` should be set using two objects of type `NSNumber` for `minimum` and `maximum`, whilst that of an `SChartDateTimeAxis` can be configured using either `NSNumber` or `NSDate` minima and maxima. In the case of `SChartCategoryAxis`, the first value has a nominal integer value of '0' and the nth value, 'n-1'.

 A few examples:
 
    // Range from 20 to 140 on an SChartNumberAxis.
    [myNumberAxis setRangeWithMinimum: @20 andMaximum: @140];
 
    // Range from June 2013 to January 2014 (approx.) on an SChartDateTimeAxis.
    [myDateTimeAxis setRangeWithMinimum: [NSDate dateWithTimeIntervalSince1970: 86400.*365*43.5] andMaximum: [NSDate dateWithTimeIntervalSince1970: 86400.*365*44]];
 
    // Range between the third and fifth elements on an SChartCategoryAxis.
    [myCategoryAxis setRangeWithMinimum: @2 andMaximum: @6];
 */
- (BOOL)setRangeWithMinimum:(id)minimum andMaximum:(id)maximum;

/** Attempts to set the current visible range `axisRange` to a range with the given minimum and maximum values.
 
 Given any restrictions on setting the range, such as `allowPanningOutOfMaxRange` etc, this method will attempt to set the current axis range.
 This implementation allows you to explicitly set whether to animate the transition to the new range or not.
 
 @param animation - Whether or not to animate the range change.
 @return Whether or not the operation was successful.
 
 See `setRangeWithMinimum:andMaximum`.
 */
- (BOOL)setRangeWithMinimum:(id)minimum andMaximum:(id)maximum withAnimation:(BOOL)animation;

/* DEPRECATED - this will be removed from the API soon. */
- (BOOL)setRangeWithMinimum:(id)minimum andMaximum:(id)maximum withAnimation:(BOOL)animation usingBounceLimits:(BOOL)rangeChecks;

/* DEPRECATED - this will be removed from the API soon. */
- (BOOL)beyondAxisLimits;

/* DEPRECATED - this will be removed from the API soon. */
- (BOOL)beyondAxisLimitsOnBothSides;

/* DEPRECATED - this will be removed from the API soon. */
- (BOOL)beyondAxisMinLimit;

/* DEPRECATED - this will be removed from the API soon. */
- (BOOL)recheckAxisRange;

/** Creates a new range object with the given maximum and minimum 
 
 The subclass of SChartRange that is returned will correspond to the axis type. 
 
 @see SChartRange
 @see SChartNumberRange
 @see SChartDateRange
 */
- (SChartRange *)getNewRangeWithMinimum:(NSNumber *)minimum withMaximum:(NSNumber *)maximum;

/** Returns a range within which all the visible (non-hidden) series on this axis will be displayed.
 
 Setting the default range to this range should frame your data nicely.
 Note that this will take baselines, bar/column widths etc into consideration and so is not necessarily the same as `dataRange`.
 
 @see SChartRange
 @see SChartNumberRange
 @see SChartDateRange
 */
- (SChartRange *)visibleRange;

#pragma mark -
#pragma mark Tick Marks

/** @name Tickmarks and labels */
/** An appropriate object representing the major tick mark frequency
 
 If this value is set, the chart will not make any auto-calculations for major tick marks and only display a major tick mark at this frequency, regardless of zoom level. The definition of appropriate value is dependent upon the axis type - ie: `SChartNumberAxis`, `SChartDateTimeAxis`. The first major tick mark will be at the absolute minimum data value across all series for this axis - with subsequent major tick marks incrementing by the frequency. To change this initial value see `anchorPoint`. By default an appropriate major tick mark value will be selected by the chart and will adapt as the user zooms the chart. */
@property (nonatomic, retain) id majorTickFrequency;

/** An appropriate object representing the minor tick mark frequency
 
 If this value is set, the chart will not make any auto-calculations for minor tick marks and only display a minor tick mark at these values, regardless of zoom level. The first minor tick mark will be at the absolute minimum data value across all series for this axis - with subsequent minor tick marks incrementing by the frequency. To change this initial value see `anchorPoint`. By default an appropriate minor tick mark value will be selected by the chart and will adapt as the user zooms the chart. In order for the chart to adhere to a non-nil value you have assigned to this property you must also set a `majorTickFrequency`.  */
@property (nonatomic, retain) id minorTickFrequency;

/** Returns the current major tick frequency in use by this axis.
 @warning *Important* `majorTickFrequency` returns the frequency that you have manually set, whereas `currentMajorTickFrequency` returns the frequency currently in use - the two are not necessarily the same.*/
- (id)currentMajorTickFrequency;
/** Returns the current minor tick frequency in use by this axis.
 @warning *Important* `minorTickFrequency` returns the frequency that you have manually set, whereas `currentMinorTickFrequency` returns the frequency currently in use - the two are not necessarily the same.*/
- (id)currentMinorTickFrequency;

/** The start point for the calculation of tick marks.
 
 For example, if your `axisRange` is @1 to @9, your `anchorPoint` is @0 and the `currentMajorTickFrequency` is @2, you will get tickmarks and labels at @2, @4, @6 and @8, assuming that the labels' text and the clipping settings permit.
 
 Regardless of whether a tick mark frequency has been set or automatically calculated, it must start somewhere. This value acts as the origin point for tickmarks on the axis.
 This defaults to the `[dataRange minimum]`. */
@property (nonatomic, retain) id anchorPoint;

/** @warning *DEPRECATED* - use `labelFormatter` to specify formatting.
 
 A string to format each tick mark label - actual format is dependent on axis type.
 If an axis is auto-calculating tick marks - it will select an appropriate label format (ie: months, days, hours, etc). However, setting this value will override all tick mark labels to use this formatter. 
 
- For a number axis, use the float formatter, ie: `@"%1.2f mm"`.
- For a date axis, use the date formatter, ie: `@"dd MMM"`.
- For a category axis, use the string formatter, ie: `@"%@ District"`.

 */
@property (nonatomic, retain) NSString *labelFormatString;

/* DEPRECATED - this will be removed from the API soon. */
@property (nonatomic, assign) CGPoint labelSizeScalers;

/** A label formatter for tick mark labels.
 
 Use this to set formatting options for tick labels on this axis - currencies, (negative) value styles etc.
 
 @see SChartTickLabelFormatter
 */
@property (nonatomic, retain) SChartTickLabelFormatter *labelFormatter;

/** This property allows you to alter the tick label clipping mode for the upper end of an axis.

    typedef enum {
    SChartTickLabelClippingModeTicksAndLabelsPersist,
    SChartTickLabelClippingModeTicksPersist,
    SChartTickLabelClippingModeNeitherPersist
    } SChartTickLabelClippingMode;`

<ol>
<li>`SChartTickLabelClippingModeTicksAndLabelsPersist` - Keep both the label and tick visible for as long as possible, allowing the label to overlap with adjacent axes.</li>
<li>`SChartTickLabelClippingModeTicksPersist`          - Keep the tick mark visible for as long as possible and clip the label as soon as it reaches the edge of its view.</li>
<li>`SChartTickLabelClippingModeNeitherPersist`        - Keep the tick mark visible as long as the tick label is visible - as soon as the tick label reaches its bounds, and is clipped, clip the tick mark too. </li>
 </ol>
 */
@property (nonatomic) SChartTickLabelClippingMode tickLabelClippingModeHigh;

/**
This property allows you to alter the tick label clipping mode for the lower end of an axis.
 
 See `tickLabelClippingModeHigh`.
 */
@property (nonatomic) SChartTickLabelClippingMode tickLabelClippingModeLow;

/**
This property comes into effect for discontinuous axes over a discontinuity.
When there are labels either side of a discontinuity which overlap, either
the higher or lower label will be removed, this property controls which.

    typedef enum
    {
        SChartDiscontinuousTickLabelClippingLow,
        SChartDiscontinuousTickLabelClippingHigh,
    } SChartDiscontinuousTickLabelClipping;

SChartDiscontinuousTickLabelClippingLow removes the lower tick label while
SChartDiscontinuousTickLabelClippingHigh removes the higher.

Defaults to 'SChartDiscontinuousTickLabelClippingLow'.
*/

@property (nonatomic) SChartDiscontinuousTickLabelClipping discontinuousTickLabelClipping;

/** This will call `sChart:alterTickMark:onAxis:` if your delegate implements it. Implement this method in your axis subclass to alter tickmarks on that axis only.
 
 This method gives you each tickMark just before it is added to its axis. Use this to set colors, borders, or even move the tickmark's label elsewhere.
 */
-(void)alterTickMark:(SChartTickMark *)tickMark;

/**
This property controls how the auto-tick-frequency calculations are done.
Normally, the axis will use the full range of data to calculate how often to
place a tick-mark, however if the range has discontinuities, this option allows
the axis to exclude the discontinuities in its calculations of the range over
which the tick marks are added.

For example - you have a year range, but are excluding 7 months using
discontinuous periods. If this property is 'NO', the tick labels will be added
as if the range is one year. If this property is 'YES', the tick labels will be
added as if the range is 5 months (12 - 7).

If YES, the axis will exclude discontinuities when calculating the range.

Defaults to 'NO'.
*/
@property (nonatomic) BOOL calculateMajorTickFrequencyFromDiscontinuousRange;


#pragma mark -
#pragma mark BarColumn Series
/** @name BarColumn Series */
/** The smallest change in value between any adjacent bars or columns. 
 
 Specifying this can improve the render time of the chart - it will not have to traverse all of the data to compare differences. */
@property (nonatomic) double barColSpacing;

/** The minimum value of a bar or column across all of the bar/column series for this axis.
 You can set this by using the appropriate `configureBars:withMinY:withMaxY:` or `configureBars:withMinY:withMaxY:` method for the axis orientation. */
@property (nonatomic, readonly) NSNumber *barColMin;

/** The maximum value of a bar or column across all of the bar/column series for this axis. 
  You can set this by using the appropriate `configureBars:withMinY:withMaxY:` or `configureBars:withMinY:withMaxY:` method for the axis orientation. */
@property (nonatomic, readonly) NSNumber *barColMax;

/** DEPRECATED - this will be removed from the API soon.
 
 During the next render process, forces the recalculation of the barcolumn series.
 During normal operation the panning and zooming will take place using transforms - with only periodic recalculations. Setting this to YES will force the bars and columns to recalculate all coordinates.
  */
@property (nonatomic) BOOL recalculateBarColumnsRequired;

/** DEPRECATED - this will be removed from the API soon.
 
 A boolean indicating if the bar and column series are already configured.
 If this is YES the chart will not traverse the data to work out spacing and ranges.
 */
@property (nonatomic) BOOL barColumnsConfigured;

/** Provide bounds and spacing data for column series within the chart to improve performance 
 
 @param colSpacing the minimum distance between any two columns along the axis, in data terms.
 @param minX the smallest `xValue` of any column on the axis.
 @param maxX the largest `xValue` of any column on the axis.
 */
- (void)configureColumns:(double) colSpacing withMinX:(NSNumber *)minX withMaxX:(NSNumber *)maxX;

/** Provide bounds and spacing data for bar series within the chart to improve performance 
 
 @param barSpacing the minimum distance between any two bars along the axis, in data terms.
 @param minY the smallest `yValue` of any bar on the axis.
 @param maxY the largest `yValue` of any bar on the axis.
 */
- (void)configureBars:(double) barSpacing withMinY:(NSNumber *)minY withMaxY:(NSNumber *)maxY;


#pragma mark -
#pragma mark Zooming
/** @name Zooming */
/** Set to `YES` to allow pinch gestures to zoom the chart. */
@property (nonatomic)         BOOL enableGestureZooming;

/** Sets the zoom of the axis, based around a fixed point.
 
 @param z - the zoom level. 1.0 is the starting zoom level, 0.5 is 2x magnification, etc.
 @param position - the position on the axis around which to zoom in/out.
 @param animation - whether or not the zoom operation should be animated. If not animated, the zoom will be instant.
 @param bounceLimits - whether or not the axisRange should 'bounce' if it strays outside of the permissable range.
 
 @return Whether or not the zoom operation was successful.
 
 */
- (BOOL)setZoom:(double)z fromPosition:(double *)position withAnimation:(BOOL)animation andBounceLimits:(BOOL)bounceLimits;

/** See `setZoom:fromPosition:withAnimation:andBounceLimits:`.
 
 The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)setZoom:(double)z fromPosition:(double *)position withAnimation:(BOOL)animation;

/** See `setZoom:fromPosition:withAnimation:andBounceLimits:`.
 
  The zoom is not animated.
  The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)setZoom:(double)z fromPosition:(double *)position;

/** See `setZoom:fromPosition:withAnimation:andBounceLimits:`.
 
  The zoom is from the midpoint of the axisRange.
  The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)setZoom:(double)s withAnimation:(BOOL)animate;

/** See `setZoom:fromPosition:withAnimation:andBounceLimits:`.
 
  The zoom is from the midpoint of the axisRange.
  The zoom is not animated.
  The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)setZoom:(double)s;

/** Zoom to a set range, centred on a point.
 
 This method is for zooming in to a point using a range in data terms rather than a zoom level.
 
 @param point - the point on the axis around which to zoom in/out.
 @param range - the magnitude of the range to zoom in to - this will be centred around the point specified.
 @param animate - whether or not the zoom operation should be animated. If not animated, the zoom will be instant.
 @param bounce - whether or not the axisRange should 'bounce' if it strays outside of the permissable range.
 */
- (void)zoomToPoint:(double)point withRange:(double)range withAnimation:(BOOL)animate usingBounceLimits:(BOOL)bounce;

/** See `zoomToPoint:withRange:withAnimation:usingBounceLimits:`.
 
 */
- (void)zoomToPoint:(double)point withRange:(double)range;

/** Sets the axis back to its original zoom 
 
 @param animate - whether or not the zoom operation should be animated. If not animated, this reset will be instant.
 @return Whether or not the zoom operation was successful.
 */
- (BOOL)resetZoomLevelWithAnimation:(BOOL)animate;

/** See `resetZoomLevelWithAnimation:`.
 
 
 */
- (BOOL)resetZoomLevel;



/** Sets the zoom to a standard level.
 
    typedef enum {
    SChartAxisZoomLevelOriginal,
    SChartAxisZoomLevelDouble,
    SChartAxisZoomLevelHalf
    } SChartAxisZoomLevel 
 
 @param zoomLevel - a predefined SChartAxisZoomLevel for the axis. To set an explicit zoom use `setZoom:fromPosition:`
 */
- (BOOL)setZoomLevel:(SChartAxisZoomLevel)zoomLevel;

/** Returns the current zoom level, relative to the `defaultRange` of the axis. */
- (double)zoom;

/** Enables momentum zooming
 
 When momentum zooming is enabled, fast pinch gestures will cause the chart to continue
 to zoom during a brief 'slowing down' period rather than stopping immediately. 
 */
@property (nonatomic, assign)   BOOL enableMomentumZooming;

/** Will always be YES when the axis is decelerating from a pinch zoom gesture 
 */
@property (nonatomic, readonly) BOOL isMomentumZooming;

/** The time steps of each deceleration after a pinch zoom gesture.
 
 If `enableMomentumZooming` is set to YES, the velocity of the zoom pinch gesture will decay over a number of increments. These increments are a fixed time period specified here. During this fixed period the velocity will decay by a factor `zoomMomentumFactor`
 */
@property (nonatomic) double zoomMomentumDelay;

/** The factor by which the velocity of the gesture will decay during one deceleration time period.
 
 If `enableMomentumZooming` is set to YES, the velocity of the zoom pinch gesture will decay over a number of increments. These increments are a fixed time period specified in `zoomMomentumDelay`. During this fixed period the velocity will decay by this factor. 
 */
@property (nonatomic) double zoomMomentumFactor;


#pragma mark -
#pragma mark Panning
/** @name Panning */
/** Set to `YES` to allow swipe gestures to pan the chart. */
@property (nonatomic) BOOL enableGesturePanning;

/** Pan the axis range by an explicit amount 
 
 @param value - the value, in data terms, by which the axis range should pan by.
 @param animation - whether or not the pan operation should be animated. If not animated, the pan will be instant.
 @param panWithBouncing - whether or not the axisRange should 'bounce' if it strays outside of the permissable range.
 @param redraw - redraw the chart after the pan operation.
 
 @return Whether or not the pan operation was successful.
 
 */
- (BOOL)panByValue:(double)value withAnimation:(BOOL)animation withBounceLimits:(BOOL)panWithBouncing andRedraw:(BOOL)redraw;

/** See `panByValue:withAnimation:andBounceLimits:andRedraw:`.
 
 */
- (BOOL)panByValue:(double)value withAnimation:(BOOL)animation withBounceLimits:(BOOL)panWithBouncing;

/** See `panByValue:withAnimation:andBounceLimits:andRedraw:`.
 
  The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)panByValue:(double)value withAnimation:(BOOL)animation;

/** See `panByValue:withAnimation:andBounceLimits:andRedraw:`.
 
 The pan is not animated.
 The axisRange will not 'bounce' if it strays outside of the permissable range.
 */
- (BOOL)panByValue:(double)value;


/**  DEPRECATED - this will be removed from the API soon.
 
 Pan to a standard position.
 To set an explicit zoom use panByValue: 
 
 typedef enum {<br>
 SChartAxisPanToStart,<br>
 SChartAxisPanToEnd,<br>
 SChartAxisPanToCenter<br>
 } SChartAxisPanTo
*/
- (BOOL)panTo:(SChartAxisPanTo)where;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)panTo:(SChartAxisPanTo)where withAnimation:(BOOL)animation;

/** Enables momentum panning
 
 When momentum panning is enabled, fast pan gestures will cause the chart to continue
 to pan during a brief 'slowing down' period rather than stopping immediately. */
@property (nonatomic, assign)   BOOL enableMomentumPanning;

/** Will always be YES when the axis is decelerating from a pan swipe gesture */
@property (nonatomic, readonly) BOOL isMomentumPanning;

/** The time steps of each deceleration after a pan swipe gesture.
 
 If enableMomentumPanning is set to YES, the velocity of the swipe gesture will decay over a number of increments. These increments are a fixed time period specified here. During this fixed period the velocity will decay by a factor `panMomentumFactor`*/
@property (nonatomic) double panMomentumDelay;

/** The factor by which the velocity of the gesture will decay during one deceleration time period.
 
 If enableMomentumPanning is set to YES, the velocity of the swipe gesture will decay over a number of increments. These increments are a fixed time period specified in `panMomentumDelay`. During this fixed period the velocity will decay by this factor. */
@property (nonatomic) double panMomentumFactor;






#pragma mark -
#pragma mark Internal: Panning and Zooming Internal
// DEPRECATED - this will be removed from the API soon.
- (BOOL)panWithMomentumStartingAt:(double)panVelocityWrapper;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)panWithMomentum;

// DEPRECATED - this will be removed from the API soon.
- (void)updateZoom;


#pragma mark -
#pragma mark Internal: Range
// DEPRECATED - this will be removed from the API soon.
- (void)refreshDataRange;

// DEPRECATED - this will be removed from the API soon.
- (void)updateMaxRange;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)zoomWithMomentum;

// Zooms the axis based on momentum, centred on a specified position
-(BOOL)zoomWithMomentum:(double)velocity fromPosition:(double)position;




#pragma mark -
#pragma mark Internal
// DEPRECATED - this will be removed from the API soon.
- (BOOL)isXAxis;

// DEPRECATED - this will be removed from the API soon.
- (void)removeViews;


#pragma mark -
#pragma mark Internal: Tick Marks
// DEPRECATED - this will be removed from the API soon.
- (NSString *)longestLabel;

// DEPRECATED - this will be removed from the API soon.
- (CGSize)sizeTickLabels;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)spaceForLabels:(NSInteger)numLabels withLabelSizeScalers:(CGPoint)scale;

// DEPRECATED - this will be removed from the API soon.
- (void)updateInternalTickFrequencies:(CGSize *)largestLabelSize;

// DEPRECATED - this will be removed from the API soon.
- (NSNumber *)firstMajorTick;

// DEPRECATED - this will be removed from the API soon.
- (NSInteger)indexOfFirstLabel:(NSInteger)ticksPerLabel;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)firstTickInsideChart:(double)firstTickValue;

// DEPRECATED - this will be removed from the API soon.
- (NSNumber *)firstMinorTick;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)isOverAlternate:(double)tickMarkValue;

// DEPRECATED - this will be removed from the API soon.
- (double)incrementTickMarkValue:(double)tickMarkValue isMajor:(BOOL) major;

// DEPRECATED - this will be removed from the API soon.
- (double)decrementTickMarkValue:(double)tickMarkValue isMajor:(BOOL) major;

// DEPRECATED - this will be removed from the API soon.
- (void)generateTickMarks:(BOOL)redrawLabels;

// DEPRECATED - this will be removed from the API soon.
- (double)getPixelforTick:(double)tickMarkValue;

// DEPRECATED - this will be removed from the API soon.
- (void)rotateLabel:(UILabel *)tickLabel;

// DEPRECATED - this will be removed from the API soon.
- (SChartTickMark *)createTickMarkWithFrame:(CGRect)frame withTickMark:(SChartTickMark *)tm forValue:(double)value asMajor:(BOOL)major shouldCreateLabel:(BOOL)createLabel isOverAlternateStripe:(BOOL)overAlternate shouldUpdateText:(BOOL)updateText;


#pragma mark -
#pragma mark Internal: Data

// DEPRECATED - this will be removed from the API soon.
- (id)doubleToData:(double)fp;

#pragma mark -
#pragma mark Internal: Series Linking

// DEPRECATED - this will be removed from the API soon.
- (BOOL)isLinkedToSeries:(SChartSeries *)series;

// DEPRECATED - this will be removed from the API soon.
- (NSArray *)ownedSeries;

#pragma mark -
#pragma mark Mapping

/** @name Data - Pixel Conversions */

/*
 * These functions are used only internally, for:
 * 1) Annotation mapping       - map a pixel to a data value to display
 * 2) Annotation mapping       - map an interpolated data value back to a pixel
 * 3) Momentum panning         - map a pixel-velocity to a coord-velocity (otherwise momentum speed would be proportional to the axis range)
 * 4) Zooming {bar,col}Spacing - for calculating the minimum gl points, to draw to, in canvas
 */


/** Returns the pixel value, in the coordinate system of the plot area, of the given data value along this axis.
 
 If a data value would fall outside of the plot area (is not currently within the range of the axis) then this method may return either a negative value,
 or a value larger than the respective height/width of the plot area in pixels.
 */
-(float)pixelValueForDataValue:(id)data;

/** Returns the data value of the given pixel value along this axis, in the coordinate system of the plot area.
 
 If the pixel value given is negative, or is larger than the respective height/width of the plot area in pixels, than this method may return a data value 
 that is not currently in range of the axis.
 */
-(id)dataValueForPixelValue:(float)px;

/** DEPRECATED - use 'offsetForSeries:' instead.
 */
-(id)offsetForDataValue:(id)data inSeries: (SChartSeries *)series DEPRECATED_ATTRIBUTE;

/** Returns the difference in data terms between where data in a series is drawn to it's value on this axis.
 
 This is useful for calculating where the centres of datapoints are, relative to their value.
 For example, where you have more than one column series along an x-axis they will stand next to each other so as not to overlap:
 If columns in two series each have an xValue of '5', the column in the first series will be offset left from '5' and the column in the second series will be offset right from '5'.
 You can use this method to find out what that offset is for each series.
 */
-(id)offsetForSeries: (SChartCartesianSeries *)series;

/* Returns the real data represented by a glCoord (1D) 
 DEPRECATED - this will be removed from the API soon. */
-(NSNumber *)dataValueFromCoord:(double)coord;

/* Map a datapoint to openGL coordinates.
 DEPRECATED - this will be removed from the API soon. */
-(void)mapCoordinatesForDataPoint:(SChartInternalDataPoint *)dp inSeries:(SChartCartesianSeries *)series;

/* Map a datapoint of a barColumnSeries to openGL coordinates.
 DEPRECATED - this will be removed from the API soon. */
-(void)mapCoordinatesForBarColumnChartDataPoint:(SChartInternalDataPoint *)dp inSeries:(SChartBarColumnSeries *)series;

/* Recalculate barcolumn spacing, min and max values
 DEPRECATED - this will be removed from the API soon. */
- (void)recalculateBarColumns:(NSArray *)barColumnSeries;



#pragma mark -
#pragma mark Values in Data Terms
/** @name Values in Data Terms */

/* DEPRECATED - this will be removed from the API soon. Use `stringForId:` instead.
 
 @see stringForId
 */
- (NSString *)stringForValue:(double)value;

/** Returns a string representation of the given object.
 
 This will use the 'labelFormatter' where possible.  This is used for creating ticklabel and crosshair text. */
- (NSString *)stringForId:(id)obj;

// DEPRECATED - this will be removed from the API soon.
- (NSString *)appropriateFormat:(id)numberObj fallbackToLabelFormatter:(BOOL)useLabelFormatter;

// DEPRECATED - this will be removed from the API soon.
- (NSString *)appropriateFormat:(id)numberObj;


#pragma mark -
#pragma mark  Drawing
/** @name Drawing */

/** Returns the amount of space in points needed to draw the axis between the plot area and the edge of the chart frame.
 
 This includes the space required to draw tickmarks and ticklabels.
 Note that altering tick labels via the delegate may cause the return value of this method to be incorrect.
 
 @param shouldIncludeTitle - Whether or not to include the space required to draw the axis title, if enabled.
 */
- (float)spaceRequiredToDrawWithTitle:(BOOL)shouldIncludeTitle;

// DEPRECATED - this will be removed from the API soon.
- (void)drawTickMarksWithGLFrame:(CGRect)glFrame usingAxisDrawer:(SChartCanvasUnderlay*)drawer needToRedrawLabels:(BOOL)redrawLabels;

/* Draws the axis relative to the openGl frame
 DEPRECATED - this will be removed from the API soon. */
- (void)drawAxisWithGLFrame:(CGRect)frame usingAxisDrawer:(SChartCanvasUnderlay *)drawer;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)valueIsVisible:(double)value onSeries:(SChartSeries *)series;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)ensureValueIsVisible:(double)value andRedraw:(BOOL)redraw;

// DEPRECATED - this will be removed from the API soon.
- (BOOL)ensureValueIsVisible:(double)value;


#pragma mark -
#pragma mark Internal: Gestures

// DEPRECATED - this will be removed from the API soon.
- (void)cancelGestures;

// DEPRECATED - this will be removed from the API soon.
- (void)stopAnimations;

// DEPRECATED - this will be removed from the API soon.
- (void)stopMomentumZooming;

// DEPRECATED - this will be removed from the API soon.
- (void)stopMomentumPanning;

// DEPRECATED - this will be removed from the API soon.
- (NSArray *)manualGenerateTickMarks;

// DEPRECATED - this will be removed from the API soon.
- (void)autoGenerateTickMarks:(BOOL)redrawLabels;

@end
