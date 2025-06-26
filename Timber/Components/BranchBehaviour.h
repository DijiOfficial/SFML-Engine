#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class TextureComp;
}

namespace diji
{
    class Transform;
    class Render;
}

namespace timber
{
    enum class BranchSide
    {
        Left,
        Right,
        None
    };
    
    class BranchBehaviour final : public diji::Component
    {
    public:
        explicit BranchBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~BranchBehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetHeight(const float height) { m_Height = height; }
        
        diji::Event<> OnDeathEvent;

    private:
        diji::TextureComp* m_TextureCompPtr = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        BranchSide m_BranchSide = BranchSide::None;

        float m_Height = 0.f;
        float m_OriginHeight = 0.f;

        void ChooseRandomSide();
        void MoveBranch(bool isLeft = false);
        void Reset();
    };
}


