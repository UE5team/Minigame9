#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CharacterBase.h"

// �R���X�g���N�^
AItemBase::AItemBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // �����蔻��p��Sphere
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(50.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    RootComponent = CollisionSphere;

    // ���b�V��
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    ItemMesh->SetupAttachment(RootComponent);

    // �f�t�H���g�ݒ�
    ItemName = TEXT("DefaultItem");
    bCanPickup = true;
}

// �Q�[���J�n��
void AItemBase::BeginPlay()
{
    Super::BeginPlay();

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapBegin);
}

// Tick
void AItemBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// �A�C�e�����E��������
void AItemBase::OnPickup(ACharacterBase* PickupInstigator)
{
    if (bCanPickup && PickupInstigator)
    {
        // �L�������ŃJ�E���g���₷
        PickupInstigator->AddItemCount();

        //UE_LOG(LogTemp, Log, TEXT("%s picked up by %s"), *ItemName, *PickupInstigator->GetName());

        // �j��
        Destroy();
    }
}

// �Փˌ��m
void AItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // �L�����N�^�[��������E�킹��
        if (ACharacterBase* Char = Cast<ACharacterBase>(OtherActor))
        {
            OnPickup(Char);
        }
    }
}

void AItemBase::MoveVertical(int z) 
{
    move_amount = z;

    FVector Location = GetActorLocation();
    if (moveup) 
    {
        Location.Z += move_amount;
    }
    else 
    {
        Location.Z -= move_amount;
    }

    SetActorLocation(Location);

    moveup = !moveup;
}
