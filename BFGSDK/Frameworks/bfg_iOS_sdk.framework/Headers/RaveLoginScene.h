//
//  RaveLoginScene.h
//
//  RaveUI
//  Copyright (c) 2013 Rave, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <bfg_iOS_sdk/RaveUtilities.h>
#import "RaveSignUpEmailScene.h"

/**
 *  Show this scene to ask a user to login in, or perhaps to create a new account
 *  -  Also may be shown indirectly through RaveSignUpEmailScene
 */
@interface RaveLoginScene : RaveScene

/**
 *  Use this callback to check for login and details of account creation
 */
@property (nonatomic, copy) BigFishSignUpCallback signUpCallback;
@end