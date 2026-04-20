#ifndef MY_H
    #define MY_H
    #include "stdlib.h"
    #include "stdint.h"
    #include "struct.h"

    // Opérations bit à bit
    uint32_t add32(uint32_t a, uint32_t b);
    uint32_t and32(uint32_t a, uint32_t b);
    uint32_t or32(uint32_t a, uint32_t b);
    uint32_t xor32(uint32_t a, uint32_t b);
    uint32_t not32(uint32_t a);

    // Rotations et décalages
    uint32_t rotl32(uint32_t x, int r);
    uint32_t rotr32(uint32_t x, int r);
    uint32_t shr32(uint32_t x, int r);

    // Fonctions SHA-256
    uint32_t ch32(uint32_t x, uint32_t y, uint32_t z);
    uint32_t maj32(uint32_t x, uint32_t y, uint32_t z);
    uint32_t bigSigma0(uint32_t x);
    uint32_t bigSigma1(uint32_t x);
    uint32_t smallSigma0(uint32_t x);
    uint32_t smallSigma1(uint32_t x);

    // Initialisation
    uint32_t *init_h(void);
    uint32_t *init_k(void);

    // Message et padding
    void add_padding(sha_t *s);
    uint32_t *build_message_schedule(uint8_t *m);
    void process_blocks(sha_t *s);
    void compression(sha_t *s);

    // Utilitaires
    int isPrime(int n);
    char **const_adress(void);
    void sha_256(char *s);
    sha_t *sha_256_create(char *s);
    char *digest_to_hex(uint32_t *digest);

    #endif /*MY.H*/