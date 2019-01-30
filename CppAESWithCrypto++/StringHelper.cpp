#include "StringHelper.h"
#include <iostream>
#include <string>
#include <sstream>
#include <io.h>
#include <tchar.h>
#include <Windows.h>

//#include "boost/algorithm/string.hpp"
#include <Bits.h>

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

/// <summary>
/// 字节BASE64编码
/// </summary>
/// <param name="input">要编码的字节</param>
/// <returns>Base64字符串</returns>
std::string base64_encode_byte(vector<BYTE> input) {
	unsigned int bufLen = input.size();
	BYTE* buf = new BYTE[bufLen];
	for (int i = 0; i < input.size(); i++) {
		buf[i] = input[i];
	}
	std::string ret;
	int i = 0;
	int j = 0;
	BYTE char_array_3[3];
	BYTE char_array_4[4];
	while (bufLen--) {
		char_array_3[i++] = *(buf++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}
	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';
		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];
		while ((i++ < 3))
			ret += '=';
	}
	return ret;
}


void removeAll(string &str, char c)
{
	string::iterator new_end = remove_if(str.begin(), str.end(), bind2nd(equal_to<char>(), c));
	str.erase(new_end, str.end());
}

std::vector<BYTE> base64_decode_byte(std::string const& encoded_string) {
	string tempStr = encoded_string;
	removeAll(tempStr, '\n');
	//iWPZ: 移除换行符
	int in_len = tempStr.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	BYTE char_array_4[4], char_array_3[3];
	std::vector<BYTE> ret;
	while (in_len-- && (tempStr[in_] != '=') && is_base64(tempStr[in_])) {
		char_array_4[i++] = tempStr[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				char_array_4[i] = base64_chars.find(char_array_4[i]);
			}
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				ret.push_back(char_array_3[i]);
			}
			i = 0;
		}
	}
	if (i) {
		for (j = i; j < 4; j++)
		{
			char_array_4[j] = 0;
		}
		for (j = 0; j < 4; j++)
		{
			char_array_4[j] = base64_chars.find(char_array_4[j]);
		}
		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
		for (j = 0; (j < i - 1); j++) { ret.push_back(char_array_3[j]); }
	}
	return ret;
}

string StringHelper::base64_encode(string in) {
	string a = StringHelper::UnicodeToUtf8(StringHelper::string2wstring(in).c_str());
	const unsigned char *bytes_to_encode = (const unsigned char*)a.c_str();
	unsigned int in_len = a.length();
	string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}
	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';
		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}
	return ret;

}

string StringHelper::base64_decode(std::string const& encoded_string) {
	string aaa = encoded_string;
	removeAll(aaa, '\n');
	int in_len = aaa.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	string ret;
	while (in_len-- && (aaa[in_] != '=') && is_base64(aaa[in_])) {
		char_array_4[i++] = aaa[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = 0; j < i; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

wstring StringHelper::string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//将wstring转换成string  
string StringHelper::wstring2string(wstring wstr)
{

	int len = WideCharToMultiByte(54936, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (len == 0)
	{
		return "";
	}
	char *pRes = new char[len];
	if (pRes == NULL)
	{
		return "";
	}
	WideCharToMultiByte(54936, 0, wstr.c_str(), wstr.length() + 2, pRes, len, NULL, NULL);
	pRes[len - 1] = '\0';
	std::string result = pRes;
	delete[] pRes;
	return result;
}

bool StringHelper::string2bool(string value) {
	if (strcmp(value.c_str(), "True") || strcmp(value.c_str(), "true")) {
		return true;
	}
	else {
		return false;
	}
}

bool StringHelper::wstring2bool(wstring value) {
	if (lstrcmpW(value.c_str(), L"True") || lstrcmpW(value.c_str(), L"true")) {
		return true;
	}
	else {
		return false;
	}
}

int StringHelper::string2int(string value) {
	return strtol(value.c_str(), NULL, 10);
}

int StringHelper::wstring2int(wstring value) {
	return wcstol(value.c_str(), NULL, 10);
}

std::wstring StringHelper::Utf8ToUnicode(const std::string &strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	if (len == 0)
	{
		return L"";
	}

	wchar_t *pRes = new wchar_t[len];
	if (pRes == NULL)
	{
		return L"";
	}

	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, pRes, len);
	pRes[len - 1] = L'\0';
	std::wstring result = pRes;
	delete[] pRes;

	return result;
}

char* StringHelper::UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}