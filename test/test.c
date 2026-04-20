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

Test(shr32, shift_by_31)
{
    cr_assert_eq(shr32(0xFFFFFFFF, 31), 0x00000001);
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

// ==========================================================================
// =================== TESTS SUPPLEMENTAIRES ================================
// ==========================================================================

// ========================== TESTS init_h ==========================
Test(init_h, returns_non_null)
{
    uint32_t *h = init_h();
    cr_assert_not_null(h, "init_h doit retourner un pointeur valide");
    free(h);
}

Test(init_h, correct_initial_values)
{
    // Valeurs SHA-256 standard : parties fractionnaires de sqrt(premiers)
    uint32_t expected[8] = {
        0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
        0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
    };
    uint32_t *h = init_h();
    cr_assert_not_null(h);

    for (int i = 0; i < 8; i++) {
        cr_assert_eq(h[i], expected[i],
            "init_h[%d]: attendu 0x%08X, obtenu 0x%08X", i, expected[i], h[i]);
    }
    free(h);
}

Test(init_h, each_value_distinct)
{
    uint32_t *h = init_h();
    cr_assert_not_null(h);

    // Toutes les valeurs initiales doivent être distinctes
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            cr_assert_neq(h[i], h[j],
                "init_h[%d] et init_h[%d] ne devraient pas être égaux (0x%08X)",
                i, j, h[i]);
        }
    }
    free(h);
}

Test(init_h, multiple_calls_same_values)
{
    uint32_t *h1 = init_h();
    uint32_t *h2 = init_h();
    cr_assert_not_null(h1);
    cr_assert_not_null(h2);

    for (int i = 0; i < 8; i++) {
        cr_assert_eq(h1[i], h2[i],
            "Deux appels à init_h doivent retourner les mêmes valeurs");
    }
    free(h1);
    free(h2);
}

// ========================== TESTS init_k ==========================
Test(init_k, returns_non_null)
{
    uint32_t *k = init_k();
    cr_assert_not_null(k, "init_k doit retourner un pointeur valide");
    free(k);
}

Test(init_k, correct_count)
{
    // init_k doit retourner 64 constantes
    uint32_t *k = init_k();
    cr_assert_not_null(k);
    // On vérifie juste que l'allocation est de 64 éléments via
    // les valeurs connues aux extrémités
    cr_assert_eq(k[0], 0x428A2F98, "k[0] attendu 0x428A2F98, obtenu 0x%08X", k[0]);
    cr_assert_eq(k[63], 0xC67178F2, "k[63] attendu 0xC67178F2, obtenu 0x%08X", k[63]);
    free(k);
}

Test(init_k, first_16_constants)
{
    // Les 16 premières constantes SHA-256 (cbrt des 16 premiers premiers)
    uint32_t expected[16] = {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
        0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
        0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
        0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174
    };
    uint32_t *k = init_k();
    cr_assert_not_null(k);

    for (int i = 0; i < 16; i++) {
        cr_assert_eq(k[i], expected[i],
            "init_k[%d]: attendu 0x%08X, obtenu 0x%08X", i, expected[i], k[i]);
    }
    free(k);
}

Test(init_k, last_16_constants)
{
    // Les 16 dernières constantes SHA-256 (cbrt des premiers 227..311)
    uint32_t expected[16] = {
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
        0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
        0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
        0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
    };
    uint32_t *k = init_k();
    cr_assert_not_null(k);

    for (int i = 0; i < 16; i++) {
        cr_assert_eq(k[48 + i], expected[i],
            "init_k[%d]: attendu 0x%08X, obtenu 0x%08X",
            48 + i, expected[i], k[48 + i]);
    }
    free(k);
}

Test(init_k, all_64_known_values)
{
    uint32_t expected[64] = {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
        0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
        0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
        0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
        0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
        0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
        0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
        0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
        0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
        0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
        0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
        0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
        0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
        0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
        0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
    };
    uint32_t *k = init_k();
    cr_assert_not_null(k);

    for (int i = 0; i < 64; i++) {
        cr_assert_eq(k[i], expected[i],
            "init_k[%d]: attendu 0x%08X, obtenu 0x%08X", i, expected[i], k[i]);
    }
    free(k);
}

