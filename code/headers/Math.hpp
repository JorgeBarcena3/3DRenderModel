// File: Math.h
// Description : Cabecera que implementa las clases de vector2, vector3 y mat4...
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2019  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <Point.hpp>
#include "Color_Buffer_Rgba8888.hpp"
#include "Model3D.hpp"
#define PI 3.14159265359f


using toolkit::Point3f;
using toolkit::Point4f;


/**** Implementacion de la clase de Vector2 con sus respectivos operandos
*/
template <class T>
class vec2
{

public:
    union {

        struct
        {
            T x;
            T y;
        };
        T v[2];
    };

public:

    /**** Implementacion del constructor por defecto (Suele estar vacio por defecto)
    */
    vec2()
    {
        x = 0;
        y = 0;
    };

    /**** Implementacion del constructor con parametros
    */
    vec2(T a_X, T a_Y) : x(a_X), y(a_Y) {
    };

    /**** Implementacion del constructor con parametros
    */
    vec2(const vec2<T>& _a) : x(_a.x), y(_a.y) {
    };

    /**** Operacion de igualacion
    */
    vec2& operator=(const vec2& vec) {

        x = vec.x;
        y = vec.y;
        return *this;
    };

    /**** Operacion de suma
    */
    vec2& operator+=(const vec2& vec2) {

        x += vec2.x;
        y += vec2.y;
        return *this;
    };

    /**** Operacion de suma
    */
    template <class T>
    vec2<T> operator+(const vec2<T> vec2) {

        return vec2<T>(*this) -= vec2;
    }

    /**** Operacion de resta
    */
    vec2& operator-=(const vec2& vec2) {


        x += (-vec2.x);
        y += (-vec2.y);
        return *this;
    };

    /**** Operacion de resta
    */
    template <class T>
    vec2<T>  operator-(const vec2<T>& vec2) {

        return vec2<T>(*this) -= vec2;

    };

    /**** Producto de un vector por un número
    */
    vec2& operator*=(T _num) {

        x *= _num;
        y *= _num;
        return *this;
    };

    /**** Operacion de Multiplicacion
    */
    template <class T>
    vec2<T>  operator*(T _num) {

        vec2 <T> result(*this);
        return  result *= _num;

    };

    /**** Division de un vector entre un número
    */
    vec2& operator/=(T _num) {
        x /= _num;
        y /= _num;
        return *this;
    };

    /**** Operacion de Multiplicacion
    */
    vec2<T>  operator*(T _num) {

        vec2 <T> result(*this);
        return  result /= _num;

    };

    /**** Operacion de comparacion
    */
    bool operator==(const vec2<T>& vec2) {
        return (*this.x == vec2.x && *this.y == vec2.y);
    };

    /**** Operacion de distinto de
    */
    bool operator!=(const vec2<T>& vec2) {
        return (*this.x != vec2.x || *this.y != vec2.y);
    };

    /**** Operador corchetes constante
    */
    const T& operator[](size_t a_Index) const {

        return v[a_Index];

    };

    /**** Operador corchetes constante
    */
    T& operator[](size_t a_Index) {

        return v[a_Index];

    };

    /**** Producto escalar de vectores
    */
    T producto_escalar(vec2 const& vec2) const {

        return (x * vec2.x + y * vec2.y);

    };

    /**** Nomaliza el vector
    */
    vec2& normalize() {

        float inv_magnitude = inv_length();
        x = x * inv_magnitude;
        y = y * inv_magnitude;
        return *this;

    };


    /**** Inversa de la longitud
    */
    vec2& inv_length() {

        return 1.f / length();

    };

    /**** Longitud del vector
    */
    T length() const {

        return sqrt((x * x) + (y * y));

    };
};


/**** Operacion de Multiplicacion
*/
template <class T>
vec2<T>  operator *(T _num, const vec2<T>& _vec) {

    vec2 <T> result(_vec);
    return  result *= _num;

};

/**** Operacion de division
*/
template <class T>
vec2<T>  operator/(T _num, const vec2<T>& _vec) {

    vec2 <T> result(_vec);
    return  result /= _num;

};

/**** Clase para almacenar vectores de 3 dimensiones
*/
template <class T>
class vec3 {

public:

    union {
        struct
        {
            T x;
            T y;
            T z;
        };
        T v[3];
        struct
        {
            T r;
            T g;
            T b;

        };
    };

public:

    /**** Constructor por defecto (Según el estandar debe estar vacio)
    */
    vec3() {

        x = z = y = 0;
    };

