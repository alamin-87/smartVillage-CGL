#ifndef INTERPOLATION_H
#define INTERPOLATION_H

namespace MathUtil {
    // Linear interpolation between a and b by factor t (0.0 to 1.0)
    float lerp(float a, float b, float t);
    
    // Smooth step (ease-in ease-out) interpolation
    float smoothstep(float edge0, float edge1, float x);
    
    // Clamp value between min and max
    float clamp(float value, float minVal, float maxVal);

    // Map a value from one range to another
    float mapRange(float value, float inMin, float inMax, float outMin, float outMax);
    
    // Ease-in quadratic
    float easeInQuad(float t);
    
    // Ease-out quadratic
    float easeOutQuad(float t);

    // Ping-pong oscillation (0 to 1 to 0 cyclically)
    float pingPong(float t, float length);
}

#endif
