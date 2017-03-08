#include "TMotorTAG.h"

TMotorTAG::TMotorTAG()
{
    //ctor
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

TCamara *TMotorTAG::crearCamara()
{
    TCamara *camara= new TCamara();
    return camara;
}

TMalla *TMotorTAG::crearMalla(char* fichero)
{

}

TNodo *TMotorTAG::getCamaraActiva()
{
    for(int i = 0; i < c_activa.size(); i++)
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
    return 1;
}

int TMotorTAG::registrarCamara(TNodo* nod)
{
    camaras.push_back(nod);
    c_activa.push_back(false);
    return 1;
}

void TMotorTAG::draw()
{

    ///drawLuces
    for(std::size_t i= 0; i < luces.size(); i++)
    {
        if(l_activa[i])
        {
            //Guardamos en un vector aux desde la luz hasta la raiz
            TNodo* nodo;
            vector<TNodo*> aux;
            aux.push_back(luces[i]);
            nodo = aux.back()->getPadre();
            while(nodo)
            {
                aux.push_back(nodo);
                nodo = aux.back()->getPadre();
            }
            //Recorre desde la raiz hasta la luz
            vector<TNodo*>::iterator it = aux.end();
            mat4 mat_aux = mat4(1.f);
            while(it != aux.begin())
            {
                //mat_aux= *it->getEntidad().getMatriz() ;
                //* mat_aux
                --it;
            }
            /*
            //	printf("LUZ:         %.1f %.1f %.1f \n", pos.x, pos.y, pos.z);
            glUniform3f(glGetUniformLocation(sh->Program, "light.position"), pos.x, pos.y, pos.z);

            //propiedades de la luz
            glUniform3f(glGetUniformLocation(sh->Program, "light.ambient"),   0.15f, 0.15f, 0.15f);
            glUniform3f(glGetUniformLocation(sh->Program, "light.diffuse"),   2.5f, 2.5f, 2.5f);
            glUniform3f(glGetUniformLocation(sh->Program, "light.specular"),  1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(sh->Program, "light.constant"),  1.0f);
            glUniform1f(glGetUniformLocation(sh->Program, "light.linear"),    0.09);
            glUniform1f(glGetUniformLocation(sh->Program, "light.quadratic"), 0.032);
            //glUniform3f
            //Aqui hemos llegado a la luz
            //Dibujar luces[i] con mat_aux aplicada
            */
        }
    }
    ///Viewport



    ///drawCamaras
    //Guardamos en un vector aux desde la luz hasta la raiz
    TNodo* nodo = getCamaraActiva();
    vector<TNodo*> aux;
    aux.push_back(nodo);
    nodo = aux.back()->getPadre();
    while(nodo)
    {
        aux.push_back(nodo);
        nodo = aux.back()->getPadre();
    }
    //Recorre de manera inversa raiz->camara
    vector<TNodo*>::iterator it = aux.end();
    mat4 mat_aux = mat4(1.f);
    while(it != aux.begin())
    {
        //mat_aux= *it->getEntidad().getMatriz() ;
        //* mat_aux
        --it;
    }
    //invertir mat_aux
    //cargar la matriz con la camara

    ///drawEscena
    escena->draw();
}
