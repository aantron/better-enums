// This file is part of Better Enums, released under the BSD 2-clause license.
// See LICENSE for details, or visit http://github.com/aantron/better-enums.

#pragma once

#ifndef _BETTER_ENUM_ENUM_H_
#define _BETTER_ENUM_ENUM_H_



#include <cstddef>          // For size_t.
#include <cstring>          // For string and memory routines.
#include <stdexcept>
#include <type_traits>



#ifdef BETTER_ENUM_PP_MAP_FILE

#include BETTER_ENUM_PP_MAP_FILE

#else

#define _ENUM_PP_MAP(macro, data, ...) \
    _ENUM_A(_ENUM_PP_MAP_VAR_COUNT, _ENUM_PP_COUNT(__VA_ARGS__)) \
        (macro, data, __VA_ARGS__)

#define _ENUM_PP_MAP_VAR_COUNT(count) _ENUM_M ## count

#define _ENUM_A(macro, ...) macro(__VA_ARGS__)

#define _ENUM_M1(m, d, x) _ENUM_A(m, d, x)
#define _ENUM_M2(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M1(m, d, __VA_ARGS__)
#define _ENUM_M3(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M2(m, d, __VA_ARGS__)
#define _ENUM_M4(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M3(m, d, __VA_ARGS__)
#define _ENUM_M5(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M4(m, d, __VA_ARGS__)
#define _ENUM_M6(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M5(m, d, __VA_ARGS__)
#define _ENUM_M7(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M6(m, d, __VA_ARGS__)
#define _ENUM_M8(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M7(m, d, __VA_ARGS__)
#define _ENUM_M9(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M8(m, d, __VA_ARGS__)
#define _ENUM_M10(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M9(m, d, __VA_ARGS__)
#define _ENUM_M11(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M10(m, d, __VA_ARGS__)
#define _ENUM_M12(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M11(m, d, __VA_ARGS__)
#define _ENUM_M13(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M12(m, d, __VA_ARGS__)
#define _ENUM_M14(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M13(m, d, __VA_ARGS__)
#define _ENUM_M15(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M14(m, d, __VA_ARGS__)
#define _ENUM_M16(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M15(m, d, __VA_ARGS__)
#define _ENUM_M17(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M16(m, d, __VA_ARGS__)
#define _ENUM_M18(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M17(m, d, __VA_ARGS__)
#define _ENUM_M19(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M18(m, d, __VA_ARGS__)
#define _ENUM_M20(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M19(m, d, __VA_ARGS__)
#define _ENUM_M21(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M20(m, d, __VA_ARGS__)
#define _ENUM_M22(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M21(m, d, __VA_ARGS__)
#define _ENUM_M23(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M22(m, d, __VA_ARGS__)
#define _ENUM_M24(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M23(m, d, __VA_ARGS__)
#define _ENUM_M25(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M24(m, d, __VA_ARGS__)
#define _ENUM_M26(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M25(m, d, __VA_ARGS__)
#define _ENUM_M27(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M26(m, d, __VA_ARGS__)
#define _ENUM_M28(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M27(m, d, __VA_ARGS__)
#define _ENUM_M29(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M28(m, d, __VA_ARGS__)
#define _ENUM_M30(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M29(m, d, __VA_ARGS__)
#define _ENUM_M31(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M30(m, d, __VA_ARGS__)
#define _ENUM_M32(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M31(m, d, __VA_ARGS__)
#define _ENUM_M33(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M32(m, d, __VA_ARGS__)
#define _ENUM_M34(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M33(m, d, __VA_ARGS__)
#define _ENUM_M35(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M34(m, d, __VA_ARGS__)
#define _ENUM_M36(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M35(m, d, __VA_ARGS__)
#define _ENUM_M37(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M36(m, d, __VA_ARGS__)
#define _ENUM_M38(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M37(m, d, __VA_ARGS__)
#define _ENUM_M39(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M38(m, d, __VA_ARGS__)
#define _ENUM_M40(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M39(m, d, __VA_ARGS__)
#define _ENUM_M41(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M40(m, d, __VA_ARGS__)
#define _ENUM_M42(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M41(m, d, __VA_ARGS__)
#define _ENUM_M43(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M42(m, d, __VA_ARGS__)
#define _ENUM_M44(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M43(m, d, __VA_ARGS__)
#define _ENUM_M45(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M44(m, d, __VA_ARGS__)
#define _ENUM_M46(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M45(m, d, __VA_ARGS__)
#define _ENUM_M47(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M46(m, d, __VA_ARGS__)
#define _ENUM_M48(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M47(m, d, __VA_ARGS__)
#define _ENUM_M49(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M48(m, d, __VA_ARGS__)
#define _ENUM_M50(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M49(m, d, __VA_ARGS__)
#define _ENUM_M51(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M50(m, d, __VA_ARGS__)
#define _ENUM_M52(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M51(m, d, __VA_ARGS__)
#define _ENUM_M53(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M52(m, d, __VA_ARGS__)
#define _ENUM_M54(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M53(m, d, __VA_ARGS__)
#define _ENUM_M55(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M54(m, d, __VA_ARGS__)
#define _ENUM_M56(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M55(m, d, __VA_ARGS__)
#define _ENUM_M57(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M56(m, d, __VA_ARGS__)
#define _ENUM_M58(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M57(m, d, __VA_ARGS__)
#define _ENUM_M59(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M58(m, d, __VA_ARGS__)
#define _ENUM_M60(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M59(m, d, __VA_ARGS__)
#define _ENUM_M61(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M60(m, d, __VA_ARGS__)
#define _ENUM_M62(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M61(m, d, __VA_ARGS__)
#define _ENUM_M63(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M62(m, d, __VA_ARGS__)
#define _ENUM_M64(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M63(m, d, __VA_ARGS__)
#define _ENUM_M65(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M64(m, d, __VA_ARGS__)
#define _ENUM_M66(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M65(m, d, __VA_ARGS__)
#define _ENUM_M67(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M66(m, d, __VA_ARGS__)
#define _ENUM_M68(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M67(m, d, __VA_ARGS__)
#define _ENUM_M69(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M68(m, d, __VA_ARGS__)
#define _ENUM_M70(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M69(m, d, __VA_ARGS__)
#define _ENUM_M71(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M70(m, d, __VA_ARGS__)
#define _ENUM_M72(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M71(m, d, __VA_ARGS__)
#define _ENUM_M73(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M72(m, d, __VA_ARGS__)
#define _ENUM_M74(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M73(m, d, __VA_ARGS__)
#define _ENUM_M75(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M74(m, d, __VA_ARGS__)
#define _ENUM_M76(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M75(m, d, __VA_ARGS__)
#define _ENUM_M77(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M76(m, d, __VA_ARGS__)
#define _ENUM_M78(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M77(m, d, __VA_ARGS__)
#define _ENUM_M79(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M78(m, d, __VA_ARGS__)
#define _ENUM_M80(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M79(m, d, __VA_ARGS__)
#define _ENUM_M81(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M80(m, d, __VA_ARGS__)
#define _ENUM_M82(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M81(m, d, __VA_ARGS__)
#define _ENUM_M83(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M82(m, d, __VA_ARGS__)
#define _ENUM_M84(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M83(m, d, __VA_ARGS__)
#define _ENUM_M85(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M84(m, d, __VA_ARGS__)
#define _ENUM_M86(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M85(m, d, __VA_ARGS__)
#define _ENUM_M87(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M86(m, d, __VA_ARGS__)
#define _ENUM_M88(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M87(m, d, __VA_ARGS__)
#define _ENUM_M89(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M88(m, d, __VA_ARGS__)
#define _ENUM_M90(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M89(m, d, __VA_ARGS__)
#define _ENUM_M91(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M90(m, d, __VA_ARGS__)
#define _ENUM_M92(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M91(m, d, __VA_ARGS__)
#define _ENUM_M93(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M92(m, d, __VA_ARGS__)
#define _ENUM_M94(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M93(m, d, __VA_ARGS__)
#define _ENUM_M95(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M94(m, d, __VA_ARGS__)
#define _ENUM_M96(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M95(m, d, __VA_ARGS__)
#define _ENUM_M97(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M96(m, d, __VA_ARGS__)
#define _ENUM_M98(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M97(m, d, __VA_ARGS__)
#define _ENUM_M99(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M98(m, d, __VA_ARGS__)
#define _ENUM_M100(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M99(m, d, __VA_ARGS__)
#define _ENUM_M101(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M100(m, d, __VA_ARGS__)
#define _ENUM_M102(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M101(m, d, __VA_ARGS__)
#define _ENUM_M103(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M102(m, d, __VA_ARGS__)
#define _ENUM_M104(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M103(m, d, __VA_ARGS__)
#define _ENUM_M105(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M104(m, d, __VA_ARGS__)
#define _ENUM_M106(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M105(m, d, __VA_ARGS__)
#define _ENUM_M107(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M106(m, d, __VA_ARGS__)
#define _ENUM_M108(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M107(m, d, __VA_ARGS__)
#define _ENUM_M109(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M108(m, d, __VA_ARGS__)
#define _ENUM_M110(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M109(m, d, __VA_ARGS__)
#define _ENUM_M111(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M110(m, d, __VA_ARGS__)
#define _ENUM_M112(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M111(m, d, __VA_ARGS__)
#define _ENUM_M113(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M112(m, d, __VA_ARGS__)
#define _ENUM_M114(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M113(m, d, __VA_ARGS__)
#define _ENUM_M115(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M114(m, d, __VA_ARGS__)
#define _ENUM_M116(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M115(m, d, __VA_ARGS__)
#define _ENUM_M117(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M116(m, d, __VA_ARGS__)
#define _ENUM_M118(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M117(m, d, __VA_ARGS__)
#define _ENUM_M119(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M118(m, d, __VA_ARGS__)
#define _ENUM_M120(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M119(m, d, __VA_ARGS__)
#define _ENUM_M121(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M120(m, d, __VA_ARGS__)
#define _ENUM_M122(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M121(m, d, __VA_ARGS__)
#define _ENUM_M123(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M122(m, d, __VA_ARGS__)
#define _ENUM_M124(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M123(m, d, __VA_ARGS__)
#define _ENUM_M125(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M124(m, d, __VA_ARGS__)
#define _ENUM_M126(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M125(m, d, __VA_ARGS__)
#define _ENUM_M127(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M126(m, d, __VA_ARGS__)
#define _ENUM_M128(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M127(m, d, __VA_ARGS__)
#define _ENUM_M129(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M128(m, d, __VA_ARGS__)
#define _ENUM_M130(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M129(m, d, __VA_ARGS__)
#define _ENUM_M131(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M130(m, d, __VA_ARGS__)
#define _ENUM_M132(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M131(m, d, __VA_ARGS__)
#define _ENUM_M133(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M132(m, d, __VA_ARGS__)
#define _ENUM_M134(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M133(m, d, __VA_ARGS__)
#define _ENUM_M135(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M134(m, d, __VA_ARGS__)
#define _ENUM_M136(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M135(m, d, __VA_ARGS__)
#define _ENUM_M137(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M136(m, d, __VA_ARGS__)
#define _ENUM_M138(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M137(m, d, __VA_ARGS__)
#define _ENUM_M139(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M138(m, d, __VA_ARGS__)
#define _ENUM_M140(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M139(m, d, __VA_ARGS__)
#define _ENUM_M141(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M140(m, d, __VA_ARGS__)
#define _ENUM_M142(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M141(m, d, __VA_ARGS__)
#define _ENUM_M143(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M142(m, d, __VA_ARGS__)
#define _ENUM_M144(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M143(m, d, __VA_ARGS__)
#define _ENUM_M145(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M144(m, d, __VA_ARGS__)
#define _ENUM_M146(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M145(m, d, __VA_ARGS__)
#define _ENUM_M147(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M146(m, d, __VA_ARGS__)
#define _ENUM_M148(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M147(m, d, __VA_ARGS__)
#define _ENUM_M149(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M148(m, d, __VA_ARGS__)
#define _ENUM_M150(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M149(m, d, __VA_ARGS__)
#define _ENUM_M151(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M150(m, d, __VA_ARGS__)
#define _ENUM_M152(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M151(m, d, __VA_ARGS__)
#define _ENUM_M153(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M152(m, d, __VA_ARGS__)
#define _ENUM_M154(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M153(m, d, __VA_ARGS__)
#define _ENUM_M155(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M154(m, d, __VA_ARGS__)
#define _ENUM_M156(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M155(m, d, __VA_ARGS__)
#define _ENUM_M157(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M156(m, d, __VA_ARGS__)
#define _ENUM_M158(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M157(m, d, __VA_ARGS__)
#define _ENUM_M159(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M158(m, d, __VA_ARGS__)
#define _ENUM_M160(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M159(m, d, __VA_ARGS__)
#define _ENUM_M161(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M160(m, d, __VA_ARGS__)
#define _ENUM_M162(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M161(m, d, __VA_ARGS__)
#define _ENUM_M163(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M162(m, d, __VA_ARGS__)
#define _ENUM_M164(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M163(m, d, __VA_ARGS__)
#define _ENUM_M165(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M164(m, d, __VA_ARGS__)
#define _ENUM_M166(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M165(m, d, __VA_ARGS__)
#define _ENUM_M167(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M166(m, d, __VA_ARGS__)
#define _ENUM_M168(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M167(m, d, __VA_ARGS__)
#define _ENUM_M169(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M168(m, d, __VA_ARGS__)
#define _ENUM_M170(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M169(m, d, __VA_ARGS__)
#define _ENUM_M171(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M170(m, d, __VA_ARGS__)
#define _ENUM_M172(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M171(m, d, __VA_ARGS__)
#define _ENUM_M173(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M172(m, d, __VA_ARGS__)
#define _ENUM_M174(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M173(m, d, __VA_ARGS__)
#define _ENUM_M175(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M174(m, d, __VA_ARGS__)
#define _ENUM_M176(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M175(m, d, __VA_ARGS__)
#define _ENUM_M177(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M176(m, d, __VA_ARGS__)
#define _ENUM_M178(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M177(m, d, __VA_ARGS__)
#define _ENUM_M179(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M178(m, d, __VA_ARGS__)
#define _ENUM_M180(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M179(m, d, __VA_ARGS__)
#define _ENUM_M181(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M180(m, d, __VA_ARGS__)
#define _ENUM_M182(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M181(m, d, __VA_ARGS__)
#define _ENUM_M183(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M182(m, d, __VA_ARGS__)
#define _ENUM_M184(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M183(m, d, __VA_ARGS__)
#define _ENUM_M185(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M184(m, d, __VA_ARGS__)
#define _ENUM_M186(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M185(m, d, __VA_ARGS__)
#define _ENUM_M187(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M186(m, d, __VA_ARGS__)
#define _ENUM_M188(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M187(m, d, __VA_ARGS__)
#define _ENUM_M189(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M188(m, d, __VA_ARGS__)
#define _ENUM_M190(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M189(m, d, __VA_ARGS__)
#define _ENUM_M191(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M190(m, d, __VA_ARGS__)
#define _ENUM_M192(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M191(m, d, __VA_ARGS__)
#define _ENUM_M193(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M192(m, d, __VA_ARGS__)
#define _ENUM_M194(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M193(m, d, __VA_ARGS__)
#define _ENUM_M195(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M194(m, d, __VA_ARGS__)
#define _ENUM_M196(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M195(m, d, __VA_ARGS__)
#define _ENUM_M197(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M196(m, d, __VA_ARGS__)
#define _ENUM_M198(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M197(m, d, __VA_ARGS__)
#define _ENUM_M199(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M198(m, d, __VA_ARGS__)
#define _ENUM_M200(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M199(m, d, __VA_ARGS__)
#define _ENUM_M201(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M200(m, d, __VA_ARGS__)
#define _ENUM_M202(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M201(m, d, __VA_ARGS__)
#define _ENUM_M203(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M202(m, d, __VA_ARGS__)
#define _ENUM_M204(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M203(m, d, __VA_ARGS__)
#define _ENUM_M205(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M204(m, d, __VA_ARGS__)
#define _ENUM_M206(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M205(m, d, __VA_ARGS__)
#define _ENUM_M207(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M206(m, d, __VA_ARGS__)
#define _ENUM_M208(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M207(m, d, __VA_ARGS__)
#define _ENUM_M209(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M208(m, d, __VA_ARGS__)
#define _ENUM_M210(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M209(m, d, __VA_ARGS__)
#define _ENUM_M211(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M210(m, d, __VA_ARGS__)
#define _ENUM_M212(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M211(m, d, __VA_ARGS__)
#define _ENUM_M213(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M212(m, d, __VA_ARGS__)
#define _ENUM_M214(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M213(m, d, __VA_ARGS__)
#define _ENUM_M215(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M214(m, d, __VA_ARGS__)
#define _ENUM_M216(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M215(m, d, __VA_ARGS__)
#define _ENUM_M217(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M216(m, d, __VA_ARGS__)
#define _ENUM_M218(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M217(m, d, __VA_ARGS__)
#define _ENUM_M219(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M218(m, d, __VA_ARGS__)
#define _ENUM_M220(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M219(m, d, __VA_ARGS__)
#define _ENUM_M221(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M220(m, d, __VA_ARGS__)
#define _ENUM_M222(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M221(m, d, __VA_ARGS__)
#define _ENUM_M223(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M222(m, d, __VA_ARGS__)
#define _ENUM_M224(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M223(m, d, __VA_ARGS__)
#define _ENUM_M225(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M224(m, d, __VA_ARGS__)
#define _ENUM_M226(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M225(m, d, __VA_ARGS__)
#define _ENUM_M227(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M226(m, d, __VA_ARGS__)
#define _ENUM_M228(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M227(m, d, __VA_ARGS__)
#define _ENUM_M229(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M228(m, d, __VA_ARGS__)
#define _ENUM_M230(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M229(m, d, __VA_ARGS__)
#define _ENUM_M231(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M230(m, d, __VA_ARGS__)
#define _ENUM_M232(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M231(m, d, __VA_ARGS__)
#define _ENUM_M233(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M232(m, d, __VA_ARGS__)
#define _ENUM_M234(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M233(m, d, __VA_ARGS__)
#define _ENUM_M235(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M234(m, d, __VA_ARGS__)
#define _ENUM_M236(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M235(m, d, __VA_ARGS__)
#define _ENUM_M237(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M236(m, d, __VA_ARGS__)
#define _ENUM_M238(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M237(m, d, __VA_ARGS__)
#define _ENUM_M239(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M238(m, d, __VA_ARGS__)
#define _ENUM_M240(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M239(m, d, __VA_ARGS__)
#define _ENUM_M241(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M240(m, d, __VA_ARGS__)
#define _ENUM_M242(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M241(m, d, __VA_ARGS__)
#define _ENUM_M243(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M242(m, d, __VA_ARGS__)
#define _ENUM_M244(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M243(m, d, __VA_ARGS__)
#define _ENUM_M245(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M244(m, d, __VA_ARGS__)
#define _ENUM_M246(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M245(m, d, __VA_ARGS__)
#define _ENUM_M247(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M246(m, d, __VA_ARGS__)
#define _ENUM_M248(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M247(m, d, __VA_ARGS__)
#define _ENUM_M249(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M248(m, d, __VA_ARGS__)
#define _ENUM_M250(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M249(m, d, __VA_ARGS__)
#define _ENUM_M251(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M250(m, d, __VA_ARGS__)
#define _ENUM_M252(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M251(m, d, __VA_ARGS__)
#define _ENUM_M253(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M252(m, d, __VA_ARGS__)
#define _ENUM_M254(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M253(m, d, __VA_ARGS__)
#define _ENUM_M255(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M254(m, d, __VA_ARGS__)
#define _ENUM_M256(m, d, x, ...) _ENUM_A(m, d, x), _ENUM_M255(m, d, __VA_ARGS__)

