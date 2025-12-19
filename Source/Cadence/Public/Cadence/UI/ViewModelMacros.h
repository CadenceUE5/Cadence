#pragma once

#if __INTELLISENSE__
#define K8_LOG(Verbosity, Message, ...)
#endif

#define K8_DECLARE_SETTINGS_VIEWMODEL(VMClassName, ValueType, PropertyName)                        \
    UCLASS()                                                                                       \
    class CADENCE_API VMClassName : public UMVVMViewModelBase, public IK8_ViewModelInterface       \
    {                                                                                              \
        GENERATED_BODY()                                                                           \
                                                                                                   \
    public:                                                                                        \
        virtual bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings) override;           \
                                                                                                   \
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly)                                              \
        bool bInitialized = false;                                                                 \
                                                                                                   \
        UFUNCTION(BlueprintPure)                                                                   \
        ValueType Get##PropertyName() const;                                                       \
                                                                                                   \
        UFUNCTION(BlueprintCallable)                                                               \
        void Set##PropertyName(ValueType& NewValue);                                               \
                                                                                                   \
    private:                                                                                       \
        UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))     \
        ValueType PropertyName;                                                                    \
    };

#define K8_DEFINE_SETTINGS_VIEWMODEL(VMClassName, ValueType, PropertyName, SettingsAccessorExpr,   \
                                     DefaultValue)                                                 \
    bool VMClassName::Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings)                    \
    {                                                                                              \
        if (!Settings)                                                                             \
        {                                                                                          \
            K8_LOG(Error, "Initialization failed, invalid settings.");                             \
            return false;                                                                          \
        }                                                                                          \
                                                                                                   \
        if (UE_MVVM_SET_PROPERTY_VALUE(PropertyName, SettingsAccessorExpr))                        \
        {                                                                                          \
            bInitialized = true;                                                                   \
                                                                                                   \
            return true;                                                                           \
        }                                                                                          \
                                                                                                   \
        return false;                                                                              \
    }                                                                                              \
                                                                                                   \
    ValueType VMClassName::Get##PropertyName() const                                               \
    {                                                                                              \
        if (!bInitialized)                                                                         \
        {                                                                                          \
            K8_LOG(Error, "Getter called without initialization");                                 \
            return DefaultValue;                                                                   \
        }                                                                                          \
                                                                                                   \
        return PropertyName;                                                                       \
    }                                                                                              \
                                                                                                   \
    void VMClassName::Set##PropertyName(ValueType& NewValue)                                       \
    {                                                                                              \
        if (!bInitialized)                                                                         \
        {                                                                                          \
            K8_LOG(Error, "Setter called without initialization");                                 \
            return;                                                                                \
        }                                                                                          \
        if (UK8_WorldSubsystemSettingsDataAsset* Settings                                          \
            = UK8_GameInstanceBase::GetCurrentWorldSettingsStatic(this))                           \
        {                                                                                          \
            if (UE_MVVM_SET_PROPERTY_VALUE(PropertyName, SettingsAccessorExpr))                    \
            {                                                                                      \
                Settings->PropertyName = NewValue;                                                 \
            }                                                                                      \
        }                                                                                          \
    }
