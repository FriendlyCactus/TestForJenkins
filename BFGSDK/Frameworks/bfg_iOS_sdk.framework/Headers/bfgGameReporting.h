//
/// \file bfgGameReporting.h
/// \brief Used by game to report significant events for analytics and placements.
///
/// \details Logging a significant event in your game helps us understand how well the players
///   are progressing. We may also provide advertising content, called "placements", after
///   these events occur.
///
/// \note This class contains keys for debugging placements in your app. Refer to the SDK
///   documentation for more information.
///
//  bfg_iOS_sdk
//
// \author Created by Michelle McKelvey on 3/5/12.
// \author Updated by Craig Thompson on 4/11/14.
// \author Updated by Craig Thompson on 7/14/15.
// \author Updated by Benjamin Flynn on 11/25/15
// \copyright Copyright (c) 2013 Big Fish Games, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "bfgReporting.h"

@protocol bfgDeferredDeepLinkDelegate;
@protocol bfgPlacementDelegate;


typedef NS_OPTIONS(NSUInteger, bfgUATrackerId) {
    bfgUATrackerIdTune = 1 << 0,
    bfgUATrackerIdKochava = 1 << 1,
    bfgUATrackerIdBigFish = 1 << 2,
    bfgUATrackerIdAll = bfgUATrackerIdTune | bfgUATrackerIdKochava | bfgUATrackerIdBigFish,
    bfgUATrackerIdHasOffers __deprecated_enum_msg("Use bfgUATrackerIdTune instead") = bfgUATrackerIdTune,
};


#pragma mark - bfgGameReporting
// ***********************************************************************************************
// * GAME REPORTING

///
///
/// Required game logging APIs.
///
///

/// \details This class is used for reporting all game events.
///
@interface bfgGameReporting : NSObject


///
/// \details Called each time the Main Menu is shown.
///
+ (void)logMainMenuShown;


///
/// \details Called each time Rate from the Main Menu is canceled.
///
+ (void)logRateMainMenuCanceled;


///
/// \details Called each time the Options Menu is shown.
///
+ (void)logOptionsShown;


///
/// \details Called each time purchase from the Main Menu is shown.
///
+ (void)logPurchaseMainMenuShown;

///
/// \details Called each time purchase from the Main Menu is closed.
///
+ (void)logPurchaseMainMenuClosed;

///
/// \details Called each time a non-mainmenu purchase paywall is shown with an identifier for the paywall.
///
+ (void)logPurchasePayWallShown:(NSString *)paywallID;


///
/// \details Called each time a non-mainmenu purchase paywall is closed with an identifier for the paywall.
///
+ (void)logPurchasePayWallClosed:(NSString *)paywallID;

///
/// \details Called each time a level has started.
///
+ (void)logLevelStart:(NSString *)levelID;


///
/// \details Called each time a level is finished.
///
+ (void)logLevelFinished:(NSString *)levelID;


///
/// \details Called each time a mini game is started.
///
+ (void)logMiniGameStart:(NSString *)miniGameID;


///
/// \details Called each time a mini game is skipped.
///
+ (void)logMiniGameSkipped:(NSString *)miniGameID;


///
/// \details Called each time a mini game is finished.
///
+ (void)logMiniGameFinished:(NSString *)miniGameID;


///
/// \details Called each time an achievement is earned.
///
+ (void)logAchievementEarned:(NSString *)achievementID;

///
/// \details Called each time a hint is requested.
///
+ (void)logGameHintRequested;

//
// \details  Calls the In-App Purchase screen when the purchase button is selected.
//
// purchaseButton can be one of the following values:
// BFG_PURCHASE_BUTTON_BUY,
// BFG_PURCHASE_BUTTON_RESTORE,
// BFG_PURCHASE_BUTTON_LATER,
// BFG_PURCHASE_BUTTON_CLOSE
//
//  Removed Flurry Events
// + (void)logIAPButtonTapped:(BFG_PURCHASE_BUTTON)purchaseButton;


///
/// \details Called when the game is completed.
///
+ (void)logGameCompleted;

