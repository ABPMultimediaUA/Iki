#ifndef FUZZY_H
#define FUZZY_H


class Fuzzy
{
    public:
        Fuzzy();
        virtual ~Fuzzy();

    /// STRUCTS
    private:
        // FUZZY SET
        typedef struct{
            double dom;   //Degree of Membership
            double rep;   //Representative Value

            int    type;  //0=Left Shoulder, 1=Triangle, 2=Right Shoulder
            double left;
            double peak;
            double right;
        }FuzzySet;

        // FUZZY VARIABLE
        // Formada por Fuzzy Sets
        typedef struct{
            FuzzySet leftSet;
            FuzzySet triangularSet;
            FuzzySet rightSet;

            double minRange;
            double maxRange;
        }FuzzyVar;

        // FUZZY RULE
        // Contiene antecedentes y consecuentes (Fuzzy Var)
        typedef struct{
            FuzzyVar antecedent1;
            FuzzyVar antecedent2;
            FuzzyVar consequent;
        }FuzzyRule;

        // FUZZY MODULE
        // Contiene las reglas, y las variables
        typedef struct{
            FuzzyRule rules[9];  //FuzzyRule rules[numRules];
            FuzzyVar  vars[3];   //FuzzyVar  vars[numVars];
        }FuzzyModule;            //(int numRules, int numVars);

    /// DECLARATE ALL THE ITEMS
    public:
        FuzzyModule fm;

};

#endif // FUZZY_H