#define _ENUM_PP_COUNT_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
    _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
    _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, \
    _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, \
    _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, \
    _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, \
    _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101,    \
    _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113,    \
    _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125,    \
    _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137,    \
    _138, _139, _140, _141, _142, _143, _144, _145, _146, _147, _148, _149,    \
    _150, _151, _152, _153, _154, _155, _156, _157, _158, _159, _160, _161,    \
    _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, _173,    \
    _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185,    \
    _186, _187, _188, _189, _190, _191, _192, _193, _194, _195, _196, _197,    \
    _198, _199, _200, _201, _202, _203, _204, _205, _206, _207, _208, _209,    \
    _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, _221,    \
    _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233,    \
    _234, _235, _236, _237, _238, _239, _240, _241, _242, _243, _244, _245,    \
    _246, _247, _248, _249, _250, _251, _252, _253, _254, _255, _256, count,   \
    ...) count

#define _ENUM_PP_COUNT(...) _ENUM_PP_COUNT_IMPL(__VA_ARGS__, 256, 255, 254,    \
    253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, \
    238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, \
    223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, \
    208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, \
    193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, \
    178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, \
    163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, \
    148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, \
    133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, \
    118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, \
    103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86,\
    85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,\
    66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48,\
    47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,\
    28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,\
    9, 8, 7, 6, 5, 4, 3, 2, 1)

