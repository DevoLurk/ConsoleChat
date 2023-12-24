#include "myCrypt.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/// sha-1

uint cycle_shift_left(uint val, int bit_count)
{
    return (val << bit_count | val >> (32 - bit_count));
}

uint bring_to_human_view(uint val)
{
    return  ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
}

uint* sha1(char* message, uint msize_bytes)
{
    uint A = H[0];
    uint B = H[1];
    uint C = H[2];
    uint D = H[3];
    uint E = H[4];

    uint totalBlockCount = msize_bytes / one_block_size_bytes;

    uint needAdditionalBytes = one_block_size_bytes - (msize_bytes - totalBlockCount * one_block_size_bytes);

    if (needAdditionalBytes < 8)
    {
        totalBlockCount += 2;
        needAdditionalBytes += one_block_size_bytes;
    }
    else
    {
        totalBlockCount += 1;
    }

    uint extendedMessageSize = msize_bytes + needAdditionalBytes;

    unsigned char* newMessage = new unsigned char[extendedMessageSize];
    memcpy(newMessage, message, msize_bytes);

    newMessage[msize_bytes] = 0x80;
    memset(newMessage + msize_bytes + 1, 0, needAdditionalBytes - 1);

    uint* ptr_to_size = (uint*)(newMessage + extendedMessageSize - 4);
    *ptr_to_size = bring_to_human_view(msize_bytes * 8);

    ExpendBlock exp_block;
    for (int i = 0; i < totalBlockCount; i++)
    {

        unsigned char* cur_p = newMessage + one_block_size_bytes * i;
        Block block = (Block)cur_p;

        for (int j = 0; j < one_block_size_uints; j++)
            exp_block[j] = bring_to_human_view(block[j]);

        for (int j = one_block_size_uints; j < block_expend_size_uints; j++)
        {
            exp_block[j] =
                exp_block[j - 3] ^
                exp_block[j - 8] ^
                exp_block[j - 14] ^
                exp_block[j - 16];
            exp_block[j] = cycle_shift_left(exp_block[j], 1);
        }

        uint a = H[0];
        uint b = H[1];
        uint c = H[2];
        uint d = H[3];
        uint e = H[4];

        for (int j = 0; j < block_expend_size_uints; j++)
        {
            uint f, k;

            if (j < 20)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40)
            {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else
            {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint temp = cycle_shift_left(a, 5) + f + e + k + exp_block[j];
            e = d;
            d = c;
            c = cycle_shift_left(b, 30);
            b = a;
            a = temp;
        }

        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
    }

    uint* digest = new uint[5];
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;

    delete[] newMessage;
    return digest;
}

bool compare_hash(uint* hash1, uint* hash2)
{
    for (int i = 0; i < 5; i++)
        if (hash1[i] != hash2[i])
            return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/// HashTable

HashTable::HashTable()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable()
{
    delete[] array;
}

int HashTable::hash_func(std::string name, int offset)
{
    int sum = 0;

    for (int i = 0; i < name.length(); i++)
        sum += name[i];

    return (sum % mem_size + offset * offset) % mem_size;
}

void HashTable::add(std::string name, std::string pass)
{
    uint* hash = sha1((char*)(pass.c_str()), static_cast<uint>(pass.size()));
    add(name, hash);
}


void HashTable::add(std::string name, uint* pass_hash)
{
    int index = -1, i = 0;

    for (; i < mem_size; i++)
    {
        index = hash_func(name, i);

        if (array[index].status != engaged)
            break;
    }

    if (i >= mem_size)
    {
        resize();
        add(name, pass_hash);
    }
    else
    {
        
        array[index] = Pair(name, pass_hash);
        count++;
    }
}

void HashTable::del(std::string name)
{
    for (int i = 0; i < mem_size; i++)
    {
        int index = hash_func(name, i);

        if (array[index].login == name)
        {
            delete array[index].password_hash;
            array[index].login.clear();
            array[index].status = deleted;
        }

        if (array[index].status == free)
            break;
    }
}

uint* HashTable::find(std::string name)
{
    for (int i = 0; i < mem_size; i++)
    {
        int index = hash_func(name, i);

        if (array[index].login == name)
            return array[index].password_hash;

        if (array[index].status == free)
            break;
    }

    return nullptr;
}

void HashTable::resize()
{
    Pair* save_ct = array;
    int oldSize = mem_size;

    mem_size *= 2;   
    count = 0;     
    array = new Pair[mem_size];

    for (int i = 0; i < oldSize; i++)
        if (save_ct[i].status == engaged)
            add(save_ct[i].login, save_ct[i].password_hash);

    delete[] save_ct;
}

bool HashTable::check(std::string name, std::string pass)
{


    return true;
}