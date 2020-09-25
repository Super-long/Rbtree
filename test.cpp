#include<bits/stdc++.h>
using namespace std;

#include"Rbtree.h"
enum TestItem{
    Insert,     // 插入一系列数据并打印树
    Delete,
};

int Switch = Insert;    // 表示测试项

int main(){
    Rbtree<int>* tree = new Rbtree<int>();
    vector<int> items = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    cout << "原始数据：\n";
    for(auto x : items){
        cout << x << " ";
    }
    putchar('\n');

    switch (Switch){
        case Insert:
        for(auto x : items){
            tree->insert(x);
        }
        tree->print();

        case Delete:
    }
    return 0;
}