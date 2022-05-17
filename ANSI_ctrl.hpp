#include <string>
#include <iostream>
#include <map>
#include <initializer_list>
using decorator = std::string;

std::string CSI = "\033[";
std::string OSC = "\033]";
char BEL = '\a';

decorator set_title(std::string title){
    return OSC + "2;" + title + BEL;
}

std::map<std::string,int> _fg = {
    {"black",30},
    {"red",31},
    {"green",32},
    {"yellow",33},
    {"blue",34},
    {"magenta",35},
    {"cyan",36},
    {"white",37},
    {"reset",39},
    {"lightblack",90},
    {"lightred",91},
    {"lightgreen",92},
    {"lightyellow",93},
    {"lightblue",94},
    {"lightmagenta",95},
    {"lightcyan",96},
    {"lightwhite",97}
};

std::map<std::string,int> _bg = {
    {"black",40},
    {"red",41},
    {"green",42},
    {"yellow",43},
    {"blue",44},
    {"magenta",45},
    {"cyan",46},
    {"white",47},
    {"reset",49},
    {"lightblack",100},
    {"lightred",101},
    {"lightgreen",102},
    {"lightyellow",103},
    {"lightblue",104},
    {"lightmagenta",105},
    {"lightcyan",106},
    {"lightwhite",107}
};

std::map<std::string,int> _st = {
    {"reset",0},
    {"bright",1},
    {"dim",2},
    {"italic",3},
    {"underline",4},
    {"blink",5},
    {"reverse",7},
    {"hidden",8},
    {"crossed",9},
    {"default",10},
    {"underline2",21}
};

std::map<std::string,char> _cs = {
    {"up",'A'},
    {"down",'B'},
    {"right",'C'},
    {"forward",'C'},
    {"left",'D'},
    {"backward",'D'},
    {"next",'E'},
    {"previous",'F'},
    {"column",'G'},
    {"line",'K'},
    {"screen",'J'},
    {"pageup",'S'},
    {"pagedown",'T'}

};

std::map<std::string,int> _er = {
    {"after",0},
    {"before",1},
    {"all",2},
    {"entire",2},
};


class foreground : public decorator {
    public: 
        foreground(int r, int g, int b) : decorator(CSI+"38;2;"+std::to_string(r)+';'+std::to_string(g)+';'+std::to_string(b)+'m') {}
        foreground(int color) : decorator(CSI+"38;5;"+std::to_string(color)+'m') {}
        foreground(std::string s) : decorator(CSI+std::to_string(_fg[s])+'m') {}
};

class background : public decorator {
    public: 
        background(int r, int g, int b) : decorator(CSI+"48;2;"+std::to_string(r)+';'+std::to_string(g)+';'+std::to_string(b)+'m') {}
        background(int color) : decorator(CSI+"48;5;"+std::to_string(color)+'m') {}
        background(std::string s) : decorator(CSI+std::to_string(_bg[s])+'m') {}
};

class style : public decorator {
    public: 
        style(int s=0) : decorator(CSI+std::to_string(s)+'m') {}
        style(std::string s) : style(_st[s]) {}
};
#define abs(x) ((x) < 0 ? -(x) : (x))
class cursor : public decorator {
    public: 
        cursor(int x, int y, bool relative=false) : decorator(
            relative ? (CSI+std::to_string(abs(x))+_cs[x>0?"right":"left"]+
                        CSI+std::to_string(abs(y))+_cs[y>0?"down":"up"])
                     : CSI+std::to_string(y)+';'+std::to_string(x)+'H' ) {}
        cursor(int x, bool relative=false): decorator(
            relative ? (CSI+std::to_string(abs(x))+_cs[x>0?"right":"left"])
                     : CSI+std::to_string(x)+'G' ) {}
        cursor(const std::string& s, int n=1) : decorator(CSI+std::to_string(n)+_cs[s]) {}
        cursor(const char* s, int n=1) : cursor(std::string(s),n) {}
};

class erase : public decorator {
    public: 
        erase(std::string m,std::string s) : decorator(CSI+std::to_string(_er[s])+_cs[m]) {}
};


std::string decorated(const std::string& s, std::initializer_list<decorator> begin={}, std::initializer_list<decorator> end={style("reset")}) {
    std::string ret = "";
    for(const auto&i : begin) ret += i;
    ret += s;
    for(const auto&i : end) ret += i;
    return ret;
}
