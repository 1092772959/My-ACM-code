#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define INF 0x3f3f3f3f
#define SIZE 1<<8     //地址流数上限
#define MAXN 32        //实存地址空间上限
const LL VM_SIZE  = 1ll<<15;        //虚存容量
const LL PAGE_SIZE = 1<<10;      //页面大小
const int PAGE_NUM = 1<<5;       //页面总数
LL a[SIZE];                     //用于生成地址流
 //最佳淘汰算法
class OPT{
private:
    int table_size;                 //实存大小
    const int length = SIZE;        //指令流长度
    int num = PAGE_NUM;             //页面总数
    int used;                       //实存中被占用数
    int pageno[SIZE];               //页面序列
    int table[MAXN];                //内存-物理块映射表
    vector<int> pos[PAGE_NUM];      //pos[j]中记录页面j在地址流中以此出现的位置
    int nxt[SIZE][PAGE_NUM];        //nxt[i][j]表示位置i处，距离页面j一下次的距离
    bool pagefault[PAGE_NUM];       //页面失效
    double accuracy;                //命中率
    int page_size;                  //页面大小

public:
    void init(){                //初始化
        used = 0;
        table_size = MAXN;
        this->page_size = PAGE_SIZE;
        memset(table,-1,sizeof(table));
        memset(pagefault,1,sizeof(pagefault));
        accuracy = 1.0;
    }

    void get_page(LL *a){
        for(int i = 0;i < PAGE_NUM;++i)  pos[i].clear();
        for(int i = 0; i < length;++i){
            pageno[i] = a[i] / page_size;
            pos[pageno[i]].push_back(i);
        }
        get_next();
        print_pageno();
    }

    void change_pagesize(int sz){           //修改页面大小
        if(sz >= (1<<10) && sz <= (1<<13))
            page_size = sz;
            table_size = VM_SIZE / page_size;
    }

    void change_tablesize(int sz){          //修改实存大小
        if(sz>=1 && sz <= 32)
            table_size = sz;
    }

    void get_next(){        //获取nxt[i][j]
        int dis;
        for(int j = 0;j < num;++j) {
            int t = pos[j].size();
            int ptr = 0;
            for(int i = 0;i < length; ++i) {
                if(ptr >= t) nxt[i][j] = length + 1;
                else if (i < pos[j][ptr]) nxt[i][j] = pos[j][ptr] - i;
                else{
                    nxt[i][j] = 0;
                    ptr++;
                }
            }
        }
    }

    void run(){                     //调度
        for(int i = 0; i < length;++i){
            bool tag = false;
            int id = pageno[i];
            if(!pagefault[id]) {            //已经在实存内
                continue;
            }
            accuracy -= (double)1.0/length;              //修改命中率
            pagefault[id] = false;
            if(used < table_size){                     //检查实存中是否有空闲
                table[used] = id;                //依次添加
                used++;
                continue;
            }
            //选择最远的替换
            int out = -1, dis = -1;
            for(int j = 0,key,d; j < table_size; ++j){
                key = table[j];
                d = nxt[i][key];
                if(d > dis) {
                    out = j;
                    dis = d;
                }
            }
            pagefault[table[out]] = true;
            table[out] = id;                //替换
        }
    }

    double get_accuracy(){ return accuracy; }

