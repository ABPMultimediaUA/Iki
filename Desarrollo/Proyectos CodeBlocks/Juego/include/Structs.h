#ifndef STRUCTS_H
#define STRUCTS_H

#include <irrlicht.h>
#include <iostream>
#include <stdio.h>
#include "vector"
#include "string"
#include <math.h>
#include <windows.h>
#include <iosfwd>
#include <limits>

#include <Box2D/Box2D.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class Structs
{
    public:
        Structs();
        virtual ~Structs();

        struct TPosicion{
            float X;
            float Y;
            float Z;

            TPosicion():X(0.0),Y(0.0),Z(0.0){}
            TPosicion(float a, float b, float c):X(a),Y(b),Z(c){}

            //returns the length of the vector
            inline float Length()const{
                return sqrt(X * X + Y * Y + Z * Z);
            }

            inline void Normalize()
            {
              float vector_length = this->Length();
              if(vector_length != 0){
                this->X = (this->X / vector_length);
                this->Y = (this->Y / vector_length);
                this->Z = (this->Z / vector_length);
              }
            }
            //returns the distance between this vector and th one passed as a parameter
            inline float Distance(const TPosicion &v2)const{
                float zSeparation = v2.Z - Z;
                float xSeparation = v2.X - X;

                return sqrt(zSeparation*zSeparation + xSeparation*xSeparation);
            }
            const TPosicion operator+(const TPosicion &rhs){

                float  x = X +rhs.X;
                float  y = Y +rhs.Y;
                float  z = Z +rhs.Z;

                TPosicion result(x,y,z);
                return result;
            }
            const TPosicion operator-(const TPosicion &rhs) {
                float  x = X - rhs.X;
                float  y = Y - rhs.Y;
                float  z = Z - rhs.Z;

                TPosicion result(x,y,z);
                return result;
            }

            const TPosicion operator*(const TPosicion &rhs){
                float  x = X *rhs.X;
                float  y = Y *rhs.Y;
                float  z = Z *rhs.Z;
                TPosicion result (x,y,z);
                return result;
            }
            const TPosicion operator*(float rhs){
                float  x = X *rhs;
                float  y = Y *rhs;
                float  z = Z *rhs;
                TPosicion result (x,y,z);
                return result;
            }

            const TPosicion operator/(float rhs){
                float  x = X /rhs;
                float  y = Y /rhs;
                float  z = Z /rhs;
                TPosicion result (x,y,z);
                return result;
            }

            const TPosicion& operator+=(const TPosicion &rhs)
            {
                X += rhs.X;
                Y += rhs.Y;
                Z += rhs.Z;

                return *this;
            }

            const TPosicion& operator-=(const TPosicion &rhs)
            {
                X -= rhs.X;
                Y -= rhs.Y;
                Z -= rhs.Z;

                return *this;
            }

            const TPosicion& operator*=(const float& rhs)
            {
                X *= rhs;
                Y *= rhs;
                Z *= rhs;

                return *this;
            }

            const TPosicion& operator/=(const float& rhs)
            {
                X /= rhs;
                Y /= rhs;
                Z /= rhs;

                return *this;
            }

            bool operator==(const TPosicion& rhs)const
            {

                  if (fabs(X-rhs.X) < 1E-12 && fabs(Y-rhs.Y) < 1E-12 && fabs(Z-rhs.Z) < 1E-12 )
                  {
                    return true;
                  }
                  else{
                    return false;
                  }

            }

            bool operator!=(const TPosicion& rhs)const
            {
                return (X != rhs.X) || (Y != rhs.Y) || (Z != rhs.Z);
            }

            //------------------ isSecondInFOVOfFirst -------------------------------------
            //
            //  returns true if the target position is in the field of view of the entity
            //  positioned at posFirst facing in facingFirst
            //-----------------------------------------------------------------------------
            inline bool isSecondInFOVOfFirst(TPosicion posFirst,
                                             TPosicion facingFirst,
                                             TPosicion posSecond,
                                             float    fov)
            {
              TPosicion toTarget = posSecond - posFirst;
              toTarget.Normalize();
              return facingFirst.Dot(toTarget) >= cos(fov/2.0);
            }
            //------------------------- Vec2DDot -------------------------------------
            //
            //  calculates the dot product
            //------------------------------------------------------------------------
            inline float Dot(const TPosicion &v2)const
            {
              return X*v2.X + Z*v2.Z;
            }
            inline void rotarVector(double radianes){
                double ca = cos(radianes);
                double sa = sin(radianes);
                this->X = ca*this->X - sa*this->Z;
                this->Z = sa*this->X + ca*this->Z;
            }

        };

        typedef struct{
            int opacity;
            int r;
            int g;
            int b;
        }TColor;

        typedef struct{
            float ancho;
            float alto;
            float profundo;
        }TMedida;

        typedef struct{
            int X_inicio;
            int Y_inicio;
            int X_final;
            int Y_final;
        }TRectangulo;

    protected:

    private:
};



#endif // STRUCTS_H
