// Copyright (c) 2025 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      utils.h
*@brief     Utilities/supporting functions and definitoins
*@author    Ziga Miklosic
*@email     ziga.miklosic@gmail.com
*@version   V0.1.0
*/
////////////////////////////////////////////////////////////////////////////////
/*!
* @addtogroup UTILS
* @{ <!-- BEGIN GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __UTILS_H
#define __UTILS_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 *  Module version
 */
#define UTILS_VER_MAJOR          ( 0 )
#define UTILS_VER_MINOR          ( 1 )
#define UTILS_VER_DEVELOP        ( 0 )

#ifndef ARRAY_SIZE
/**
 * Get size [element] of statically allocated array
 * 
 * @param[in]	array   - Array
 * @return      Size [element]
 */
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))
#endif

#ifndef UNUSED
/**
 * Mark variable as unused
 *
 * This macro will mark variable or function argument as unused preventing
 * compiler from emitting related warning.
 * 
 * @param[in]	x   - Variable
 */
#define UNUSED(x)   ((void)(x))
#endif

#ifndef STATIC_ASSERT
/**
 * Compile-time assertion provided by C11
 *
 * @param[in]	cond    - Condition to evaluate
 * @param[in]   msg     - Message
 */
#define STATIC_ASSERT(cond, msg)    _Static_assert(cond, msg)
#endif

/**
 * Compile-time assert numeric types match.
 * 
 * See: https://stackoverflow.com/a/64911/1806687
 *
 * @param[in]	type1   First numeric type.
 * @param[in]   type2   Second numeric type.
 */
#define STATIC_ASSERT_TYPES(type1, type2)                                                                                                                                               \
    /* Suppress "comparison is always false/true" compiler warning */                                                                                                                   \
    COMPILER_WARN_IGNORE("-Wtype-limits")                                                                                                                                               \
    STATIC_ASSERT((sizeof(type1) == sizeof(type2)) && ((IS_SIGNED_TYPE(type1) && IS_SIGNED_TYPE(type2)) || (IS_UNSIGNED_TYPE(type1) && IS_UNSIGNED_TYPE(type2))), "Types mismatched");  \
    COMPILER_WARN_RESTORE()

#ifndef MAX
/**
 * Get maximum of two values.
 *
 * @param[in]	a   First value.
 * @param[in]   b   Second value.
 * @return      Maximum of two values.
 */
#define MAX(a, b)   (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
/**
 * Get minimum of two values.
 *
 * @param[in]	a   First value.
 * @param[in]   b   Second value.
 * @return      Minimum of two values.
 */
#define MIN(a, b)   (((a) < (b)) ? (a) : (b))
#endif

#ifndef STRINGIFY
/**
 * Stringify preprocessor token.
 *
 * @param[in]	x   Token.
 * @return      String.
 */
#define STRINGIFY(x)    #x
#endif

#ifdef __GNUC__
#define COMPILER_WARN_IGNORE(warns)                     \
    _Pragma(STRINGIFY(GCC diagnostic push))             \
    _Pragma(STRINGIFY(GCC diagnostic ignored warns))

#define COMPILER_WARN_RESTORE() _Pragma(STRINGIFY(GCC diagnostic pop))
#endif

/**
 * Get member size of structure or union
 *
 * See https://stackoverflow.com/questions/3553296/sizeof-single-struct-member-in-c
 *
 * @param[in]	type    - Type of structure
 * @param[in]	member  - Name of member
 */
#define SIZE_OF(type, member)	(sizeof(((type *)0)->member))

/**
 * Macro to set nth-bit
 *
 * @param[in]    pos - Set single bit at pos to '1' by generating a mask
 */
#define SET_BIT_MASK(pos)    (1U << pos)

/**
 *  Function to set bit
 */
#define UTILS_SET_BIT( val, bit_nmb )             (( val ) |= ( 1U << bit_nmb ))

/**
 *  Function to clear bit
 */
#define UTILS_CLEAR_BIT( val, bit_nmb )           (( val &= ~ ( 1 << bit_nmb)))

/**
 * Get number of bits required to represent maximum value
 * 
 * Value must be of the form: (1 << k) - 1 where 0 <= k < 2040.
 * 
 * See: https://stackoverflow.com/a/4589384/1806687
 * 
 * @param[in]   x   - Value.
 * @return      Number of bits.
 */
#define MAX_BITS(x) (((((x) / (((x) % 255) + 1) / 255) % 255) * 8) + 7 - (86 / (((x) % 255) + 12)))

/**
 * Get position of set bit
 * 
 * Value must be of the form: (1 << k) where 0 <= k < 2040.
 * 
 * @param[in]   x   - Value.
 * @return      Bit position.
 */