    void print_pageno(){
        cout<<"PAGE NUMBER WITH SIZE "<<(page_size>>10)<<
            "k FOR EACH ADDRESS IS: "<<endl;
        for(int i = 0;i< length; i+=4){
            for(int j=0;j<4;++j){
                cout<<"pageno["<<i+j<<"]: "<<pageno[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"======================================"<<endl;
    }

    void show(){                    //输出实存中内容
        cout<<"实存中的内容: ";
        for(int i = 0;i < table_size;++i){
            if(table[i]==-1) cout<<"-1\t";
            else cout<<table[i]<<"\t";
        }
        cout<<endl;
    }

    ~OPT(){ cout << "End the result for opt "<<endl; }
};

struct node{            //链表结点
    int id;
    node * next;
};
typedef node * pointer;

class LRU{
private:
    node * head;                                //实存链表表头
    const static int num = PAGE_NUM;            //页面总数
    const static int length = SIZE;             //指令流长度
    int used;                                   //实存空闲空间
    bool pagefault[PAGE_NUM];                   //页面失效标志
    int table_size;                             //实存大小
    int pageno[SIZE];                           //指令流对应的页面号
    double accuracy;
    int page_size;

public:
    LRU(){
        head = new node;
        head ->next = NULL;
    }

    void init(){            //初始化
        head -> next = NULL;
        table_size = MAXN;
        memset(pagefault,1,sizeof(pagefault));
        used = 0 ;
        accuracy = 1.0 ;
    }

    void get_page(LL *a){
        srand((int)(time(0)));
        for(int i=0 ;i< length;++i){
            pageno[i] = a[i] / page_size;
        }
        print_pageno();
    }

    void change_pagesize(int sz){
        if(sz >= (1<<10) && sz <= (1<<13))
            page_size = sz;
    }

    void change_tablesize(int sz ){
        if(sz >=1 && sz <= 32)
            table_size = sz;
    }

    void delete_head(){                 //删除表头
        pointer ptr = head->next;
        if(ptr != NULL){
            head -> next = ptr->next;
            pagefault[ptr->id] = true;
            delete ptr;
        }
    }

    void move_to_tail(int id){          //移至表尾
        pointer ptr = head, pre, key;
        while(ptr->next != NULL){
            pre = ptr;
            ptr = ptr->next;
            if(ptr->id == id){
                key = ptr;
                pre ->next = ptr->next;
                ptr = pre;
                continue;
            }
        }
        ptr->next = key;
        key->next = NULL;
    }

    void insert(int id){            //不在实存中时
        pointer ptr = head, pre;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        pointer np = new node;
        np->id = id;
        np->next = NULL;
        ptr->next = np;
    }

    void run(){                                 //调用
        for(int i=0;i<length;++i){
            if(pagefault[pageno[i]]){           //若不在实存中,则加入
                insert(pageno[i]);
                pagefault[pageno[i]] = false;
                if(used >= table_size)             //检查是否需要将队首删除
                    delete_head();
                else used++;
                accuracy -= 1.0/length;
            }
            else{                               //若已经在队列中，则调整其至队尾
                move_to_tail(pageno[i]);
            }
        }
        clear();
    }

    double get_accuracy(){ return accuracy; }

    void print_pageno(){
        cout<<"PAGE NUMBER WITH SIZE "<<(page_size>>10)<<
            "k FOR EACH ADDRESS IS: "<<endl;
        for(int i = 0;i< length; i+=4){
            for(int j=0;j<4;++j){
                cout<<"pageno["<<i+j<<"]: "<<pageno[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"======================================"<<endl;
    }

    void show(){                //内存中的内容，debug用
        cout<<"实存中的内容:";
        pointer ptr = head;
        while(ptr->next != NULL){
            ptr = ptr -> next;
            cout<<ptr -> id;
            if(ptr -> next!=NULL)  cout<<" -> ";
        }
        cout<<endl;
    }

    void clear(){               //删除链表
        pointer ptr = head->next,cur;
        while(ptr != NULL){
            cur = ptr;
            ptr = ptr->next;
            delete cur;
        }
    }

    ~LRU(){
        cout<<"End the result for lru "<<endl;
        delete head;
    }
};

//实习题二
class FIFO{
private:
    const int num = PAGE_NUM;                   //页面总数
    const int length = SIZE;                    //指令流长度
    int used;                                   //实存空闲空间
    bool pagefault[PAGE_NUM];                   //页面失效标志
    int table_size;                             //实存大小
    int pageno[SIZE];                           //实存存放的页表
    double accuracy;
    int page_size;
    int table[MAXN];

public:
    void init(){                //初始化
        used = 0;
        table_size = MAXN;
        this->page_size = page_size;
        memset(table,-1,sizeof(table));
        memset(pagefault,1,sizeof(pagefault));
        accuracy = 1.0;
    }

    void get_page(LL *a){
        for(int i = 0; i < length;++i){
            pageno[i] = a[i] / page_size;
        }
        print_pageno();
    }

    void change_pagesize(int sz){           //修改页面大小
        if(sz >= (1<<10) && sz <= (1<<13))
            page_size = sz;
    }

    void change_tablesize(int sz){          //修改实存大小
        if(sz>=1 && sz <= 32)
            table_size = sz;
    }

    void print_pageno(){
        cout<<"PAGE NUMBER WITH SIZE "<<(page_size>>10)<<
            "k FOR EACH ADDRESS IS: "<<endl;
        for(int i = 0;i< length; i+=4){
            for(int j=0;j<4;++j){
                cout<<"pageno["<<i+j<<"]: "<<pageno[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"======================================"<<endl;
    }

    double get_accuracy() {return accuracy;}

    void run(){
        int ptr = 0;                            //用一个指针记录应该淘汰的位置
        for(int i = 0, key, out;i<length;++i){
            key = pageno[i];
            if(!pagefault[key]) continue;
            accuracy -= 1.0 / length;
            pagefault[key] = false;
            if(used < table_size){
                table[used++] = key;
            }
            else{
                out = table[ptr];
                pagefault[out] = true;
                table[ptr] = key;
            }
            ptr++;
            ptr %= table_size;
        }
    }

    ~FIFO() { cout<<"End the result for fifo "<<endl; }
};

class LFU{
private:
    const int num = PAGE_NUM;                   //页面总数
    const int length = SIZE;                    //指令流长度
    int used;                                   //实存空闲空间
    bool pagefault[PAGE_NUM];                   //页面失效标志
    int table_size;                             //实存大小
    int pageno[SIZE];                           //实存存放的页表
    double accuracy;
    int page_size;
    int table[MAXN];
    int cnt[MAXN];                              //计数器

public:
    void init(){
        used = 0;
        table_size = MAXN;
        this->page_size = page_size;
        memset(table,-1,sizeof(table));
        memset(cnt,0,sizeof(cnt));
        memset(pagefault,1,sizeof(pagefault));
        accuracy = 1.0;
    }
    
    void get_page(LL *a){
        for(int i = 0; i < length;++i){
            pageno[i] = a[i] / page_size;
        }
        print_pageno();
    }

    void change_pagesize(int sz){           //修改页面大小
        if(sz >= (1<<10) && sz <= (1<<13))
            page_size = sz;
    }

    void change_tablesize(int sz){          //修改实存大小
        if(sz>=1 && sz <= 32)
            table_size = sz;
    }

    void print_pageno(){
        cout<<"PAGE NUMBER WITH SIZE "<<(page_size>>10)<<
            "k FOR EACH ADDRESS IS: "<<endl;
        for(int i = 0;i< length; i+=4){
            for(int j=0;j<4;++j){
                cout<<"pageno["<<i+j<<"]: "<<pageno[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"======================================"<<endl;
    }

    double get_accuracy() {return accuracy;}

    void run(){
        for(int i=0;i< length;++i){
            int key = pageno[i];
            if(!pagefault[key]) {
                for(int j =0;j< used;++j){
                    if(table[j] == key){
                        cnt[j]++;
                        break;
                    }
                }
                continue;
            }
            accuracy -= 1.0 / length;
            pagefault[key] = false;
            if(used < table_size){
                table[used++] = key;
            }
            else{
                int mn = INF, pos = -1;
                for(int j=0;j<table_size;++j){
                    if(cnt[j]<mn){
                        mn = cnt[j];
                        pos = j;
                    }
                }
                cnt[pos] = 0;
                int out = table[pos];
                pagefault[out] = true;
                table[pos] = key;
            }
        }   
    }
};

//-------------------------------------------------------------测试
void menu()
{
    cout<<"(1) 最佳淘汰算法(OPT)"<<endl;
    cout<<"(2) 最近最少使用页淘汰算法(LRU)"<<endl;
    cout<<"(3) 先进先出算法(FIFO)"<<endl;
    cout<<"(4) 最少使用置换算法(LFU)"<<endl;
    cout<<"(9) 退出"<<endl;
    cout<<"选择替换算法";
}

void test_OPT(){
    OPT gao;
    double acc[33];
    cout<<"The algorithm is OPT \n";
    for(int p = 1; p <= 8; p<<=1 ){
        gao.change_pagesize((1<<10)*p);
        gao.get_page(a);
        for(int i=4; i*p <= 32;i+=2){
            gao.init();
            gao.change_tablesize(i);
            gao.run();
            acc[i] = gao.get_accuracy();
        }
        cout<<"page assigned\t\t"<<"pages_in/total references"<<endl;
        for(int i = 4; i*p <= 32; i += 2){
            cout<<i<<"\t\t\t\t\t"<<acc[i]<<endl;
        }
    }
}

void test_LRU(){
    LRU gao;
    double acc[33];
    cout<<"The algorithm is LRU\n";
    for(int p = 1; p <= 8; p<<=1 ){
        gao.change_pagesize((1<<10)*p);
        gao.get_page(a);
        for(int i=4;i * p <= 32;i += 2){
            gao.init();
            gao.change_tablesize(i);
            gao.run();
            acc[i] = gao.get_accuracy();
        }
        cout<<"page assigned\t\t"<<"pages_in/total references"<<endl;
        for(int i=4;i*p <= 32;i+=2){
            cout<<i<<"\t\t\t\t\t"<<acc[i]<<endl;
        }
    }
}

void test_FIFO(){
    FIFO gao;
    double acc[33];
    cout<<"The algorithm is opt \n";
    for(int p = 1; p <= 8; p<<=1 ){
        gao.change_pagesize((1<<10)*p);
        gao.get_page(a);
        for(int i=4;i*p<=32;i += 2){
            gao.init();
            gao.change_tablesize(i);
            gao.run();
            acc[i] = gao.get_accuracy();
        }
        cout<<"page assigned\t\t"<<"pages_in/total references"<<endl;
        for(int i = 4; i*p <= 32; i += 2){
            cout<<i<<"\t\t\t\t\t"<<acc[i]<<endl;
        }
    }
}

void test_LFU(){
    LFU gao;
    double acc[33];
    cout<<"The algorithm is LFU \n";
    for(int p = 1; p <= 8; p<<=1 ){
        gao.change_pagesize((1<<10)*p);
        gao.get_page(a);
        for(int i=4;i*p<=32;i += 2){
            gao.init();
            gao.change_tablesize(i);
            gao.run();
            acc[i] = gao.get_accuracy();
        }
        cout<<"page assigned\t\t"<<"pages_in/total references"<<endl;
        for(int i = 4; i*p <= 32; i += 2){
            cout<<i<<"\t\t\t\t\t"<<acc[i]<<endl;
        }
    }
}

void generate_address(){            //生成地址流并打印
    const int length = SIZE;
    cout<<"THE VIRTUAL ADDRESS STREAM AS FOLLOWS: "<<endl;
    srand(int(time(0)));
    int tot = VM_SIZE, half = VM_SIZE/2;
    int start = rand() % (tot-SIZE) ;
    for(int i = 0 ,j = start;i < length/2;++i,++j)    //百分之五十连续
        a[i] = j;
    for(int i =length/2; i<length;++i) {     //百分之二五 前半部分， 百分之二五后半部分
        if(i &1) a[i] = rand()% half;
        else a[i] = rand()% tot;
    }
    //输出
    for(int i = 0;i < length; i+=4){
        for(int j=0;j<4;++j){
            cout<<"a["<<i+j<<"]="<<setw(9)<<setiosflags(ios::left)<<a[i+j];
        }
        cout<<endl;
    }
    cout<<"======================================"<<endl;
}

int main(){
    int mode;
    bool tag = true;
    double acc[33];
    generate_address();
    while(tag){
        menu();
        cin>>mode;
        switch (mode){
        case 1:
            test_OPT();
        break;
        case 2:
            test_LRU();
        break;
        case 3:
            test_FIFO();
        break;
        case 4:
            test_LFU();
        break;
        case 9:
            tag = false;
        break;
        default:
            cout<<"错误的选择"<<endl;
        break;
        }
    }
    return 0;
}
