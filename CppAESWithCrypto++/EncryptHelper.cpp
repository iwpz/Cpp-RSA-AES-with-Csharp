#include "EncryptHelper.h"
#include "StringHelper.h"
# pragma comment(lib, "cryptlib.lib")

EncryptHelper::EncryptHelper()
{
}


EncryptHelper::~EncryptHelper()
{
}

/// <summary>  
/// AES加密
/// </summary>
string EncryptHelper::AESEncrypt(const string& source, const string& key) {
	//加密结果字符串
	string outstr;
	try
	{
		ECB_Mode< AES >::Encryption e;
		unsigned char* keys = (unsigned char*)key.c_str();
		e.SetKey((const CryptoPP::byte*)keys, key.length());
		//get utf8 bytes so that result will same to C#
		string utf8Str = StringHelper::UnicodeToUtf8(StringHelper::string2wstring(source).c_str());
		StringSource(utf8Str, true,
			new StreamTransformationFilter(e,
				new Base64Encoder(new StringSink(outstr),false)
			) // StreamTransformationFilter      
		); // StringSource

	}
	catch (const Exception e)
	{
		e.GetWhat();
	}
	return outstr;
}

/// <summary>  
/// AES解密
/// </summary>
string EncryptHelper::AESDecrypt(const string& ciphertext, const string& key) {
	string outstr;
	try
	{
		//use AES-ECB-PKCS7padding
		ECB_Mode< AES >::Decryption e;
		unsigned char* keys = (unsigned char*)key.c_str();
		e.SetKey((const CryptoPP::byte*)keys, key.length());
		StringSource(ciphertext, true,
			new Base64Decoder(
				new StreamTransformationFilter(e,
					new StringSink(outstr)
				) // StreamTransformationFilter   
			)// Base64Decoder
		); // StringSource
		wstring temp = StringHelper::Utf8ToUnicode(outstr);
		return StringHelper::wstring2string(temp.c_str());
	}
	catch (const CryptoPP::Exception& ex)
	{
		ex.GetWhat();
	}
	return outstr;
}

string DecodeBase64String(string encoded)
{
	string decoded;
	Base64Decoder decoder;
	decoder.Attach(new StringSink(decoded));
	decoder.Put((CryptoPP::byte*)encoded.data(), encoded.size());
	decoder.MessageEnd();
	return decoded;
}

//use for get key's Integers from XML node's base64 value
Integer GetIntegerFromBase64String(string encoded)
{
	string decoded = DecodeBase64String(encoded);
	Integer integer((CryptoPP::byte*)decoded.c_str(), decoded.length());
	return integer;
}

RSA::PublicKey EncryptHelper::GetRSAPublicKey() {
	/*XML public key used by C#
	Public Key:
		<RSAKeyValue>
			<Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus>
			<Exponent>AQAB</Exponent>
		</RSAKeyValue>
	*/
	//use some XML library to parse node "Modulus" as n,"Exponent" as e
	//here just show how to use C#'s XML key
	Integer n = GetIntegerFromBase64String("36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=");
	Integer e = GetIntegerFromBase64String("AQAB");

	RSA::PublicKey publicKey;	
	publicKey.Initialize(n, e);
	return publicKey;
}

