//
//  SChartTitleStyle.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SChart.h"


/** The look of a chart is managed by an instance of `SChartTheme` or one of its sub-classes.  Themes contain a set of style objects, each of which are responsible for managing the look of a particular aspect of the chart.  You'll find instances of this class or a subclass on the theme for axes titles and for the chart title.
 
 The SChartTitleStyle class is responsible for managing the look of the titles on the chart.  This includes things like:
 
 - The title color.
 - The title font.
 - The minimum font size for the title.
 - The background color of the title label.
 - The position of the title.
 
 There are two subclasses of SChartTitleStyle.  `SChartAxisTitleStyle` is used for the titles on the chart axes.  `SChartMainTitleStyle` is used for the main title on the chart.
 
 @available Standard
 @available Premium
 */
@interface SChartTitleStyle : NSObject <NSCopying>

/** @name Styling Properties */

/** The color of the text for the title. */
@property (nonatomic, retain)     UIColor           *textColor;

/** The font for the title text. */
@property (nonatomic, retain)     UIFont            *font;

/** The minimum font size for the title text.
 
 Functions in the same way as the UILabel equivalent property.
 
 DEPRECATED - Use `minimumScaleFactor` instead.*/
@property (nonatomic)             CGFloat           minimumFontSize DEPRECATED_ATTRIBUTE;

/** The minimum scale factor for the title text.
 
 Functions in the same way as the UILabel equivalent property.
 **/
@property (nonatomic)             CGFloat           minimumScaleFactor;

/** The text alignment of the title. */
@property (nonatomic)             NSTextAlignment   textAlign;

/** The background color of the title label. */
@property (nonatomic, retain)     UIColor           *backgroundColor;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

/** Where the title will appear relative to the chart or axis. 
 
 The possible values of position are defined as follows:
 
    typedef enum {
        SChartTitlePositionCenter,
        SChartTitlePositionBottomOrLeft,
        SChartTitlePositionTopOrRight
    } SChartTitlePosition;
 */
@property (nonatomic) SChartTitlePosition           position;

@end
