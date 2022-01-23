#include <iostream>

//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

// 全局变量，记录递归函数的递归层数
int count = 0;

// 输入 n，打印 n 个 tab 缩进
void printIndent(int n) {
    for (int i = 0; i < n; i++) {
        printf("    ");
    }
}

int main(){
    printIndent(2);
}