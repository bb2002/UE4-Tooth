// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tooth.h"
#include "UObject/NoExportTypes.h"
#include "Library/Http/Data/ServerRankingObject.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Games/Instance/ToothGameInstance.h"
#include "GameHttpRequester.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnServerResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyRankResponse, int32, Rank);

/**
 * 
 */
UCLASS()
class UGameHttpRequester : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnServerResponse OnServerResponseCallback;

	UPROPERTY(BlueprintAssignable)
	FOnMyRankResponse OnMyRankCallback;

	UFUNCTION(BlueprintCallable, DisplayName = "UploadRanking")
	void UploadRank();

	UFUNCTION(BlueprintCallable, DisplayName = "LoadServerRanking")
	void LoadServerRank();

	UFUNCTION(BlueprintCallable, DisplayName = "LoadMyRanking")
	void LoadMyRanking();

	TSharedRef<IHttpRequest> InitRequest();

	void LoadServerRankListener(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void MyRankListener(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataSet")
	TArray<FServerRankingObject> RankDataSet;

private:
	FHttpModule* Http;
	FString APIBaseUrl = "http://saintdev.kr/tooth/";
	FString AuthHeader = TEXT("Authorization");
};
