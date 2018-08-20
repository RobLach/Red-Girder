#include "stdafx.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Parser.h"

using namespace std;
using namespace G3D;



Parser::Parser(const string &filename)
{
	parse(filename);
}

Parser::~Parser()
{
	// this may or may not be right for cleaning up memory
	tabTypes.deleteValues();
}
void Parser::parse(const string &fileName)
{
    ifstream myFile(fileName.c_str());
	string strKey;
	string strValue;
	string line;
	string strType;
	string strSubType;

	Table<string, string> *tabConfigs;

    if (! myFile)
    {
        cout << "Error opening output file" << endl;
    }

	while(getline(myFile, line))
	{
		line = commentTrim(line);

		if(!isEmpty(line))
		{
			if(isHeader(line))
			{
				strType = extractHeader(line);
				
				if(isSubsection(strType))
				{
					string strParent;

					splitLine(strType, strParent, strSubType, "/");
					
					/* Not worrying if parent exists of not anymore
					if(!tabTypes.containsKey(strType))
					{
						tabConfigs = new Table<string, string>();
						tabTypes.set(strType, tabConfigs);
					}
					*/
					
					tabConfigs = new Table<string, string>();
					tabTypes.set(strSubType, tabConfigs);
					tabConfigs->set("parent", strParent);

				}
				else
				{
					if(!tabTypes.containsKey(strType))
					{
						tabConfigs = new Table<string, string>();
						tabTypes.set(strType, tabConfigs);
					}
					else
						tabConfigs = tabTypes.get(strType);
				}
			}
			else //not a header
			{
				//protection against badly formed lines
				if(splitLine(line, strKey, strValue))
				{
					tabConfigs->set(strKey, strValue);
					//cout << "for " << strType << ", " << strKey << " has value " << strValue << endl;
				}
			}
		}
	}

	myFile.close();
}


string Parser::fetchAsString(const string &type, const string &attrib)
{
	Table<string, string> *tabConfigs;
	//Table<string, string> *tabParent;
	string retStr;
	string temp;

	//look to see if you can find it
	if(tabTypes.get(type, tabConfigs)) //get type table
		if(tabConfigs->get(attrib, retStr)) //look in table
			return retStr;
		else
			//if you cant find it look for parent
			while(tabConfigs->get("parent", temp))//has a parent
			{
				if(tabTypes.get(temp, tabConfigs)) //tabConfigs now points to parent
				{
					if(tabConfigs->get(attrib, retStr)) //check in parent table
						return retStr;
				}
				else
					break; //no info about parent
			}

	return "";
}

int Parser::fetchAsInt(const string &type, const string &attrib)
{
	return atoi(fetchAsString(type, attrib).c_str());
}

double Parser::fetchAsDouble(const string &type, const string &attrib)
{
	return atof(fetchAsString(type, attrib).c_str());
}

float Parser::fetchAsFloat(const string &type, const string &attrib)
{
	return atof(fetchAsString(type, attrib).c_str());
}


NixTextureRef Parser::fetchAsTexture(TextureCache &vc, const string &type, const string &attrib)
{
	return vc.get(fetchAsString(type,attrib));
}



bool Parser::isSubsection( const string &str, const string &divider )
{
	return(str.find(divider) != string::npos);
}

string Parser::extractHeader( const string &str )
{
	string::size_type index1 = str.find('[');
	string::size_type index2 = str.find(']');

	return trim(str.substr(index1 + 1, index2-index1 - 1));
}

bool Parser::isHeader( const string &str )
{
	string::size_type index = str.find_first_not_of("\t ");
	if ( index == string::npos ) //blank line
		return false;

	if( str.substr(index, 1) == "[" ) //starts with [
	{
		if ( str.find(']') == string::npos ) // doesn't have ]
		{	
			cout << "Warning: Possibly missing ] for intended header." << endl;
			return false;
		}
		else //starts with [ and has ]
			return true;
	}

	return false; //doesn't start with [
}

bool Parser::isEmpty( const string &str )
{
	return(str.find_first_not_of("\t ") == string::npos);
}

string Parser::ltrim( const string &str, const string &whitespace)
{
   string::size_type index = str.find_first_not_of(whitespace);
   if( index != string::npos )
       return str.substr(index);
   
   return "";
}

string Parser::rtrim( const string &str, const string &whitespace)
{

   string::size_type index = str.find_last_not_of(whitespace);
   if( index != string::npos )
       return str.substr(0,index+1);

   return str;
}

string Parser::commentTrim( const string &str, const string &delim)
{
	string::size_type index = str.find(delim);
	if (index != string::npos)
		return str.substr(0, index);

	return str;
}

string Parser::trim( const string &str, const string &whitespace)
{
	return rtrim(ltrim(str, whitespace), whitespace);
}

string Parser::fullTrim( const string &str, const string &delim, const string &whitespace )
{
	return trim(commentTrim(str, delim), whitespace);
}

bool Parser::splitLine(const string &str, string &firsthalf, string &secondhalf, const string &delim)
{
	string::size_type index = commentTrim(str).find(delim);
	if (index != string::npos)
	{
		firsthalf = trim(str.substr(0, index));
		secondhalf = fullTrim(str.substr(index + delim.length()));
		return true;
	}
	else
	{
		cout << "Error: Can't find delimiter to split line around" << endl;
		return false;
	}
}