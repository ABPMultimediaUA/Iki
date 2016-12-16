#ifndef FUZZYSET_TRIANGLE_H
#define FUZZYSET_TRIANGLE_H

#include <FuzzySet.h>


class FuzzySet_Triangle : public FuzzySet
{
    private:
        double m_dPeakPoint;
        double m_dLeftOffset;
        double m_dRightOffset;

    public:
        FuzzySet_Triangle(double mid,
                          double lft,
                          double rgt):FuzzySet(mid),
                                      m_dPeakPoint(mid),
                                      m_dLeftOffset(lft),
                                      m_dRightOffset(rgt)
    {}

    double CalculateDOM(double val)const;
};

#endif // FUZZYSET_TRIANGLE_H
