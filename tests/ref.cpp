#include "monako.hpp"

namespace mk = monako;

int main()
{
    int32 x = 10;
    constexpr int32 y = 10;

    mk::Ref<int> r1 = mk::Ref(x);
    mk::RefMut r2 = {x};

    MK_UNUSE(x, r1, r2);
}