///
/// \details logCustomEvent logs a custom event.
///
/// @param
/// name The name of the event at its lowest level of detail.
/// @param
/// value The value of this parameter is dependent on eventDetails1.
/// @param
/// level This parameter can be used to track game levels where custom events occur. 
/// If it is not applicable to your event, you should use 1.
/// @param
/// details1 This field should be outlined in a document provided by your producer.
/// @param
/// details2 Typically reflects the "type" of an event occurring within details1.
/// @param
/// details3 Typically describes the method or location of an event.
/// @param
/// additionalDetails For reporting purposes, any additional data pertaining to the event 
/// can be added as a dictionary. This *must* be 
/// a flat dictionary containing only NSString * as keys and values.
/// \return
/// \retval YES if the custom event was added to the event queue.
/// \retval NO if otherwise.
+ (BOOL)logCustomEvent:(NSString *)name
                 value:(NSInteger)value
                 level:(NSInteger)level
              details1:(NSString *)details1
              details2:(NSString *)details2
              details3:(NSString *)details3
     additionalDetails:(NSDictionary *)additionalDetails;

///
/// \details logCustomEvent logs a custom event.
///
/// \param
/// name The name of the event at its lowest level of detail.
/// \param
/// value The value of this parameter is dependent on eventDetails1.
/// \param
/// level This parameter can be used to track game levels where custom events occur.
/// If it is not applicable to your event, you should use 1.
/// \param
/// details1 This field should be outlined in a document provided by your producer.
/// \param
/// details2 Typically reflects the "type" of an event occurring within details1.
/// \param
/// details3 Typically describes the method or location of an event.
/// \param
/// additionalDetails For reporting purposes, any additional data pertaining to the event
/// can be added as a dictionary. This *must* be
/// a flat dictionary containing only NSString * as keys and values.
/// \param
/// error Used for indicating KT is disabled or that the payload is invalid for any of these 3 reasons:
///       1) Payload is too big, over 2000 characters.
///       2) Use of invalid characters (like spaces) in name, details1, details2 or details3.
///       3) details2 is set but there is no details1 or details3 is set but there is no details2.
///
/// \since 5.11
/// \return
/// \retval YES if the custom event was added to reporting queues as appropriate (Kontagent / Big Fish)
/// \retval NO if otherwise.
///
+ (BOOL)logCustomEvent:(NSString *)name
                 value:(NSInteger)value
                 level:(NSInteger)level
              details1:(NSString *)details1
              details2:(NSString *)details2
              details3:(NSString *)details3
     additionalDetails:(NSDictionary *)additionalDetails
                 error:(NSError *__autoreleasing *)error;

///
/// \details Logs a custom event and immediately delivers it
///
/// \note Do not use this method unless you absolutely have to as it undermines the queuing of
/// events.
///
/// @param
/// name The name of the event at its lowest level of detail.
/// @param
/// value The value of this parameter is dependent on eventDetails1.
/// @param
/// level This parameter can be used to track game levels where custom events occur.
/// If it is not applicable to your event, you should use 1.
/// @param
/// details1 This field should be outlined in a document provided by your producer.
/// @param
/// details2 Typically reflects the "type" of an event occurring within details1.
/// @param
/// details3 Typically describes the method or location of an event.
/// @param
/// additionalDetails For reporting purposes, any additional data pertaining to the event
/// can be added as a dictionary. This *must* be
/// a flat dictionary containing only NSString * as keys and values.
///
/// \since 5.7
/// \return
/// \retval YES if the custom event was logged.
/// \retval NO if otherwise.
///
+ (BOOL)logCustomEventImmediately:(NSString *)name
                            value:(NSInteger)value
                            level:(NSInteger)level
                         details1:(NSString *)details1
                         details2:(NSString *)details2
                         details3:(NSString *)details3
                additionalDetails:(NSDictionary *)additionalDetails;

///
/// \details Logs a custom event and immediately delivers it
///
/// \param
/// name The name of the event at its lowest level of detail.
/// \param
/// value The value of this parameter is dependent on eventDetails1.
/// \param
/// level This parameter can be used to track game levels where custom events occur.
/// If it is not applicable to your event, you should use 1.
/// \param
/// details1 This field should be outlined in a document provided by your producer.
/// \param
/// details2 Typically reflects the "type" of an event occurring within details1.
/// \param
/// details3 Typically describes the method or location of an event.
/// \param
/// additionalDetails For reporting purposes, any additional data pertaining to the event
/// can be added as a dictionary. This *must* be
/// a flat dictionary containing only NSString * as keys and values.
/// \param
/// error Used for indicating KT is disabled or that the payload is invalid for any of these 3 reasons:
///       1) Payload is too big, over 2000 characters.
///       2) Use of invalid characters (like spaces) in name, details1, details2 or details3.
///       3) details2 is set but there is no details1 or details3 is set but there is no details2.
///
/// \since 5.11
/// \return
/// \retval YES if the custom event was added to immediate reporting queues as appropriate (Kontagent / Big Fish)
/// \retval NO if otherwise.
///
+ (BOOL)logCustomEventImmediately:(NSString *)name
                            value:(NSInteger)value
                            level:(NSInteger)level
                         details1:(NSString *)details1
                         details2:(NSString *)details2
                         details3:(NSString *)details3
                additionalDetails:(NSDictionary *)additionalDetails
                            error:(NSError *__autoreleasing *)error;

