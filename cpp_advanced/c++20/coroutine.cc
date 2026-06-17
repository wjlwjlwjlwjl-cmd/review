#include <iostream>
#include <coroutine>

struct Generator{
    struct promise_type{
        int _current_value;
        std::exception_ptr _exptr;
        int ret;

        Generator get_return_object(){
            return Generator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend(){
            std::cout << "initail suspend" << std::endl;
            return {};
        }
        std::suspend_always yield_value(int value){
            std::cout << "yield value" << std::endl;
            _current_value = value;
            return {};
        }
        std::suspend_always final_suspend() noexcept{
            std::cout << "final suspend" << std::endl;
            return {};
        }

        void return_value(int val){
            _current_value = val;
            std::cout << "return_value: " << val << std::endl;
        }

        void unhandled_exception(){
            _exptr = std::current_exception();
        }
    };
    std::coroutine_handle<promise_type> _handle;

    explicit Generator(std::coroutine_handle<promise_type> handle){
        _handle = handle;
    }

    ~Generator(){
        if(_handle){
            _handle.destroy();
        }
    }

    int value(){
        return _handle.promise()._current_value;
    }

    bool next(){
        if(!_handle.done()){
            _handle.resume();
        }
        return !_handle.done();
    }
};

Generator range(int start, int end){
    for(int i = start; i < end; i++){
        co_yield i;
    }
    co_return 100;
}

int main(){
    auto gen = range(1, 10);
    try{
        while(gen.next()){
            std::cout << gen.value() << std::endl;
        }
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}