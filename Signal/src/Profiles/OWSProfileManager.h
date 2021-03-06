//
//  Copyright (c) 2017 Open Whisper Systems. All rights reserved.
//

#import <SignalServiceKit/ProfileManagerProtocol.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kNSNotificationName_LocalProfileDidChange;
extern NSString *const kNSNotificationName_OtherUsersProfileDidChange;

@class TSThread;

// This class can be safely accessed and used from any thread.
@interface OWSProfileManager : NSObject <ProfileManagerProtocol>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)sharedManager;

- (void)resetProfileStorage;

#pragma mark - Local Profile

// These two methods should only be called from the main thread.
- (NSData *)localProfileKey;
- (BOOL)hasLocalProfile;
- (nullable NSString *)localProfileName;
- (nullable UIImage *)localProfileAvatarImage;

// This method is used to update the "local profile" state on the client
// and the service.  Client state is only updated if service state is
// successfully updated.
//
// This method should only be called from the main thread.
- (void)updateLocalProfileName:(nullable NSString *)profileName
                   avatarImage:(nullable UIImage *)avatarImage
                       success:(void (^)())successBlock
                       failure:(void (^)())failureBlock;

#pragma mark - Profile Whitelist

- (void)addThreadToProfileWhitelist:(TSThread *)thread;

- (BOOL)isThreadInProfileWhitelist:(TSThread *)thread;

- (BOOL)isUserInProfileWhitelist:(NSString *)recipientId;

- (void)setContactRecipientIds:(NSArray<NSString *> *)contactRecipientIds;

#pragma mark - Other User's Profiles

- (void)setProfileKey:(NSData *)profileKey forRecipientId:(NSString *)recipientId;

- (nullable NSData *)profileKeyForRecipientId:(NSString *)recipientId;

- (nullable NSString *)profileNameForRecipientId:(NSString *)recipientId;

- (nullable UIImage *)profileAvatarForRecipientId:(NSString *)recipientId;

- (void)refreshProfileForRecipientId:(NSString *)recipientId;

- (void)updateProfileForRecipientId:(NSString *)recipientId
               profileNameEncrypted:(NSData *_Nullable)profileNameEncrypted
                      avatarUrlData:(NSData *_Nullable)avatarUrlData
                       avatarDigest:(NSData *_Nullable)avatarDigest;

@end

NS_ASSUME_NONNULL_END
