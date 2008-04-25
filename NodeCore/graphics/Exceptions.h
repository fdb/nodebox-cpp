#ifndef Exceptions_h
#define Exceptions_h

namespace NodeCore {

class NodeBoxError : public std::exception
{
public:
    NodeBoxError(const std::string& message) : m_message(message) {}
    virtual ~NodeBoxError() throw () {}
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

} // namespace NodeCore

#endif // BezierPath_h