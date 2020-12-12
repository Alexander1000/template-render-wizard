#include <trw.h>
#include <iostream>

namespace TemplateRenderWizard
{
    void Render::render_if_expression(IOBuffer::IOBuffer *buffer, bool result)
    {
        auto token = this->getNextToken();

        bool skipBlock = !result;
        bool stopRender = false;

        INIT_CHAR_STRING(keyword, 32)

        while (token != nullptr) {
            switch (token->getType()) {
                case TemplateRenderWizard::Token::Type::PlainTextType: {
                    if (skipBlock) {
                        break;
                    }
                    this->to_buffer_plain_text(buffer, token);
                    break;
                }
                case TemplateRenderWizard::Token::Type::PlainValueType: {
                    if (skipBlock) {
                        break;
                    }
                    this->to_buffer_value(buffer, token);
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::CloseTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenControlTagType: {
                    token = this->getNextToken();
                    if (token->getType() != TemplateRenderWizard::Token::Type::KeywordType) {
                        std::cout << "Line: " << token->getLine() << "; Column: " << token->getColumn() << std::endl;
                        throw new UnexpectedToken;
                    }
                    memset(keyword, 0, sizeof(char) * 32);
                    RESET_TOKEN_READER(token);
                    token->getReader()->read(keyword, 32);

                    if (strcmp(keyword, "if") == 0) {
                        this->pushBackToken(token);
                        this->renderControlExpression(buffer);
                    }

                    if (strcmp(keyword, "else") == 0) {
                        skipBlock = result;
                        this->getNextToken(); // close tag
                    }

                    if (strcmp(keyword, "endif") == 0) {
                        this->getNextToken(); // close tag
                        stopRender = true;
                    }
                    break;
                }

                default: {
                    std::cout << "Line: " << token->getLine() << "; Column: " << token->getColumn() << std::endl;
                    throw new UnexpectedToken;
                }
            }

            if (stopRender) {
                break;
            }

            token = this->getNextToken();
        }
    }
}