#define BIT_POSITION(x) MAX_BITS((x) - 1)

/**
 * Maximum unsigned integer representable with n bits
 *
 * @param[in]   n   - Number of bits.
 * @return      Maximum unsigned integer.
 */
#define UINT_MAX(n) ((1 << ((n) - 1)) | ((1 << ((n) - 1)) - 1))

/**
 * Size of object in bits
 *
 * @param[in]   x   - Object.
 * @return      Size [bit].
 */
#define SIZEOF_BITS(x)  (sizeof(x) * 8)

/**
 * Check if numeric type is signed
 * 
 * @param[in]   type    - Numeric type.
 * @return      True if signed, false otherwise.
 */
#define IS_SIGNED_TYPE(type) ((type)-1 < 0)

/**
 * Check if numeric type is unsigned
 * 
 * @param[in]   type    - Numeric type.
 * @return      True if unsigned, false otherwise.
 */
#define IS_UNSIGNED_TYPE(type) (IS_SIGNED_TYPE(type) != true)

/**
 * Check if integer is even
 * 
 * @param[in]   x   - Integer.
 * @return      True if even, false otherwise.
 */
#define IS_EVEN(x)  (((x) & 0x1) == 0)

/**
 * Check if integer is odd
 * 
 * @param[in]   x   - Integer.
 * @return      True if odd, false otherwise.
 */
#define IS_ODD(x)  (!IS_EVEN(x))

/**
 * Maximum positive integer range that can be exactly represented without gaps
 *
 * Integers in range [-X, X], where X is this value, can be exactly represented
 * by 32-bit float.
 */
#define F32_MAX_INT_RANGE   (1U << 24)

/**
 * 32-bit floating point type.
 */
typedef float float32_t;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
* Get maximum of two signed 32-bit integers
*
* @param[in]    a   - First integer
* @param[in]    b   - Second integer
* @return       max - Maximum integer
*/
////////////////////////////////////////////////////////////////////////////////
static inline int32_t max_i32(const int32_t a, const int32_t b)
{
    return MAX(a, b);
}

////////////////////////////////////////////////////////////////////////////////
/**
* Get minimum of two signed 32-bit integers
*
* @param[in]    a   - First integer
* @param[in]    b   - Second integer
* @return       min - Minimum integer
*/
////////////////////////////////////////////////////////////////////////////////
static inline int32_t min_i32(const int32_t a, const int32_t b)
{
    return MIN(a, b);
}

////////////////////////////////////////////////////////////////////////////////
/**
* Get maximum of two unsigned 32-bit integers
*
* @param[in]    a   - First integer
* @param[in]    b   - Second integer
* @return       max - Maximum integer
*/
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t max_u32(const uint32_t a, const uint32_t b)
{
    return MAX(a, b);
}

////////////////////////////////////////////////////////////////////////////////
/**
* Get minimum of two unsigned 32-bit integers
*
* @param[in]    a   - First integer
* @param[in]    b   - Second integer
* @return       min - Minimum integer
*/
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t min_u32(const uint32_t a, const uint32_t b)
{
    return MIN(a, b);
}

////////////////////////////////////////////////////////////////////////////////
/**
*       Calculate CRC-8
*
* @param[in]    p_data  - Pointer to data
* @param[in]    size    - Size of data to calc crc
* @param[in]    poly    - CRC polynomial
* @param[in]    seed    - CRC seed
* @return       crc8    - Calculated CRC
*/
////////////////////////////////////////////////////////////////////////////////
static inline uint8_t crc8_calc(const uint8_t * const p_data, const uint16_t size, const uint8_t poly, const uint8_t seed)
{
    uint8_t crc8 = seed;

    for (uint16_t i = 0; i < size; i++)
    {
        crc8 = ( crc8 ^ p_data[i] );

        for (uint16_t j = 0U; j < 8U; j++)
        {
            if ( crc8 & 0x80U )
            {
                crc8 = (( crc8 << 1U ) ^ poly );
            }
            else
            {
                crc8 = ( crc8 << 1U );
            }
        }
    }

    return crc8;
}

////////////////////////////////////////////////////////////////////////////////
/**
* Get number of leading 0's starting from MSb
*
* @param[in]    x   - Value
* @return       clz - Number of 0's
*/
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t clz32(uint32_t x)
{
    return (uint32_t)__builtin_clz(x);
}

////////////////////////////////////////////////////////////////////////////////
/**
* Get number of trailing 0's starting from LSb
*
* @param[in]    x   - Value
* @return       ctz - Number of 0's
*/
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t ctz32(uint32_t x)
{
    return (uint32_t)__builtin_ctz(x);
}

#endif // __UTILS_H

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
