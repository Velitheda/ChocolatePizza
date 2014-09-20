#include <emscripten/bind.h>

using namespace emscripten;
std::string unxz(const std::string& compressed);

EMSCRIPTEN_BINDINGS(xz) {
    function("unxz", &unxz);
}

