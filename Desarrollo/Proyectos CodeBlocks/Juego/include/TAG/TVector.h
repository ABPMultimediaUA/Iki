#ifndef TVECTOR_H
#define TVECTOR_H


class TVector
{
    public:
        TVector(float x1,float y1,float z1) : X(x1), Y(y1), Z(z1) {}
        ~TVector();

        float dotProduct(TVector other){return X*other.X + Y*other.Y + Z*other.Z;};


        float X, Y, Z;

        // operators

        TVector operator-() const { return TVector(-X, -Y, -Z); }

        TVector& operator=(const TVector& other) { X = other.X; Y = other.Y; Z = other.Z; return *this; }

        TVector operator+(const TVector& other) const { return TVector(X + other.X, Y + other.Y, Z + other.Z); }
        TVector& operator+=(const TVector& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }
        TVector operator+(const float val) const { return TVector(X + val, Y + val, Z + val); }
        TVector& operator+=(const float val) { X+=val; Y+=val; Z+=val; return *this; }

        TVector operator-(const TVector& other) const { return TVector(X - other.X, Y - other.Y, Z - other.Z); }
        TVector& operator-=(const TVector& other) { X-=other.X; Y-=other.Y; Z-=other.Z; return *this; }
        TVector operator-(const float val) const { return TVector(X - val, Y - val, Z - val); }
        TVector& operator-=(const float val) { X-=val; Y-=val; Z-=val; return *this; }

        TVector operator*(const TVector& other) const { return TVector(X * other.X, Y * other.Y, Z * other.Z); }
        TVector& operator*=(const TVector& other) { X*=other.X; Y*=other.Y; Z*=other.Z; return *this; }
        TVector operator*(const float v) const { return TVector(X * v, Y * v, Z * v); }
        TVector& operator*=(const float v) { X*=v; Y*=v; Z*=v; return *this; }

        TVector operator/(const TVector& other) const { return TVector(X / other.X, Y / other.Y, Z / other.Z); }
        TVector& operator/=(const TVector& other) { X/=other.X; Y/=other.Y; Z/=other.Z; return *this; }
        TVector operator/(const float v) const { float i=(float)1.0/v; return TVector(X * i, Y * i, Z * i); }
        TVector& operator/=(const float v) { float i=(float)1.0/v; X*=i; Y*=i; Z*=i; return *this; }

    protected:

    private:

};

#endif // TVECTOR_H
