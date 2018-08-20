#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <G3DAll.h>
#include "NixVfs.h"
#include "ContentCache.h"

//#include "stdafx.h"

using namespace std;
using namespace G3D;


class Parser
{
public:
	Parser(const string &filename);
	~Parser(); 

	void parse(const string &fileName);

	string fetchAsString(const string &type, const string &attrib);
	int fetchAsInt(const string &type, const string &attrib);
	double fetchAsDouble(const string &type, const string &attrib);
	float fetchAsFloat(const string &type, const string &attrib);

	NixTextureRef fetchAsTexture(TextureCache &vc, const string &type, 
								 const string &attrib);

private:

	string fullTrim( const string &str, const string &delim = ";", const string &whitespace = "\t ");
	string trim( const string &str, const string &whitespace = "\t ");
	string ltrim( const string &str, const string &whitespace = "\t ");
	string rtrim( const string &str, const string &whitespace = "\t ");
	string commentTrim ( const string &str, const string &delim = ";" );
	bool isEmpty( const string &str );
	bool splitLine(const string &str, string &firsthalf, string &secondhalf, const string &delim = "=");
	string extractHeader( const string &str );
	bool isHeader( const string &str );
	bool isSubsection( const string &str, const string &divider = "/" );


	Table<string, Table<string, string>* > tabTypes;

};

#endif