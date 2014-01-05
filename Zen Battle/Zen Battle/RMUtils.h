//
//  RMUtils.h
//  AMBEST
//
//  Created by James Zimmerman II on 1/5/12.
//  Copyright (c) 2012 Raster Media. All rights reserved.
//

#import <Foundation/Foundation.h>

#define RMLog(__Format__, ...) RM_Log(__FILE__, __LINE__, __Format__, ##__VA_ARGS__)
#define RMLogSave(__Format__, ...) RM_Log_Save(__FILE__, __LINE__, __Format__, ##__VA_ARGS__)

@interface RMUtils : NSObject

#pragma mark - Easy AlertView
+ (void)showAlertViewWithTitle:(NSString *)title message:(NSString *)message cancelMessage:(NSString *)cancelMessage;

#pragma mark - Button Tools
+ (void)styleRoundedButton:(UIButton *)button;

#pragma mark - TextField/View Tools
+ (void)styleTextField:(UITextField *)textField;
+ (void)styleTextView:(UITextView *)textView;

#pragma mark - Color Tools
+ (UIColor *)colorForHex:(NSString *)hexString;
+ (UIColor *)colorForHex:(NSString *)hexString withAlpha:(CGFloat)alphaOrNil;

#pragma mark - Log Tools
+ (NSString *)logFilePath;
+ (void)logWithNamespace:(id)namespace withMessage:(NSString*)message, ...;

void RM_Log(char *file, int line, NSString *message, ...);
void RM_Log_Save(char *file, int line, NSString *message, ...);
+ (void)deleteLogFile;

#pragma mark - Table Tools
+ (UITableViewCell *)getParentTableViewCell:(id)sender;

@end