#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int SEG_SIZE = 4;         //段大小
const int TABLE_SIZE = 4;      //实存最大段数
const int PAGE_SIZE = 4;        //页面大小
const int MEM_SIZE = (1<<10);   //内存总大小
//以上皆为存储上限

class Query{                    //查询结构体
public:
    int seg_num;            //段号
    int page_num;           //页号
    int offset;             //偏移量

    Query(int s_num = 0,int p_num = 0, int oset = 0):
        seg_num(s_num), page_num(p_num), offset(oset){}
};

class Segment{      //段表结构
private:
    const int len = SEG_SIZE;           //段长，不可修改
    int page_table[SEG_SIZE];           //页表
    int start_pos;                      //起始编号

public:
    Segment(){
        start_pos = -1;
        //按次序分配页表
        memset(page_table,-1,sizeof(page_table));
    }

    void set_page(int start){
        start_pos = start;
        for(int i=0, j = start;i<len;++i,j+=PAGE_SIZE){
            page_table[i] = j;
        }
    }

    int get_page(int index){
        if(index<0 || index>=len) return -1;
        return page_table[index];
    }

    void print_page(){
        cout << "起始页号: " << start_pos << endl;
        for(int i = 0;i< len; i+=4){
            for(int j=0;j<4;++j){
                cout<<"page["<<i+j<<"]: "<<page_table[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"===================================================="<<endl;
    }
};

class Segment_Page{         //段页式存储结构
private:
    const int size = TABLE_SIZE;        //表大小
    Segment table[TABLE_SIZE];          //段表
    LL mem[MEM_SIZE];                   //内存中内存

public:
    Segment_Page() {
        srand((int)(time(0)));
        for(int i=0;i<MEM_SIZE;++i){
            mem[i] = (LL)rand();
        }

        for(int i=0,j=0;i<TABLE_SIZE && j*PAGE_SIZE<MEM_SIZE;
            ++i,j+= SEG_SIZE*PAGE_SIZE){
            table[i].set_page(j);
        }
    }
    void print_table(){
        for(int i=0;i<size;++i){
            table[i].print_page();
        }
    }

    void print_mem(){
        for(int i = 0;i< MEM_SIZE; i+=8){
            for(int j=0;j<8;++j){
                cout<<"MEM["<<i+j<<"]: "<<mem[i+j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"====================================================" << endl;
    }

    LL query(const Query & Q){              //查询
        int s_num = Q.seg_num, p_num = Q.page_num, off = Q.offset;
        //判断是否越界等错误
        if(s_num < 0 || s_num >= TABLE_SIZE ){
            cout << "段号越界!" <<endl;
            return -1;
        }
        int base = table[s_num].get_page(p_num);       //获取该页的起始地址
        if(base < 0){
            cout << "页号越界!" <<endl;
            return -1;
        }

        if(off<0 || off >= PAGE_SIZE || base+off >= MEM_SIZE){
            cout<< "偏移量越界!" <<endl;
            return -1;
        }

        return mem[base +off];
    }
};

//---------------------------------测试

void test(){
    Segment_Page sys;
    sys.print_mem();
    sys.print_table();
    Query Q;
    int tag=0;
    do{
        cout << "实存大小: "<< TABLE_SIZE<<endl;
        cout << "段表大小: "<< SEG_SIZE << endl;
        cout << "页表大小: " << PAGE_SIZE <<endl;
        cout << "-----------------------" << endl;
        cout << "段号: ";  cin>>Q.seg_num;
        cout << "页号: ";  cin>>Q.page_num;
        cout << "偏移量: ";   cin>>Q.offset;
        int info = sys.query(Q);
        cout<<"得到内容为: "<<info<<endl;

        cout << "输入9退出: "; cin>>tag;
    }while(tag!=9);
    cout<<"The end of test."<<endl;
}

int main(){
    test();
    return 0;
}
