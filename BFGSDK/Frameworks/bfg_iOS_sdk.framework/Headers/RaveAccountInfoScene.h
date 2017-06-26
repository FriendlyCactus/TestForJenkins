//
//  RaveAccountInfoScene.h
//
//  RaveUI
//  Copyright (c) 2013 Rave, Inc. All rights reserved.
//

#import <bfg_iOS_sdk/RaveScene.h>
#import <bfg_iOS_sdk/RaveUtilities.h>
#import <bfg_iOS_sdk/RaveConnectWidget.h>
#import "RaveSignUpEmailScene.h"

@interface RaveAccountInfoScene : RaveScene
+ (BOOL)shouldAutomaticallyShow;
+ (void)setShouldAutomaticallyShow:(BOOL)shouldAutomaticallyShow;

- (void)handleManage:(id)sender;
- (void)handleSignOut:(id)sender;

/**
 *  Use this callback to check for login and details of account creation
 */
@property (nonatomic, copy) BigFishSignUpCallback signUpCallback;

@end
