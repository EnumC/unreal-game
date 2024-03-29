// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "OnlineSubSystemHeader.h"

#include "UpdateSessionCallbackProxyAdvanced.generated.h"

UCLASS(MinimalAPI)
class UUpdateSessionCallbackProxyAdvanced : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when the session was updated successfully
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there was an error updating the session
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	// Creates a session with the default online subsystem with advanced optional inputs
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject",AutoCreateRefTerm="ExtraSettings"), Category = "Online|AdvancedSessions")
	static UUpdateSessionCallbackProxyAdvanced* UpdateSession(UObject* WorldContextObject, int32 PublicConnections, bool bUseLAN, bool bAllowInvites, bool bAllowJoinInProgress, const TArray<FSessionPropertyKeyPair> &ExtraSettings, bool bRefreshOnlineData = true, bool bIsDedicatedServer = false);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when session creation completes, calls StartSession
	void OnUpdateCompleted(FName SessionName, bool bWasSuccessful);

	// The delegate executed by the online subsystem
	FOnUpdateSessionCompleteDelegate OnUpdateSessionCompleteDelegate;

	// Handles to the registered delegates above
	FDelegateHandle OnUpdateSessionCompleteDelegateHandle;

	// Number of public connections
	int NumPublicConnections;

	// Whether or not to search LAN
	bool bUseLAN;

	// Whether or not to allow invites
	bool bAllowInvites;

	// Store extra settings
	TArray<FSessionPropertyKeyPair> ExtraSettings;

	// Whether to update the online data
	bool bRefreshOnlineData;

	// Allow joining in progress
	bool bAllowJoinInProgress;

	// Update whether this is a dedicated server or not
	bool bDedicatedServer;

	// The world context object in which this call is taking place
	UObject* WorldContextObject;
};

