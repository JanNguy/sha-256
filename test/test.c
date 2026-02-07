#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

char **const_adress(void);

// ========================== TESTS add32 ==========================
Test(add32, basic_addition)
{
    cr_assert_eq(add32(1, 2), 3);
    cr_assert_eq(add32(0, 0), 0);
    cr_assert_eq(add32(100, 200), 300);
}

Test(add32, overflow_wraps)
{
    cr_assert_eq(add32(0xFFFFFFFF, 1), 0);
    cr_assert_eq(add32(0xFFFFFFFF, 2), 1);
}

Test(add32, max_values)
{
    cr_assert_eq(add32(0x80000000, 0x80000000), 0);
}

// ========================== TESTS and32 ==========================
Test(and32, basic_and)
{
    cr_assert_eq(and32(0xFF, 0x0F), 0x0F);
    cr_assert_eq(and32(0xFFFFFFFF, 0x00000000), 0x00000000);
    cr_assert_eq(and32(0xAAAAAAAA, 0x55555555), 0x00000000);
}

Test(and32, same_value)
{
    cr_assert_eq(and32(0x12345678, 0x12345678), 0x12345678);
}

Test(and32, all_ones)
{
    cr_assert_eq(and32(0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF);
}

// ========================== TESTS or32 ==========================
Test(or32, basic_or)
{
    cr_assert_eq(or32(0xF0, 0x0F), 0xFF);
    cr_assert_eq(or32(0x00000000, 0xFFFFFFFF), 0xFFFFFFFF);
    cr_assert_eq(or32(0xAAAAAAAA, 0x55555555), 0xFFFFFFFF);
}

Test(or32, zero_values)
{
    cr_assert_eq(or32(0x00000000, 0x00000000), 0x00000000);
}

Test(or32, same_value)
{
    cr_assert_eq(or32(0x12345678, 0x12345678), 0x12345678);
}

// ========================== TESTS xor32 ==========================
Test(xor32, basic_xor)
{
    cr_assert_eq(xor32(0xFF, 0xFF), 0x00);
    cr_assert_eq(xor32(0xFF, 0x00), 0xFF);
    cr_assert_eq(xor32(0xAAAAAAAA, 0x55555555), 0xFFFFFFFF);
}

Test(xor32, self_xor_is_zero)
{
    cr_assert_eq(xor32(0x12345678, 0x12345678), 0x00000000);
}

Test(xor32, xor_with_zero)
{
    cr_assert_eq(xor32(0xDEADBEEF, 0x00000000), 0xDEADBEEF);
}

// ========================== TESTS not32 ==========================
Test(not32, basic_not)
{
    cr_assert_eq(not32(0x00000000), 0xFFFFFFFF);
    cr_assert_eq(not32(0xFFFFFFFF), 0x00000000);
    cr_assert_eq(not32(0xAAAAAAAA), 0x55555555);
}

Test(not32, double_not_is_identity)
{
    cr_assert_eq(not32(not32(0x12345678)), 0x12345678);
}

// ========================== TESTS shr32 ==========================
Test(shr32, basic_shift)
{
    cr_assert_eq(shr32(0x80000000, 1), 0x40000000);
    cr_assert_eq(shr32(0xFF, 4), 0x0F);
    cr_assert_eq(shr32(0x12345678, 0), 0x12345678);
}

Test(shr32, shift_all_bits)
{
    cr_assert_eq(shr32(0xFFFFFFFF, 32), 0x00000000);
}

Test(shr32, shift_by_16)
{
    cr_assert_eq(shr32(0xFFFF0000, 16), 0x0000FFFF);
}

// ========================== TESTS rotl32 ==========================
Test(rotl32, basic_rotate_left)
{
    cr_assert_eq(rotl32(0x80000000, 1), 0x00000001);
    cr_assert_eq(rotl32(0x00000001, 1), 0x00000002);
}

Test(rotl32, rotate_by_4)
{
    cr_assert_eq(rotl32(0xF0000000, 4), 0x0000000F);
}

Test(rotl32, zero_rotation)
{
    cr_assert_eq(rotl32(0xDEADBEEF, 0), 0xDEADBEEF);
}

Test(rotl32, rotate_by_8)
{
    cr_assert_eq(rotl32(0x12345678, 8), 0x34567812);
}

// ========================== TESTS rotr32 ==========================
Test(rotr32, basic_rotate_right)
{
    cr_assert_eq(rotr32(0x00000001, 1), 0x80000000);
    cr_assert_eq(rotr32(0x80000000, 1), 0x40000000);
}

Test(rotr32, rotate_by_8)
{
    cr_assert_eq(rotr32(0x12345678, 8), 0x78123456);
}

Test(rotr32, rotate_by_4)
{
    cr_assert_eq(rotr32(0x0000000F, 4), 0xF0000000);
}

Test(rotr32, zero_rotation)
{
    cr_assert_eq(rotr32(0xDEADBEEF, 0), 0xDEADBEEF);
}

// ========================== TESTS isPrime ==========================
Test(isPrime, small_primes)
{
    cr_assert_eq(isPrime(2), 1);
    cr_assert_eq(isPrime(3), 1);
    cr_assert_eq(isPrime(5), 1);
    cr_assert_eq(isPrime(7), 1);
    cr_assert_eq(isPrime(11), 1);
    cr_assert_eq(isPrime(13), 1);
}

Test(isPrime, non_primes)
{
    cr_assert_eq(isPrime(0), 0);
    cr_assert_eq(isPrime(1), 0);
    cr_assert_eq(isPrime(4), 0);
    cr_assert_eq(isPrime(6), 0);
    cr_assert_eq(isPrime(9), 0);
    cr_assert_eq(isPrime(15), 0);
}

Test(isPrime, negative_numbers)
{
    cr_assert_eq(isPrime(-1), 0);
    cr_assert_eq(isPrime(-5), 0);
}

Test(isPrime, larger_primes)
{
    cr_assert_eq(isPrime(97), 1);
    cr_assert_eq(isPrime(101), 1);
    cr_assert_eq(isPrime(127), 1);
}

// ========================== TESTS ch32 ==========================
Test(ch32, basic_choice)
{
    // ch(x, y, z) = (x AND y) XOR ((NOT x) AND z)
    cr_assert_eq(ch32(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555), 0xAAAAAAAA);
    cr_assert_eq(ch32(0x00000000, 0xAAAAAAAA, 0x55555555), 0x55555555);
}

Test(ch32, mixed_bits)
{
    // Si x = 0xF0F0F0F0, les bits à 1 choisissent y, les bits à 0 choisissent z
    uint32_t result = ch32(0xF0F0F0F0, 0xFFFFFFFF, 0x00000000);
    cr_assert_eq(result, 0xF0F0F0F0);
}

Test(ch32, all_zeros)
{
    cr_assert_eq(ch32(0x00000000, 0x00000000, 0x00000000), 0x00000000);
}

// ========================== TESTS maj32 ==========================
Test(maj32, basic_majority)
{
    // maj(x, y, z) = bit majoritaire parmi x, y, z
    cr_assert_eq(maj32(0xFFFFFFFF, 0xFFFFFFFF, 0x00000000), 0xFFFFFFFF);
    cr_assert_eq(maj32(0x00000000, 0x00000000, 0xFFFFFFFF), 0x00000000);
}

Test(maj32, all_same)
{
    cr_assert_eq(maj32(0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA), 0xAAAAAAAA);
}

Test(maj32, two_of_three)
{
    cr_assert_eq(maj32(0xFFFFFFFF, 0xFFFFFFFF, 0x00000000), 0xFFFFFFFF);
    cr_assert_eq(maj32(0xFFFFFFFF, 0x00000000, 0xFFFFFFFF), 0xFFFFFFFF);
    cr_assert_eq(maj32(0x00000000, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF);
}

// ========================== TESTS bigSigma0 ==========================
Test(bigSigma0, zero_input)
{
    cr_assert_eq(bigSigma0(0x00000000), 0x00000000);
}

Test(bigSigma0, all_ones)
{
    cr_assert_eq(bigSigma0(0xFFFFFFFF), 0xFFFFFFFF);
}

// ========================== TESTS bigSigma1 ==========================
Test(bigSigma1, zero_input)
{
    cr_assert_eq(bigSigma1(0x00000000), 0x00000000);
}

Test(bigSigma1, all_ones)
{
    cr_assert_eq(bigSigma1(0xFFFFFFFF), 0xFFFFFFFF);
}

// ========================== TESTS smallSigma0 ==========================
Test(smallSigma0, zero_input)
{
    cr_assert_eq(smallSigma0(0x00000000), 0x00000000);
}

// ========================== TESTS smallSigma1 ==========================
Test(smallSigma1, zero_input)
{
    cr_assert_eq(smallSigma1(0x00000000), 0x00000000);
}

// ========================== TESTS const_adress ==========================
Test(const_adress, returns_valid_array)
{
    char **result = const_adress();
    cr_assert_not_null(result);

    // Vérifier qu'il y a 8 entrées + NULL
    int count = 0;
    while (result[count] != NULL) {
        count++;
    }
    cr_assert_eq(count, 8);

    // Libérer la mémoire
    for (int i = 0; i < 8; i++) {
        free(result[i]);
    }
    free(result);
}

Test(const_adress, valid_hex_format)
{
    char **result = const_adress();
    cr_assert_not_null(result);

    // Chaque entrée doit être une chaîne hexadécimale de 8 caractères
    for (int i = 0; i < 8; i++) {
        cr_assert_not_null(result[i]);
        cr_assert_eq(strlen(result[i]), 8);

        // Vérifier que ce sont des caractères hexadécimaux
        for (int j = 0; j < 8; j++) {
            char c = result[i][j];
            int is_hex = (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
            cr_assert(is_hex, "Character '%c' is not hexadecimal", c);
        }
    }

    // Libérer la mémoire
    for (int i = 0; i < 8; i++) {
        free(result[i]);
    }
    free(result);
}

Test(const_adress, known_sha256_constants)
{
    char **result = const_adress();
    cr_assert_not_null(result);

    // Les 8 premières constantes SHA-256 (parties fractionnaires des racines carrées)
    // des 8 premiers nombres premiers: 2, 3, 5, 7, 11, 13, 17, 19
    const char *expected[] = {
        "6A09E667", // sqrt(2)
        "BB67AE85", // sqrt(3)
        "3C6EF372", // sqrt(5)
        "A54FF53A", // sqrt(7)
        "510E527F", // sqrt(11)
        "9B05688C", // sqrt(13)
        "1F83D9AB", // sqrt(17)
        "5BE0CD19"  // sqrt(19)
    };

    for (int i = 0; i < 8; i++) {
        cr_assert_str_eq(result[i], expected[i],
            "Constante %d incorrecte: attendu %s, obtenu %s", i, expected[i], result[i]);
    }

    // Libérer la mémoire
    for (int i = 0; i < 8; i++) {
        free(result[i]);
    }
    free(result);
}

Test(const_adress, null_terminated)
{
    char **result = const_adress();
    cr_assert_not_null(result);
    cr_assert_null(result[8]);

    // Libérer la mémoire
    for (int i = 0; i < 8; i++) {
        free(result[i]);
    }
    free(result);
}