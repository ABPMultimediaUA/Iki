#ifndef FUZZYTERM_H
#define FUZZYTERM_H


class FuzzyTerm
{
    public:

      virtual ~FuzzyTerm(){}
      virtual FuzzyTerm* Clone()const = 0;

      virtual float      GetDOM()const=0;
      virtual void       ClearDOM()=0;
      virtual void       ORwithDOM(float val)=0;
};

#endif // FUZZYTERM_H
