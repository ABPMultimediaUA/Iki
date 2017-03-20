#ifndef FUZZYSET_RIGHT_H
#define FUZZYSET_RIGHT_H

#include <FuzzySet.h>


class FuzzySet_Right : public FuzzySet
{
    public:
        FuzzySet_Right();
        virtual ~FuzzySet_Right();

        FuzzySet_Right(float peak, float LeftOffset, float RightOffset):
            FuzzySet( ((peak + RightOffset) + peak) / 2),
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

#endif // FUZZYSET_RIGHT_H
