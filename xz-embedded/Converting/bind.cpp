#include "xz.h"

#include <emscripten/bind.h>

using namespace emscripten;


EMSCRIPTEN_BINDINGS(xz) {
    function("xz_crc32_init", &xz_crc32_init);
}