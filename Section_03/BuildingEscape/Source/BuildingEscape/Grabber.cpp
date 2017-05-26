// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent(){
    /// Look for attached Physics Handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        //Physics handle found
    }
    else
    {
        UE_LOG(LogTemp,Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
    }
}


/// Look for attached Input Component (only appears at run time)
void UGrabber::SetupInputComponent(){
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        //Input component found
        UE_LOG(LogTemp, Warning, TEXT("Input Component Found"))
        /// Bind input axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp,Error, TEXT("%s missing input component"), *GetOwner()->GetName())
    }

}

void UGrabber::Grab(){
    UE_LOG(LogTemp, Error, TEXT("Grab pressed"))
    
    // LINE TRACE and see if we reach actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    // If we hit something, then attach a physics handle
    if (ActorHit){
    ///TODO attach physics handle
    PhysicsHandle->GrabComponent(
                                 ComponentToGrab,
                                 NAME_None,
                                 ComponentToGrab->GetOwner()->GetActorLocation(),
                                 true // allow rotation
                            );
    }
}

void UGrabber::Release(){
    UE_LOG(LogTemp, Error, TEXT("Grab released"))
    ///TODO release physics handle
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Get player viewpoint this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
    //UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
    // Draw a red trace in the world to visualize
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    

    // if the physics handle is attached
    if(PhysicsHandle->GrabbedComponent){
        
        // move the object we are holding
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
        
    }

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
    // Get player viewpoint this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
    //UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
    // Draw a red trace in the world to visualize
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    
    /// Setup  query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// Ray-cast out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT Hit,
                                            PlayerViewPointLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            
                                            );
    /// See what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
    }
    return Hit;
}
