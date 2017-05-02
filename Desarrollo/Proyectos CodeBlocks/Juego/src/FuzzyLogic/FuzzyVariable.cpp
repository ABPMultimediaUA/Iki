#include "FuzzyVariable.h"

#include "FuzzySet_Left.h"
#include "FuzzySet_Right.h"
#include "FuzzySet_Triangle.h"
#include "FzSet.h"

FuzzyVariable::~FuzzyVariable()
{
    MemberSets::iterator it;
    for (it = fvMembers.begin(); it != fvMembers.end(); ++it)
    {
        delete it->second;
    }
}

void FuzzyVariable::Fuzzify(float val)
{
    MemberSets::const_iterator curSet;
    for (curSet = fvMembers.begin(); curSet != fvMembers.end(); ++curSet)
    {
        curSet->second->SetDOM(curSet->second->CalculateDOM(val));
    }
}

// OUTPUT = sum (maxima * DOM) / sum (DOMs)
float FuzzyVariable::DeFuzzifyMaxAv()const
{
    float bottom = 0.0;
    float top    = 0.0;

    MemberSets::const_iterator curSet;
    for (curSet = fvMembers.begin(); curSet != fvMembers.end(); ++curSet)
    {
        bottom += curSet->second->GetDOM();
        top += curSet->second->GetRepv() * curSet->second->GetDOM();
    }

    if (0 == bottom) return 0.0;

    return top / bottom;
}

FzSet FuzzyVariable::AddTriangularSet(std::string name, float minBound, float peak, float maxBound)
{
    FuzzySet* fzset = new FuzzySet_Triangle(peak, peak-minBound, maxBound-peak);
    fvMembers[name] = fzset;

    this->AdjustRangeToFit(minBound, maxBound);
    return FzSet(*fvMembers[name]);
}

FzSet FuzzyVariable::AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
    FuzzySet* fzset = new FuzzySet_Left(peak, peak-minBound, maxBound-peak);
    fvMembers[name] = fzset;

    AdjustRangeToFit(minBound, maxBound);
    return FzSet(*fvMembers[name]);
}

FzSet FuzzyVariable::AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
    FuzzySet* fzset = new FuzzySet_Right(peak, peak-minBound, maxBound-peak);
    fvMembers[name] = fzset;

    AdjustRangeToFit(minBound, maxBound);
    return FzSet(*fvMembers[name]);
}

void FuzzyVariable::AdjustRangeToFit(float min, float max)
{
    if (min < fMinRange) fMinRange = min;
    if (max > fMaxRange) fMaxRange = max;
}
