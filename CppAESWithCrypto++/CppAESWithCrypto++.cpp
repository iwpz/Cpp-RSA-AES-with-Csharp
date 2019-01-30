// by iwpz
//

#include "pch.h"
#include <iostream>
#include <string>
#include "EncryptHelper.h"
using namespace std;

void AESTest() {
	cout << "===================C++ AES-ECB-PKCS7padding Demo===================" << endl;
	string str = "english string to encrypt";
	string enStr = EncryptHelper::AESEncrypt(str);
	cout << "Encrypt:\n" + str + "\n to \n" + enStr << endl;
	cout << "========================================================" << endl;
	string deStr = EncryptHelper::AESDecrypt(enStr);
	cout << "Decrypt:\n" + enStr + "\n to \n" + deStr << endl;
	cout << "========================================================" << endl;
	string cnStr = "锄禾日当午";
	string enCNStr = EncryptHelper::AESEncrypt(cnStr);
	cout << "加密：:\n" + cnStr + "\n 到 \n" + enCNStr << endl;
	cout << "========================================================" << endl;
	string deCNStr = EncryptHelper::AESDecrypt(enCNStr);
	cout << "解密:\n" + enCNStr + "\n 到 \n" + deCNStr << endl;
	cout << "========================================================" << endl;
	string longStr = "测试要加密的长文本哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈";
	string enLongStr = EncryptHelper::AESEncrypt(longStr);
	cout << "加密：:\n" + longStr + "\n 到 \n" + enLongStr << endl;
	string deLongStr = EncryptHelper::AESDecrypt(enLongStr);
	cout << "解密:\n" + enLongStr + "\n 到 \n" + deLongStr << endl << endl;
}

void RSATest() {
	cout << "===================C++ RSA Demo===================" << endl;
	string str = "english string to encrypt";
	string enStr = EncryptHelper::PublicKeyEncrypt(str);
	cout << "PublicKey Encrypt:\n" + str + "\n to \n" + enStr << endl;
	cout << "========================================================" << endl;
	string deStr = EncryptHelper::PrivateKeyDecrypt(enStr);
	cout << "PrivateKey Decrypt:\n" + enStr + "\n to \n" + deStr << endl;
	cout << "========================================================" << endl;
	string cnStr = "锄禾日当午";
	string enCNStr = EncryptHelper::PublicKeyEncrypt(cnStr);
	cout << "公钥加密：:\n" + cnStr + "\n 到 \n" + enCNStr << endl;
	cout << "========================================================" << endl;
	string deCNStr = EncryptHelper::PrivateKeyDecrypt(enCNStr);
	cout << "私钥解密:\n" + enCNStr + "\n 到 \n" + deCNStr << endl;
	cout << "========================================================" << endl<<endl;
}

void RSATestCSharpValue() {
	cout << "===================C++ Decrypt C# Value Demo===================" << endl;
	//Encrypted by C# 
	//"english string to encrypt"
	string CSharpPublicKeyEncryptedStr = "pXMv3Q5JeVIZZSExK4uDCL7jmb5asK+wIexFydwUhtlu6IZwec+SPitSIgvcbOZpqqrCZL3tb2Lw7qKt3nmPVoUnp284LnySANFXM1TxKG27S7rRfDY8hh0K6QbEpMMZoWnmjiRKCQniMy4SUClZxbTwXCNLbHYYsMoi7t0At5I=";
	//Encrypted by C#
	//"锄禾日当午汗滴禾下土"
	string CSharpPublicKeyEncryptedStr2 = "dJfffUY8H5U9GjraVdQHoOOqDp2oSEk+SOB3HMSwAAjrn1xGk+2QGBsSrA1uQZxSDlnPB+9wLQng8TsA0XetB+6R+1cFa17q5FvqWj1Mhx4xwDSnHAK4u49hvC9WUoyu8YdJ3kIKFmKhrvaF6w0P+otF3RqSHFJ/5Ncc2CV2Tw0=";
	string CppPrivateKeyDecryptedStr = EncryptHelper::PrivateKeyDecrypt(CSharpPublicKeyEncryptedStr);
	string CppPrivateKeyDecryptedStr2 = EncryptHelper::PrivateKeyDecrypt(CSharpPublicKeyEncryptedStr2);
	
	cout << "C++ PrivateKey Dectypt result:" << CppPrivateKeyDecryptedStr << endl;
	cout << "C++私钥解密结果:" << CppPrivateKeyDecryptedStr2 << endl;

}

int main()
{
	AESTest();
	RSATest();
	RSATestCSharpValue();
}
