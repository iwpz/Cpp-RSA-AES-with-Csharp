#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <cryptopp/randpool.h>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
typedef unsigned char       BYTE;
using namespace CryptoPP;

using namespace std;
/// <summary>
/// Encrypt Helper
/// </summary>
class EncryptHelper
{
public:
	EncryptHelper();
	~EncryptHelper();
	/// <summary>  
	/// AES Encrypt 
	/// </summary>
	static string AESEncrypt(const string& source, const std::string& key = EncryptHelper::GetAESKey());

	/// <summary>  
	/// AES Decrypt
	/// </summary>
	static string AESDecrypt(const string& ciphertext, const std::string& key = EncryptHelper::GetAESKey());

	/// <summary>  
	/// RSA Public Key Encrypt 
	/// </summary>
	static string PublicKeyEncrypt(string value,RSA::PublicKey publicKey = EncryptHelper::GetRSAPublicKey());
	/// <summary>  
	/// RSA Private Key Decrypt 
	/// </summary>
	static string PrivateKeyDecrypt(string encryptedValue, RSA::PrivateKey privateKey = EncryptHelper::GetRSAPrivateKey());
private:
	static string GetAESKey() { return "SA#%^433@!#$&#$%"; }
	/*
		Public Key PEM:
		-----BEGIN PUBLIC KEY-----
	   MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDfqchPmQDwDU3zg86OXpP+zP6R
	   FTyQNtQ7RUrOkGXl1JWGh6aUxrVhdrxfqARfHqGJyprM1u1JIuOoe+jgUQ9Gbwvx
	   BLVTttD8PJ0xZyP3oWKspt4UslkYgCEEJkUM4NY31MAX+QebIvqWiC+a7K8g0M+/
	   q+gs3pjNea3oWCV4GQIDAQAB
	   -----END PUBLIC KEY-----
	   Public Key XML:
		   <RSAKeyValue><Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>
	   Private Key PEM:
	   -----BEGIN RSA PRIVATE KEY-----
	   MIICXQIBAAKBgQDfqchPmQDwDU3zg86OXpP+zP6RFTyQNtQ7RUrOkGXl1JWGh6aU
	   xrVhdrxfqARfHqGJyprM1u1JIuOoe+jgUQ9GbwvxBLVTttD8PJ0xZyP3oWKspt4U
	   slkYgCEEJkUM4NY31MAX+QebIvqWiC+a7K8g0M+/q+gs3pjNea3oWCV4GQIDAQAB
	   AoGAW9Ie6xacPPCpVNSCww3u4gcUZ0l5oJbx0BdlW6IKQy1f6WfdKmzdX9LYCMk4
	   ajhwBtqHbJq7tW++WJfuBdEhXHt6CMHw0y4+5tBVErq6nwkqFeogu/dV4ksBSwI/
	   N644El1k3uBPOUigvDkLXn5qIrlO2sa+JUml65ABSy3jS4UCQQDnPRXsZqgln8Fk
	   xnvnnKep7XC78GPucHc2rt4Tnp5i9yNE8chAFSjLwLR2y5f5I4TQ7vZdrrhniGcD
	   D0bbXrtbAkEA950IhQUK0hyyLXIlEB1T1O1P5aapEScPq8cFpAbsawPefklgFiK4
	   S87XWL9K/b1JISfo7XexJ0nlq2j29WSYmwJAfa4x0D8rfOeLkV5f0c7PQgiPkVZi
	   uiHeaZY5lahMpbV1Me/Hyyy086lVbIvTmdG4SmbW+KwSBhOZCYywEmM2qQJBALlc
	   EJijYapQWQG0RRJ/IdZvoDPmQwHYH98TqaFUnX6u8svO2eM4MoZtXL/O07CHFkt/
	   uNqrky46H3flp5mjqKkCQQDhUYCB5yjAz9Rv7iQXd9ZU3+TX6R6lN3ANeQx6m31c
	   ptqvTyWa00bK8xlT/1rDAJhll+zqXWAXJYsspWbeDVQV
	   -----END RSA PRIVATE KEY-----
	   Private Key XML:
	   <RSAKeyValue><Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus><Exponent>AQAB</Exponent><P>5z0V7GaoJZ/BZMZ755ynqe1wu/Bj7nB3Nq7eE56eYvcjRPHIQBUoy8C0dsuX+SOE0O72Xa64Z4hnAw9G2167Ww==</P><Q>950IhQUK0hyyLXIlEB1T1O1P5aapEScPq8cFpAbsawPefklgFiK4S87XWL9K/b1JISfo7XexJ0nlq2j29WSYmw==</Q><DP>fa4x0D8rfOeLkV5f0c7PQgiPkVZiuiHeaZY5lahMpbV1Me/Hyyy086lVbIvTmdG4SmbW+KwSBhOZCYywEmM2qQ==</DP><DQ>uVwQmKNhqlBZAbRFEn8h1m+gM+ZDAdgf3xOpoVSdfq7yy87Z4zgyhm1cv87TsIcWS3+42quTLjofd+WnmaOoqQ==</DQ><InverseQ>4VGAgecowM/Ub+4kF3fWVN/k1+kepTdwDXkMept9XKbar08lmtNGyvMZU/9awwCYZZfs6l1gFyWLLKVm3g1UFQ==</InverseQ><D>W9Ie6xacPPCpVNSCww3u4gcUZ0l5oJbx0BdlW6IKQy1f6WfdKmzdX9LYCMk4ajhwBtqHbJq7tW++WJfuBdEhXHt6CMHw0y4+5tBVErq6nwkqFeogu/dV4ksBSwI/N644El1k3uBPOUigvDkLXn5qIrlO2sa+JUml65ABSy3jS4U=</D></RSAKeyValue>

	   PEM convert with XML use https://superdry.apphb.com/tools/online-rsa-key-converter
			*/
	static RSA::PublicKey GetRSAPublicKey();
	static RSA::PrivateKey GetRSAPrivateKey();
};

