#ifndef __TLETC_VEC3__
#define __TLETC_VEC3__

#include <iostream>
#include <string.h>
#include <logging.h>

namespace tletc {
    //3 Float vector
    struct Vec3{
        union{
            float elements[3];
            struct {float x; float y; float z;};
        };

        Vec3();
        Vec3(float x, float y, float z);
        ~Vec3();

        const float& operator[](int index) const;
        float& operator[](int index);
        
        void operator+=(const Vec3& other);
        void operator-=(const Vec3& other);
        void operator*=(const Vec3& other);
        void operator/=(const Vec3& other);

        friend std::ostream& operator<<(std::ostream& stream, Vec3& vector);

        friend Vec3 operator+(Vec3 left, Vec3 right);
        friend Vec3 operator-(Vec3 left, Vec3 right);
        friend Vec3 operator*(Vec3 left, Vec3 right);
        friend Vec3 operator/(Vec3 left, Vec3 right);

        private:
        void add(const Vec3& other);
        void subtract(const Vec3& other);
        void multiply(const Vec3& other);
        void divide(const Vec3& other);
    };
}


#endif