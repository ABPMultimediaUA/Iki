#include "FuzzyVariable.h"

FuzzyVariable::~FuzzyVariable()
{
    //dtor
    MemberSets::iterator it;
    for (it = m_MemberSets.begin(); it != m_MemberSets.end(); ++it)
    {
        delete it->second;
    }
}

void FuzzyVariable::Fuzzify(float val)
{
    MemberSets::const_iterator curSet;
    for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
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
    for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
    {
        bottom += curSet->second->GetDOM();
        top += curSet->second->GetRepv() * curSet->second->GetDOM();
    }

    if (0 == bottom) return 0.0;

    return top / bottom;
}

FzSet FuzzyVariable::AddTriangularSet(std::string name, float minBound, float peak, float maxBound)
{
  m_MemberSets[name] = new FuzzySet_Triangle(peak, peak-minBound, maxBound-peak);

  AdjustRangeToFit(minBound, maxBound);
  return FzSet(*m_MemberSets[name]);
}

FzSet FuzzyVariable::AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
  m_MemberSets[name] = new FuzzySet_LeftShoulder(peak, peak-minBound, maxBound-peak);

  AdjustRangeToFit(minBound, maxBound);
  return FzSet(*m_MemberSets[name]);
}

FzSet FuzzyVariable::AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound)
{
  m_MemberSets[name] = new FuzzySet_RightShoulder(peak, peak-minBound, maxBound-peak);

  AdjustRangeToFit(minBound, maxBound);
  return FzSet(*m_MemberSets[name]);
}
