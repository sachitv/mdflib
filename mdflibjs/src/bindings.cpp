#include <emscripten/bind.h>

#include <mdf/mdfreader.h>

using namespace emscripten;

float add(float a, float b) {
    return a + b;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("add", &add);
}
