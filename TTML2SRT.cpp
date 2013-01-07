#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct SubtitleLine {
string bh;
string bm;
string bs;
string bms;
string ds;
string dms;
string eh;
string em;
string es;
string ems;
string content;
};

string stripCR_Endl(string line) {
string newline;
for(int i = 0; i < line.length(); i++) {
if(line[i] != '\r' && line[i] != '\n' && (i != 0 || line[i] != ' ') ) {
newline += line[i];
}	
}
return newline;
}

string leadingZero(string s, int m) {
if(s.length() == 1 && m == 1) {
s.insert(0,1,'0');
} else if(s.length() == 1 && m == 2) {
s.insert(0,1,'0');
s.insert(0,1,'0');
} else if(s.length() == 2 && m == 2) {
s.insert(0,1,'0');
}
return s;
}

string convertFromTime(string s, int m) {
	string tmp = "";
	string result = "";
	if(m == 1) {
	for(int i = 0; i < s.length(); i++) {
		if(s[i] == ':') {
			if(tmp == "") {
			tmp = "0";	
			}
			tmp = leadingZero(tmp, 1);
			result += tmp;
			tmp = "";
		} else if(s[i] == '.') {
		if(tmp == "") {
		tmp = "0";	
		}
			tmp = leadingZero(tmp, 1);
			result += tmp;
			tmp = "";
		} else {
		tmp += s[i];	
		}
	}
	if(tmp == "") {
		tmp = "0";	
		}
			tmp = leadingZero(tmp, 2);
			result += tmp;
			tmp = "";
	} else if(m == 2) {
	result += "0000";
	for(int i = 0; i < s.length(); i++) {
		if(s[i] == '.') {
		if(tmp == "") {
		tmp = "0";	
		}
			tmp = leadingZero(tmp, 1);
			result += tmp;
			tmp = "";
		} else {
		tmp += s[i];	
		}
	}
	tmp = leadingZero(tmp, 2);
			result += tmp;
			tmp = "";
	}
	return result;
}

string convertToTime(string s) {
	string result = "";
	for(int i = 0; i < s.length(); i++) {
	if(s[i] != 0) {
	result += s[i];	
	}
	if(i == 1) {
	result += ':';	
	}
	if(i == 3) {
	result += ':';	
	}
	if(i == 5) {
	result += '.';	
	}
	}
return result;
}

string addStringInts(string a, string b) {
string c;
char add;
bool mem = false;
int i = a.length()-1;
while(i >= 0) {
if(mem == true) {
if(((a[i]-48)+(b[i]-48)+1) > 9) {
mem = true;
add = ((a[i]-48)+(b[i]-48)+1)%10+48;
c.insert(0,1,add);
} else {
mem = false;
add = ((a[i]-48)+(b[i]-48)+1)+48;
c.insert(0,1,add);
}
} else {
if(((a[i]-48)+(b[i]-48)) > 9) {
mem = true;
add = ((a[i]-48)+(b[i]-48))%10+48;
c.insert(0,1,add);
} else {
mem = false;
add = ((a[i]-48)+(b[i]-48))+48;
c.insert(0,1,add);
}	
}
i--;
}
return c;
}

