#include <trw.h>
#include <iostream>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    Value* Render::get_value_from_syntax_element(SyntaxElement* element)
    {
        switch (element->getType()) {
            case SyntaxTokenType: {
                return this->getValueFromToken((SyntaxTree::Token::Token*) element->getData(), nullptr);
            }
            case SyntaxValueType: {
                return (Value*) element->getData();
            }
            case SyntaxExpressionType: {
                return this->calc_expr((Expression*) element->getData());
            }
        }

        std::cout << "Unexpected syntax element" << std::endl;
        throw new UnexpectedToken;
    }
}
