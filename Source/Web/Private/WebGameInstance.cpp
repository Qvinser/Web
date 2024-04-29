// Fill out your copyright notice in the Description page of Project Settings.


#include "WebGameInstance.h"

bool UWebGameInstance::HostSession(APlayerController* Player, FName SessionName, bool bIsLAN, int32 MaxNumPlayers)
{
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(Player->GetWorld());
	if (OnlineSub)
	{
		// Get the Session Interface to call the StartSession function
		const IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			// Clear the SessionComplete delegate handle, since we finished this call
			auto SessionSettings = (new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = false;
			SessionSettings->bIsDedicated = false;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings->bUsesStats = true;
			SessionSettings->bUseLobbiesIfAvailable = true;
			SessionSettings->Set(TEXT("CustomServerName"), SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
			
			//SessionSettings->Set("SETTING_MAPNAME", FString("Level2"), EOnlineDataAdvertisementType::ViaOnlineService);
			bool retVal = Sessions->CreateSession(*(Player->GetLocalPlayer()->GetPreferredUniqueNetId()), SessionName, *SessionSettings);
			//bool retVal = Sessions->CreateSession(0, SessionName, SessionSettings);
			if (retVal)
			{
				retVal = retVal && Sessions->StartSession(SessionName);
				return retVal;
			};
			return false;
			//return Sessions->CreateSession(UserId, MaxNumPlayers, SessionName, *SessionSettings);
		}
		
		return false;
	}
	return false;
}

