#include "EncryptionModule.h"

// g++ -Wall -std=c++11 evp-encrypt.cxx -o evp-encrypt.exe -lcrypto

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;
using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;




int main(int argc, char* argv[])
{
    EncryptionModule em;
    // Load the necessary cipher
    EVP_add_cipher(EVP_aes_256_cbc());

    // plaintext, ciphertext, recovered text
    std::string hello = "helalsdasd";
    secure_string ptext = hello.c_str();
    secure_string ctext, rtext;

    byte key[KEY_SIZE], iv[BLOCK_SIZE];
    em.gen_params(key, iv);

    em.aes_encrypt(key, iv, ptext, ctext);
    em.aes_decrypt(key, iv, ctext, rtext);

    OPENSSL_cleanse(key, KEY_SIZE);
    OPENSSL_cleanse(iv, BLOCK_SIZE);

    std::cout << "Original message:\n" << ptext << std::endl;
    std::cout << "Recovered message:\n" << rtext << std::endl;




    RSA *private_key;
    RSA *public_key;

    char message[KEY_LENGTH / 8] = "Batuhan AVLAYAN - OpenSSL_RSA demo";
    char *encrypt = NULL;
    char *decrypt = NULL;

    char private_key_pem[12] = "private_key";
    char public_key_pem[11]  = "public_key";

    RSA *keypair = RSA_generate_key(KEY_LENGTH, PUBLIC_EXPONENT, NULL, NULL);

    private_key = em.create_RSA(keypair, PRIVATE_KEY_PEM, private_key_pem);

    public_key  = em.create_RSA(keypair, PUBLIC_KEY_PEM, public_key_pem);

    encrypt = (char*)malloc(RSA_size(public_key));
    int encrypt_length = em.public_encrypt(strlen(message) + 1, (unsigned char*)message, (unsigned char*)encrypt, public_key, RSA_PKCS1_OAEP_PADDING);
    if(encrypt_length == -1) {
        printf("An error occurred in public_encrypt() method");
    }
    printf("Data has been encrypted.");

    em.create_encrypted_file(encrypt, public_key);
    printf("Encrypted file has been created.");

    decrypt = (char *)malloc(encrypt_length);
    int decrypt_length = em.private_decrypt(encrypt_length, (unsigned char*)encrypt, (unsigned char*)decrypt, private_key, RSA_PKCS1_OAEP_PADDING);
    if(decrypt_length == -1) {
        printf("An error occurred in private_decrypt() method");
    }
    printf("Data has been decrypted.");

    FILE *decrypted_file = fopen("decrypted_file.txt", "w");
    fwrite(decrypt, sizeof(*decrypt), decrypt_length - 1, decrypted_file);
    fclose(decrypted_file);
    printf("Decrypted file has been created.");

    RSA_free(keypair);
    free(private_key);
    free(public_key);
    free(encrypt);
    free(decrypt);
    printf("OpenSSL_RSA has been finished.");

    return 0;
}


