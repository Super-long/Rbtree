#include<bits/stdc++.h>
using namespace std;

#include"Rbtree.h"

#define TestInsert  (1)     // 插入
#define TestRemove  (1<<2)  // 删除
#define TestPre     (1<<3)  // 寻找前驱
#define TestSuc     (1<<4)  // 寻找后继   

int Switch = TestInsert | TestRemove | TestPre | TestSuc;    // 表示测试项

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

    if(Switch&TestPre){
        cout << "寻找前驱\n";
        cout << tree->predecessor(80, -1) << endl;
        putchar('\n');
    }

    if(Switch&TestSuc){
        cout << "寻找后继\n";
        tree->insert(85);
        cout << tree->successor(85, -1) << endl;
        cout << tree->successor(90, -1) << endl;
        putchar('\n');
    }

    delete tree;    // 使用时记得智能指针
    return 0;
}