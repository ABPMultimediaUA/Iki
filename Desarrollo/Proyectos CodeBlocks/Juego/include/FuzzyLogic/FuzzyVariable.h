#ifndef FUZZYVARIABLE_H
#define FUZZYVARIABLE_H

#include <map>
#include <FuzzySet.h>

class FuzzyVariable
{
    private:
        typedef std::map<std::string, FuzzySet*> MemberSets;
    private:
        //disallow copies
        FuzzyVariable(const FuzzyVariable&);
        FuzzyVariable& operator=(const FuzzyVariable&);
    private:
        MemberSets fvMembers;

        float m_dMinRange;
        float m_dMaxRange;

        void AdjustRangeToFit(float min, float max);

        //a client retrieves a reference to a fuzzy variable when an instance is
        //created via FuzzyModule::CreateFLV(). To prevent the client from deleting
        //the instance the FuzzyVariable destructor is made private and the
        //FuzzyModule class made a friend.
        ~FuzzyVariable();

        friend class FuzzyModule;

    public:

        FuzzyVariable():m_dMinRange(0.0),m_dMaxRange(0.0){}

        //the following methods create instances of the sets named in the method
        //name and adds them to the member set map. Each time a set of any type is
        //added the m_dMinRange and m_dMaxRange are adjusted accordingly. All of the
        //methods return a proxy class representing the newly created instance. This
        //proxy set can be used as an operand when creating the rule base.

        FzSet AddLeftShoulderSet(std::string name,
                                 float minBound,
                                 float peak,
                                 float maxBound);
        FzSet AddRightShoulderSet(std::string name,
                                  float minBound,
                                  float peak,
                                  float maxBound);
        FzSet AddTriangularSet(std::string name,
                               float minBound,
                               float peak,
                               float maxBound);

        void Fuzzify(float val);
        float DeFuzzifyMaxAv()const;

};

#endif // FUZZYVARIABLE_H
