#include "Events/Event.h"

namespace licht
{
    class Core
    {
    public:
        Event<>& get_update();
        Event<>& get_fixed_update();
        Event<>& get_late_update();
        Event<>& get_render();

    private:
        Event<> m_update;
        Event<> m_fixed_update;
        Event<> m_late_update;
        Event<> m_render;
    };
} // namespace licht
