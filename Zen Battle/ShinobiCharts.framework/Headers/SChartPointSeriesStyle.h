//
//  SChartPointSeriesStyle.h
//  ShinobiControls_Source
//
//  Copyright (c) 2013 Scott Logic Ltd. All rights reserved.
//
//

#import "SChartSeriesStyle.h"
@class SChartBasePointStyle;

@interface SChartPointSeriesStyle : SChartSeriesStyle {
    @protected
    SChartBasePointStyle *_pointStyle;
    SChartBasePointStyle *_selectedPointStyle;
}

/** @name Style Properties */
/** The style of points that are not selected */
- (SChartBasePointStyle*) pointStyle;
- (void) setPointStyle:(SChartBasePointStyle *)pointStyle;

/** The style of points that are selected */
- (SChartBasePointStyle*) selectedPointStyle;
- (void) setSelectedPointStyle:(SChartBasePointStyle *) selectedPointStyle;

/** Supplements this style object by taking styles this object doesn't have, from the argument, `style` */
- (void)supplementStyleFromStyle:(SChartPointSeriesStyle *)style;

@end
