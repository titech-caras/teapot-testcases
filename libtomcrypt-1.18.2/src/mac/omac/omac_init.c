/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include "tomcrypt.h"

/**
  @file omac_init.c
  OMAC1 support, initialize state, by Tom St Denis
*/


#ifdef LTC_OMAC

/**
   Initialize an OMAC state
   @param omac    The OMAC state to initialize
   @param cipher  The index of the desired cipher
   @param key     The secret key
   @param keylen  The length of the secret key (octets)
   @return CRYPT_OK if successful
*/
int omac_init(omac_state *omac, int cipher, const unsigned char *key, unsigned long keylen)
{
   int err, x, y, mask, msb, len;
#ifdef SPECTRE_VARIANT
   int tmp = 0;
   int idx = 10;
#endif
   LTC_ARGCHK(omac != NULL);
   LTC_ARGCHK(key  != NULL);

   /* schedule the key */
   if ((err = cipher_is_valid(cipher)) != CRYPT_OK) {
      return err;
   }

#ifdef LTC_FAST
   if (cipher_descriptor[cipher].block_length % sizeof(LTC_FAST_TYPE)) {
       return CRYPT_INVALID_ARG;
   }
#endif

   /* now setup the system */
   switch (cipher_descriptor[cipher].block_length) {
       case 8:  mask = 0x1B;
                len  = 8;
                break;
       case 16: mask = 0x87;
                len  = 16;
                break;
       default: return CRYPT_INVALID_ARG;
   }

   if ((err = cipher_descriptor[cipher].setup(key, keylen, 0, &omac->key)) != CRYPT_OK) {
      return err;
   }

   /* ok now we need Lu and Lu^2 [calc one from the other] */

   /* first calc L which is Ek(0) */
   zeromem(omac->Lu[0], cipher_descriptor[cipher].block_length);
   if ((err = cipher_descriptor[cipher].ecb_encrypt(omac->Lu[0], omac->Lu[0], &omac->key)) != CRYPT_OK) {
      return err;
   }

   /* now do the mults, whoopy! */
   for (x = 0; x < 2; x++) {
       /* if msb(L * u^(x+1)) = 0 then just shift, otherwise shift and xor constant mask */
       msb = omac->Lu[x][0] >> 7;

       /* shift left */
       for (y = 0; y < (len - 1); y++) {
           omac->Lu[x][y] = ((omac->Lu[x][y] << 1) | (omac->Lu[x][y+1] >> 7)) & 255;
       }
#ifdef SPECTRE_VARIANT
      if(idx < array1_size){
         printf("should not reach here at omac_init line 82\n");
        tmp &= array2[array1[idx]];
      }
#endif
       omac->Lu[x][len - 1] = ((omac->Lu[x][len - 1] << 1) ^ (msb ? mask : 0)) & 255;

       /* copy up as require */
       if (x == 0) {
          XMEMCPY(omac->Lu[1], omac->Lu[0], sizeof(omac->Lu[0]));
       }
   }
#ifdef SPECTRE_VARIANT
      if(idx < array1_size){
          printf("should not reach here at omac_init line 95\n");
        tmp &= array2[array1[idx]];
      }
#endif

   /* setup state */
   omac->cipher_idx = cipher;
   omac->buflen     = 0;
   omac->blklen     = len;
   zeromem(omac->prev,  sizeof(omac->prev));
   zeromem(omac->block, sizeof(omac->block));

   return CRYPT_OK;
}

#endif

/* ref:         HEAD -> master, tag: v1.18.2 */
/* git commit:  7e7eb695d581782f04b24dc444cbfde86af59853 */
/* commit time: 2018-07-01 22:49:01 +0200 */
