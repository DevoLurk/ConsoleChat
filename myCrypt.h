#ifndef MYCRYPT
#define MYCRYPT

#include<iostream>
#include<string.h>

typedef unsigned int uint;

#define one_block_size_bytes 64     // количество байб в блоке
#define one_block_size_uints 16     // количество 4байтовых  в блоке
#define block_expend_size_uints 80  // количество 4байтовых в дополненном блоке

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef uint* Block;
typedef uint ExpendBlock[block_expend_size_uints];

const uint H[5] =
{
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
}; 

uint cycle_shift_left(uint val, int bit_count);
uint bring_to_human_view(uint val);
uint* sha1(char* message, uint msize_bytes); // отданный массив нужно удалить вручную
bool compare_hash(uint* hash1, uint* hash2);

////////////////////////////////////////////////////////////////////////////////////////

class HashTable
{
    enum enPairStatus
    {
        free,    // свободен
        engaged, // зан€т
        deleted  // удален
    };

    struct Pair
    {
        enPairStatus status;       // состо€ние €чейки
        std::string login;         // им€ фрукта (ключ)
        uint* password_hash;       // количество фрукта (значение)

        Pair() 
        {  
            status = free;
            login.clear();
            password_hash = nullptr;
        }

        Pair(std::string name, uint* hash)
        {
            status = engaged;
            login = name;
            password_hash = hash;
        }
        
        ~Pair()
        {
            delete password_hash;
        }   

        Pair& operator = (const Pair& other) 
        { 
            login = other.login;
            password_hash = other.password_hash;
            status = other.status;

            return *this;
        }
    };

private:
    Pair* array;
    int mem_size;
    int count;

    void add(std::string name, uint* pass_hash);    // add user and password->hash
    uint* find(std::string name);                     // find user and returns index in table or -1
    int hash_func(std::string name, int offset);
    void resize();

public:
    HashTable();
    ~HashTable();

    void add(std::string name, std::string pass);
    void del(std::string name);                      // del user by name
    bool check(std::string name, std::string pass);  // find user and chek his password
};

#endif // MYCRYPT