int main(int argc, char** argv) {
cout << "TTML2SRT Subtitle Format Converter v. 0.1 (C) 2013 by Phitherek_" << endl;
if(argc != 3) {
//DEBUG: if(argc != 2) {
cout << "Usage: " << argv[0] << " input.xml output.srt" << endl;	
} else {
ifstream in(argv[1]);
if(!in) {
cerr << "Could not open	input TTML file! Exiting..." << endl;
return EXIT_FAILURE;
}
vector<SubtitleLine> v;
string line;
string action = "parseLine";
string parsed = "";
string begin = "";
string dur = "";
string h = "";
string m = "";
string s = "";
string ms = "";
string ds = "";
string dms = "";
while(!in.eof()) {
char cline[9999];
in.getline(cline, 9999);
line = cline;
if(in) {
line = stripCR_Endl(line);
cout << "TTML Input >> '" << line << "'" << endl;
for(int i = 0; i < line.length(); i++) {
if(action == "parseLine") {
if(line[i] == '<') {
action = "parseMarkup";
}
} else if(action == "parseMarkup") {
if(line[i] != '>' && line[i] != ' ') {
parsed += line[i];
} else {
if(parsed == "?xml") {
	cout << "Parse: Found XML header, skipping..." << endl;
	action = "skip";
} else if(parsed == "tt") {
	cout << "Parse: Found TTML document start markup, skipping..." << endl;
	action = "skip";
} else if(parsed == "head") {
	cout << "Parse: Found HEAD markup, skipping all the HEAD content..." << endl;
	action = "skipHead";
} else if(parsed == "body") {
	cout << "Parse: Found BODY markup..." << endl;
	action = "parseLine";	
} else if(parsed == "div") {
	cout << "Parse: Found DIV markup, skipping..." << endl;
	action = "skip";	
} else if(parsed == "p") {
	cout <<	"Parse: Found P markup, proceeding to subtitle line parsing..." << endl;
	action = "parseP";
} else if(parsed == "/div") {
	cout << "Parse: Found DIV end markup..." << endl;
	action = "parseLine";
} else if(parsed == "/body") {
	cout << "Parse: Found BODY end markup..." << endl;
	action = "parseLine";
} else if(parsed == "/tt") {
	cout << "Parse: Found TTML document end markup..." << endl;
	action = "parseLine";	
} else {
	cout << "Parse: Unknown markup: " << parsed << "!" << endl;
	action = "parseLine";	
}
parsed = "";
}
} else if(action == "skip") {
if(line[i] == '>') {
action = "parseLine";
}	
} else if(action == "skipHead") {
if(line[i] == '<') {
action = "parseSkipHead";
}	
} else if(action == "parseSkipHead") {
if(line[i] != '>') {
parsed += line[i];
} else {
if(parsed == "/head") {
action = "parseLine";	
} else {
action = "skipHead";	
}
parsed = "";
}	
} else if(action == "parseP") {
if(line[i] != ' ' && line[i] != '=' && line[i] != '>') {
	parsed += line[i];
} else if(line[i] == '=') {
	if(parsed == "begin") {
	cout << "ParseP: BEGIN found..." << endl;
	action = "parseBegin";	
	} else if(parsed == "dur") {
	cout << "ParseP: DUR found..." << endl;
	action = "parseDur";	
	}
	parsed = "";
} else if(line[i] == '>') {
	cout << "ParseP: > found, parsing content..." << endl;
action = "parseContent";
parsed = "";
}
} else if(action == "parseBegin") {
if(line[i] == '"') {
action = "parseBeginContent";	
}
} else if(action == "parseBeginContent") {
if(line[i] != '"') {
parsed += line[i];
} else {
string newparsed = "";
string fill = "h";
begin = parsed;
bool wasdot = false;
for(int j = 0; j < parsed.length(); j++) {
	if(parsed[j] != ':' && parsed[j] != '.') {
		newparsed += parsed[j];
	} else if(parsed[j] == ':') {
		if(fill == "h") {
		h = newparsed;
		newparsed = "";
		fill = "m";
		} else if(fill == "m") {
		m = newparsed;
		newparsed = "";
		}
	} else if(parsed[j] == '.') {
		s = newparsed;
		newparsed = "";
		wasdot = true;
	}
}
if(wasdot == true) {
ms = newparsed;
} else {
s = newparsed;
ms = "0";
}
newparsed = "";
cout << "ParseP: Parsed BEGIN: Hour: " << h << ", Minute: " << m << ", Second: " << s << ", Milisecond: " << ms << endl;
action = "parseP";
parsed = "";
}	
} else if(action == "parseDur") {
if(line[i] == '"') {
action = "parseDurContent";
}	
} else if(action == "parseDurContent") {
if(line[i] != '"') {
parsed += line[i];
} else {
dur = parsed;
string newparsed = "";
bool wasdot = false;
for(int j = 0; j < parsed.length(); j++) {
if(parsed[j] == '.') {
ds = newparsed;
newparsed = "";
wasdot = true;
} else {
newparsed += parsed[j];
}	
}
if(wasdot == true) {
dms = newparsed;
} else {
ds = newparsed;
dms = "0";
}
newparsed = "";
cout << "ParseP: Parsed DUR: Seconds: " << ds << ", Miliseconds: " << dms << endl;
action = "parseP";
parsed = "";
}
} else if(action == "parseContent") {
if(line[i] != '<' && line[i] != '{' && line[i] != '/') {
parsed += line[i];
if(i == line.length()-1) {
parsed += '\n';	
}
} else if(line[i] == '<') {
cout << "ParseP: Parsed CONTENT: " << parsed << endl;
if(h != "" && m != "" && s != "" && ms != "" && ds != "") {
if(dms == "") {
dms = "0";
}
cout << "ParseP: Creating new SubtitleLine with parsed data..." << endl;
SubtitleLine sl;
sl.bh = h;
sl.bm = m;
sl.bs = s;
sl.bms = ms;
sl.ds = ds;
sl.dms = dms;
sl.content = parsed;
cout << "ParseP: Computing missing values and freeing temporary variables..." << endl;
h = "";
m = "";
s = "";
ms = "";
ds = "";
dms = "";
parsed = "";
string end = convertToTime(addStringInts(convertFromTime(begin, 1), convertFromTime(dur, 2)));
begin = "";
dur = "";
cout << "ParseP: Computing END..." << endl;;
string newparsed = "";
string eh = "";
string em = "";
string es = "";
string ems = "";
string fill = "h";
bool wasdot = false;
for(int j = 0; j < end.length(); j++) {
	if(end[j] != ':' && end[j] != '.') {
		newparsed += end[j];
	} else if(end[j] == ':') {
		if(fill == "h") {
		eh = newparsed;
		newparsed = "";
		fill = "m";
		} else if(fill == "m") {
		em = newparsed;
		newparsed = "";
		}
	} else if(end[j] == '.') {
		es = newparsed;
		newparsed = "";
		wasdot = true;
	}
}
if(wasdot == true) {
ems = newparsed;
} else {
es = newparsed;
ems = "0";
}
newparsed = "";
cout << "ParseP: Computed END: Hour: " << eh << ", Minute: " << em << ", Second: " << es << ", Milisecond: " << ems << endl;
sl.eh = eh;
sl.em = em;
sl.es = es;
sl.ems = ems;
cout << "ParseP: Saving SubtitleLine to vector..." << endl;
v.push_back(sl);
} else {
cout << "ParseP: Incomplete/incorrect P, ignoring..." << endl;
h = "";
m = "";
s = "";
ms = "";
ds = "";
dms = "";
parsed = "";
}
action = "parseLine";
} else if(line[i] == '{') {
action = "parseContentSkipBrackets";	
}
} else if(action == "parseContentSkipBrackets") {
if(line[i] == '}') {
action = "parseContent";	
}
}	
}
}
}
if(v.size() == 0) {
cerr << "Parse failed! Exiting..." << endl;
return EXIT_FAILURE;
} else {
cout << "Parse completed successfully! Number of read lines: " << v.size() << endl;
cout << "Saving content as .SRT to output file..." << endl;
ofstream out(argv[2]);
if(!out) {
cerr << "Could not open output SRT file! Exiting..." << endl;
return EXIT_FAILURE;
}
int SRTSubNumber = 1;
for(int i = 0; i < v.size(); i++) {
out << SRTSubNumber << endl << leadingZero(v[i].bh, 1) << ":" << leadingZero(v[i].bm, 1) << ":" << leadingZero(v[i].bs, 1) << "," << leadingZero(v[i].bms, 2) << " --> " << leadingZero(v[i].eh, 1) << ":" << leadingZero(v[i].em, 1) << ":" << leadingZero(v[i].es, 1) << "," << leadingZero(v[i].ems, 2) << endl << v[i].content << endl << endl;
SRTSubNumber++;
}
}
}
cout << "All done! Thank you for using Phitherek' s TTLM2SRT Subtitle Format Converter!" << endl;
return EXIT_SUCCESS;
}
