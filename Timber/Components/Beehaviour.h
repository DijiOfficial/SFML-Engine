#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
}

namespace timber 
{
    class Beehaviour : public diji::Component
    {
    public:
        Beehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Beehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override;
		
        void FixedUpdate() override {}
        void Update() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
        
    protected:
        float m_MinSpeed = 200.f;
        float m_MaxSpeed = 400.f;
        float m_MinHeight = 500.f;
        float m_MaxHeight = 1000.f;
        float m_StartPosition = 2000.f;
        int m_SpeedModifier = -1;
        
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        float m_Speed = 0.f;
        
        void Randomize();
    };
}