// ========================== TESTS add_padding ==========================
Test(add_padding, empty_string)
{
    sha_t s;
    char *input = strdup("");
    s.s = input;
    s.msg = (uint8_t *)input;
    s.len = malloc(sizeof(size_t));
    *s.len = 0;
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad, "Le padding ne doit pas être NULL");
    // Message vide : pad_len doit être 64 (un seul bloc)
    cr_assert_eq(*s.len_pad, 64,
        "Longueur paddée attendue 64, obtenue %zu", *s.len_pad);
    // Premier octet après le message doit être 0x80
    cr_assert_eq(s.msg_pad[0], 0x80,
        "Le premier octet de padding doit être 0x80");
    // Les 8 derniers octets encodent la longueur en bits (0 pour chaîne vide)
    for (int i = 56; i < 64; i++) {
        cr_assert_eq(s.msg_pad[i], 0x00,
            "Longueur en bits doit être 0 pour chaîne vide (octet %d)", i);
    }

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(input);
}

Test(add_padding, short_message_abc)
{
    sha_t s;
    char *input = strdup("abc");
    s.s = input;
    s.msg = (uint8_t *)input;
    s.len = malloc(sizeof(size_t));
    *s.len = 3;
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad);
    // "abc" (3 octets) => un seul bloc de 64
    cr_assert_eq(*s.len_pad, 64,
        "Longueur paddée attendue 64, obtenue %zu", *s.len_pad);
    // Les 3 premiers octets sont 'a', 'b', 'c'
    cr_assert_eq(s.msg_pad[0], 'a');
    cr_assert_eq(s.msg_pad[1], 'b');
    cr_assert_eq(s.msg_pad[2], 'c');
    // Suivi de 0x80
    cr_assert_eq(s.msg_pad[3], 0x80);
    // Octets de remplissage 0x00 de l'index 4 à 55
    for (int i = 4; i < 56; i++) {
        cr_assert_eq(s.msg_pad[i], 0x00,
            "Octet de padding à l'index %d doit être 0x00", i);
    }
    // Les 8 derniers octets : longueur en bits = 3 * 8 = 24 = 0x18
    // En big-endian sur 8 octets : 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x18
    cr_assert_eq(s.msg_pad[63], 0x18,
        "Dernier octet de longueur doit être 0x18 (24 bits)");
    for (int i = 56; i < 63; i++) {
        cr_assert_eq(s.msg_pad[i], 0x00,
            "Octet de longueur à l'index %d doit être 0x00", i);
    }

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(input);
}

Test(add_padding, exactly_55_bytes)
{
    // 55 octets => le padding tient dans un seul bloc de 64
    sha_t s;
    char input[56];
    memset(input, 'A', 55);
    input[55] = '\0';

    char *duped = strdup(input);
    s.s = duped;
    s.msg = (uint8_t *)duped;
    s.len = malloc(sizeof(size_t));
    *s.len = 55;
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad);
    cr_assert_eq(*s.len_pad, 64,
        "55 octets → un seul bloc de 64, obtenu %zu", *s.len_pad);
    cr_assert_eq(s.msg_pad[55], 0x80);

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(duped);
}

Test(add_padding, exactly_56_bytes)
{
    // 56 octets => nécessite 2 blocs (128 octets)
    sha_t s;
    char input[57];
    memset(input, 'B', 56);
    input[56] = '\0';

    char *duped = strdup(input);
    s.s = duped;
    s.msg = (uint8_t *)duped;
    s.len = malloc(sizeof(size_t));
    *s.len = 56;
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad);
    cr_assert_eq(*s.len_pad, 128,
        "56 octets → deux blocs (128), obtenu %zu", *s.len_pad);
    cr_assert_eq(s.msg_pad[56], 0x80);

    // Longueur en bits = 56 * 8 = 448 = 0x1C0
    cr_assert_eq(s.msg_pad[127], 0xC0);
    cr_assert_eq(s.msg_pad[126], 0x01);

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(duped);
}

