#include <trw.h>
#include <io-buffer.h>
#include <map>
#include <string>

namespace TemplateRenderWizard
{
    TokenFile::TokenFile(const char *tokenFile)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(tokenFile);
        this->charStream = new IOBuffer::CharStream(fileReader);

        this->tokenMap = new std::map<std::string, Token::Type>;
        (*this->tokenMap)["plainText"] = Token::Type::PlainTextType;
        (*this->tokenMap)["openTagValue"] = Token::Type::OpenTagValueType;
        (*this->tokenMap)["closeTagValue"] = Token::Type::CloseTagValueType;
        (*this->tokenMap)["plainValue"] = Token::Type::PlainValueType;
        (*this->tokenMap)["openControlTag"] = Token::Type::OpenControlTagType;
        (*this->tokenMap)["closeControlTag"] = Token::Type::CloseControlTagType;
        (*this->tokenMap)["roundBracketOpen"] = Token::Type::RoundBracketOpenType;
        (*this->tokenMap)["roundBracketClose"] = Token::Type::RoundBracketCloseType;
        (*this->tokenMap)["exprValue"] = Token::Type::ExpressionValueType;
        (*this->tokenMap)["mathOp"] = Token::Type::MathOperationType;
        (*this->tokenMap)["compare"] = Token::Type::CompareType;
        (*this->tokenMap)["keyword"] = Token::Type::KeywordType;
    }

    Token::Type TokenFile::getNextTokenType()
    {
        char* nextChar = this->charStream->getNext();
        if (nextChar == nullptr) {
            return Token::EofType;
        }

        IOBuffer::IOMemoryBuffer* ioWriter = nullptr;

        while (this->isEmptyChar(nextChar)) {
            nextChar = this->charStream->getNext();
        }
        if (nextChar == nullptr) {
            return Token::EofType;
        }

        ioWriter = new IOBuffer::IOMemoryBuffer(16);
        int length = 0;

        while (!this->isEmptyChar(nextChar)) {
            ioWriter->write(nextChar, 1);
            length++;
            nextChar = this->charStream->getNext();
        }

        length++;
        INIT_CHAR_STRING(strTokenName, length)
        ioWriter->read(strTokenName, length - 1);

        return this->getTokenTypeByName(strTokenName);
    }

    bool TokenFile::isEmptyChar(char* symbol) {
        return symbol == nullptr || *symbol == ' ' || *symbol == 0x0A;
    }

    Token::Type TokenFile::getTokenTypeByName(const char *tokenName) {
        if (this->tokenMap->find(tokenName) != this->tokenMap->end()) {
            return this->tokenMap->at(tokenName);
        }

        throw new UnknownToken;
    }
}