#endif // #ifdef BETTER_ENUM_PP_MAP_FILE



namespace _enum {



#define _ENUM_WEAK      __attribute__((weak))



template <typename EnumType, typename Iterator>
class _Iterable;

template <typename Derived>
class _BaseIterator {
  public:
    Derived& operator ++()
        { ++_index; return static_cast<Derived&>(*this); }
    constexpr bool operator ==(const Derived &other) const
        { return other._index == _index; }
    constexpr bool operator !=(const Derived &other) const
        { return other._index != _index; }

  protected:
    constexpr _BaseIterator(size_t index) : _index(index) { }

    size_t  _index;
};

template <typename EnumType>
class _ValueIterator :
    public _BaseIterator<_ValueIterator<EnumType>> {

    using _Super = _BaseIterator<_ValueIterator<EnumType>>;

  public:
    constexpr EnumType operator *() const
        { return EnumType::_value_array[_Super::_index]; }

  private:
    using _Super::_Super;

    friend _Iterable<EnumType, _ValueIterator<EnumType>>;
};

template <typename EnumType>
class _NameIterator :
    public _BaseIterator<_NameIterator<EnumType>> {

    using _Super = _BaseIterator<_NameIterator<EnumType>>;

  public:
    const char* operator *() const
        { return EnumType::_getProcessedName(_Super::_index); }

  private:
    using _Super::_Super;

    friend _Iterable<EnumType, _NameIterator<EnumType>>;
};

template <typename EnumType, typename Iterator>
class _Iterable {
  public:
    using iterator = Iterator;

