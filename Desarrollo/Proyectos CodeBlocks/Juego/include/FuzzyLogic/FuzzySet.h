#ifndef FUZZYSET_H
#define FUZZYSET_H


class FuzzySet
{
    public:
        //this will hold the degree of membership in this set of a given value
        float dom;
        //this is the maximum of the set's membership function. For instance, if
        //the set is triangular then this will be the peak point of the triangle.
        //If the set has a plateau then this value will be the midpoint of the
        //plateau. This value is set in the constructor to avoid run-time
        //calculation of midpoint values.
        float repv;

    public:
        FuzzySet();
        virtual ~FuzzySet();

        FuzzySet(float RepVal):dom(0.0), repv(RepVal){}
        //return the degree of membership in this set of the given value. NOTE:
        //this does not set m_dDOM to the DOM of the value passed as the parameter.
        //This is because the centroid defuzzification method also uses this method
        //to determine the DOMs of the values it uses as its sample points.
        virtual float CalculateDOM(float val)const = 0;
        //if this fuzzy set is part of a consequent FLV and it is fired by a rule,
        //then this method sets the DOM (in this context, the DOM represents a
        //confidence level) to the maximum of the parameter value or the set's
        //existing m_dDOM value
        void ORwithDOM(float val){if (val > dom) dom = val;}
        //accessor methods
        float GetRepv()const{return repv;}
        float GetDOM()const {return dom; }
        void SetDOM(float val){dom = val;}
        void ClearDOM(){dom = 0.0;}
};

#endif // FUZZYSET_H