    /**** Constructor con parametros
    */
    vec3(T a_X, T a_Y, T a_Z) : x(a_X), y(a_Y), z(a_Z) {
    };

    /**** Constructor con parametros
    */
    vec3(const vec3<T>& _a) : x(_a.x), y(_a.y), z(_a.z) {
    };

    /**** Operador de igualacion
    */
    vec3& operator=(const vec3& vec) {

        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    };

    /**** Operador de suma
    */
    vec3& operator+=(const vec3& vec2) {

        x += vec2.x;
        y += vec2.y;
        z += vec2.z;
        return *this;
    };

    /**** Operador de suma
    */
    vec3<T> operator+(const vec3<T>& vec2) {
        vec3 <T> result(*this);
        return result += vec2;
    };

    /**** Operador de resta
    */
    vec3& operator-=(const vec3& vec2) {

        x += -vec2.x;
        y += -vec2.y;
        z += -vec2.z;
        return *this;
    };

    /**** Operador de resta
    */
    vec3<T> operator-(const vec3<T>& vec2) {
        vec3 <T> result(*this);
        return result -= vec2;
    };

    /**** Operador de multiplicacion
    */
    vec3& operator*=(T _num) {

        x *= _num;
        y *= _num;
        z *= _num;
        return *this;

    };

    /**** Operador de multiplicacion
    */
    vec3<T> operator*(T _num) {
        vec3 <T> result(*this);
        return result *= _num;
    };

    /**** Operador de division
    */
    vec3& operator/=(T _num) {

        x /= _num;
        y /= _num;
        z /= _num;
        return *this;
    };


    /**** Operador de multiplicacion
    */
    vec3<T> operator/(T _num) {
        vec3 <T> result(*this);
        return result /= _num;
    };

    /**** Operador corchetes constante
    */
    T& operator[](size_t a_Index) const {

        return v[a_Index];

    };

    /**** Operador corchetes constante
    */
    T& operator[](size_t a_Index) {

        return v[a_Index];

    };

    /**** Operador distinto de
    */
    bool operator!=(const vec3<T>& vec2) {
        return (*this.x == vec2.x && *this.y == vec2.y && *this.z == vec2.z);
    };

    /**** Operador comparador
    */
    bool operator==(const vec3<T>& vec2) {
        return (*this.x == vec2.x && *this.y == vec2.y && *this.z == vec2.z);
    };

    /**** Producto escalar de vectores
    */
    T producto_escalar(vec3 const& vec2) const {

        return (x * vec2.x + y * vec2.y + z * vec2.z);

    };

    /**** Operacion de cross. Obtiene el vector perpendicular dados dos vectores
    */
    vec3 cross(vec3 const& vec2) const {

        return vec3((y * vec2.z) - (z * vec2.y), (z * vec2.x) - (x * vec2.z), (x * vec2.y) - (y * vec2.x));

    };

    /**** Operacion de normalizacion
    */
    vec3& normalize() {

        float inv_magnitude = invLength();
        x = x * inv_magnitude;
        y = y * inv_magnitude;
        z = z * inv_magnitude;

        return *this;

    };

    /**** Inversa de la longitud del vector
    */
    T invLength() const {

        return 1 / sqrt((x * x) + (y * y) + (z * z));

    };

    /**** Longitud del vector
    */
    T length() const {

        return sqrt((x * x) + (y * y) + (z * z));

    };

    static vec3<float> toVec3f(toolkit::Point3f& point)
    {
        return vec3<float>(point[0], point[1], point[2]);
    }

    static vec3<float> toVec3f(toolkit::Point4f point)
    {
        return vec3<float>(point[0], point[1], point[2]);
    }

    static vec3<float> toVec3f(RenderModel::Model3D::Color& point)
    {
        return vec3<float>(point.data.component.r, point.data.component.g, point.data.component.b);
    }
};


/**** Operacion de Multiplicacion
*/
template <class T>
vec3<T>  operator *(T _num, const vec3<T>& _vec) {

    vec3 <T> result(_vec);
    return  result *= _num;

};

/**** Operacion de division
*/
template <class T>
vec3<T>  operator/(T _num, const vec3<T>& _vec) {

    vec3 <T> result(_vec);
    return  result /= _num;

};


/**** Operacion de producto escalar
*/
template <class T>
float producto_escalar(const vec3<T>& vec1, const vec3<T>& vec2) {
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}



typedef vec3<float> vec3f;

inline float dot(const vec3f& a_Lhs, const vec3f& a_Rhs) { return (a_Lhs.x * a_Rhs.x + a_Lhs.y * a_Rhs.y + a_Lhs.z * a_Rhs.z); }