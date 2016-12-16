#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
    //ctor

    /// Fuzzy Logic Variables
    //FLV DISTANCIA
    const FuzzySet distanciaCorta = { 0, 0, 0,  0, 20, 50 };
    const FuzzySet distanciaMedia = { 0, 0, 1, 20, 50, 80 };
    const FuzzySet distanciaLarga = { 0, 0, 2, 50, 80, 120};
    FuzzyVar distanciaVar = { distanciaCorta, distanciaMedia, distanciaLarga, distanciaCorta.left, distanciaLarga.right };

    //FLV SOSPECHA
    const FuzzySet sospechaBaja  = { 0, 0, 0,  0, 20, 40 };
    const FuzzySet sospechaMedia = { 0, 0, 1, 20, 40, 70 };
    const FuzzySet sospechaAlta  = { 0, 0, 2, 40, 70, 100};
    FuzzyVar sospechaVar = { sospechaBaja, sospechaMedia, sospechaAlta, sospechaBaja.left, sospechaAlta.right };

    //FLV INTERES
    const FuzzySet interesBajo  = { 0, 0, 0,  0, 25, 50 };
    const FuzzySet interesMedio = { 0, 0, 1, 25, 50, 90 };
    const FuzzySet interesAlto  = { 0, 0, 2, 50, 90, 100};
    FuzzyVar interesVar = { interesBajo, interesMedio, interesAlto, interesBajo.left, interesAlto.right };

    /// Fuzzy Rules
    const FuzzyRule r1 = { distanciaCorta , sospechaBaja , interesMedio };
    const FuzzyRule r2 = { distanciaCorta , sospechaMedia, interesAlto  };
    const FuzzyRule r3 = { distanciaCorta , sospechaAlta , interesAlto  };

    const FuzzyRule r4 = { distanciaMedia , sospechaBaja , interesBajo  };
    const FuzzyRule r5 = { distanciaMedia , sospechaMedia, interesMedio };
    const FuzzyRule r6 = { distanciaMedia , sospechaAlta , interesAlto  };

    const FuzzyRule r7 = { distanciaLarga , sospechaBaja , interesBajo  };
    const FuzzyRule r8 = { distanciaLarga , sospechaMedia, interesBajo  };
    const FuzzyRule r9 = { distanciaLarga , sospechaAlta , interesMedio };

    /// Fuzzy Modules
    fm.vars[0]=distanciaVar; fm.vars[1]=sospechaVar; fm.vars[2]=interesVar;

}

Fuzzy::~Fuzzy()
{
    //dtor
}



