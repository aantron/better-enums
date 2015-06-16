#include <cxxtest/TestSuite.h>
#include <enum.h>

// This test uses internal constants declared by feature testing macros in
// enum.h. They are not part of the public interface, but are used here to avoid
// duplication of definitions for C++11 and C++98.
//
// BETTER_ENUMS__CONSTEXPR is a synonym for constexpr when available, and
// othewise expands to nothing.



// Using a type trait.
struct html_color_1 {
    unsigned char   r, g, b;

    BETTER_ENUMS__CONSTEXPR
    html_color_1(unsigned char _r, unsigned char _g, unsigned char _b) :
        r(_r), g(_g), b(_b) { }
};

// In C++11, can simply to struct ::better_enums::underlying_traits below.
namespace better_enums {

template <>
struct underlying_traits<html_color_1> {
    typedef unsigned int    integral_representation;

    BETTER_ENUMS__CONSTEXPR static html_color_1 from_integral(unsigned int i)
        { return html_color_1(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff); }

    BETTER_ENUMS__CONSTEXPR static unsigned int to_integral(html_color_1 v)
        { return (unsigned int)v.r << 16 | (unsigned int)v.g << 8 | v.b; }
};

}

ENUM(HtmlColor1, html_color_1,
     darksalmon = 0xc47451, purplemimosa = 0x9e7bff, slimegreen = 0xbce954)



// Using member definitions.
struct html_color_2 {
    unsigned char   r, g, b;

    BETTER_ENUMS__CONSTEXPR
    html_color_2(unsigned char _r, unsigned char _g, unsigned char _b) :
        r(_r), g(_g), b(_b) { }



    typedef unsigned int    integral_representation;

    explicit BETTER_ENUMS__CONSTEXPR html_color_2(unsigned int i) :
        r(i >> 16 & 0xff), g(i >> 8 & 0xff), b(i & 0xff) { }

    BETTER_ENUMS__CONSTEXPR operator unsigned int() const
        { return (unsigned int)r << 16 | (unsigned int)g << 8 | b; }
};

// Initializers are not supported before GCC 5.1, even with a literal type and
// constexpr conversion to integer.
#ifdef BETTER_ENUMS__HAVE_CONSTEXPR
#   ifdef __GNUC__
#       ifdef __clang__
#           define SUPPORT_INITIALIZER
#       else
#           if __GNUC__ >= 5
#               define SUPPORT_INITIALIZER
#           endif
#       endif
#   endif
#endif

#ifdef SUPPORT_INITIALIZER
ENUM(HtmlColor2, html_color_2,
     darksalmon = 0xc47451, purplemimosa = 0x9e7bff, slimegreen = 0xbce954,
     celeste = html_color_2(0x50, 0xeb, 0xec))
#else
ENUM(HtmlColor2, html_color_2,
     darksalmon = 0xc47451, purplemimosa = 0x9e7bff, slimegreen = 0xbce954)
#endif



class UnderlyingTypeTests : public CxxTest::TestSuite {
  public:
    void test_basics_and_operators()
    {
        HtmlColor1  color_1 = HtmlColor1::darksalmon;

        TS_ASSERT_EQUALS(color_1->r, 0xc4);
        TS_ASSERT_EQUALS(color_1->g, 0x74);
        TS_ASSERT_EQUALS(color_1->b, 0x51);

        TS_ASSERT_EQUALS(sizeof(HtmlColor1), sizeof(html_color_1));

        HtmlColor2  color_2 = HtmlColor2::purplemimosa;

        TS_ASSERT_EQUALS(color_2->r, 0x9e);
        TS_ASSERT_EQUALS(color_2->g, 0x7b);
        TS_ASSERT_EQUALS(color_2->b, 0xff);

        TS_ASSERT_EQUALS(sizeof(HtmlColor2), sizeof(html_color_2));

#ifdef SUPPORT_INITIALIZER
        HtmlColor2  color_3 = HtmlColor2::celeste;

        TS_ASSERT_EQUALS(color_3->r, 0x50);
        TS_ASSERT_EQUALS(color_3->g, 0xeb);
        TS_ASSERT_EQUALS(color_3->b, 0xec);
#endif

        color_1->r = 0;

        const HtmlColor1    const_color = HtmlColor1::slimegreen;
        TS_ASSERT_EQUALS(const_color->r, 0xbc);

        html_color_1        &color_1_reference = *color_1;
        const html_color_1  &const_color_reference = *const_color;

        TS_ASSERT_EQUALS(color_1_reference.r, 0);
        TS_ASSERT_EQUALS(const_color_reference.r, 0xbc);
    }

    void test_conversion_functions()
    {
        HtmlColor2      color_1 = HtmlColor2::darksalmon;
        html_color_2    color_1_underlying = color_1._to_underlying();

        TS_ASSERT_EQUALS(color_1_underlying.r, color_1->r);
        TS_ASSERT_EQUALS(color_1_underlying.g, color_1->g);
        TS_ASSERT_EQUALS(color_1_underlying.b, color_1->b);

        color_1_underlying = html_color_2(HtmlColor2::slimegreen);
        color_1 = HtmlColor2::_from_underlying(color_1_underlying);

        TS_ASSERT_EQUALS(color_1->r, color_1_underlying.r);
        TS_ASSERT_EQUALS(color_1->g, color_1_underlying.g);
        TS_ASSERT_EQUALS(color_1->b, color_1_underlying.b);

        color_1_underlying = html_color_2(1, 2, 3);
        color_1 = HtmlColor2::_from_underlying_unchecked(color_1_underlying);

        TS_ASSERT_EQUALS(color_1->r, color_1_underlying.r);
        TS_ASSERT_EQUALS(color_1->g, color_1_underlying.g);
        TS_ASSERT_EQUALS(color_1->b, color_1_underlying.b);
    }

    void test_switch()
    {
#ifndef BETTER_ENUMS_STRICT_CONVERSION

        HtmlColor1      html_color_1 = HtmlColor1::purplemimosa;

        switch (html_color_1) {
            case HtmlColor1::darksalmon:   TS_ASSERT(false); break;
            case HtmlColor1::purplemimosa: TS_ASSERT(true); break;
            case HtmlColor1::slimegreen:   TS_ASSERT(false); break;
        }

#else
#   ifdef BETTER_ENUMS__HAVE_CONSTEXPR

        HtmlColor1      html_color_1 = HtmlColor1::purplemimosa;

        switch (html_color_1) {
            case +HtmlColor1::darksalmon:   TS_ASSERT(false); break;
            case +HtmlColor1::purplemimosa: TS_ASSERT(true); break;
            case +HtmlColor1::slimegreen:   TS_ASSERT(false); break;
        }

#   endif
#endif
    }
};
