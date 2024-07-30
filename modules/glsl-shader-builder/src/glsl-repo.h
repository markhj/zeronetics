#pragma once

#include <string>

const char *structCamera3D = R"(struct Camera3D {
    vec3 position;
};)";

const char *structDirectionalLight3D = R"(struct DirectionalLight3D {
    vec3 direction;
    vec3 color;
};)";

const char *calculateDirectionalLight3D = R"(vec3 calculateDirectionalLight3D(DirectionalLight3D light) {
    vec3 viewDir = normalize(camera3d.position - position);
    vec3 lightDir = normalize(-light.direction);
    vec3 diffuse = light.color * max(dot(normal, lightDir), 0.0);

    return diffuse;
})";

const char *structPointLight3D = R"(struct PointLight3D {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};)";

const char *calculatePointLight3D = R"(vec3 calculatePointLight3D(PointLight3D light) {
    vec3 viewDir = normalize(camera3d.position - position);
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(normal, lightDir), 0.0);
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return attenuation * light.color * diff;
})";
