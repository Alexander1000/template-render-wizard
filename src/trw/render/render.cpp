#include <io-buffer.h>
#include <memory.h>
#include <iostream>
#include <list>
#include <trw.h>

namespace TemplateRenderWizard
{
    IOBuffer::IOMemoryBuffer* Render::toBuffer()
    {
        IOBuffer::IOMemoryBuffer* buffer;
        buffer = new IOBuffer::IOMemoryBuffer(TRW_RENDER_MEMORY_BLOCK_SIZE);
        char* tBuffer = (char*) malloc(sizeof(char) * TRW_RENDER_BUFFER_SIZE);

        TemplateRenderWizard::Token::Token* token;
        token = this->getNextToken();

        while (token != nullptr) {
            switch (token->getType()) {
                case TemplateRenderWizard::Token::Type::PlainTextType: {
                    IOBuffer::IOReader* reader = token->getReader();
                    int nSizeRead = 0;
                    do {
                        memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                        nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                        buffer->write(tBuffer, nSizeRead);
                    } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
                    break;
                }
                case TemplateRenderWizard::Token::Type::PlainValueType: {
                    IOBuffer::IOReader* reader = token->getReader();
                    memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                    reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                    TemplateRenderWizard::Tree::LeafElement* leafElement = this->tree->get(tBuffer);
                    if (leafElement != nullptr) {
                        switch (leafElement->getType()) {
                            case TemplateRenderWizard::Tree::LeafElementType::LeafElementText: {
                                std::string* tbValue = (std::string*) leafElement->getData();
                                buffer->write((char*) tbValue->c_str(), strlen(tbValue->c_str()));
                                break;
                            }
                        }
                    }
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::CloseTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenControlTagType: {
                    this->renderControlExpression(buffer);
                }
            }

            token = this->getNextToken();
        }

        free(tBuffer);

        return buffer;
    }

    void Render::renderControlExpression(IOBuffer::IOMemoryBuffer* buffer)
    {
        TemplateRenderWizard::Token::Token* token;
        token = this->getNextToken();

        if (token->getType() != TemplateRenderWizard::Token::Type::KeywordType) {
            throw new UnexpectedToken;
        }

        INIT_CHAR_STRING(keyword, 32)
        token->getReader()->read(keyword, 32);

        if (strcmp(keyword, "if") == 0) {
            // calculate condition
            bool result = this->ifExpressionControlTag();
            if (result) {
                token = this->getNextToken();
                char* tBuffer = (char*) malloc(sizeof(char) * TRW_RENDER_BUFFER_SIZE);

                bool skipBlock = false;
                bool stopRender = false;

                while (token != nullptr) {
                    switch (token->getType()) {
                        case TemplateRenderWizard::Token::Type::PlainTextType: {
                            if (skipBlock) {
                                break;
                            }
                            IOBuffer::IOReader* reader = token->getReader();
                            int nSizeRead = 0;
                            do {
                                memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                                nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                                buffer->write(tBuffer, nSizeRead);
                            } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
                            break;
                        }
                        case TemplateRenderWizard::Token::Type::PlainValueType: {
                            if (skipBlock) {
                                break;
                            }
                            IOBuffer::IOReader* reader = token->getReader();
                            memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                            reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                            TemplateRenderWizard::Tree::LeafElement* leafElement = this->tree->get(tBuffer);
                            if (leafElement != nullptr) {
                                switch (leafElement->getType()) {
                                    case TemplateRenderWizard::Tree::LeafElementType::LeafElementText: {
                                        std::string* tbValue = (std::string*) leafElement->getData();
                                        buffer->write((char*) tbValue->c_str(), strlen(tbValue->c_str()));
                                        break;
                                    }
                                }
                            }
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
                                throw new UnexpectedToken;
                            }
                            keyword = new char[32];
                            memset(keyword, 0, sizeof(char) * 32);
                            token->getReader()->read(keyword, 32);

                            if (strcmp(keyword, "if") == 0) {
                                this->pushBackToken(token);
                                this->renderControlExpression(buffer);
                            }
                            if (strcmp(keyword, "else") == 0) {
                                skipBlock = true;
                                this->getNextToken(); // close tag
                            }
                            if (strcmp(keyword, "endif") == 0) {
                                this->getNextToken(); // close tag
                                stopRender = true;
                            }
                        }
                    }

                    if (stopRender) {
                        break;
                    }

                    token = this->getNextToken();
                }
            } else {
                token = this->getNextToken();
                char* tBuffer = (char*) malloc(sizeof(char) * TRW_RENDER_BUFFER_SIZE);

                bool skipBlock = true;
                bool stopRender = false;

                while (token != nullptr) {
                    switch (token->getType()) {
                        case TemplateRenderWizard::Token::Type::PlainTextType: {
                            if (skipBlock) {
                                break;
                            }
                            IOBuffer::IOReader* reader = token->getReader();
                            int nSizeRead = 0;
                            do {
                                memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                                nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                                buffer->write(tBuffer, nSizeRead);
                            } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
                            break;
                        }
                        case TemplateRenderWizard::Token::Type::PlainValueType: {
                            if (skipBlock) {
                                break;
                            }
                            IOBuffer::IOReader* reader = token->getReader();
                            memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                            reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                            TemplateRenderWizard::Tree::LeafElement* leafElement = this->tree->get(tBuffer);
                            if (leafElement != nullptr) {
                                switch (leafElement->getType()) {
                                    case TemplateRenderWizard::Tree::LeafElementType::LeafElementText: {
                                        std::string* tbValue = (std::string*) leafElement->getData();
                                        buffer->write((char*) tbValue->c_str(), strlen(tbValue->c_str()));
                                        break;
                                    }
                                }
                            }
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
                                throw new UnexpectedToken;
                            }
                            keyword = new char[32];
                            memset(keyword, 0, sizeof(char) * 32);
                            token->getReader()->read(keyword, 32);

                            if (strcmp(keyword, "if") == 0) {
                                this->pushBackToken(token);
                                this->renderControlExpression(buffer);
                            }
                            if (strcmp(keyword, "else") == 0) {
                                skipBlock = false;
                                this->getNextToken(); // close tag
                            }
                            if (strcmp(keyword, "endif") == 0) {
                                this->getNextToken(); // close tag
                                stopRender = true;
                            }
                        }
                    }

                    if (stopRender) {
                        break;
                    }

                    token = this->getNextToken();
                }
            }
        }
    }

    bool Render::ifExpressionControlTag() {
        std::list<TemplateRenderWizard::Token::Token*> tokens;

        TemplateRenderWizard::Token::Token* token;
        token = this->getNextToken();

        while (token->getType() != TemplateRenderWizard::Token::Type::CloseControlTagType) {
            tokens.push_back(token);
            token = this->getNextToken();
        }

        bool leftSide = true;
        std::list<TemplateRenderWizard::Token::Token*> lTokens, rTokens;
        TemplateRenderWizard::Token::Token* cmpToken;

        for (auto it = tokens.begin(); it != tokens.end(); it++) {
            if (leftSide) {
                if ((*it)->getType() == TemplateRenderWizard::Token::Type::CompareType) {
                    leftSide = false;
                    cmpToken = *it;
                    continue;
                }
                lTokens.push_back(*it);
            } else {
                rTokens.push_back(*it);
            }
        }

        return this->compare_value(this->get_value(&lTokens), this->get_value(&rTokens), cmpToken);
    }

    Value* Render::get_value(std::list<Token::Token*> *tokens) {
        Token::Token* token = nullptr;
        int count = 0;
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            token = *it;
            count++;
        }

        if (count == 1) {
            return this->getValueFromToken(token);
        }

        if (count == 3) {
            Expression* expr;
            auto it = tokens->begin();
            Token::Token* t1 = *it;
            it++;
            Token::Token* t2 = *it;
            it++;
            Token::Token* t3 = *it;
            return this->calc_expr(new Expression(new SyntaxElement(t1), new SyntaxElement(t3), t2));
        }

        std::list<SyntaxElement*>* lElement;
        lElement = new std::list<SyntaxElement*>;

        // first priority check braces
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            if ((*it)->getType() == Token::RoundBracketOpenType) {
                it++;
                std::list<Token::Token*>* nestedTokens;
                nestedTokens = new std::list<Token::Token*>;
                int nestedLevel = 0;
                do {
                    nestedTokens->push_back(*it);
                    it++;
                    if ((*it)->getType() == Token::RoundBracketOpenType) {
                        nestedLevel++;
                        nestedTokens->push_back(*it);
                        continue;
                    }
                    if ((*it)->getType() == Token::RoundBracketCloseType) {
                        if (nestedLevel == 0) {
                            break;
                        } else {
                            nestedTokens->push_back(*it);
                            nestedLevel--;
                        }
                    }
                } while(it != tokens->end());

                lElement->push_back(new SyntaxElement(this->get_value(nestedTokens)));
            } else {
                lElement->push_back(new SyntaxElement(*it));
            }
        }

        std::list<SyntaxElement*>* lSecondElement;
        lSecondElement = new std::list<SyntaxElement*>;

        // check operations * and /
        SyntaxElement* prevElement = nullptr;
        for (auto it = lElement->begin(); it != lElement->end(); it++) {
            if ((*it)->getType() == SyntaxElementType::SyntaxTokenType) {
                auto t = (Token::Token*) (*it)->getData();
                if (t->getType() == TemplateRenderWizard::Token::Type::MathOperationType) {
                    INIT_CHAR_STRING(strMathOp, 4)
                    t->getReader()->read(strMathOp, 4);
                    if (strcmp(strMathOp, "*") == 0 || strcmp(strMathOp, "/") == 0) {
                        lSecondElement->pop_back();
                        it++;
                        SyntaxElement* rValue = *it;
                        Expression* expr;
                        expr = new Expression(prevElement, rValue, t);
                        prevElement = new SyntaxElement(this->calc_expr(expr));
                        lSecondElement->push_back(prevElement);
                        continue;
                    }
                }
            }

            prevElement = *it;
            lSecondElement->push_back(*it);
        }

        // low priority operations
        int tryCount = 0;
        lElement = lSecondElement;
        do {
            if (tryCount == 100) {
                std::cout << "Loop detected" << std::endl;
                break;
            }
            lElement = this->filter_low_priority_operations(lElement);
            tryCount++;
        } while(this->is_unprocessed_token_exist(lElement));

        count = 0;
        for (auto it = lElement->begin(); it != lElement->end(); it++) {
            count++;
        }

        if (count == 1) {
            SyntaxElement* el = (*lElement->begin());
            if (el->getType() == SyntaxValueType) {
                return (Value*) el->getData();
            }
        }

        throw new UnexpectedToken;

        return nullptr;
    }

    bool Render::is_unprocessed_token_exist(std::list<SyntaxElement*>* lElements)
    {
        bool isExists = false;

        for (auto it = lElements->begin(); it != lElements->end(); it++) {
            if ((*it)->getType() == SyntaxElementType::SyntaxTokenType) {
                auto t = (Token::Token*) (*it)->getData();
                std::cout << "Token: " << t->getType() << "; Coords (Line:" << t->getLine() << "; Column: " << t->getColumn() << ")" << std::endl;
                std::cout << "Value: " << this->getValueFromToken(t)->getData<char*>() << std::endl;
                isExists = true;
                break;
            }
        }

        return isExists;
    }

    std::list<SyntaxElement*>* Render::filter_low_priority_operations(std::list<SyntaxElement*>* lElements) {
        std::list<SyntaxElement *> *lReturnElements;
        lReturnElements = new std::list<SyntaxElement *>;
        SyntaxElement *prevElement = nullptr;

        for (auto it = lElements->begin(); it != lElements->end(); it++) {
            if ((*it)->getType() == SyntaxElementType::SyntaxTokenType) {
                auto t = (Token::Token *) (*it)->getData();
                if (t->getType() == TemplateRenderWizard::Token::Type::MathOperationType) {
                    INIT_CHAR_STRING(strMathOp, 4)
                    RESET_TOKEN_READER(t);
                    t->getReader()->read(strMathOp, 4);
                    if (strcmp(strMathOp, "+") == 0 || strcmp(strMathOp, "-") == 0) {
                        lReturnElements->pop_back();
                        it++;
                        SyntaxElement *rValue = *it;
                        Expression *expr;
                        expr = new Expression(prevElement, rValue, t);
                        prevElement = new SyntaxElement(this->calc_expr(expr));
                        lReturnElements->push_back(prevElement);
                        continue;
                    }
                }
            }

            prevElement = *it;
            lReturnElements->push_back(*it);
        }

        return lReturnElements;
    }

    bool Render::compare_value(Value *lValue, Value *rValue, Token::Token *token)
    {
        RESET_TOKEN_READER(token);
        INIT_CHAR_STRING(cmpValue, 4)
        token->getReader()->read(cmpValue, 4);

        if (lValue->getType() == ValueType::String && ctype_digits(lValue->getData<char*>())) {
            const char* src = lValue->getData<char*>();
            int size = strlen(src) + 1;
            INIT_CHAR_STRING(dst, size)
            memcpy(dst, src, sizeof(char) * (size - 1));
            Value* v;
            v = new Value();
            v->setData(atoi(lValue->getData<char *>()));
            lValue = v;
        }

        if (rValue->getType() == ValueType::String && ctype_digits(rValue->getData<char*>())) {
            const char* src = rValue->getData<char*>();
            int size = strlen(src) + 1;
            INIT_CHAR_STRING(dst, size)
            memcpy(dst, src, sizeof(char) * (size - 1));
            Value* v;
            v = new Value();
            v->setData(atoi(rValue->getData<char *>()));
            rValue = v;
        }

        if (lValue->getType() == ValueType::Integer && rValue->getType() == ValueType::Integer) {
            if (strcmp(cmpValue, ">=") == 0) {
                return *lValue->getData<int*>() >= *rValue->getData<int*>();
            }
        }

        throw new UnexpectedToken;

        return false;
    }
}