    constexpr iterator begin() const { return iterator(0); }
    constexpr iterator end() const { return iterator(EnumType::_size); }
    constexpr size_t size() const { return EnumType::_size; }

  private:
    constexpr _Iterable() { };

    friend EnumType;
};



template <typename UnderlyingType>
class _eat_assign {
  private:
    UnderlyingType  _value;

  public:
    explicit constexpr _eat_assign(UnderlyingType value) : _value(value) { }
    template <typename Any>
    constexpr UnderlyingType operator =(Any dummy) const
        { return _value; }
    constexpr operator UnderlyingType () const { return _value; }
};

#define _ENUM_EAT_ASSIGN_SINGLE(UnderlyingType, expression)                    \
    ((_enum::_eat_assign<UnderlyingType>)expression)

#define _ENUM_EAT_ASSIGN(UnderlyingType, ...)                                  \
    _ENUM_PP_MAP(_ENUM_EAT_ASSIGN_SINGLE, UnderlyingType, __VA_ARGS__)



#define _ENUM_STRINGIZE_SINGLE(ignored, expression)     #expression

#define _ENUM_STRINGIZE(...)                                                   \
    _ENUM_PP_MAP(_ENUM_STRINGIZE_SINGLE, ignored, __VA_ARGS__)



#define _ENUM_NAME_ENDERS   "= \t\n"

constexpr bool _endsName(char c, size_t index = 0)
{
    return
        // First, test whether c is equal to the current character in
        // _ENUM_NAME_ENDERS. In the case where c is the null terminator, this
        // will cause _endsName to return true when it has exhausted
        // _ENUM_NAME_ENDERS.
        c == _ENUM_NAME_ENDERS[index]    ? true  :
        // If _ENUM_NAME_ENDERS has been exhausted and c never matched, return
        // false.
        _ENUM_NAME_ENDERS[index] == '\0' ? false :
        // Otherwise, go on to the next character in _ENUM_ENDERS.
        _endsName(c, index + 1);
}

constexpr char _toLowercaseAscii(char c)
{
    return c >= 0x41 && c <= 0x5A ? c + 0x20 : c;
}

constexpr bool _namesMatch(const char *stringizedName,
                           const char *referenceName,
                           size_t index = 0)
{
    return
        // If the current character in the stringized name is a name ender,
        // return true if the reference name ends as well, and false otherwise.
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        // The current character in the stringized name is not a name ender. If
        // the reference name ended, then it is too short, so return false.
        referenceName[index] == '\0'     ? false                        :
        // Neither name has ended. If the two current characters don't match,
        // return false.
        stringizedName[index] !=
            referenceName[index]         ? false                        :
        // Otherwise, if the characters match, continue by comparing the rest of
        // the names.
        _namesMatch(stringizedName, referenceName, index + 1);
}

constexpr bool _namesMatchNocase(const char *stringizedName,
                                 const char *referenceName,
                                 size_t index = 0)
{
    return
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        referenceName[index] == '\0' ? false :
        _toLowercaseAscii(stringizedName[index]) !=
            _toLowercaseAscii(referenceName[index]) ? false :
        _namesMatchNocase(stringizedName, referenceName, index + 1);
}



template <typename UnderlyingType>
constexpr UnderlyingType _findMinLoop(const UnderlyingType *values,
                                      size_t valueCount, size_t index,
                                      UnderlyingType best)
{
    return
        index == valueCount ? best :
        values[index] < best ?
            _findMinLoop(values, valueCount, index + 1, values[index]) :
            _findMinLoop(values, valueCount, index + 1, best);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMin(const UnderlyingType *values,
                                  size_t valueCount)
{
    return _findMinLoop(values, valueCount, 1, values[0]);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMaxLoop(const UnderlyingType *values,
                                      size_t valueCount, size_t index,
                                      UnderlyingType best)
{
    return
        index == valueCount ? best :
        values[index] > best ?
            _findMaxLoop(values, valueCount, index + 1, values[index]) :
            _findMaxLoop(values, valueCount, index + 1, best);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMax(const UnderlyingType *values, size_t count)
{
    return _findMaxLoop(values, count, 1, values[0]);
}



static inline const char * const* _processNames(const char * const *rawNames,
                                                size_t count)
{
    // Allocate the replacement names array.
    const char      **processedNames = new const char*[count];
    if (processedNames == nullptr)
        return nullptr;

    // Count the number of bytes needed in the replacement names array (an upper
    // bound).
    size_t          bytesNeeded = 0;
    for (size_t index = 0; index < count; ++index)
        bytesNeeded += std::strlen(rawNames[index]) + 1;

    // Allocate memory for the string data.
    char            *nameStorage = new char[bytesNeeded];
    if (nameStorage == nullptr) {
        delete[] processedNames;
        return nullptr;
    }

    // Trim each name and place the result in storage, then save a pointer to
    // it.
    char            *writePointer = nameStorage;
    for (size_t index = 0; index < count; ++index) {
        const char  *nameEnd =
            std::strpbrk(rawNames[index], _ENUM_NAME_ENDERS);

        size_t      symbolCount =
            nameEnd == nullptr ?
                std::strlen(rawNames[index]) :
                nameEnd - rawNames[index];

        std::strncpy(writePointer, rawNames[index], symbolCount);
        processedNames[index] = writePointer;
        writePointer += symbolCount;

        *writePointer = '\0';
        ++writePointer;
    }

    return processedNames;
}

#define _ENUM_TAG(EnumType)     _tag_ ## EnumType
#define _ENUM_TAG_DECLARATION(EnumType)                                        \
    namespace _enum {                                                          \
        struct _ENUM_TAG(EnumType);                                            \
    }

template <typename Tag> class _GeneratedArrays;

#define _ENUM_ARRAYS(EnumType, Integral, Tag, ...)                             \
    namespace _enum {                                                          \
                                                                               \
    template <>                                                                \
    class _GeneratedArrays<Tag> {                                              \
      protected:                                                               \
        using _Integral = Integral;                                            \
                                                                               \
      public:                                                                  \
        constexpr static const char* _name = #EnumType;                        \
                                                                               \
        enum _Enumerated : _Integral { __VA_ARGS__ };                          \
                                                                               \
      protected:                                                               \
        constexpr static _Enumerated        _value_array[] =                   \
            { _ENUM_EAT_ASSIGN(_Enumerated, __VA_ARGS__) };                    \
                                                                               \
        constexpr static const char         *_name_array[] =                   \
            { _ENUM_STRINGIZE(__VA_ARGS__) };                                  \
    };                                                                         \
                                                                               \
    }

#define _ENUM_NOT_FOUND     ((size_t)-1)

template <typename Tag>
class _Enum : public _GeneratedArrays<Tag> {
  protected:
    using _arrays = _GeneratedArrays<Tag>;
    using _arrays::_value_array;
    using _arrays::_name_array;

  public:
    using typename _arrays::_Enumerated;
    using typename _arrays::_Integral;

    constexpr static const size_t       _size =
        sizeof(_value_array) / sizeof(_Enumerated);
    static_assert(_size > 0, "no constants defined in enum type");

    constexpr static const _Enumerated  _first = _value_array[0];
    constexpr static const _Enumerated  _last = _value_array[_size - 1];
    constexpr static const _Enumerated  _min = _findMin(_value_array, _size);
    constexpr static const _Enumerated  _max = _findMax(_value_array, _size);

    constexpr static const _Integral    _span = _max - _min + 1;

    _Enum() = delete;
    constexpr _Enum(_Enumerated constant) : _value(constant) { }

    constexpr _Integral to_integral() const
    {
        return _value;
    }

    constexpr static const _Enum _from_integral(_Integral value)
    {
        return _value_array[_from_int_loop(value, true)];
    }

    constexpr static const _Enum _from_integral_unchecked(_Integral value)
    {
        return (_Enumerated)value;
    }

    const char* to_string() const
    {
        _processNames();

        for (size_t index = 0; index < _size; ++index) {
            if (_value_array[index] == _value)
                return _processedNames[index];
        }

        throw std::domain_error("Enum::_to_string: invalid enum value");
    }

    constexpr static const _Enum _from_string(const char *name)
    {
        return _value_array[_from_string_loop(name, true)];
    }

    constexpr static const _Enum _from_string_nocase(const char *name)
    {
        return _value_array[_from_string_nocase_loop(name, true)];
    }

    constexpr static bool _is_valid(_Integral value)
    {
        return _from_int_loop(value, false) != _ENUM_NOT_FOUND;
    }

    constexpr static bool _is_valid(const char *name)
    {
        return _from_string_loop(name, false) != _ENUM_NOT_FOUND;
    }

    constexpr static bool _is_valid_nocase(const char *name)
    {
        return _from_string_nocase_loop(name, false) != _ENUM_NOT_FOUND;
    }

    constexpr operator _Enumerated() const { return _value; }

  protected:
    _Enumerated                         _value;

    static const char * const           *_processedNames;

    static void _processNames()
    {
        if (_processedNames == nullptr)
            _processedNames = _enum::_processNames(_name_array, _size);
    }

    static const char* _getProcessedName(size_t index)
    {
        _processNames();
        return _processedNames[index];
    }

    using _ValueIterable = _Iterable<_Enum, _ValueIterator<_Enum>>;
    using _NameIterable  = _Iterable<_Enum, _NameIterator<_Enum>>;

    friend _ValueIterator<_Enum>;
    friend _NameIterator<_Enum>;

  public:
    static const _ValueIterable     _values;
    static const _NameIterable      _names;

  protected:
    constexpr static size_t _from_int_loop(_Integral value,
                                           bool throw_exception,
                                           size_t index = 0)
    {
        return
            index == _size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "Enum::_from_integral: invalid integer value") :
                    _ENUM_NOT_FOUND) :
            _value_array[index] == value ? index :
            _from_int_loop(value, throw_exception, index + 1);
    }

    constexpr static size_t _from_string_loop(const char *name,
                                              bool throw_exception,
                                              size_t index = 0)
    {
        return
            index == _size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "Enum::_from_string: invalid string argument") :
                    _ENUM_NOT_FOUND) :
            _namesMatch(_name_array[index], name) ? index :
            _from_string_loop(name, throw_exception, index + 1);
    }

