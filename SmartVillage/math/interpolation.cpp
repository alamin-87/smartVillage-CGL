#include "interpolation.h"
#include <cmath>

namespace MathUtil {

    float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    float smoothstep(float edge0, float edge1, float x) {
        float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return t * t * (3.0f - 2.0f * t);
    }

    float clamp(float value, float minVal, float maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }

    float mapRange(float value, float inMin, float inMax, float outMin, float outMax) {
        return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));
    }

    float easeInQuad(float t) {
        return t * t;
    }

    float easeOutQuad(float t) {
        return t * (2.0f - t);
    }

    float pingPong(float t, float length) {
        float mod = fmod(t, length * 2.0f);
        if (mod > length) mod = length * 2.0f - mod;
        return mod / length;
    }
}
