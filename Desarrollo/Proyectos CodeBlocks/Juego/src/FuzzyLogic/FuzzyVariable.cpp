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



//--------------------------- Fuzzify -----------------------------------------
//
//  takes a crisp value and calculates its degree of membership for each set
//  in the variable.
//-----------------------------------------------------------------------------
void FuzzyVariable::Fuzzify(double val)
{
  //for each set in the flv calculate the DOM for the given value
  MemberSets::const_iterator curSet;
  for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
  {
    curSet->second->SetDOM(curSet->second->CalculateDOM(val));
  }
}

//--------------------------- DeFuzzifyMaxAv ----------------------------------
//
// defuzzifies the value by averaging the maxima of the sets that have fired
//
// OUTPUT = sum (maxima * DOM) / sum (DOMs)
//-----------------------------------------------------------------------------
double FuzzyVariable::DeFuzzifyMaxAv()const
{
  double bottom = 0.0;
  double top    = 0.0;

  MemberSets::const_iterator curSet;
  for (curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
  {
    bottom += curSet->second->GetDOM();

    top += curSet->second->GetRepv() * curSet->second->GetDOM();
  }

  //make sure bottom is not equal to zero
  if (0 == bottom) return 0.0;

  return top / bottom;
}


/*
//------------------------- AddTriangularSet ----------------------------------
//
//  adds a triangular shaped fuzzy set to the variable
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddTriangularSet(std::string name,
                                     double       minBound,
                                     double       peak,
                                     double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_Triangle(peak,
                                             peak-minBound,
                                             maxBound-peak);
  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}

//--------------------------- AddLeftShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddLeftShoulderSet(std::string name,
                                        double       minBound,
                                        double       peak,
                                        double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_LeftShoulder(peak, peak-minBound, maxBound-peak);

  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}


//--------------------------- AddRightShoulder ---------------------------------
//
//  adds a left shoulder type set
//-----------------------------------------------------------------------------
FzSet FuzzyVariable::AddRightShoulderSet(std::string name,
                                         double       minBound,
                                         double       peak,
                                         double       maxBound)
{
  m_MemberSets[name] = new FuzzySet_RightShoulder(peak, peak-minBound, maxBound-peak);

  //adjust range if necessary
  AdjustRangeToFit(minBound, maxBound);

  return FzSet(*m_MemberSets[name]);
}
*/
