#include "Utilities.h"

    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        // Skip leading whitespaces
        while (next_pos < str.size() && std::isspace(str[next_pos])) {
            ++next_pos;  // Move past any leading spaces
        }

        size_t start = str.find_first_of(m_delimiter, next_pos);
        std::string token;

        if (start != std::string::npos) {
            token = str.substr(next_pos, start - next_pos);
            next_pos = start + 1;
        }
        else {
            token = str.substr(next_pos);
            next_pos = std::string::npos;
        }
        if (token.empty() && next_pos != std::string::npos) {
            more = false;
            throw "Delimiter found at next_pos, empty token!";
        }

        more = (next_pos != std::string::npos);

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }
        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
