#ifndef ATOM_MATH_HPP
#define ATOM_MATH_HPP
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace AtomMath
{
    // Constantes matemáticas
    const float PI = 3.14159265358979323846f;
    const float DEG_TO_RAD = PI / 180.0f;
    const float RAD_TO_DEG = 180.0f / PI;

    // Usando GLM para eficiencia
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Matrix4 = glm::mat4;

    // Funciones útiles
    inline float ToRadians(float degrees) { return degrees * DEG_TO_RAD; }
    inline float ToDegrees(float radians) { return radians * RAD_TO_DEG; }

    inline Vector2 Normalize(const Vector2& v) { return glm::normalize(v); }
    inline Vector3 Normalize(const Vector3& v) { return glm::normalize(v); }
    inline Vector4 Normalize(const Vector4& v) { return glm::normalize(v); }

    inline float Dot(const Vector2& a, const Vector2& b) { return glm::dot(a, b); }
    inline float Dot(const Vector3& a, const Vector3& b) { return glm::dot(a, b); }
    inline float Dot(const Vector4& a, const Vector4& b) { return glm::dot(a, b); }

    inline Vector3 Cross(const Vector3& a, const Vector3& b) { return glm::cross(a, b); }

    inline float Length(const Vector2& v) { return glm::length(v); }
    inline float Length(const Vector3& v) { return glm::length(v); }
    inline float Length(const Vector4& v) { return glm::length(v); }

    inline float Distance(const Vector2& a, const Vector2& b) { return glm::distance(a, b); }
    inline float Distance(const Vector3& a, const Vector3& b) { return glm::distance(a, b); }

    // Matrices
    inline Matrix4 Translate(const Matrix4& m, const Vector3& v) { return glm::translate(m, v); }
    inline Matrix4 Rotate(const Matrix4& m, float angle, const Vector3& axis) { return glm::rotate(m, angle, axis); }
    inline Matrix4 ScaleMatrix(const Matrix4& m, const Vector3& v) { return glm::scale(m, v); }

    inline Matrix4 Perspective(float fovy, float aspect, float near, float far) {
        return glm::perspective(fovy, aspect, near, far);
    }

    inline Matrix4 Ortho(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f) {
        return glm::ortho(left, right, bottom, top, near, far);
    }

    inline Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
        return glm::lookAt(eye, center, up);
    }
}

#endif // !ATOM_MATH_HPP