///
/// \details logCustomPlacement logs a custom placement.
///
/// @param
/// placementName The name of the custom placement that has occurred.
///
+ (void)logCustomPlacement:(NSString * )placementName;

///
/// \details preloadCustomPlacement Pre-load the content of a custom event.
///
/// @param
/// placementName The name of the placement to be custom loaded.
///
/// Note: Frequency capping will not be respected for placements that are custom loaded.
///
+ (void)preloadCustomPlacement:(NSString * )placementName;

///
/// \details User is presented with a content gate.
/// \note This is not for prompting the user to install Big Fish Games App for strategy guides --
/// use logBigFishGamesAppOverlayShown for that.
///
/// \since 5.0
///
+ (void)logContentGateShown;

///
/// \details If you have a specific need to send a custom event to Kochava, you can use this method.
///
/// \param name
///
/// \since 5.6
///
+ (void)logKochavaCustomEvent:(NSString *)name;

///
/// \details If you have a specific need to send a custom event to Kochava, you can use this method.
///
/// \param name
/// \param value
///
/// \since 5.6
///
+ (void)logKochavaCustomEvent:(NSString *)name value:(NSString *)value;

///
/// \details If you have a specific need to send custom events to MobileAppTracking (HasOffers),
/// you can use this method.
///
/// \param name
///
/// \since 5.7
///
+ (void)logMobileAppTrackingCustomEvent:(NSString *)name;

///
/// \details Placements will make calls to their delegate in addition to posting notifications. If you prefer
/// using delegation to NSNotifications, implement the delegate calls and set your delegate here.
///
/// \param delegate
///
/// \since 5.7
///
+ (void)setPlacementDelegate:(id<bfgPlacementDelegate>)delegate;

///
/// \details Calling this method will trigger a call to for a placement to present a user with a survey.
///
/// \note The placement associated with this event is called 'survey_time'.
///
/// \since 5.7
///
+ (void)logSurveyEvent;

/// \details If it would be inappropriate for a placement ad to appear over the game in the moment,
///   set suppressPlacements to YES. As soon as it is ok to show placements again, be sure to set
///   it back to no.
///
/// \since 5.10
///
+ (void)setSuppressPlacement:(BOOL)suppressPlacements;

/// \details If a placement is showing, it is automatically and instantly dismissed. If no placement
///  is showing, does nothing.
///
/// \since 5.10
///
+ (void)dismissVisiblePlacement;

/// \details Set this before initializing bfgManager to receive notifications if you received a deferred
/// deep link.
///
/// \param delegate The delegate is informed when deferred deep links succeed or fail.
///
/// \since 5.10
///
+ (void)setDeferredDeepLinkDelegate:(id<bfgDeferredDeepLinkDelegate>)delegate;

@end


#pragma mark - bfgDeferredDeepLinkDelegate
// ***********************************************************************************************
// * DEFERRED DEEPLINK DELEGATION

/// \since 5.10
@protocol bfgDeferredDeepLinkDelegate <NSObject>

@optional

/// \details Called when an attempt to receive a deferred deep link completes.
///
/// \param deepLinkString Stringified deep link URL. nil on error or if none present.
/// \param error Error retrieving deep link. May be nil if there simply is no deep link.
/// \param provider The service that is reporting the deep link.
/// \param timeSinceLaunch Elapsed seconds between the app launching and deferred deep
/// link arriving.
///
/// \since 5.10
///
- (void)didReceiveDeferredDeepLink:(NSString *)deepLinkString error:(NSError *)error provider:(bfgUATrackerId)provider timeSinceLaunch:(NSTimeInterval)timeSinceLaunch;

@end


