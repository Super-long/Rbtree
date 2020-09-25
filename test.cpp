#include<bits/stdc++.h>
using namespace std;

#include"Rbtree.h"

#define TestInsert (1)      // 插入
#define TestRemove (1<<2)   // 删除

int Switch = TestInsert | TestRemove;    // 表示测试项

int main(){
    Rbtree<int>* tree = new Rbtree<int>();
    vector<int> items = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    cout << "原始数据：\n";
    for(auto x : items){
        cout << x << " ";
    }
    putchar('\n');
    if(Switch&TestInsert){
        cout << "开始插入\n";
        for(auto x : items){
            tree->insert(x);
        }
        tree->print();
        putchar('\n');
    } 
    if(Switch&TestRemove){
        cout << "开始删除\n";
        for (size_t i = 0; i < items.size()/2; i++){
            tree->remove(items[i]);
        }
        tree->print();
        putchar('\n');
    }
    return 0;
}