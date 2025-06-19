#pragma once
namespace diji 
{
    class GameObject;

    // todo: should be interface?
    class Component
    {
    public:
        virtual ~Component() noexcept = default;

        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;

        virtual void Init() = 0;
        virtual void OnEnable() = 0;
        virtual void Start() = 0;
		
        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;

        virtual void OnDisable() = 0;
        virtual void OnDestroy() = 0;
    protected:
        explicit Component(GameObject* ownerPtr) : m_OwnerPtr{ ownerPtr } {}
        const GameObject* GetOwner() const { return m_OwnerPtr; }

    private:
        GameObject* m_OwnerPtr = {};
    };
}
