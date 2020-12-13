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
