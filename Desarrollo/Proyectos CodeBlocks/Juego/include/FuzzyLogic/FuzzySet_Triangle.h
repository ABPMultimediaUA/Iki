#ifndef FUZZYSET_TRIANGLE_H
#define FUZZYSET_TRIANGLE_H

#include <FuzzySet.h>


class FuzzySet_Triangle : public FuzzySet
{
    public:
        FuzzySet_Triangle();
        virtual ~FuzzySet_Triangle();

        FuzzySet_Triangle(float mid, float lft, float rgt):
            FuzzySet(mid),
            m_dPeakPoint(mid),
            m_dLeftOffset(lft),
            m_dRightOffset(rgt)
        {}
        //this method calculates the degree of membership for a particular value
        float CalculateDOM(float val)const;

    private:
        //the values that define the shape of this FLV
        float m_dPeakPoint;
        float m_dLeftOffset;
        float m_dRightOffset
};

#endif // FUZZYSET_TRIANGLE_H
