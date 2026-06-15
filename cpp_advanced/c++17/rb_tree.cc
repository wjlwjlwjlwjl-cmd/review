#include <variant>
#include <vector>
#include <list>
#include <set>
#include <iostream>

template <class...Lambda>
struct overload: Lambda...{
    using Lambda::operator()...;
};

template <class T>
class rb_tree{
public:
    rb_tree(int table_size = 11, int trans_size = 2) : _table_size(table_size), _trans_size(trans_size){
        _table.resize(_table_size);
    }

    void insert(T data){
        int hashi = data % _table_size;
        auto list_insert = [&](std::list<T>& lt){
            if(lt.size() < _trans_size){
                std::cout << "list insert: " << data << std::endl;
                lt.push_back(data);
            }
            else{
                std::set<T> new_con(lt.begin(), lt.end());
                new_con.insert(data);
                std::cout << "set insert: " << data << std::endl;
                _table[hashi] = std::move(new_con);
            }
        };
        auto set_insert = [&](std::set<T>& s){
            s.insert(data);
            std::cout << "set insert: " << data << std::endl;
        };
        std::visit(overload{list_insert, set_insert}, _table[hashi]);
    }

    T& find(T key){
        int hashi = key % _table_size;
        auto list_find = [&](){
            if(auto it = find(_table[hashi].begin(), _table[hashi].end(), key); it != nullptr){
                return true;
            }
            return false;
        };
        auto set_find = [&](){
            if(auto it = find(_table[hashi].begin(), _table[hashi].end(), key); it != nullptr){
                std::cout << "set find: " << key << std::endl;
                return true;
            }
            return false;
        };
        std::visit(overload{list_find, set_find}, _table[hashi]);
    }
private:
    std::vector<std::variant<std::list<T>, std::set<T>>> _table;
    int _table_size;
    int _trans_size;
};

int main(){
    rb_tree<int> rb;
    rb.insert(11);
    rb.insert(22);
    rb.insert(33);
    return 0;
}
