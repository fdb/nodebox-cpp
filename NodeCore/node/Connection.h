#ifndef Connection_h
#define Connection_h

#include <vector>
#include <string>

namespace NodeCore {
    
class Field;
class Node;

class ConnectionError : public std::exception {
public:
    ConnectionError(std::string message = "")
        :m_message(message) {}
    virtual ~ConnectionError() throw () {}
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

class Connection {
public:
    Connection(Field *outputField, Field *inputField);
    virtual ~Connection();

    Field* getOutputField();
    Node* getOutputNode();
    Field* getInputField();
    Node* getInputNode();

    friend std::ostream& operator<<(std::ostream& o, const Connection& c);

private:
    void markDirtyDownstream();
    void update();
    
    Field* m_output;
    Field* m_input;
    
    friend class Field;
};

} // namespace NodeCore

#endif // Connection_h
