#ifndef FUZZYSET_TRIANGLE_H
#define FUZZYSET_TRIANGLE_H

#include <FuzzySet.h>


class FuzzySet_Triangle : public FuzzySet
{
    public:
        FuzzySet_Triangle(float mid, float lft, float rgt):
            FuzzySet(mid),
            m_dPeakPoint(mid),
            m_dLeftOffset(lft),
            m_dRightOffset(rgt)
        {}

        float CalculateDOM(float val)const;

    private:
        float m_dPeakPoint;
        float m_dLeftOffset;
        float m_dRightOffset;
};

#endif // FUZZYSET_TRIANGLE_H
