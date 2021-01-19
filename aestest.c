#include <stdio.h>
#include "aes.c"

int main()
{
    uint8_t key[] = "secret key 123";
    uint8_t in[]  = "my message";
    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

    printf("Length: %lu",strlen((char*)in));

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, in, strlen((char*)in));
    printf("\nENC: %s",(char*) in); // don't use this string as an input

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, in, strlen((char*)in));
    printf("\nDEC: %s",(char*) in);
    return 0;
}