Test(add_padding, message_64_bytes)
{
    // 64 octets => 2 blocs
    sha_t s;
    char input[65];
    memset(input, 'C', 64);
    input[64] = '\0';

    char *duped = strdup(input);
    s.s = duped;
    s.msg = (uint8_t *)duped;
    s.len = malloc(sizeof(size_t));
    *s.len = 64;
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad);
    cr_assert_eq(*s.len_pad, 128,
        "64 octets → deux blocs (128), obtenu %zu", *s.len_pad);
    cr_assert_eq(s.msg_pad[64], 0x80);

    // Longueur en bits = 64 * 8 = 512 = 0x200
    cr_assert_eq(s.msg_pad[127], 0x00);
    cr_assert_eq(s.msg_pad[126], 0x02);

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(duped);
}

Test(add_padding, preserves_original_message)
{
    // Vérifier que les données originales ne sont pas altérées
    sha_t s;
    char *input = strdup("Hello, World!");
    s.s = input;
    s.msg = (uint8_t *)input;
    s.len = malloc(sizeof(size_t));
    *s.len = strlen(input);
    s.msg_pad = NULL;
    s.len_pad = malloc(sizeof(size_t));
    s.states = NULL;
    s.hex = NULL;

    add_padding(&s);

    cr_assert_not_null(s.msg_pad);
    for (size_t i = 0; i < strlen(input); i++) {
        cr_assert_eq(s.msg_pad[i], (uint8_t)input[i],
            "Le message original doit être préservé à l'index %zu", i);
    }

    free(s.len);
    free(s.len_pad);
    free(s.msg_pad);
    free(input);
}

Test(add_padding, length_is_multiple_of_64)
{
    // Le résultat doit toujours être un multiple de 64
    const char *inputs[] = {"", "a", "ab", "abc", "abcdefghij",
        "The quick brown fox jumps over the lazy dog"};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t t = 0; t < num_inputs; t++) {
        sha_t s;
        char *input = strdup(inputs[t]);
        s.s = input;
        s.msg = (uint8_t *)input;
        s.len = malloc(sizeof(size_t));
        *s.len = strlen(input);
        s.msg_pad = NULL;
        s.len_pad = malloc(sizeof(size_t));
        s.states = NULL;
        s.hex = NULL;

        add_padding(&s);

        cr_assert_not_null(s.msg_pad);
        cr_assert_eq(*s.len_pad % 64, 0,
            "len_pad (%zu) doit être multiple de 64 pour \"%s\"",
            *s.len_pad, inputs[t]);

        free(s.len);
        free(s.len_pad);
        free(s.msg_pad);
        free(input);
    }
}

// ========================== TESTS build_message_schedule ==========================
Test(build_message_schedule, returns_non_null)
{
    // Un bloc de 64 octets nuls
    uint8_t block[64];
    memset(block, 0, 64);

    uint32_t *w = build_message_schedule(block);
    cr_assert_not_null(w, "build_message_schedule ne doit pas retourner NULL");
    free(w);
}

Test(build_message_schedule, first_16_words_from_block)
{
    // Bloc "abc" paddé manuellement
    uint8_t block[64];
    memset(block, 0, 64);
    block[0] = 'a'; // 0x61
    block[1] = 'b'; // 0x62
    block[2] = 'c'; // 0x63
    block[3] = 0x80;
    // Longueur en bits = 24 = 0x18 à la position 63
    block[63] = 0x18;

    uint32_t *w = build_message_schedule(block);
    cr_assert_not_null(w);

    // w[0] = 0x61626380 (big-endian de "abc" + 0x80)
    cr_assert_eq(w[0], 0x61626380,
        "w[0] attendu 0x61626380, obtenu 0x%08X", w[0]);
    // w[1] à w[14] doivent être 0
    for (int i = 1; i < 15; i++) {
        cr_assert_eq(w[i], 0x00000000,
            "w[%d] attendu 0, obtenu 0x%08X", i, w[i]);
    }
    // w[15] = 0x00000018 (longueur en bits)
    cr_assert_eq(w[15], 0x00000018,
        "w[15] attendu 0x00000018, obtenu 0x%08X", w[15]);

    free(w);
}

