#include <iostream>
#include "type_traits"
#include "serializer.h"
#include "deserializer.h"
#include "assert.h"
#include "sstream"


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

int main() {

    Data a{1 , false , 4};
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(a);
    Data b{1, false , 4};
    Deserializer deserializer(stream);
    Error err = deserializer.load(b);
    Data c{1, true ,4 };
    assert(a.b != c.b);

}