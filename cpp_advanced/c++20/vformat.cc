#include <iostream>
#include <format>

class Logger{
public:
    enum class Level{
        debug,     
        error
    };

    Logger(Level l) :_l(l) {}

    template <class...Args>
    void log_error(const std::string& format, Args&&...args){
        std::cout << std::vformat(format, std::make_format_args(args...)) << std::endl;
    }

private:
    Level _l;
};

int main(){
    Logger log(Logger::Level::error);
    log.log_error("hello, {}, this is an {} msg", "world", "error");
    return 0;
}