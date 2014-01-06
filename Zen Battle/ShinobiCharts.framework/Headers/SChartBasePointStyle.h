//
//  SChartBubbleStyle.h
//  ShinobiControls_Source
//
//  Copyright (c) 2013 Scott Logic Ltd. All rights reserved.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/** This is an abstract base class for other point style classes.
 
 This abstract style corresponds to the abstract series SChartPointSeries.*/

@interface SChartBasePointStyle : NSObject

/** @name Styling Properties */
/** Defines whether points should be displayed on our chart series. */
@property (nonatomic, assign)     BOOL showPoints;

/* DEPRECATED - This will be moved off the public API in a future commit. */
@property (nonatomic, assign)     BOOL showPointsSet;

/** The color of the data points. */
@property (nonatomic, retain)     UIColor   *color;

/** The color of the data points when the chart series goes below its baseline. */
@property (nonatomic, retain)     UIColor   *colorBelowBaseline;

/** The radius of the outer section of a data point. */
@property (nonatomic, retain)     NSNumber  *radius;

/** An image to be used for each data point.  If this property is set, the image will displayed rather than the default of an inner and outer circle. */
@property (nonatomic, retain)     UIImage   *texture;

/** Supplements this style object by taking styles this object doesn't have, from the argument, `style` */
- (void)supplementStyleFromStyle:(SChartBasePointStyle *)style;

@end
