#ifndef TMALLA_H
#define TMALLA_H

#include "TEntidad.h"
#include "TRecursoMalla.h"
#include "TTextura.h"
#include "TShader.h"

//#include <glm/gtx/string_cast.hpp>
//#include <iostream>
#include <string>



class TMalla : public TEntidad
{
    public:
        TMalla(){}
        virtual ~TMalla();

        virtual void beginDraw();
		virtual void endDraw();

		void loadMesh(const std::string& meshPath);

		const bool& getView() const;

		void setView(const bool& view);

        void printMatrices();

    protected:
    private:
        bool m_isFixed;
		bool m_view;

		TRecursoMalla* m_RecursoMalla;

		glm::mat4 m_MVP;
		glm::mat4 m_MV;
		glm::mat4 m_NormalMatrix;
};

#endif // TMALLA_H
