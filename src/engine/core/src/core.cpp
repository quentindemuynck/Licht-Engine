#include "Core.h"


Event<>& licht::Core::get_update(){
    return m_update;
};
Event<>& licht::Core::get_fixed_update(){
    return m_fixed_update;
};
Event<>& licht::Core::get_late_update(){
    return m_late_update;
};
Event<>& licht::Core::get_render(){
    return m_render;
};
