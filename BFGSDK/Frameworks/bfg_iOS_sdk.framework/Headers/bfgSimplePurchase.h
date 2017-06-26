//
//  bfgSimplePurchase.h
//  BFGUIKitExample
//
//  Created by Benjamin Flynn on 12/16/15.
//  Copyright © 2015 Big Fish Games, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

///
/// \details Registers one of your classes as a delegate of the bfgSimplePurchase class. It will
///  be notified whenever a purchase or restore succeeds or fails.
///
/// \since 5.10
///
@protocol bfgSimplePurchaseDelegate <NSObject>

@required

///
/// \details If you receive this call, the user just purchased your game.
///
/// \since 5.10
///
- (void)simplePurchaseDidSucceed;

///
/// \details If you receive this call, something went unexpectedly wrong in the purchase process.
///  Show a UI to let the user know there was a failure.
///
/// \since 5.10
///
- (void)simplePurchaseDidFail;

///
/// \details If you receive this call, the user just restored your game, which they had previously purchased.
///
/// \since 5.10
///
- (void)simpleRestoreDidSucceed;

///
/// \details If you receive this call, something went unexpectedly wrong in the restore process,
///  or the user has never made any simple purchases.  Show a UI to let the user know there was a
///  failure.
///
/// \since 5.10
///
- (void)simpleRestoreDidFail;

///
/// \details If you receive this call, the user's purchase was deferred. A deferred purchase
/// can occur when family shared purchases and Ask To Buy are enabled. If this method is called,
/// resume the game with the expectation of the purchase completing sometime in the future (once
/// the purchase has been approved by the parent/card holder). Be aware that when a purchase is
/// deferred, the simplePurchaseDidSucceed method will continue to return NO even though the 
/// purchase might eventually succeed.
///
/// \since 5.10
///
- (void)simplePurchaseWasDeferred;


@optional

///
/// \details If you receive this call, the user decided not make the purchase after all. You would get this
///  after you start a purchase or start a restore, instead of a success or a failure.
/// \note This is optional. If you are pausing your game during the purchase process, you should implement this
///  method on your delegate.
///
/// \since 5.10
///
- (void)simplePurchaseOrRestoreDidCancel;

@end

///
/// \brief Manages In-App Purchases for games that have a single, non-consumable purchase.
///
/// \details Use bfgSimplePurchase instead of bfgPurchase if your app sells only a single, non-consumable In-App Purchase.
///  You must declare the name of the In-App Purchase in your bfg_first_launch_settings.json -- use the key
///  "iap_default_product_id". For more information on the settings json files, see the Big Fish documentation.
///
/// \since 5.10
///
@interface bfgSimplePurchase : NSObject

///
/// \details Call this as early as possible, generally right after you initialize bfgManager. Must be called for
///  purchase to work.
/// \param delegate A class that implements bfgSimplePurchaseDelegate and will receive purchase events.
///
/// \since 5.10
///
+ (void)startServiceWithDelegate:(id<bfgSimplePurchaseDelegate>)delegate;

///
/// \details Call this when a user indicates they would like to purchase the In-App Purchase.
///
/// \since 5.10
///
+ (void)startSimplePurchase;

///
/// \details Call this when a user indicates they would like to restore a previous purchase.
///
/// \since 5.10
///
+ (void)startSimpleRestore;

///
/// \details Convenience method to determine purchased state. First call is heavyweight, subsequent calls
///  are lightweight, so it could be called in a loop without degrading performance.
/// \return YES if the In-App Purchase has been purchased, otherwise NO.
///
/// \since 5.10
///
+ (BOOL)isPurchasedSimple;

@end
