#pragma once

#include <string>

std::string structCamera3D = R"(struct Camera3D {
    vec3 position;
};)";

std::string structPointLight3D = R"(struct PointLight3D {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};)";

std::string calculatePointLight3D = R"(vec3 calculatePointLight3D(PointLight3D light) {
    vec3 viewDir = normalize(camera3d.position - position);
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(normal, lightDir), 0.0);
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return attenuation * light.color * diff;
})";