    constexpr static size_t _from_string_nocase_loop(const char *name,
                                                     bool throw_exception,
                                                     size_t index = 0)
    {
        return
            index == _size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "Enum::_from_string_nocase: invalid string argument") :
                    _ENUM_NOT_FOUND) :
                _namesMatchNocase(_name_array[index], name) ? index :
                _from_string_nocase_loop(name, throw_exception, index + 1);
    }

  public:
    constexpr bool operator ==(const _Enum &other) const
        { return _value == other._value; }
    constexpr bool operator ==(const _Enumerated value) const
        { return _value == value; }
    template <typename T> bool operator ==(T other) const = delete;

    constexpr bool operator !=(const _Enum &other) const
        { return !(*this == other); }
    constexpr bool operator !=(const _Enumerated value) const
        { return !(*this == value); }
    template <typename T> bool operator !=(T other) const = delete;

    constexpr bool operator <(const _Enum &other) const
        { return _value < other._value; }
    constexpr bool operator <(const _Enumerated value) const
        { return _value < value; }
    template <typename T> bool operator <(T other) const = delete;

    constexpr bool operator <=(const _Enum &other) const
        { return _value <= other._value; }
    constexpr bool operator <=(const _Enumerated value) const
        { return _value <= value; }
    template <typename T> bool operator <=(T other) const = delete;

    constexpr bool operator >(const _Enum &other) const
        { return _value > other._value; }
    constexpr bool operator >(const _Enumerated value) const
        { return _value > value; }
    template <typename T> bool operator >(T other) const = delete;

    constexpr bool operator >=(const _Enum &other) const
        { return _value >= other._value; }
    constexpr bool operator >=(const _Enumerated value) const
        { return _value >= value; }
    template <typename T> bool operator >=(T other) const = delete;

    int operator -() const = delete;
    template <typename T> int operator +(T other) const = delete;
    template <typename T> int operator -(T other) const = delete;
    template <typename T> int operator *(T other) const = delete;
    template <typename T> int operator /(T other) const = delete;
    template <typename T> int operator %(T other) const = delete;

    template <typename T> int operator <<(T other) const = delete;
    template <typename T> int operator >>(T other) const = delete;

    int operator ~() const = delete;
    template <typename T> int operator &(T other) const = delete;
    template <typename T> int operator |(T other) const = delete;
    template <typename T> int operator ^(T other) const = delete;

    int operator !() const = delete;
    template <typename T> int operator &&(T other) const = delete;
    template <typename T> int operator ||(T other) const = delete;
};

