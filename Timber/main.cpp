#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "engine/core/Engine.h"
#include "Core/GameLoader.h"

int main(int, char* [])
{
    const diji::Engine engine("../Timber/Resources/");
    engine.Run(Scene::DefaultCircle);
    
    return 0;
}
