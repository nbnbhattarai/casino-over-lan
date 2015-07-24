#ifndef EXCEPTION
#define EXCEPTION
#include <iostream>

namespace cardgame {

class Exception{
public:
    enum Code{
        FILE_CANNOT_LOAD,
        MEMORY_CANNOT_ALLOCATE,
        SYSTEM_NOT_RESPONDING,
        CANNOT_CONNECT_TO_SERVER,
        CANNOT_BIND_TO_PORT,
        CANNOT_ACCEPT_CONNECTION,
        CANNOT_SEND_FILE,
        CANNOT_RECEIVE_FILE
    };

private:
    std::string errorName;
    Code code;
public:
    Exception (Code c, std::string name = "");
    void display (void);
};

Exception :: Exception (Code c, std::string name):errorName(name){
    code = c;
}

void Exception::display(void){
    std::cout << "Exception : ";
    switch (code){
        case 0:
            std::cout << "Can not load file [" << errorName << "]" << std::endl;
            break;
        case 1:
            std::cout << "Memory Cannot allocate" << std::endl;
            break;
        case 2:
            std::cout << "System Not responding" << std::endl;
            break;
        case 3:
            std::cout << "Cannot Connect to server [" << errorName <<"]" << std::endl;
            break;
        case 4:
            std::cout << "Cannot Bind to PORT [" << errorName << "]" << std::endl;
            break;
        case 5:
            std::cout << "Cannot Accept Connection." << std::endl;
            break;
        default :
            std::cout << "Unknown Exception!" << std::endl;
            break;
        }
}
}
#endif // EXCEPTION
