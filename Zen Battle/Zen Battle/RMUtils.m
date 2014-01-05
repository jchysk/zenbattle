//
//  RMUtils.m
//  AMBEST
//
//  Created by James Zimmerman II on 1/5/12.
//  Copyright (c) 2012 Raster Media. All rights reserved.
//

#import "RMUtils.h"
#import <QuartzCore/QuartzCore.h>

@implementation RMUtils

#pragma mark - Easy AlertView
+ (void)showAlertViewWithTitle:(NSString *)title message:(NSString *)message cancelMessage:(NSString *)cancelMessage
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:cancelMessage otherButtonTitles:nil] ;
	[alert show] ;
}


#pragma mark - Button Tools
+ (void)styleRoundedButton:(UIButton *)button
{
	button.layer.cornerRadius = 10.0f;
	button.layer.masksToBounds = YES;
	button.backgroundColor = [self colorForHex:@"#575555"];
	button.titleLabel.font = [UIFont boldSystemFontOfSize:11.0f];
	button.titleLabel.textColor = [self colorForHex:@"#e9e9e9"];
	
}

#pragma mark - TextField/View Tools

+ (void)styleTextField:(UITextField *)textField
{
    UIColor *borderColor = [UIColor colorWithWhite:0.6 alpha:1.0];
	
	textField.layer.borderColor = [borderColor CGColor];
	textField.layer.borderWidth = 1.0f;
	textField.layer.cornerRadius = 4.0f;
	textField.layer.masksToBounds = YES;
}

+ (void)styleTextView:(UITextView *)textView
{
	UIColor *borderColor = [self colorForHex:@"#49b6e3"];
	
	textView.layer.borderColor = [borderColor CGColor];
	textView.layer.borderWidth = 3.0f;
	textView.layer.cornerRadius = 16.0f;
	textView.layer.masksToBounds = YES;
}

#pragma mark - Color Tools
+ (UIColor *)colorForHex:(NSString *)hexString
{
	return [self colorForHex:hexString
				   withAlpha:1.0];
}

+ (UIColor *)colorForHex:(NSString *)hexString
			  withAlpha:(CGFloat)alphaOrNil
{
	if( alphaOrNil ) {
		alphaOrNil = 1.0;
	}
	hexString =
	[[[hexString stringByTrimmingCharactersInSet:
	   [NSCharacterSet whitespaceAndNewlineCharacterSet]]
	  stringByReplacingOccurrencesOfString:@"#"
	  withString:@""]
	 uppercaseString];
	NSString *redValue;
	NSString *greenValue;
	NSString *blueValue;
	if( hexString.length == 3 ) {
		redValue = [hexString substringWithRange:NSMakeRange(0, 1)];
		greenValue = [hexString substringWithRange:NSMakeRange(1, 1)];
		blueValue = [hexString substringWithRange:NSMakeRange(2, 1)];
	} else if( hexString.length == 6 ) {
		redValue = [hexString substringWithRange:NSMakeRange(0, 2)];
		greenValue = [hexString substringWithRange:NSMakeRange(2, 2)];
		blueValue = [hexString substringWithRange:NSMakeRange(4, 2)];
	} else {
		return [UIColor blackColor];
	}
	unsigned int r, g, b;
	[[NSScanner scannerWithString:redValue] scanHexInt:&r];
	[[NSScanner scannerWithString:greenValue] scanHexInt:&g];
	[[NSScanner scannerWithString:blueValue] scanHexInt:&b];
	return [UIColor colorWithRed:((float) r / 255.0f)
						   green:((float) g / 255.0f)
							blue:((float) b / 255.0f)
						   alpha:alphaOrNil];
}

#pragma mark - Log Tools

+ (NSString *)logFilePath
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *filePath = [documentsDirectory stringByAppendingString:@"/logFile.txt"];
    return filePath;
}

+ (void)logWithNamespace:(id)namespace withMessage:(NSString*)message, ...
{
	if (RMDEBUG) {
        
        NSString *strspace = ([namespace isKindOfClass:[NSString class]]) ? namespace : [[namespace class] description];
        
		va_list args;
		va_start(args, message);
		NSMutableString *rawMessage = [NSMutableString stringWithFormat:@"[%@] ", strspace];
		[rawMessage appendString:message];
		NSLogv(rawMessage, args);
		va_end(args);
	}
}

void RM_Log(char *file, int line, NSString *message, ...)
{
    if (RMDEBUG) {
        // Create a string with the file name and line number
        NSMutableString *s = [[NSMutableString alloc] initWithFormat:@"[%@:%d] ",
                              [[[NSString stringWithUTF8String:file] lastPathComponent] stringByDeletingPathExtension], line];
        
        // Append the message and arguments
        va_list args;
        va_start(args, message);
        [s appendString:[[NSString alloc] initWithFormat:message arguments:args]];
        va_end(args);
        
        // Output the entire message to the log screen
        NSLog(@"%@", s);
    }
}

void RM_Log_Save(char *file, int line, NSString *message, ...)
{
    if (RMDEBUG) {
        // Create a string with the file name and line number
        NSMutableString *s = [[NSMutableString alloc] initWithFormat:@"[%@:%d] ",
                              [[[NSString stringWithUTF8String:file] lastPathComponent] stringByDeletingPathExtension], line];
        
        // Append the message and arguments
        va_list args;
        va_start(args, message);
        [s appendString:[[NSString alloc] initWithFormat:message arguments:args]];
        va_end(args);
        
        // Output the entire message to the log screen
        NSLog(@"%@", s);
        
        // Save the message to the log file with the current time
        NSString *filePath = [RMUtils logFilePath];
        NSFileHandle *output = [NSFileHandle fileHandleForWritingAtPath:filePath];
        if(output == nil) {
            [[NSFileManager defaultManager] createFileAtPath:filePath contents:nil attributes:nil];
            output = [NSFileHandle fileHandleForWritingAtPath:filePath];
        }
        [output truncateFileAtOffset:[output seekToEndOfFile]];
        [output writeData:[[NSString stringWithFormat:@"%@ %@\n", [[NSDate date] description], s] dataUsingEncoding:NSUTF8StringEncoding]];
        [output closeFile];
    }
}

+ (void)deleteLogFile
{
    NSString *filePath = [RMUtils logFilePath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    BOOL isDir;
    if ([fileManager fileExistsAtPath:filePath isDirectory:&isDir] && !isDir) {
        [fileManager removeItemAtPath:filePath error:nil];
    }
}

#pragma mark - Table Tools

+ (UITableViewCell *)getParentTableViewCell:(id)sender
{
    UITableViewCell *cell;
    while (sender != nil) {
        if ([sender isKindOfClass:[UITableViewCell class]]) {
            cell = (UITableViewCell *)sender;
            break;
        } else {
            sender = [sender superview];
        }
    }
    return cell;
}

@end