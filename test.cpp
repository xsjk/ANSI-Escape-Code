#include "main.hpp"

int main() {

    std::cout << foreground("red");			// 设置字体颜色为红色
    std::cout << background("black");       // 设置背景颜色为黑色
    std::cout << "Hello, world!\n";
    std::cout << style("reset");			// 重置以清除所有效果

    std::cout << style("underline");		// 设置下划线
    std::cout << "Hello, world!\n";
    std::cout << style("reset");			// 重置以清除所有效果

    std::cout << cursor("up",2);			// 向上移动2个单位
    std::cout << cursor("right");			// 向右移动1个单位
    std::cout << "***";
    std::cout << cursor(5,1,true);			// 向右移动5个单位，向下移动1个单位

    std::cout << erase("line","before");		// 删除 
    std::cout << "Hello, world!\n";

    
    std::cout << decorated("Hello, World!\n", {foreground("red"), background("black")});
    std::cout << decorated("Hello, World!\n", {style("underline")});
    std::cout << decorated("***", {cursor("up",2),cursor("right")}, {cursor(5,1,true)});
    std::cout << decorated("Hello, World!\n", {erase("line","before")});

}

