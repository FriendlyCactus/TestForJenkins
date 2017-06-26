//
//  BigFishMergeDecisionScene.h
//  BigFishScenePack
//
//  Copyright © 2016 Rave Social, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BigFishMergeDecisionScene : RaveScene
@property (nonatomic, retain) id<RaveUser> otherUser;
@property (nonatomic, copy) RaveUserMergeDecisionCallback callback;
@end