#pragma mark - bfgPlacementDelegate
// ***********************************************************************************************
// * PLACEMENT DELEGATION

/// \brief Notifies when placement activities occur. Implement a delegate to pause your
///   game at appropriate times.
///
/// \since 5.10
///
@protocol bfgPlacementDelegate <NSObject>

@required

/// \brief A placement will be opening in front of the game.
///
/// \since 5.10
///
- (void)bfgPlacementContentWillOpen:(NSString *)placementKey;

/// \brief A placement has closed and is no longer displaying.
///
/// \since 5.10
///
- (void)bfgPlacementContentDidDismiss:(NSString *)placementKey;


@optional

/// \brief A placement has been opened and is displaying in front of the game.
///
/// \since 5.10
///
- (void)bfgPlacementContentDidOpen:(NSString *)placementKey;

/// \brief A placement will close.
///
/// \since 5.10
///
- (void)bfgPlacementContentWillDismiss:(NSString *)placementKey;

/// \brief A placement failed to load and will not display.
///
/// \since 5.7
///
- (void)bfgPlacementContentError:(NSString *)contentName error:(NSError *)error;

/// \brief
///
/// \since 5.10
///
- (void)bfgPlacementRewardReceived:(NSString *)placementKey
                        rewardName:(NSString *)rewardName
                    rewardQuantity:(NSNumber *)rewardQuantity;

/// \brief A purchase has been requested. Your game should start the purchase.
///
/// \param contentName Name of the placement.
/// \param productId The Apple product identifier.
/// \param productQuantity The number of products being requested for purchase (should always be 1).
///
/// \return YES if your delegate will start the purchase flow. If NO, the SDK will start the purchase.
///
/// \since 5.10
///
- (BOOL)bfgPlacementStartPurchase:(NSString *)placementKey
                        productId:(NSString *)productId
                  productQuantity:(NSNumber *)productQuantity;

@end


// ***********************************************************************************************
// * PLACEMENT DEBUG

/// \brief Set to true to enable placement debugging. Value: @"placementDebugMode"
/// \since 5.10
///
FOUNDATION_EXPORT NSString * const kBFGPlacementDebug_DebugMode;

/// \brief Set to an in-app purchase product ID to test a placement sellling that product.
///   Value: @"placementDebugProductId"
/// \since 5.10
///
FOUNDATION_EXPORT NSString * const kBFGPlacementDebug_ProductId;

/// \brief Set to the ID of an item you could reward in the game. Value: @"placementDebugRewardId"
/// \since 5.10
///
FOUNDATION_EXPORT NSString * const kBFGPlacementDebug_RewardId;


// Just to be more explicit
typedef NSString BFGPlacementDebugPlacementKey;

/// \brief Setting this key to one of the below values will cause every placement triggered to
///   be of the specified type. See the BFGPlacementDebugPlacementKeys. Value: @"placementDebugPlacementKey"
/// \since 5.10
///
FOUNDATION_EXPORT NSString * const kBFGPlacementDebug_PlacementKey;

/// \brief A placement that opens the external AppStore. Value: @"placementDebugExternalStorePlacement"
/// \since 5.10
///
FOUNDATION_EXPORT BFGPlacementDebugPlacementKey * const kBFGPlacementDebug_ExternalStore_PlacementKey;

/// \brief A placement that opens the in-game AppStore. Value: @"placementDebugInternalStorePlacement"
/// \since 5.10
///
FOUNDATION_EXPORT BFGPlacementDebugPlacementKey * const kBFGPlacementDebug_InternalStore_PlacementKey;

/// \brief A placement that triggers and in-app purchase. Uses the placement debug product ID, or
///   otherwise the debug. Value: @"placementDebugInAppPurchasePlacement"
/// \since 5.10
///
FOUNDATION_EXPORT BFGPlacementDebugPlacementKey * const kBFGPlacementDebug_InAppPurchase_PlacementKey;

/// \brief A placement that opens a page in Safari. Value: @"placementDebugSafariPlacement"
/// \since 5.10
///
FOUNDATION_EXPORT BFGPlacementDebugPlacementKey * const kBFGPlacementDebug_Safari_PlacementKey;

/// \brief A placement that triggers a reward. Value: @"placementDebugInAppRewardPlacement"
/// \since 5.10
///
FOUNDATION_EXPORT BFGPlacementDebugPlacementKey * const kBFGPlacementDebug_InAppReward_PlacementKey;