Test(build_message_schedule, zero_block_first_16_zero)
{
    uint8_t block[64];
    memset(block, 0, 64);

    uint32_t *w = build_message_schedule(block);
    cr_assert_not_null(w);

    for (int i = 0; i < 16; i++) {
        cr_assert_eq(w[i], 0x00000000,
            "w[%d] doit être 0 pour un bloc nul", i);
    }
    // Pour un bloc tout-zéro, w[16..63] aussi tout-zéro
    for (int i = 16; i < 64; i++) {
        cr_assert_eq(w[i], 0x00000000,
            "w[%d] doit être 0 pour un bloc nul", i);
    }

    free(w);
}

Test(build_message_schedule, expansion_consistency)
{
    // Vérifier que w[i] = smallSigma1(w[i-2]) + w[i-7] + smallSigma0(w[i-15]) + w[i-16]
    uint8_t block[64];
    for (int i = 0; i < 64; i++)
        block[i] = (uint8_t)(i * 7 + 3);

    uint32_t *w = build_message_schedule(block);
    cr_assert_not_null(w);

    for (int i = 16; i < 64; i++) {
        uint32_t expected_val = add32(
            add32(smallSigma1(w[i - 2]), w[i - 7]),
            add32(smallSigma0(w[i - 15]), w[i - 16])
        );
        cr_assert_eq(w[i], expected_val,
            "w[%d]: attendu 0x%08X, obtenu 0x%08X", i, expected_val, w[i]);
    }
    free(w);
}

