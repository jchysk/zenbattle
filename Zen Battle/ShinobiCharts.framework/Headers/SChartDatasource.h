//
//  SChartDatasource.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ShinobiChart;
@class SChartSeries;
@class SChartRadialSeries;
@class SChartInternalDataPoint;
@class SChartAxis;
@protocol SChartData;

/** The `SChartDatasource` protocol is adopted by an object that wishes to provide data for a `ShinobiChart`. The data source provides the chart with the information it needs to construct the chart object. In general, styling and event response is handled by objects implementing the `SChartDelegate` protocol - the data source has minimal impact on the look and feel of the chart.
 
 The _required_ methods provide the chart with information about all of the series to be displayed on that chart - and the data for those series. The relevant chart object is always returned - to support the option of using a single object as the data source for multiple charts.
 
 @available Standard
 @available Premium
 @sa ChartsUserGuide
 @sample Area
 @sample BarChart
 @sample ColumnChart
 @sample FinancialChart
 @sample LargeDataSet
 @sample LineChart
 @sample PieChart
 */
@protocol SChartDatasource <NSObject>

#pragma mark -
#pragma mark REQUIRED
@required

#pragma mark -
#pragma mark Providing data to a ShinobiChart
/** @name Providing data to a ShinobiChart */

/** Returns the number of series in the given chart.
 
 The chart can display multiple series, and can display series of different types at the same time. For each of these series, the chart will expect to receive a `SChartSeries` object from the datasource, through the `sChart:seriesAtIndex:` method.
 
 @param chart The chart for which the datasource is providing data.
 */
- (NSInteger)numberOfSeriesInSChart:(ShinobiChart*)chart;

/** Returns the `SChartSeries` object at the given index in the specified chart. 
 
 The number of `SChartSeries` in the chart are specified by the `numberOfSeriesInSChart:` method.
 
 The order is important for some series layouts - lower index series are placed on the chart first and will be _behind_ subsequent series.
 
 One of the concrete subclasses of `SChartSeries` will be returned here.  The available types are:
 
 - `SChartBarSeries`
 - `SChartColumnSeries`
 - `SChartLineSeries`
 - `SChartStepLineSeries`
 - `SChartBandSeries`
 - `SChartScatterSeries`
 - `SChartCandlestickSeries`
 - `SChartOHLCSeries`
 - `SChartDonutSeries`
 - `SChartPieSeries`
 
 @param chart The chart on which the series will be displayed.
 @param index The index of the given series in the chart.
 */
- (SChartSeries*)sChart:(ShinobiChart*)chart seriesAtIndex:(NSInteger)index;

/** Returns the number of data points in the specified series.
 
 For each of the data points in the series, the chart will expect to receive an object that adopts the `SChartData` protocol.  Data points will be provided to the chart either via the `sChart:dataPointAtIndex:forSeriesAtIndex:` method, or via the `sChart:dataPointsForSeriesAtIndex:` method.
 
 @param chart The chart on which the series will be displayed.
 @param seriesIndex The index of the given series in the chart, which will contain the data points.
 */
- (NSInteger)sChart:(ShinobiChart*)chart numberOfDataPointsForSeriesAtIndex:(NSInteger)seriesIndex;

/** Returns the object that represents the data point at the given index in the specified chart series.
 
 The number of points in each series is set by the `sChart:numberOfDataPointsForSeriesAtIndex:` method. 
 
 The data point can be any object that implements the `SChartData` protocol.  We provide a set of data point classes which can be used.  These are:
 
 - `SChartDataPoint` - used for simple cartesian data points.
 - `SChartRadialDataPoint` - used for radial data points.
 - `SChartMultiYDataPoint` - used for cartesian data points with multiple y values.
 - `SChartMultiXDataPoint` - used for cartesian data points with multiple x values.
 
 @param chart The chart on which the data point will be drawn.
 @param dataIndex The index of the data point in the chart series which contains it.
 @param seriesIndex The index of the series which contains the data point, in the chart.
 */
- (id<SChartData>)sChart:(ShinobiChart*)chart dataPointAtIndex:(NSInteger)dataIndex forSeriesAtIndex:(NSInteger)seriesIndex;


#pragma mark -
#pragma mark OPTIONAL
@optional

#pragma mark -
#pragma mark Custom tick marks
/** @name Custom tick marks */

/** Returns an array of major tick mark values, to be used by the given chart axis.
 
 If this method is implemented, the major tick marks on the axis will be fixed as the values in the array.  No other values will be calculated or interpolated.
 
 Objects in the array should be instances of the NSNumber class. 
 @param chart The chart containing the axis.
 @param axis The axis for which we are setting the major tick values.
 */
- (NSArray *)sChart:(ShinobiChart*)chart majorTickValuesForAxis:(SChartAxis *)axis;


#pragma mark -
#pragma mark Custom data points
/** @name Custom data points */

