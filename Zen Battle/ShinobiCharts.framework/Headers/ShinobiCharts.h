//
//  ShinobiCharts.h
//  ShinobiCharts
//
//

#import <Foundation/Foundation.h>

@class SChartTheme;

/** A utility class which allows you to set themes and licenseKeys for all the ShinobiCharts in your app, rather than having to configure each independently.
 
 This is best done early on, before any charts are created.

 @sa ChartsUserGuide
 
 @available Standard
 @available Premium
 */

@interface ShinobiCharts : NSObject

/** Set a licenseKey for all ShinobiCharts in your app.
 */
+ (void)setLicenseKey:(NSString *)key;

/** The licenseKey set for all ShinobiCharts in your app.
 */
+ (NSString *)licenseKey;

/** Set a theme for all ShinobiCharts in your app.
 
 @sa SChartTheme
 */
+ (void)setTheme:(SChartTheme *)theme;

/** The theme set for all ShinobiCharts in your app.
 
 @sa SChartTheme
 */
+ (SChartTheme *)theme;

@end
