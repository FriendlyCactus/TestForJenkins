//
//  RaveUIAlertProxy.h
//  RaveUI
//
//  Copyright (c) 2013 Gorilla Graph, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^UIAlertProxyConfirmationCallback)(NSInteger buttonIndex);

/**
 *  Proxy interface as a stand-in for UIAlertView (deprecated in iOS8) and UIAlertController (new in iOS9)
 */

typedef void (^RaveUIAlertProxyEditTextCallback)(NSString * text);

@interface RaveUIAlertProxy : NSObject
+ (void)showMessage:(NSString*)message;
+ (void)showError:(NSError*)error;
+ (void)showTitle:(NSString *)title message:(NSString *)message;
+ (void)showTitle:(NSString*)title message:(NSString*)message
    buttonsTitles:(NSArray*)buttons
         callback:(UIAlertProxyConfirmationCallback)callback;
+ (void)showEditTextTitle:(NSString *)title message:(NSString *)message placeholder:(NSString *)placeholder callback:(RaveUIAlertProxyEditTextCallback)callback;
@end
