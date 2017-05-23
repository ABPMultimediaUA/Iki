#include "TMotorTAG.h"

#include "TTransform.h"
#include "TMalla.h"
#include "TLuz.h"
#include "TCamara.h"
#include "TAnimacion.h"
#include <SFML/Graphics.hpp>

TMotorTAG::TMotorTAG() //: shader("")
{
    //ctor
    shader = new TShader("./resources/res/basicShader");
    escena = new TNodo();

}

TMotorTAG::~TMotorTAG()
{
    //dtor
}

TNodo *TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent)
{
    TNodo *nodo = new TNodo();
    nodo->setEntidad(ent);
    padre->addHijo(nodo);

    return nodo;
}

TTransform *TMotorTAG::crearTransform()
{
    TTransform *tranformacion = new TTransform();
    return tranformacion;
}

TLuz *TMotorTAG::crearLuz()
{
    TLuz *luz = new TLuz();
    return luz;
}

TNodo *TMotorTAG::crearCamara(const vec3& pos, float grad, int anch,int alt, float cer, float lej)
{

    TCamara *cCamara= new TCamara(pos, grad, anch, alt, cer, lej);

    TTransform *tTraslacion = new TTransform();
    TTransform *tRotacion = new TTransform();

    tTraslacion->trasladar (0.0f, 0.0f, 10.0f);
    tRotacion->rotar(45.0f, 0.0f, 30.0f, 0.0f);

    TNodo *nTraslacion = new TNodo();
    TNodo *nRotacion = new TNodo();
    TNodo *nCamara = new TNodo();

    nTraslacion->setEntidad(tTraslacion);
    nRotacion->setEntidad(tRotacion);
    nCamara->setEntidad(cCamara);

    escena->addHijo(nTraslacion);
    nTraslacion->addHijo(nRotacion);
    nRotacion->addHijo(nCamara);

    return nCamara;
}

TNodo *TMotorTAG::crearMalla(const std::string& filename)
{

    TMalla* mMalla= new TMalla();
    mMalla->loadMesh(filename);

    TTransform *tEscalado = new TTransform();
    TTransform *tTraslacion = new TTransform();
    TTransform *tRotacion = new TTransform();

    TNodo *nEscalado = new TNodo();
    TNodo *nTraslacion = new TNodo();
    TNodo *nRotacion = new TNodo();
    TNodo *nMalla = new TNodo();

    nEscalado->setEntidad(tEscalado);
    nTraslacion->setEntidad(tTraslacion);
    nRotacion->setEntidad(tRotacion);
    nMalla->setEntidad(mMalla);

    escena->addHijo(nEscalado);
    nEscalado->addHijo(nTraslacion);
    nTraslacion->addHijo(nRotacion);
    nRotacion->addHijo(nMalla);
    std::cout<<"Malla cargada"<<std::endl;

    return nMalla;
}

TNodo* TMotorTAG::cargarAnimacion(const std::string& filename, const unsigned int& longitud)
{
        TNodo* nEscalado = new TNodo();
        TNodo* nRotacion = new TNodo();
        TNodo* nTraslacion = new TNodo();
        TNodo* nAnimacion = new TNodo();

        TTransform* tEscalado = new TTransform();
        TTransform* tRotacion = new TTransform();
        TTransform* tTraslacion = new TTransform();
        TAnimacion* aAnimacion = new TAnimacion(longitud);

        escena->addHijo(nEscalado);
        nEscalado->addHijo(nTraslacion);
        nTraslacion->addHijo(nRotacion);
        nRotacion->addHijo(nAnimacion);

        nEscalado->setEntidad(tEscalado);
        nRotacion->setEntidad(tRotacion);
        nTraslacion->setEntidad(tTraslacion);
        nAnimacion->setEntidad(aAnimacion);

        aAnimacion->cargarAnimacion(filename);

        return nAnimacion;
}

TShader TMotorTAG::cargarShader(const std::string& filename)
{
    shader = new TShader(filename);
}
TNodo *TMotorTAG::getCamaraActiva()
{
    for(std::size_t i=0; i < c_activa.size(); i++)
    {
        if(c_activa[i])
            return camaras[i];
    }
    return nullptr;
}

int TMotorTAG::registrarLuz(TNodo* nod)
{
    luces.push_back(nod);
    l_activa.push_back(true);

    size_t vSize = l_activa.size();
    return static_cast<int>(vSize)-1;
}

int TMotorTAG::registrarCamara(TNodo* nod)
{
    camaras.push_back(nod);
    c_activa.push_back(false);

    size_t vSize = c_activa.size();
    return static_cast<int>(vSize)-1;
}

void TMotorTAG::drawLuces()
{
    for(std::size_t i=0; i < luces.size(); i++)
    {
        if(l_activa[i])
        {

            vector<TNodo*> aux;
            aux.push_back(luces[i]);
            TNodo* nodo = luces[i]->getPadre();
            while(nodo)
            {
                aux.push_back(nodo);
                nodo = aux.back()->getPadre();
            }
            glm::mat4 mat_aux = mat4(1.f);
            for(std::size_t i=aux.size()-1; i > 0; i--)
            {
               // std::cout << "    Aplicamos matriz transform en una auxiliar" << std::endl;
                //mat_aux= *it->getEntidad().getMatriz() ;
                //* mat_aux
                //--it;
            }

        }
    }
}

void TMotorTAG::drawCamaras()
{
    for(std::size_t i=0; i < camaras.size(); i++)
    {
        if(c_activa[i])
        {
            TNodo* nodo;
            vector<TNodo*> aux;
            aux.push_back(camaras[i]);
            nodo = camaras[i]->getPadre();
            while(nodo)
            {
                aux.push_back(nodo);
                nodo = aux.back()->getPadre();
            }
            glm::mat4 mat_aux = mat4(1.f);
            for(std::size_t i=aux.size()-1; i > 0; i--)
            {
                TTransform* t = dynamic_cast<TTransform*>(aux[i]->getEntidad());
                if (t)
                {
                    mat_aux = t->getMatriz() * mat_aux;
                }
            }
            TShader::viewMatrix = inverse(mat_aux);
            shader->setUniform(TShader::Uniforms::MODEL_VIEW_MTX, TShader::viewMatrix);
            //cargar la matriz con la camara
        }
    }
}

void TMotorTAG::draw()
{
    drawLuces();

    drawCamaras();

    escena->draw();
}

