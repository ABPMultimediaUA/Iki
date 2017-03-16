#include "TMotorTAG.h"
#include "TShader.h"


TMotorTAG::TMotorTAG()
{
    //ctor
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

TCamara *TMotorTAG::crearCamara(const vec3& pos, float grad, int anch,int alt, float cer, float lej)
{
    TCamara *camara= new TCamara(pos, grad, anch, alt, cer, lej);
    return camara;
}

TMalla *TMotorTAG::crearMalla(const std::string& filename)
{
    TMalla* malla= new TMalla();
    malla->LoadMesh(filename);
    return malla;
}

TShader TMotorTAG::cargarShader(const std::string& filename)
{
    TShader shader(filename);
    return shader;
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
    std::cout << "Recorriendo el registro de luces" << std::endl;

    for(std::size_t i=0; i < luces.size(); i++)
    {
        std::cout << " > Comprobando luz numero " << i << std::endl;
        if(l_activa[i])
        {
            std::cout << "   Luz numero " << i << " is activa" << std::endl;
            std::cout << "   Recorremos desde la luz hasta la raiz" << std::endl;
            //Guardamos en un vector aux desde la luz hasta la raiz

            vector<TNodo*> aux;
            aux.push_back(luces[i]);
            std::cout<< "    > Insertamos la luz en el vector aux" << std::endl;
            TNodo* nodo = luces[i]->getPadre();
            while(nodo)
            {
                std::cout << "     > Insertamos padre" << std::endl;
                aux.push_back(nodo);
                nodo = aux.back()->getPadre();
            }
            std::cout << "    Recorremos al reves" << std::endl;
            //Recorre desde la raiz hasta la luz
            //vector<TNodo*>::iterator it = aux.end();
            mat4 mat_aux = mat4(1.f);
            //while(it != aux.begin())
            //{
            for(std::size_t i=aux.size()-1; i > 0; i--)
            {
                std::cout << "    Aplicamos matriz transform en una auxiliar" << std::endl;
                //mat_aux= *it->getEntidad().getMatriz() ;
                //* mat_aux
                //--it;
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
        else
            std::cout << "   Luz numero " << i << " is not activa" << std::endl;

        std:cout << std::endl;
    }
}

void TMotorTAG::drawCamaras()
{
    std::cout << "Recorriendo el registro de camaras" << std::endl;
    for(std::size_t i=0; i < camaras.size(); i++)
    {
        std::cout << " > Comprobando camara numero " << i << std::endl;
        if(c_activa[i])
        {
            std::cout << "   Camara numero " << i << " is activa" << std::endl;
            std::cout << "   Recorremos desde la camara hasta la raiz" << std::endl;
            //Guardamos en un vector aux desde la camara hasta la raiz
            TNodo* nodo;
            vector<TNodo*> aux;
            aux.push_back(camaras[i]);
            std::cout << "    > Insertamos la camara en el vector aux" << std::endl;
            nodo = camaras[i]->getPadre();
            while(nodo)
            {
                std::cout << "     > Insertamos padre" << std::endl;
                aux.push_back(nodo);
                nodo = aux.back()->getPadre();
            }
            std::cout << "    Recorremos al reves" << std::endl;
            //Recorre de manera inversa raiz->camara
            //vector<TNodo*>::iterator it = aux.end();
            mat4 mat_aux = mat4(1.f);
            //while(it != aux.begin())
            //{
            for(std::size_t i=aux.size()-1; i > 0; i--)
            {
                std::cout << "    Aplicamos matriz transform en una auxiliar" << std::endl;
                TTransform* t = dynamic_cast<TTransform*>(aux[i]->getEntidad());
                if (t)
                {
                    mat_aux = t->getMatriz() * mat_aux;

                        for(int i =0; i<4; i++){
                            for(int j =0; j<4; j++){
                                if(j != 3)
                                    cout<<mat_aux[i][j]<<" ";
                                else
                                    cout<<mat_aux[i][j]<<endl;
                            }
                        }
                        cout<<endl;
                                    std::cout << "........-------------------------------------------------" << std::endl;
                }
                //mat_aux= *it->getEntidad().getMatriz() ;
                //* mat_aux
                //--it;
            }
            TShader::viewMatrix = inverse(mat_aux);

            //invertir mat_aux
            //cargar la matriz con la camara
        }
        else
            std::cout << "   Camara numero " << i << " is not activa" << std::endl;

        std::cout << std::endl;
    }
}

void TMotorTAG::draw()
{
    std::cout << "Iniciando dibujado de la escena" << std::endl;
    std::cout << std::endl;
    drawLuces();
    //drawViewport();
    std::cout << std::endl;
    drawCamaras();

    std::cout << std::endl;
    std::cout << "Dibujando mallas" << std::endl;
    escena->draw();
}