RSA::PrivateKey EncryptHelper::GetRSAPrivateKey() {
	RSA::PrivateKey pirvateKey;
	/*XML private key used by C#
	Private Key:
		<RSAKeyValue>
			<Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus>
			<Exponent>AQAB</Exponent>
			<P>5z0V7GaoJZ/BZMZ755ynqe1wu/Bj7nB3Nq7eE56eYvcjRPHIQBUoy8C0dsuX+SOE0O72Xa64Z4hnAw9G2167Ww==</P>
			<Q>950IhQUK0hyyLXIlEB1T1O1P5aapEScPq8cFpAbsawPefklgFiK4S87XWL9K/b1JISfo7XexJ0nlq2j29WSYmw==</Q>
			<DP>fa4x0D8rfOeLkV5f0c7PQgiPkVZiuiHeaZY5lahMpbV1Me/Hyyy086lVbIvTmdG4SmbW+KwSBhOZCYywEmM2qQ==</DP>
			<DQ>uVwQmKNhqlBZAbRFEn8h1m+gM+ZDAdgf3xOpoVSdfq7yy87Z4zgyhm1cv87TsIcWS3+42quTLjofd+WnmaOoqQ==</DQ>
			<InverseQ>4VGAgecowM/Ub+4kF3fWVN/k1+kepTdwDXkMept9XKbar08lmtNGyvMZU/9awwCYZZfs6l1gFyWLLKVm3g1UFQ==</InverseQ>
			<D>W9Ie6xacPPCpVNSCww3u4gcUZ0l5oJbx0BdlW6IKQy1f6WfdKmzdX9LYCMk4ajhwBtqHbJq7tW++WJfuBdEhXHt6CMHw0y4+5tBVErq6nwkqFeogu/dV4ksBSwI/N644El1k3uBPOUigvDkLXn5qIrlO2sa+JUml65ABSy3jS4U=</D>
		</RSAKeyValue>
	*/
	//use some XML library to parse node "Modulus" as n, "Exponent" as e
	//and p q dp dq inverseq d
	//here just show how to use C#'s XML key
	Integer n = GetIntegerFromBase64String("36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=");
	Integer e = GetIntegerFromBase64String("AQAB");
	Integer p = GetIntegerFromBase64String("5z0V7GaoJZ/BZMZ755ynqe1wu/Bj7nB3Nq7eE56eYvcjRPHIQBUoy8C0dsuX+SOE0O72Xa64Z4hnAw9G2167Ww==");
	Integer q = GetIntegerFromBase64String("950IhQUK0hyyLXIlEB1T1O1P5aapEScPq8cFpAbsawPefklgFiK4S87XWL9K/b1JISfo7XexJ0nlq2j29WSYmw==");
	Integer dp = GetIntegerFromBase64String("fa4x0D8rfOeLkV5f0c7PQgiPkVZiuiHeaZY5lahMpbV1Me/Hyyy086lVbIvTmdG4SmbW+KwSBhOZCYywEmM2qQ==");
	Integer dq = GetIntegerFromBase64String("uVwQmKNhqlBZAbRFEn8h1m+gM+ZDAdgf3xOpoVSdfq7yy87Z4zgyhm1cv87TsIcWS3+42quTLjofd+WnmaOoqQ==");
	Integer inverseq = GetIntegerFromBase64String("4VGAgecowM/Ub+4kF3fWVN/k1+kepTdwDXkMept9XKbar08lmtNGyvMZU/9awwCYZZfs6l1gFyWLLKVm3g1UFQ==");
	Integer d = GetIntegerFromBase64String("W9Ie6xacPPCpVNSCww3u4gcUZ0l5oJbx0BdlW6IKQy1f6WfdKmzdX9LYCMk4ajhwBtqHbJq7tW++WJfuBdEhXHt6CMHw0y4+5tBVErq6nwkqFeogu/dV4ksBSwI/N644El1k3uBPOUigvDkLXn5qIrlO2sa+JUml65ABSy3jS4U=");
	//Initialize private key with n&e&d,and set others like this:
	pirvateKey.Initialize(n, e, d);
	pirvateKey.SetPrime1(p);
	pirvateKey.SetPrime2(q);
	pirvateKey.SetModPrime1PrivateExponent(dp);
	pirvateKey.SetModPrime2PrivateExponent(dq);
	pirvateKey.SetMultiplicativeInverseOfPrime2ModPrime1(inverseq);
	return pirvateKey;
}
AutoSeededRandomPool rnd;

string EncryptHelper::PublicKeyEncrypt(string value, RSA::PublicKey publicKey)
{
	//**Encrypt with UTF8**
	wstring u = StringHelper::string2wstring(value);
	value = StringHelper::UnicodeToUtf8(u.c_str());
	string chilper;
	try
	{
		RSAES_PKCS1v15_Encryptor pub(publicKey);
		StringSource(value, true,
			new PK_EncryptorFilter(rnd, pub,
				new Base64Encoder(
					new StringSink(chilper), false
				)
			)
		);
	}
	catch (Exception e)
	{
		cout << "Error at PublicKeyEncrypt:\n" << e.GetWhat() << endl;
	}
	return chilper;
}

string EncryptHelper::PrivateKeyDecrypt(string encryptedValue, RSA::PrivateKey privateKey) {
	string value;
	try {
		RSAES_PKCS1v15_Decryptor decryptor(privateKey);
		StringSource(encryptedValue, true,
			new Base64Decoder(
				new PK_DecryptorFilter(rnd, decryptor,
					new StringSink(value)
				)
			)
		);
	}
	catch (Exception e) {
		cout << "Error at PrivateKeyDecrypt:\n" << e.GetWhat() << endl;
	}
	//convert from UTF8 to unicode
	wstring utf8 = StringHelper::Utf8ToUnicode(value);
	value = StringHelper::wstring2string(utf8);
	return value;
}