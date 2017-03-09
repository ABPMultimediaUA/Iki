#ifndef TRECURSO_H
#define TRECURSO_H


class TRecurso
{
    public:
        TRecurso();
        virtual ~TRecurso();
        virtual char *getNombre() = 0;
        virtual void setNombre(char* n) = 0;

    protected:

    private:
        char* nombre;
};

#endif // TRECURSO_H