/** Returns an array containing the data points for the series at the given index.
 
 You can pre-create and cache the data points in an array, and present this array to the chart using this method.  This is more efficient than querying the datasource for its data points one at a time.
 @param chart The chart which will display the data points.
 @param seriesIndex The index of the series in the chart. */
- (NSArray *)sChart:(ShinobiChart*)chart dataPointsForSeriesAtIndex:(NSInteger)seriesIndex;

/** Returns an image to be displayed for the specified data point in the chart.
 
 If you implement this method, and it returns a non-nil image for the specified data point, that image will be displayed for the data point in the chart.
 
 @param chart The chart containing the data point.
 @param dataIndex The index of the data point within the series which contains it.
 @param seriesIndex The index of the series in the chart which contains the data point.
 */
- (UIImage *)sChartTextureForPoint:(ShinobiChart*)chart dataPointAtIndex:(NSInteger)dataIndex forSeriesAtIndex:(NSInteger)seriesIndex;

/** @name Custom data point radii */

/** Returns the radius of the given data point, in points.
 
 By default, data points on the chart are displayed as two circles, one inside the other.  The radius of a data point defines the radius of the outer circle in its representation on the chart.
 
 If you implement this method, and it returns a positive, non-zero value, that radius is used for the given data point in the specified series on the chart.

 @param chart The chart containing the data point.
 @param dataIndex The index of the data point in the series which contains it.
 @param seriesIndex The index of the series in the chart which contains the data point.
 */
- (float)sChartRadiusForDataPoint:(ShinobiChart*)chart dataPointAtIndex:(NSInteger)dataIndex forSeriesAtIndex:(NSInteger)seriesIndex;

/** Returns the inner radius of the given data point, in points.
 
 By default, data points on the chart are displayed as two circles, one inside the other.  The inner radius of a data point defines the radius of the inner circle in its representation on the chart.
 
 If you implement this method, and it returns a positive, non-zero value, that radius is used for the inner circle on the given data point in the specified series on the chart.
 
 @param chart The chart containing the data point.
 @param dataIndex The index of the data point in the series which contains it.
 @param seriesIndex The index of the series in the chart which contains the data point.
 */
- (float)sChartInnerRadiusForDataPoint:(ShinobiChart*)chart dataPointAtIndex:(NSInteger)dataIndex forSeriesAtIndex:(NSInteger)seriesIndex;

#pragma mark -
#pragma mark Radial Chart Labels
/** @name Custom labels for radial charts */

/** DEPRECATED - use sChart:labelForSliceAtIndex:inRadialSeries: instead.
 
 Returns a UILabel corresponding to the 'slice' of the specified radial chart series at the given index.
 
 If this method is implemented and a non-nil UILabel is returned for a 'slice' in a radial chart series, that UILabel will be added to the chart.
 */
- (UILabel *)getLabelsForRadialChartSeries:(SChartSeries *)series forIndex:(NSInteger)sliceIndex;

/** Returns a UILabel corresponding to a 'slice' of a radial chart series.
 
 If this method is implemented and a non-nil UILabel is returned for the given 'slice' in the radial chart series, that UILabel will be added to the chart. 
 @param chart The chart containing the radial series.
 @param sliceIndex The index of the slice of interest within the specified chart series.
 @param series The chart series which contains the slice of interest.
 */
- (UILabel *)sChart:(ShinobiChart *)chart labelForSliceAtIndex:(NSInteger)sliceIndex inRadialSeries:(SChartRadialSeries *)series;

#pragma mark -
#pragma mark Axes
/** @name Assigning an axis to a series */

/** Returns the x axis for this series on the chart.
 
 If this method is implemented the chart will look here for which axis to use when representing this series, otherwise this series will default to using the primary x axis on the chart.
 
 Hint: This is only needed on charts with multiple axes.
 
 *Note: The `SChartAxis` returned should be referenced from an existing chart axis and not a new object. _eg: return chart.xAxis_*
 
 To specify an axis for some series and not for others, returning `nil` for a series index will revert to the default behaviour for that series.
 
 @param chart The chart containing the axis.
 @param index The index of the chart series within the chart.
 */
- (SChartAxis*)sChart:(ShinobiChart*)chart xAxisForSeriesAtIndex:(NSInteger)index;

/** The y-axis for this series on the chart
 
 If this method is implemented the chart will look here for which axis to use when representing this series, otherwise this series will default to using the primary y axis on the chart.
 
 Hint: This is only needed on charts with multiple axes.
 
 *Note: The `SChartAxis` returned should be referenced from an existing chart axis and not a new object. _eg: return chart.yAxis_*
 
 To specifiy an axis for some series and not for others, returning `nil` for a series index will revert to the default behaviour for that series.
 
 @param chart The chart containing the axis.
 @param index The index of the chart series within the chart.
 */
- (SChartAxis*)sChart:(ShinobiChart*)chart yAxisForSeriesAtIndex:(NSInteger)index;


@end
