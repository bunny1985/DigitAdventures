#include "RESPATH.h"
#include <string>

using namespace std;



const char* respatchFix(char * patch){
#ifndef _WP8 
	return patch;	
#else
	string patchStr = string(patch);
	replaceAll(patchStr, "/", "\\");
	return patchStr.c_str();
#endif

}


void replaceAll(string &s, const string &search, const string &replace) {
	for (size_t pos = 0;; pos += replace.length()) {
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}