#include <trw.h>
#include <io-buffer.h>

namespace TemplateRenderWizard
{
    TokenFile::TokenFile(const char *tokenFile)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(tokenFile);
        this->charStream = new IOBuffer::CharStream(fileReader);
        this->tokenMap = new Token::TokenMap;
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
        return this->tokenMap->getType(tokenName);
    }
}
