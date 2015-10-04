// This file was generated automatically.

// Representation
//
// Let's go over some of the low-level properties of a Better Enum. This time,
// we will declare a more unusual enum than the ones we have seen.

#include <cassert>
#include <iostream>
#include <enum.h>

BETTER_ENUM(ContentType, short,
     CompressedVideo = 5, PCM = 8, Subtitles = 17, Comment = 44)

// This is for a hypothetical multimedia container file format. Perhaps the
// files have sections, and each one has a header:

struct Header {
    ContentType     type;
    short           flags;
    int             offset;
};


// Here is what we have.

int main()
{
    assert(sizeof(ContentType) == 2);

// ContentType behaves just like a short, in fact it simply wraps one. This
// makes it possible to lay out structures in a predictable fashion:

    Header      header = {ContentType::PCM, 0, 0};

    assert(sizeof(header) == 8);
    assert((size_t)&header.flags - (size_t)&header.type == 2);


// uint16_t is called ContentType's underlying or representation type. If you
// want to know the representation type of any enum you have declared, it is
// available as the member type ::_integral:

    ContentType::_integral  untrusted_value = 44;

// Use this if you want a sized field to receive untrusted data, but aren't
// willing to call it ContentType yet because you have not validated it. Your
// validator will likely call ::_from_integral_nothrow, perform any other
// validation your application requires, and then return ContentType.

    ContentType             type =
        ContentType::_from_integral(untrusted_value);
    std::cout << type._to_string() << std::endl;


// You have probably noticed the initializers on each of the constants in
// ContentType. This allows you to declare sparse enums for compatibility with
// external protocols or previous versions of your software. The initializers
// don't need to be literal integers - they can be anything that the compiler
// would accept in a normal enum declaration. If there was a macro called
// BIG_FAT_MACRO declared above, we could have written Subtitles =
// BIG_FAT_MACRO. We could also have written Subtitles = CompressedVideo.

// The in-memory representation of an enum value is simply the number it has
// been assigned by the compiler. You should be safe passing enums to functions
// like fread and fwrite, and casting memory blocks known to be safe to struct
// types containg enums. The enums will behave as expected.


    return 0;
}
