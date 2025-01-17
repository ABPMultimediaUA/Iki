#include "FuzzyQuery.h"
#include "FuzzyModule.h"

FuzzyQuery::FuzzyQuery()
{
    //ctor
}

FuzzyQuery::~FuzzyQuery()
{
    //dtor
}


float FuzzyQuery::Query(float x, float y, int type)
{
    FuzzyModule fm;

    ///Create FLV
    FuzzyVariable& GdSospecha = fm.CreateFLV("GradoDeSospecha");
    FuzzyVariable& DistanciaJ = fm.CreateFLV("DistanciaJugador");
    FuzzyVariable& Bateria    = fm.CreateFLV("Bateria");
    FuzzyVariable& VidaJ      = fm.CreateFLV("VidaJugador");
    FuzzyVariable& NivelInvs  = fm.CreateFLV("NivelDeInvestigacion");
    FuzzyVariable& Velocidad  = fm.CreateFLV("Velocidad");
    FuzzyVariable& Potencia   = fm.CreateFLV("Potencia");


    ///AddSetsToFLV
    FzSet GdSospecha_Low   = GdSospecha.AddLeftShoulderSet("Sospecha_Low",0,25,45);
    FzSet GdSospecha_Med   = GdSospecha.AddTriangularSet("Sospecha_Med",25,45,70);
    FzSet GdSospecha_High  = GdSospecha.AddRightShoulderSet("Sospecha_Med",45,70,100);

    FzSet DistanciaJ_Low  = DistanciaJ.AddLeftShoulderSet("Distancia_Low",0,5,10);
    FzSet DistanciaJ_Med  = DistanciaJ.AddTriangularSet("Distancia_Med",5,15,20);
    FzSet DistanciaJ_High = DistanciaJ.AddRightShoulderSet("Distancia_High",20,25,30);

    FzSet Bateria_Low  = Bateria.AddLeftShoulderSet("Bateria_Low",0,25,50);
    FzSet Bateria_Med  = Bateria.AddTriangularSet("Bateria_Med",25,50,75);
    FzSet Bateria_High = Bateria.AddRightShoulderSet("Bateria_High",50,75,100);

    FzSet VidaJ_Low  = VidaJ.AddLeftShoulderSet("VidaJ_Low",0,20,35);
    FzSet VidaJ_Med  = VidaJ.AddTriangularSet("VidaJ_Med",20,35,70);
    FzSet VidaJ_High = VidaJ.AddRightShoulderSet("VidaJ_High",35,70,100);

    FzSet NivelInvs_Low  = NivelInvs.AddLeftShoulderSet("Invs_Low",0,0,1);
    FzSet NivelInvs_Med  = NivelInvs.AddTriangularSet("Invs_Med",0,1,2);
    FzSet NivelInvs_High = NivelInvs.AddRightShoulderSet("Invs_High",1,2,2);

    FzSet Velocidad_Low  = Velocidad.AddLeftShoulderSet("Velocidad_Low",0,35,45);
    FzSet Velocidad_Med  = Velocidad.AddTriangularSet("Velocidad_Med",35,45,70);
    FzSet Velocidad_High = Velocidad.AddRightShoulderSet("Velocidad_High",45,70,100);

    FzSet Potencia_Low  = Potencia.AddLeftShoulderSet("Potencia_Low",0,3,4);
    FzSet Potencia_Med  = Potencia.AddTriangularSet("Potencia_Med",3,4,7);
    FzSet Potencia_High = Potencia.AddRightShoulderSet("Potencia_High",4,7,10);


    ///AddRules Using Sets
    fm.AddRule(GdSospecha_Low  , NivelInvs_Low);
    fm.AddRule(GdSospecha_Med  , NivelInvs_Med);
    fm.AddRule(GdSospecha_High , NivelInvs_High);
    fm.AddRule(DistanciaJ_Low  , NivelInvs_High);
    fm.AddRule(DistanciaJ_Med  , NivelInvs_Med);
    fm.AddRule(DistanciaJ_High , NivelInvs_Low);

    fm.AddRule(Bateria_Low     , Velocidad_Low);
    fm.AddRule(Bateria_Med     , Velocidad_Med);
    fm.AddRule(Bateria_High    , Velocidad_High);
    fm.AddRule(DistanciaJ_Low  , Velocidad_Low);
    fm.AddRule(DistanciaJ_Med  , Velocidad_Med);
    fm.AddRule(DistanciaJ_High , Velocidad_High);

    fm.AddRule(Bateria_Low , Potencia_Low);
    fm.AddRule(Bateria_Med , Potencia_Med);
    fm.AddRule(Bateria_High, Potencia_High);
    fm.AddRule(VidaJ_Low   , Potencia_Low);
    fm.AddRule(VidaJ_Med   , Potencia_Med);
    fm.AddRule(VidaJ_High  , Potencia_High);

    ///Test
    if (type == 1){
        fm.Fuzzify("DistanciaJugador", x);
        fm.Fuzzify("Bateria", y);

        float fl = fm.DeFuzzify("Velocidad");

        return fl;
    }else{
        fm.Fuzzify("VidaJugador", x);
        fm.Fuzzify("Bateria", y);

        float fl = fm.DeFuzzify("Potencia");

        return fl;
    }
}
