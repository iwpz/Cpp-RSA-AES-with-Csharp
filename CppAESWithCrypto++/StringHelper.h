#pragma once
#include <string>
#include <vector>
//#include <Windows.h>
#include <cryptopp/randpool.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
//#include <boost/program_options.hpp>

typedef unsigned char       BYTE;
using namespace std;

class StringHelper
{
public:
	StringHelper();
	~StringHelper();

	static wstring string2wstring(string str);
	static string wstring2string(wstring wstr);
	static bool string2bool(string value);
	static bool wstring2bool(wstring value);
	static int string2int(string value);
	static int wstring2int(wstring value);
	static wstring Utf8ToUnicode(const string &strUTF8);
	static char* UnicodeToUtf8(const wchar_t* unicode);
	static string base64_encode(string in);
	static std::string base64_decode(std::string const& s);
};

