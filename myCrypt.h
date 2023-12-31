#ifndef MYCRYPT
#define MYCRYPT

#include<iostream>
#include<string.h>


typedef unsigned int uint;

struct Hash
{
    uint _part1;
    uint _part2;
    uint _part3;
    uint _part4;
    uint _part5;

    Hash() = default;
    Hash(uint part1, uint part2, uint part3, uint part4, uint part5) :
        _part1(part1), _part2(part2), _part3(part3), _part4(part4), _part5(part5) {};

    bool operator==(Hash const& other)
    {
        if (_part1 != other._part1)
            return false;
        if (_part2 != other._part2)
            return false;
        if (_part3 != other._part3)
            return false;
        if (_part4 != other._part4)
            return false;
        if (_part5 != other._part5)
            return false;

        return true;
    }

    Hash operator=(const Hash& other);
};

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
Hash sha1(char* message, uint msize_bytes); // отданный массив нужно удалить вручную


#endif // MYCRYPT