// ========================== TESTS digest_to_hex ==========================
Test(digest_to_hex, returns_non_null)
{
    uint32_t digest[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char *hex = digest_to_hex(digest);
    cr_assert_not_null(hex);
}

Test(digest_to_hex, correct_length)
{
    uint32_t digest[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char *hex = digest_to_hex(digest);
    cr_assert_eq(strlen(hex), 64,
        "Le hash hexadécimal doit avoir 64 caractères");
}

Test(digest_to_hex, all_zeros)
{
    uint32_t digest[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char *hex = digest_to_hex(digest);
    cr_assert_str_eq(hex,
        "0000000000000000000000000000000000000000000000000000000000000000",
        "Digest tout-zéro doit donner 64 zéros");
}

Test(digest_to_hex, known_initial_hash_values)
{
    // Les valeurs initiales H de SHA-256
    uint32_t digest[8] = {
        0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
        0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
    };
    char *hex = digest_to_hex(digest);
    cr_assert_str_eq(hex,
        "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
        "Digest des valeurs initiales H incorrect");
}

Test(digest_to_hex, single_word_value)
{
    uint32_t digest[8] = {0xDEADBEEF, 0, 0, 0, 0, 0, 0, 0};
    char *hex = digest_to_hex(digest);
    // Les 8 premiers caractères doivent être "deadbeef"
    cr_assert_eq(strncmp(hex, "deadbeef", 8), 0,
        "Les 8 premiers caractères doivent être 'deadbeef'");
}

Test(digest_to_hex, all_ff)
{
    uint32_t digest[8] = {
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
    };
    char *hex = digest_to_hex(digest);
    cr_assert_str_eq(hex,
        "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
        "Digest tout-FF incorrect");
}

Test(digest_to_hex, hex_chars_are_lowercase)
{
    uint32_t digest[8] = {
        0xABCDEF01, 0x23456789, 0xABCDEF01, 0x23456789,
        0xABCDEF01, 0x23456789, 0xABCDEF01, 0x23456789
    };
    char *hex = digest_to_hex(digest);
    for (int i = 0; i < 64; i++) {
        if (hex[i] >= 'a' && hex[i] <= 'f')
            continue;
        if (hex[i] >= '0' && hex[i] <= '9')
            continue;
        cr_assert(0, "Caractère inattendu '%c' à l'index %d (attendu lowercase hex)", hex[i], i);
    }
}

// ========================== TESTS bigSigma0 (valeurs spécifiques) ==========================
Test(bigSigma0, known_value_one)
{
    // bigSigma0(x) = rotr(x, 2) XOR rotr(x, 13) XOR rotr(x, 22)
    uint32_t x = 0x6A09E667;
    uint32_t expected = xor32(xor32(rotr32(x, 2), rotr32(x, 13)), rotr32(x, 22));
    cr_assert_eq(bigSigma0(x), expected,
        "bigSigma0(0x6A09E667): attendu 0x%08X, obtenu 0x%08X", expected, bigSigma0(x));
}

Test(bigSigma0, known_value_two)
{
    uint32_t x = 0xABCDEF01;
    uint32_t expected = xor32(xor32(rotr32(x, 2), rotr32(x, 13)), rotr32(x, 22));
    cr_assert_eq(bigSigma0(x), expected);
}

// ========================== TESTS bigSigma1 (valeurs spécifiques) ==========================
Test(bigSigma1, known_value_one)
{
    // bigSigma1(x) = rotr(x, 6) XOR rotr(x, 11) XOR rotr(x, 25)
    uint32_t x = 0x510E527F;
    uint32_t expected = xor32(xor32(rotr32(x, 6), rotr32(x, 11)), rotr32(x, 25));
    cr_assert_eq(bigSigma1(x), expected,
        "bigSigma1(0x510E527F): attendu 0x%08X, obtenu 0x%08X", expected, bigSigma1(x));
}

Test(bigSigma1, known_value_two)
{
    uint32_t x = 0x12345678;
    uint32_t expected = xor32(xor32(rotr32(x, 6), rotr32(x, 11)), rotr32(x, 25));
    cr_assert_eq(bigSigma1(x), expected);
}

// ========================== TESTS smallSigma0 (valeurs spécifiques) ==========================
Test(smallSigma0, known_value)
{
    // smallSigma0(x) = rotr(x, 7) XOR rotr(x, 18) XOR shr(x, 3)
    uint32_t x = 0x61626380;
    uint32_t expected = xor32(xor32(rotr32(x, 7), rotr32(x, 18)), shr32(x, 3));
    cr_assert_eq(smallSigma0(x), expected,
        "smallSigma0(0x61626380): attendu 0x%08X, obtenu 0x%08X", expected, smallSigma0(x));
}

Test(smallSigma0, all_ones)
{
    // rotr(0xFFFFFFFF, 7) = 0xFFFFFFFF, rotr(..., 18) = 0xFFFFFFFF, shr(..., 3) = 0x1FFFFFFF
    // XOR: 0xFFFFFFFF ^ 0xFFFFFFFF ^ 0x1FFFFFFF = 0x1FFFFFFF
    uint32_t x = 0xFFFFFFFF;
    uint32_t expected = xor32(xor32(rotr32(x, 7), rotr32(x, 18)), shr32(x, 3));
    cr_assert_eq(smallSigma0(x), expected,
        "smallSigma0(0xFFFFFFFF): attendu 0x%08X, obtenu 0x%08X", expected, smallSigma0(x));
}

// ========================== TESTS smallSigma1 (valeurs spécifiques) ==========================
Test(smallSigma1, known_value)
{
    // smallSigma1(x) = rotr(x, 17) XOR rotr(x, 19) XOR shr(x, 10)
    uint32_t x = 0x00000018;
    uint32_t expected = xor32(xor32(rotr32(x, 17), rotr32(x, 19)), shr32(x, 10));
    cr_assert_eq(smallSigma1(x), expected,
        "smallSigma1(0x00000018): attendu 0x%08X, obtenu 0x%08X", expected, smallSigma1(x));
}

Test(smallSigma1, all_ones)
{
    uint32_t x = 0xFFFFFFFF;
    uint32_t expected = xor32(xor32(rotr32(x, 17), rotr32(x, 19)), shr32(x, 10));
    cr_assert_eq(smallSigma1(x), expected);
}

// ========================== TESTS ch32 (valeurs supplémentaires) ==========================
Test(ch32, all_ones_input)
{
    // ch(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF) = 0xFFFFFFFF
    cr_assert_eq(ch32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF);
}

Test(ch32, alternating_pattern)
{
    // x = 0xAAAAAAAA => bits alternés 1010...
    // y = 0x12345678, z = 0x9ABCDEF0
    // ch choisit y quand x=1, z quand x=0
    uint32_t result = ch32(0xAAAAAAAA, 0x12345678, 0x9ABCDEF0);
    uint32_t expected = xor32(and32(0xAAAAAAAA, 0x12345678),
                              and32(not32(0xAAAAAAAA), 0x9ABCDEF0));
    cr_assert_eq(result, expected);
}

// ========================== TESTS maj32 (valeurs supplémentaires) ==========================
Test(maj32, all_zeros)
{
    cr_assert_eq(maj32(0x00000000, 0x00000000, 0x00000000), 0x00000000);
}

Test(maj32, all_ones)
{
    cr_assert_eq(maj32(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF);
}

Test(maj32, alternating_pattern)
{
    // maj = (x AND y) XOR (x AND z) XOR (y AND z)
    uint32_t x = 0xAAAAAAAA, y = 0xCCCCCCCC, z = 0xF0F0F0F0;
    uint32_t expected = xor32(xor32(and32(x, y), and32(x, z)), and32(y, z));
    cr_assert_eq(maj32(x, y, z), expected);
}

// ========================== TESTS sha_256_create (hash final complet) ==========================
Test(sha_256_create, empty_string)
{
    // SHA-256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    sha_t *result = sha_256_create("");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
        "SHA-256 de chaîne vide incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, abc)
{
    // SHA-256("abc") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
    sha_t *result = sha_256_create("abc");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
        "SHA-256 de 'abc' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, hello_world)
{
    // SHA-256("Hello, World!") = dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f
    sha_t *result = sha_256_create("Hello, World!");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f",
        "SHA-256 de 'Hello, World!' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, single_char_a)
{
    // SHA-256("a") = ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
    sha_t *result = sha_256_create("a");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb",
        "SHA-256 de 'a' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, test_string)
{
    // SHA-256("test") = 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
    sha_t *result = sha_256_create("test");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08",
        "SHA-256 de 'test' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, quick_brown_fox)
{
    // SHA-256("The quick brown fox jumps over the lazy dog")
    // = d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592
    sha_t *result = sha_256_create(
        "The quick brown fox jumps over the lazy dog");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592",
        "SHA-256 'quick brown fox' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, quick_brown_fox_period)
{
    // SHA-256("The quick brown fox jumps over the lazy dog.")
    // = ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c
    sha_t *result = sha_256_create(
        "The quick brown fox jumps over the lazy dog.");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c",
        "SHA-256 'quick brown fox.' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, numeric_string)
{
    // SHA-256("0123456789") = 84d89877f0d4041efb6bf91a16f0248f2fd573e6af05c19f96bedb9f882f7882
    sha_t *result = sha_256_create("0123456789");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "84d89877f0d4041efb6bf91a16f0248f2fd573e6af05c19f96bedb9f882f7882",
        "SHA-256 de '0123456789' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, sha256_of_sha256)
{
    // SHA-256("sha256")
    // = 5d5b09f6dcb2d53a5fffc60c4ac0d55fabdf556069d6631545f42aa6e3500f2e
    sha_t *result = sha_256_create("sha256");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "5d5b09f6dcb2d53a5fffc60c4ac0d55fabdf556069d6631545f42aa6e3500f2e",
        "SHA-256 de 'sha256' incorrect: %s", result->hex);
    free(result);
}

Test(sha_256_create, hex_output_length)
{
    sha_t *result = sha_256_create("test");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_eq(strlen(result->hex), 64,
        "Le hash hex doit faire 64 caractères, obtenu %zu",
        strlen(result->hex));
    free(result);
}

Test(sha_256_create, deterministic)
{
    // Deux appels avec la même entrée doivent donner le même résultat
    sha_t *r1 = sha_256_create("deterministic test");
    sha_t *r2 = sha_256_create("deterministic test");
    cr_assert_not_null(r1);
    cr_assert_not_null(r2);
    cr_assert_str_eq(r1->hex, r2->hex,
        "SHA-256 doit être déterministe");
    free(r1);
    free(r2);
}

Test(sha_256_create, different_inputs_different_outputs)
{
    sha_t *r1 = sha_256_create("input1");
    cr_assert_not_null(r1);
    // digest_to_hex utilise un buffer static, donc on copie le résultat
    char hex1[65];
    strncpy(hex1, r1->hex, 64);
    hex1[64] = '\0';

    sha_t *r2 = sha_256_create("input2");
    cr_assert_not_null(r2);

    cr_assert_str_neq(hex1, r2->hex,
        "Deux entrées différentes doivent donner des hash différents");
    free(r1);
    free(r2);
}

Test(sha_256_create, single_space)
{
    // SHA-256(" ") = 36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068
    sha_t *result = sha_256_create(" ");
    cr_assert_not_null(result);
    cr_assert_not_null(result->hex);
    cr_assert_str_eq(result->hex,
        "36a9e7f1c95b82ffb99743e0c5c4ce95d83c9a430aac59f84ef3cbfab6145068",
        "SHA-256 de ' ' incorrect: %s", result->hex);
    free(result);
}

// ========================== TESTS rotations complémentaires ==========================
Test(rotr32, full_rotation_32)
{
    // rotation de 32 = identité
    cr_assert_eq(rotr32(0xDEADBEEF, 32), 0xDEADBEEF);
}

Test(rotl32, full_rotation_32)
{
    cr_assert_eq(rotl32(0xDEADBEEF, 32), 0xDEADBEEF);
}

Test(rotr32, rotate_by_16)
{
    cr_assert_eq(rotr32(0x12345678, 16), 0x56781234);
}

Test(rotl32, rotate_by_16)
{
    cr_assert_eq(rotl32(0x12345678, 16), 0x56781234);
}

Test(rotr32, rotate_by_24)
{
    cr_assert_eq(rotr32(0x12345678, 24), 0x34567812);
}

// ========================== TESTS add32 complémentaires ==========================
Test(add32, commutative)
{
    cr_assert_eq(add32(0x12345678, 0x9ABCDEF0), add32(0x9ABCDEF0, 0x12345678));
}

Test(add32, identity_element)
{
    cr_assert_eq(add32(0xDEADBEEF, 0), 0xDEADBEEF);
    cr_assert_eq(add32(0, 0xDEADBEEF), 0xDEADBEEF);
}

// ========================== TESTS isPrime complémentaires ==========================
Test(isPrime, sha256_primes)
{
    // Tous les premiers utilisés dans SHA-256 (les 64 premiers premiers)
    int sha_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
    for (int i = 0; i < 16; i++) {
        cr_assert_eq(isPrime(sha_primes[i]), 1,
            "%d devrait être premier", sha_primes[i]);
    }
}

Test(isPrime, perfect_squares)
{
    cr_assert_eq(isPrime(25), 0);
    cr_assert_eq(isPrime(49), 0);
    cr_assert_eq(isPrime(121), 0);
    cr_assert_eq(isPrime(169), 0);
}