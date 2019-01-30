// by iwpz
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpAES
{
    class Program
    {
        static void Main(string[] args)
        {
            AESTest();
            RSATest();
            RSATestCppValue();
        }

        static void AESTest() {
            Console.WriteLine("===================C# AES-ECB-PKCS7padding Demo===================");
            string str = "english string to encrypt";
            string enStr = EncryptHelper.AESEncrypt(str);
            Console.WriteLine("Encrypt:\n" + str + "\nto:\n" + enStr);
            Console.WriteLine("========================================================");
            string deStr = EncryptHelper.AESDecrypt(enStr);
            Console.WriteLine("Decrypt:\n" + enStr + "\nto:\n" + deStr);
            Console.WriteLine("========================================================");
            string cnStr = "锄禾日当午";
            string enCNStr = EncryptHelper.AESEncrypt(cnStr);
            Console.WriteLine("加密：:\n" + cnStr + "\n到:\n" + enCNStr);
            Console.WriteLine("========================================================");
            string deCNStr = EncryptHelper.AESDecrypt(enCNStr);
            Console.WriteLine("解密:\n" + enCNStr + "\n到:\n" + deCNStr);
            Console.WriteLine("========================================================");
            string longStr = "测试要加密的长文本哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈";
            string enLongStr = EncryptHelper.AESEncrypt(longStr);
            Console.WriteLine("加密：:\n" + longStr + "\n到:\n" + enLongStr);
            string deLongStr = EncryptHelper.AESDecrypt(enLongStr);
            Console.WriteLine("解密:\n" + enLongStr + "\n到:\n" + deLongStr);
            Console.WriteLine();
        }
        static void RSATest() {
            Console.WriteLine("===================C# RSA Demo===================");
            string str = "english string to encrypt";
            string enStr = EncryptHelper.PublicKeyEncrypt(str);
            Console.WriteLine("PublicKeyEncrypt:\n" + str + "\nto:\n" + enStr);
            Console.WriteLine("========================================================");
            string deStr = EncryptHelper.PrivateKeyDecrypt(enStr);
            Console.WriteLine("PrivateKeyDecrypt:\n" + enStr + "\nto:\n" + deStr);
            Console.WriteLine("========================================================");

            string cnStr = "锄禾日当午汗滴禾下土";
            string enCNStr = EncryptHelper.PublicKeyEncrypt(cnStr);
            Console.WriteLine("公钥加密：:\n" + cnStr + "\n到:\n" + enCNStr);
            Console.WriteLine("========================================================");
            string deCNStr = EncryptHelper.PrivateKeyDecrypt(enCNStr);
            Console.WriteLine("私钥解密:\n" + enCNStr + "\n到:\n" + deCNStr);
            Console.WriteLine();
        }

        static void RSATestCppValue() {
            Console.WriteLine("===================C# Decrypt C++ Value Demo===================");
            //Encrypted by C++
            //"english string to encrypt"
            string CppPublicKeyEncryptedStr = "IVdX6YqvmiBD1qDd1hpw3eC9vZqSzuZ8XV9tTBvHrktiCbjX7oshgPgySglOGCJ+lFFBUTSbxA7auuS3LVP54Vu6kn1qY+Q4zar0ZsdDwfKtqb2FDHh9l6u3Sqh1ebNDaNJ6z19O4E+6D1aOxTyzKtPTWYeHairrlrfkSfwTaRM=";
            //Encrypted by C# 
            //"锄禾日当午汗滴禾下土"
            string CppPublicKeyEncryptedStr2 = "OAArQ5L3ig0HKf6EWB8KE7fjz5O82M1ThJ93s9ni7BSfyp6ONzE/esGr+j+AUgZSSFOyi/0zzd31VvuxLMrcfv8pkL1bBqqSokJnbWoKdSOwx9Zoi4wDDwIJ8nkcOO8ApG0gGady4Y46Z4le2GdA2QPbpN7Q72fz9eGb98EV0bA=";
            string CSharpPrivateKeyDecryptedStr = EncryptHelper.PrivateKeyDecrypt(CppPublicKeyEncryptedStr);
            string CSharpPrivateKeyDecryptedStr2 = EncryptHelper.PrivateKeyDecrypt(CppPublicKeyEncryptedStr2);
            Console.WriteLine("C# PrivateKey Dectypt result:" + CSharpPrivateKeyDecryptedStr);
            Console.WriteLine("C# 私钥解密结果:" + CSharpPrivateKeyDecryptedStr2);
        }
    }
}
