#ifndef FUZZYSET_LEFT_H
#define FUZZYSET_LEFT_H

#include <FuzzySet.h>


class FuzzySet_Left : public FuzzySet
{
    public:
        FuzzySet_Left(float peak, float LeftOffset, float RightOffset):
            FuzzySet( ((peak - RightOffset) + peak) / 2),
            m_dPeakPoint(peak),
            m_dLeftOffset(LeftOffset),
            m_dRightOffset(RightOffset)
        {}

        //this method calculates the degree of membership for a particular value
        float CalculateDOM(float val)const;

    private:
        //the values that define the shape of this FLV
        float m_dPeakPoint;
        float m_dLeftOffset;
        float m_dRightOffset;
};

#endif // FUZZYSET_LEFT_H
