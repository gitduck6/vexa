#include "../include/core/common.hpp"

namespace mk = cone;

int main() {
    constexpr usize BUFFER_SIZE = { 24 };
    char buffer[BUFFER_SIZE];
    auto item_size = mk::item_size(buffer);
    mk::log::info("item-size: {}", item_size);
}
