// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tooth.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Library/Http/GameHttpRequester.h"
#include "ToothDefaultPawn.generated.h"

UCLASS()
class AToothDefaultPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AToothDefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta=(AllowPrivateAccess = true))
	USceneComponent* VRCameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller", Meta = (AllowPrivateAccess = true))
	UMotionControllerComponent* MotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller", Meta = (AllowPrivateAccess = true))
	UWidgetInteractionComponent* WidgetInteractor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller", Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MotionControllerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Util", Meta = (AllowPrivateAccess = true))
	UGameHttpRequester* HttpRequesterComponent;
};
