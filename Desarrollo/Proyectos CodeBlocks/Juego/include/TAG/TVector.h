#ifndef TVECTOR_H
#define TVECTOR_H


class TVector
{
    public:
        TVector(T,T,T);
        ~TVector();

        T dotProduct(TVector);

        T x, y, z;

        // operators

        TVector operator-() const { return TVector(-X, -Y, -Z); }

        TVector& operator=(const TVector& other) { X = other.X; Y = other.Y; Z = other.Z; return *this; }

        TVector operator+(const TVector& other) const { return TVector(X + other.X, Y + other.Y, Z + other.Z); }
        TVector& operator+=(const TVector& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }
        TVector operator+(const T val) const { return TVector(X + val, Y + val, Z + val); }
        TVector& operator+=(const T val) { X+=val; Y+=val; Z+=val; return *this; }

        TVector operator-(const TVector& other) const { return TVector(X - other.X, Y - other.Y, Z - other.Z); }
        TVector& operator-=(const TVector& other) { X-=other.X; Y-=other.Y; Z-=other.Z; return *this; }
        TVector operator-(const T val) const { return TVector(X - val, Y - val, Z - val); }
        TVector& operator-=(const T val) { X-=val; Y-=val; Z-=val; return *this; }

        TVector operator*(const TVector& other) const { return TVector(X * other.X, Y * other.Y, Z * other.Z); }
        TVector& operator*=(const TVector& other) { X*=other.X; Y*=other.Y; Z*=other.Z; return *this; }
        TVector operator*(const T v) const { return TVector(X * v, Y * v, Z * v); }
        TVector& operator*=(const T v) { X*=v; Y*=v; Z*=v; return *this; }

        TVector operator/(const TVector& other) const { return TVector(X / other.X, Y / other.Y, Z / other.Z); }
        TVector& operator/=(const TVector& other) { X/=other.X; Y/=other.Y; Z/=other.Z; return *this; }
        TVector operator/(const T v) const { T i=(T)1.0/v; return TVector(X * i, Y * i, Z * i); }
        TVector& operator/=(const T v) { T i=(T)1.0/v; X*=i; Y*=i; Z*=i; return *this; }

    protected:

    private:

};

#endif // TVECTOR_H
