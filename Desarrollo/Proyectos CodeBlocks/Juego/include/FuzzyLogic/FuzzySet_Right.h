#ifndef FUZZYSET_RIGHT_H
#define FUZZYSET_RIGHT_H

#include "FuzzySet.h"


class FuzzySet_Right : public FuzzySet
{
    public:
        FuzzySet_Right(float peak, float LeftOffset, float RightOffset):
            FuzzySet( ((peak + RightOffset) + peak) / 2),
            m_dPeakPoint(peak),
            m_dLeftOffset(LeftOffset),
            m_dRightOffset(RightOffset)
        {}

        float CalculateDOM(float val)const;

    private:
        float m_dPeakPoint;
        float m_dLeftOffset;
        float m_dRightOffset;
};

#endif // FUZZYSET_RIGHT_H
