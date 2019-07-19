// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHttpRequester.h"
#include "Games/Saves/ToothRanking.h"
#include "Games/Saves/ToothSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Games/Modes/ToothDefaultGameMode.h"

void UGameHttpRequester::UploadRank() {
	UToothGameInstance * Instance = Cast<UToothGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UToothSettings* SettingInstance = Instance->LoadGameSettings();
	UToothRanking* RankingInstance = Instance->LoadGameRanking();

	FString PlayerName = SettingInstance->PlayerName;
	FString PlayerUUID = SettingInstance->PlayerUUID;
	FString HighestScore = FString::FromInt(RankingInstance->HighestScore);
	FString HighestLevel = FString::FromInt(RankingInstance->HighestLevel);

	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = InitRequest();
	Request->SetURL(APIBaseUrl + "rankup.php?pn=" + PlayerName + "&ud=" + PlayerUUID + "&se=" + HighestScore + "&ts=" + HighestLevel);
	Request->ProcessRequest();
}

void UGameHttpRequester::LoadServerRank()
{
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = InitRequest();
	Request->SetURL(APIBaseUrl + "loadrank.php");

	Request->OnProcessRequestComplete().BindUObject(this, &UGameHttpRequester::LoadServerRankListener);
	Request->ProcessRequest();
}

void UGameHttpRequester::LoadMyRanking()
{
	UToothGameInstance * Instance = Cast<UToothGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UToothSettings* SettingInstance = Instance->LoadGameSettings();

	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = InitRequest();
	Request->SetURL(APIBaseUrl + "myrank.php?uuid=" + SettingInstance->PlayerUUID);

	Request->OnProcessRequestComplete().BindUObject(this, &UGameHttpRequester::MyRankListener);
	Request->ProcessRequest();
}

TSharedRef<IHttpRequest> UGameHttpRequester::InitRequest()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->SetVerb("GET");
	return Request;
}

void UGameHttpRequester::MyRankListener(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return;

	FString Data = Response->GetContentAsString();
	int32 Rank = FCString::Atoi(*Data);

	OnMyRankCallback.Broadcast(Rank);
}

void UGameHttpRequester::LoadServerRankListener(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid()) return;

	FString JsonResponse = Response->GetContentAsString();
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonResponse);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	TArray<FServerRankingObject> RankList;

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid()) {
		// Json OK.
		auto NameArray = JsonObject->GetArrayField("name_array");
		auto ScoreArray = JsonObject->GetArrayField("score_array");
		auto TopStageArray = JsonObject->GetArrayField("top_stage_array");

		for (int i = 0; i < NameArray.Num(); ++i) {
			FServerRankingObject RankObject;

			FString NameTmp;
			double ScoreTmp, TopStageTmp;

			// Recv
			NameArray[i]->TryGetString(NameTmp);
			ScoreArray[i]->TryGetNumber(ScoreTmp);
			TopStageArray[i]->TryGetNumber(TopStageTmp);

			RankObject.PlayerNickname = NameTmp;
			RankObject.HighestScore = ScoreTmp;
			RankObject.HighestStage = TopStageTmp;
			RankList.Add(RankObject);
		}
	}

	RankDataSet = RankList;
	OnServerResponseCallback.Broadcast();

}
