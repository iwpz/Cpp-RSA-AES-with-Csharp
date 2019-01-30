using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Cryptography;
using System.IO;
using System.Security;

    /// <summary>
    /// Encrypt Helper
    /// </summary>
    public class EncryptHelper
    {
        //Default AES Key
        private const string AESKey = "SA#%^433@!#$&#$%";
        /// <summary>  
        /// AES Encrypt
        /// </summary>
        public static string AESEncrypt(string value, string _aeskey = AESKey)
        {
            if (string.IsNullOrEmpty(_aeskey))
            {
                _aeskey = AESKey;
            }

            byte[] keyArray = Encoding.UTF8.GetBytes(_aeskey);
            byte[] toEncryptArray = Encoding.UTF8.GetBytes(value);

            RijndaelManaged rDel = new RijndaelManaged();
            rDel.Key = keyArray;
            rDel.Mode = CipherMode.ECB;
            rDel.Padding = PaddingMode.PKCS7;

            ICryptoTransform cTransform = rDel.CreateEncryptor();
            byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

            return Convert.ToBase64String(resultArray, 0, resultArray.Length);
        }

        /// <summary>  
        /// AES Decrypt
        /// </summary>
        public static string AESDecrypt(string value, string _aeskey = AESKey)
        {
            try
            {
                if (string.IsNullOrEmpty(_aeskey))
                {
                    _aeskey = AESKey;
                }
                byte[] keyArray = Encoding.UTF8.GetBytes(_aeskey);
                byte[] toEncryptArray = Convert.FromBase64String(value);

                RijndaelManaged rDel = new RijndaelManaged();
                rDel.Key = keyArray;
                rDel.Mode = CipherMode.ECB;
                rDel.Padding = PaddingMode.PKCS7;

                ICryptoTransform cTransform = rDel.CreateDecryptor();
                byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

                return Encoding.UTF8.GetString(resultArray);
            }
            catch
            {
                return string.Empty;
            }
        }

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
         
    PEM convert from XML use https://superdry.apphb.com/tools/online-rsa-key-converter
         */
    private const string RSAPublicKey = "<RSAKeyValue><Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
    private const string RSAPrivateKey = "<RSAKeyValue><Modulus>36nIT5kA8A1N84POjl6T/sz+kRU8kDbUO0VKzpBl5dSVhoemlMa1YXa8X6gEXx6hicqazNbtSSLjqHvo4FEPRm8L8QS1U7bQ/DydMWcj96FirKbeFLJZGIAhBCZFDODWN9TAF/kHmyL6logvmuyvINDPv6voLN6YzXmt6FgleBk=</Modulus><Exponent>AQAB</Exponent><P>5z0V7GaoJZ/BZMZ755ynqe1wu/Bj7nB3Nq7eE56eYvcjRPHIQBUoy8C0dsuX+SOE0O72Xa64Z4hnAw9G2167Ww==</P><Q>950IhQUK0hyyLXIlEB1T1O1P5aapEScPq8cFpAbsawPefklgFiK4S87XWL9K/b1JISfo7XexJ0nlq2j29WSYmw==</Q><DP>fa4x0D8rfOeLkV5f0c7PQgiPkVZiuiHeaZY5lahMpbV1Me/Hyyy086lVbIvTmdG4SmbW+KwSBhOZCYywEmM2qQ==</DP><DQ>uVwQmKNhqlBZAbRFEn8h1m+gM+ZDAdgf3xOpoVSdfq7yy87Z4zgyhm1cv87TsIcWS3+42quTLjofd+WnmaOoqQ==</DQ><InverseQ>4VGAgecowM/Ub+4kF3fWVN/k1+kepTdwDXkMept9XKbar08lmtNGyvMZU/9awwCYZZfs6l1gFyWLLKVm3g1UFQ==</InverseQ><D>W9Ie6xacPPCpVNSCww3u4gcUZ0l5oJbx0BdlW6IKQy1f6WfdKmzdX9LYCMk4ajhwBtqHbJq7tW++WJfuBdEhXHt6CMHw0y4+5tBVErq6nwkqFeogu/dV4ksBSwI/N644El1k3uBPOUigvDkLXn5qIrlO2sa+JUml65ABSy3jS4U=</D></RSAKeyValue>";

    public static string PublicKeyEncrypt(string value, string publicKey = RSAPublicKey)
    {
        RSACryptoServiceProvider rsp = new RSACryptoServiceProvider();
        rsp.FromXmlString(publicKey);
        
        byte[] valueBytes = StringToBytes(value);
        byte[] encryptedBytes = rsp.Encrypt(valueBytes, false);
        string base64EncryptedValue = Convert.ToBase64String(encryptedBytes);
        return base64EncryptedValue;
        //return Convert.ToBase64String(rsp.Encrypt(StringToBytes(value), false));
    }

    public static string PrivateKeyDecrypt(string encryptedValue, string privateKey = RSAPrivateKey)
    {
        RSACryptoServiceProvider rsp = new RSACryptoServiceProvider();
        rsp.FromXmlString(privateKey);
        byte[] encryptedBytes = Convert.FromBase64String(encryptedValue);
        byte[] valueBytes = rsp.Decrypt(encryptedBytes, false);
        string value = BytesToString(valueBytes);
        return value;
        //return BytesToString(rsp.Decrypt(Convert.FromBase64String(encryptedValue),false));
    }

    /// <summary>
    /// Base64 Encode
    /// </summary>
    /// <returns></returns>
    public static string Base64Encode(string value)
    {
        string result = Convert.ToBase64String(Encoding.UTF8.GetBytes(value));
        return result;
    }
    /// <summary>
    /// Base64 Decode
    /// </summary>
    /// <returns></returns>
    public static string Base64Decode(string value)
    {
        string result = Encoding.UTF8.GetString(Convert.FromBase64String(value));
        return result;
    }

    /// <summary>
    /// string to byte[]
    /// </summary>
    /// <param name="txt"></param>
    /// <returns></returns>
    public static byte[] StringToBytes(string txt)
    {
        return Encoding.UTF8.GetBytes(txt);
    }

    /// <summary>
    /// byte[] to string
    /// </summary>
    /// <param name="bitBytes"></param>
    /// <returns></returns>
    public static string BytesToString(byte[] bitBytes)
    {
        return Encoding.UTF8.GetString(bitBytes);
    }
}