#define _ENUM_GLOBALS(EnumType, Tag)                                           \
    namespace _enum {                                                          \
                                                                               \
    constexpr const EnumType operator +(EnumType::_Enumerated enumerated)      \
        { return (EnumType)enumerated; }                                       \
                                                                               \
    template <>                                                                \
    constexpr EnumType::_ValueIterable _ENUM_WEAK EnumType::_values{};         \
                                                                               \
    template <>                                                                \
    constexpr EnumType::_NameIterable _ENUM_WEAK EnumType::_names{};           \
                                                                               \
    constexpr _GeneratedArrays<Tag>::_Enumerated _ENUM_WEAK                    \
        _GeneratedArrays<Tag>::_value_array[];                                 \
                                                                               \
    constexpr const char * _ENUM_WEAK _GeneratedArrays<Tag>::_name_array[];    \
                                                                               \
    template <>                                                                \
    const char * const * _ENUM_WEAK EnumType::_processedNames = nullptr;       \
                                                                               \
    }

} // namespace _enum

#define ENUM(EnumType, Integral, ...)                                          \
    _ENUM_TAG_DECLARATION(EnumType);                                           \
    _ENUM_ARRAYS(EnumType, Integral, _ENUM_TAG(EnumType), __VA_ARGS__);        \
    using EnumType = _enum::_Enum<_enum::_ENUM_TAG(EnumType)>;                 \
    _ENUM_GLOBALS(EnumType, _ENUM_TAG(EnumType));



#endif // #ifndef _BETTER_ENUM_ENUM_H_
