//
//  SChartLegendStyle.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/** Manages the appearance of the legend on the chart.  The legend is an instance of `SChartLegend`.
 
 @available Standard
 @available Premium
 */
@interface SChartLegendStyle : NSObject <NSCopying>

/** @name Styling Properties */

/** The font used for the series titles. */
@property (nonatomic, retain)   UIFont *font;

/** The color of the text used to display the series titles. */
@property (nonatomic, retain)   UIColor *fontColor;

/** The alignment of the series titles. */
@property (nonatomic)           NSTextAlignment textAlignment;

/** The font for the legend title. */
@property (nonatomic, retain)   UIFont *titleFont;

/** The color for the legend title text. */
@property (nonatomic, retain)   UIColor *titleFontColor;

/** The amount of padding around the inside perimeter of the legend, in points. */
@property (nonatomic, retain)   NSNumber *marginWidth;

/** The color of the border line of the legend. */
@property (nonatomic, retain)   UIColor *borderColor;

/** The width of the legend border in points. */
@property (nonatomic, retain)   NSNumber *borderWidth;

/** The radius of the corners of the legend view.
 
 Setting a radius of `0` will draw square corners. */
@property (nonatomic, retain)   NSNumber *cornerRadius;

/** The radius of the corners of the legend symbols.
 
 Setting a radius of `0` will draw square corners. */
@property (nonatomic, retain)   NSNumber *symbolCornerRadius;

/** Defines whether symbols will be shown in the legend.

The default value is `YES` (symbols will be shown). Symbols are collected from each of the chart series using the `SChartLegendItem` protocol.  If this is set to `NO`, each chart series will be represented in the legend by a text label only. */
@property (nonatomic)           BOOL showSymbols;

/** The alignment of the symbols in the legend.
 
 The options available are:
 
    typedef enum {
        SChartSeriesLegendAlignSymbolsLeft,
        SChartSeriesLegendAlignSymbolsRight
    } SChartSeriesLegendSymbolAlignment;
 
 If `showSymbols` is set to `NO`, this property will have no effect.
 
 @see showSymbols
 */
@property (nonatomic)           SChartSeriesLegendSymbolAlignment symbolAlignment;

/** The layout of the series within the legend.
 
 The options available are:
 
    typedef enum {
        SChartLegendOrientationVertical,
        SChartLegendOrientationHorizontal
    } SChartLegendOrientation;
 */
@property (nonatomic)           SChartLegendOrientation orientation;

/** The color of the background of the legend. */
@property (nonatomic, retain)   UIColor *areaColor;

/** The horizontal padding between the symbol and the label representing a chart series in the legend, and also between different series within a row. 
 */
@property (nonatomic, retain)   NSNumber    *horizontalPadding;

/** The vertical padding between rows in the legend.
 */
@property (nonatomic, retain)   NSNumber    *verticalPadding;

/** Updates this style object using the configuration of the passed in style.
 @param style The new style with which to update this style object. */
-(void)supplementStyleFromStyle:(SChartLegendStyle *)style;

/* DEPRECATED - This will be taken off the public API in a future commit. */
-(BOOL)textAlignmentSet;

@end
