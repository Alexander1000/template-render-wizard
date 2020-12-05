#ifndef H_TRW_POSITION_INCLUDED
#define H_TRW_POSITION_INCLUDED

namespace TemplateRenderWizard
{
    class Position
    {
    public:
        Position(int line, int column);
        int getLine();
        int getColumn();
        void setLine(int line);
        void setColumn(int column);
    private:
        int line;
        int column;
    };
}

#endif
