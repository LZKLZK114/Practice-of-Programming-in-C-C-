/*
感谢2024级通班牛煦同学的开源😭

*/
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;
int hour;int minute;
int city[22][3];int sum_citys;//每座城市存2个数，0---红方编号，1---蓝方编号，利用city访问时要减1
int monsters_element[5]={};int monsters_attack[5]={};string monsters_name[5]={"dragon","ninja","iceman","lion","wolf"};string weapon_name[4]={"sword","bomb","arrow","arrow"};
int lion_loyalty_loss;
bool game_end=false;
void print_time(){
    cout<<setfill('0')<<setw(3)<<hour<<':'<<setfill('0')<<setw(2)<<minute<<' ';
}
class Warrior{
public:
    int num;//勇士的编号
    int kind;
    int HP;//生命值
    int attack;//攻击力
    int position;//在几号城市
    bool alive;
    string name;
    int weapon[4]={};
    int sum_of_equipment;
    Warrior(int n):num(n),sum_of_equipment(0),alive(true){}
    virtual ~Warrior(){}
};
class Dragon:public Warrior{
public:
    Dragon(int n):Warrior(n){
        kind=0;
        HP=monsters_element[0];
        weapon[num%3]++;
        sum_of_equipment++;
    }
};
class Ninja:public Warrior{
public:
    Ninja(int n):Warrior(n){
        kind=1;
        HP=monsters_element[1];
        weapon[num%3]++;
        weapon[(num+1)%3]++;
        sum_of_equipment+=2;
    }    
};
class Iceman:public Warrior{
public:
    Iceman(int n):Warrior(n){
        kind=2;
        HP=monsters_element[2];
        weapon[num%3]++;
        sum_of_equipment++;
    }
};
class Lion:public Warrior{
public:
    int loyalty;
    Lion(int n,int l):Warrior(n),loyalty(l){
        kind=3;
        HP=monsters_element[3];
        weapon[num%3]++;
        sum_of_equipment++;
    }
};
class Wolf:public Warrior{
public:
    Wolf(int n):Warrior(n){
        kind=4;
        HP=monsters_element[4];
    }
};
class Army{
public:
    friend Warrior;
    string name;
    int army_num;
    int elements;
    int sum_warriors;//仅仅是编号，包括已经战死的和逃跑的
    bool able_to_create;
    Warrior** warrior;//这是存的是指针的Warrior数组
    int orders[5];
    void set_orders(int x1,int x2,int x3,int x4,int x5){
        orders[0]=x1;orders[1]=x2;orders[2]=x3;orders[3]=x4;orders[4]=x5;
    }
    Army():sum_warriors(0),able_to_create(true),warrior(NULL){}
    ~Army(){
        for(int i=0;i<sum_warriors;i++){
            delete warrior[i];
        }
        delete[] warrior;
    }
    void create_monster(){
        if(able_to_create){
            if(elements<monsters_element[orders[hour%5]]){able_to_create=false;return;}
            elements-=monsters_element[orders[hour%5]];
            Warrior* new_warrior=NULL;
            print_time();
            cout<<name<<' '<<monsters_name[orders[hour%5]]<<' '<<hour+1<<" born"<<endl;
            switch(orders[hour%5]){
            case 0:new_warrior=new Dragon(hour+1);break;
            case 1:new_warrior=new Ninja(hour+1);break;
            case 2:new_warrior=new Iceman(hour+1);break;
            case 3:new_warrior=new Lion(hour+1,elements);cout<<"Its loyalty is "<<elements<<endl;break;
            case 4:new_warrior=new Wolf(hour+1);break;
            }
            new_warrior->position=(sum_citys+1)*army_num;
            new_warrior->attack=monsters_attack[new_warrior->kind];
            city[(sum_citys+1)*army_num][army_num]=hour+1;
            Warrior**tempwarrior=new Warrior*[sum_warriors+1];
            memcpy(tempwarrior,warrior,sizeof(Warrior*)*sum_warriors);
            tempwarrior[sum_warriors]=new_warrior;
            delete[] warrior;
            warrior=tempwarrior;            
            sum_warriors++;
        }
    }
};
Army red,blue;
void _create_monster(){
    red.create_monster();blue.create_monster();
}
void lion_escape(){
    for(int c=0;c<=sum_citys+1;c++){
        if(city[c][0]){
            if(red.warrior[city[c][0]-1]->kind==3){
                auto p=(Lion*)red.warrior[city[c][0]-1];
                if(p->loyalty<=0){
                    red.warrior[city[c][0]-1]->alive=false;
                    print_time();
                    cout<<"red lion "<<city[c][0]<<" ran away"<<endl;
                    city[c][0]=0;
                }
            }
        }
        if(city[c][1]){
            if(blue.warrior[city[c][1]-1]->kind==3){
                auto p=(Lion*)blue.warrior[city[c][1]-1];
                if(p->loyalty<=0){
                    blue.warrior[city[c][1]-1]->alive=false;
                    print_time();
                    cout<<"blue lion "<<city[c][1]<<" ran away"<<endl;
                    city[c][1]=0;
                }   
            }
        }
    }
}
void march(){
    if(city[1][1]&&blue.warrior[city[1][1]-1]->alive){
        blue.warrior[city[1][1]-1]->position=0;
        if(blue.warrior[city[1][1]-1]->kind==2){
            int debuff=blue.warrior[city[1][1]-1]->HP*1/10;
            blue.warrior[city[1][1]-1]->HP-=debuff;
        }
        print_time();cout<<"blue "<<monsters_name[blue.warrior[city[1][1]-1]->kind]<<' '<<city[1][1]<<" reached red headquarter with "
        <<blue.warrior[city[1][1]-1]->HP<<" elements and force "<<blue.warrior[city[1][1]-1]->attack<<endl;
        print_time();cout<<"red headquarter was taken"<<endl;
        game_end=true;
    }
    for(int c=1;c<=sum_citys;c++){
        if(city[c-1][0]&&red.warrior[city[c-1][0]-1]->alive){
            red.warrior[city[c-1][0]-1]->position++;
            if(red.warrior[city[c-1][0]-1]->kind==3){
                auto p=(Lion*)red.warrior[city[c-1][0]-1];
                p->loyalty-=lion_loyalty_loss;
            }
            if(red.warrior[city[c-1][0]-1]->kind==2){
                int debuff=red.warrior[city[c-1][0]-1]->HP*1/10;
                red.warrior[city[c-1][0]-1]->HP-=debuff;
            }
            print_time();cout<<"red "<<monsters_name[red.warrior[city[c-1][0]-1]->kind]<<' '<<city[c-1][0]<<" marched to city "<<c
            <<" with "<<red.warrior[city[c-1][0]-1]->HP<<" elements and force "<<red.warrior[city[c-1][0]-1]->attack<<endl;            
        }
        if(city[c+1][1]&&blue.warrior[city[c+1][1]-1]->alive){
            blue.warrior[city[c+1][1]-1]->position--;
            if(blue.warrior[city[c+1][1]-1]->kind==3){
                auto p=(Lion*)blue.warrior[city[c+1][1]-1];
                p->loyalty-=lion_loyalty_loss;
            }
            if(blue.warrior[city[c+1][1]-1]->kind==2){
                int debuff=blue.warrior[city[c+1][1]-1]->HP*1/10;
                blue.warrior[city[c+1][1]-1]->HP-=debuff;
            }
            print_time();cout<<"blue "<<monsters_name[blue.warrior[city[c+1][1]-1]->kind]<<' '<<city[c+1][1]<<" marched to city "<<c
            <<" with "<<blue.warrior[city[c+1][1]-1]->HP<<" elements and force "<<blue.warrior[city[c+1][1]-1]->attack<<endl;            
        }
    }
    if(city[sum_citys][0]&&red.warrior[city[sum_citys][0]-1]->alive){
        red.warrior[city[sum_citys][0]-1]->position=sum_citys+1;
        if(red.warrior[city[sum_citys][0]-1]->kind==2){
            int debuff=red.warrior[city[sum_citys][0]-1]->HP*1/10;
            red.warrior[city[sum_citys][0]-1]->HP-=debuff;
        }
        print_time();cout<<"red "<<monsters_name[red.warrior[city[sum_citys][0]-1]->kind]<<' '<<city[sum_citys][0]<<" reached blue headquarter with "
        <<red.warrior[city[sum_citys][0]-1]->HP<<" elements and force "<<red.warrior[city[sum_citys][0]-1]->attack<<endl;
        print_time();cout<<"blue headquarter was taken"<<endl;
        game_end=true;
    }
    for(int c=0;c<=sum_citys;c++){city[c][1]=city[c+1][1];}city[sum_citys+1][1]=0;
    for(int c=sum_citys+1;c>0;c--){city[c][0]=city[c-1][0];}city[0][0]=0;
}
void wolf_rob(){
    int s;
    for(int c=1;c<=sum_citys;c++){
        if(city[c][0]&&city[c][1]){
            if(red.warrior[city[c][0]-1]->kind==4&&blue.warrior[city[c][1]-1]->kind==4)continue;
            if(red.warrior[city[c][0]-1]->kind==4){
                if(blue.warrior[city[c][1]-1]->sum_of_equipment==0||red.warrior[city[c][0]-1]->sum_of_equipment==10)continue;
                if(blue.warrior[city[c][1]-1]->weapon[0]!=0){
                    s=min(blue.warrior[city[c][1]-1]->weapon[0],10-red.warrior[city[c][0]-1]->sum_of_equipment);
                    blue.warrior[city[c][1]-1]->weapon[0]-=s;blue.warrior[city[c][1]-1]->sum_of_equipment-=s;
                    red.warrior[city[c][0]-1]->weapon[0]+=s;red.warrior[city[c][0]-1]->sum_of_equipment+=s;
                    print_time();cout<<"red wolf "<<city[c][0]<<" took "<<s<<" sword from blue "
                    <<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" in city "<<c<<endl;
                }
                else if(blue.warrior[city[c][1]-1]->weapon[1]!=0){
                    s=min(blue.warrior[city[c][1]-1]->weapon[1],10-red.warrior[city[c][0]-1]->sum_of_equipment);
                    blue.warrior[city[c][1]-1]->weapon[1]-=s;blue.warrior[city[c][1]-1]->sum_of_equipment-=s;
                    red.warrior[city[c][0]-1]->weapon[1]+=s;red.warrior[city[c][0]-1]->sum_of_equipment+=s;
                    print_time();cout<<"red wolf "<<city[c][0]<<" took "<<s<<" bomb from blue "
                    <<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" in city "<<c<<endl;
                }
                else{
                    int s1=0,s2=0;
                    s=min(blue.warrior[city[c][1]-1]->weapon[2]+blue.warrior[city[c][1]-1]->weapon[3],10-red.warrior[city[c][0]-1]->sum_of_equipment);
                    if(s>blue.warrior[city[c][1]-1]->weapon[2]){s1=blue.warrior[city[c][1]-1]->weapon[2];s2=s-s1;}
                    blue.warrior[city[c][1]-1]->weapon[2]-=s1;blue.warrior[city[c][1]-1]->weapon[3]-=s2;blue.warrior[city[c][1]-1]->sum_of_equipment-=s;
                    red.warrior[city[c][0]-1]->weapon[2]+=s1;red.warrior[city[c][0]-1]->weapon[3]+=s2;red.warrior[city[c][0]-1]->sum_of_equipment+=s;
                    print_time();cout<<"red wolf "<<city[c][0]<<" took "<<s<<" arrow from blue "
                    <<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" in city "<<c<<endl;
                }
            }
            if(blue.warrior[city[c][1]-1]->kind==4){
                if(red.warrior[city[c][0]-1]->sum_of_equipment==0||blue.warrior[city[c][1]-1]->sum_of_equipment==10)continue;
                if(red.warrior[city[c][0]-1]->weapon[0]!=0){
                    s=min(red.warrior[city[c][0]-1]->weapon[0],10-blue.warrior[city[c][1]-1]->sum_of_equipment);
                    red.warrior[city[c][0]-1]->weapon[0]-=s;red.warrior[city[c][0]-1]->sum_of_equipment-=s;
                    blue.warrior[city[c][1]-1]->weapon[0]+=s;blue.warrior[city[c][1]-1]->sum_of_equipment+=s;
                    print_time();cout<<"blue wolf "<<city[c][1]<<" took "<<s<<" sword from red "
                    <<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" in city "<<c<<endl;
                }
                else if(red.warrior[city[c][0]-1]->weapon[1]!=0){
                    s=min(red.warrior[city[c][0]-1]->weapon[1],10-blue.warrior[city[c][1]-1]->sum_of_equipment);
                    red.warrior[city[c][0]-1]->weapon[1]-=s;red.warrior[city[c][0]-1]->sum_of_equipment-=s;
                    blue.warrior[city[c][1]-1]->weapon[1]+=s;blue.warrior[city[c][1]-1]->sum_of_equipment+=s;
                    print_time();cout<<"blue wolf "<<city[c][1]<<" took "<<s<<" bomb from red "
                    <<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" in city "<<c<<endl;
                }
                else{
                    int s1=0,s2=0;
                    s=min(red.warrior[city[c][0]-1]->weapon[2]+red.warrior[city[c][0]-1]->weapon[3],10-blue.warrior[city[c][1]-1]->sum_of_equipment);
                    if(s>red.warrior[city[c][0]-1]->weapon[2]){s1=red.warrior[city[c][0]-1]->weapon[2];s2=s-s1;}
                    red.warrior[city[c][0]-1]->weapon[2]-=s1;red.warrior[city[c][0]-1]->weapon[3]-=s2;red.warrior[city[c][0]-1]->sum_of_equipment-=s;
                    blue.warrior[city[c][1]-1]->weapon[2]+=s1;blue.warrior[city[c][1]-1]->weapon[3]+=s2;blue.warrior[city[c][1]-1]->sum_of_equipment+=s;
                    print_time();cout<<"red wolf "<<city[c][1]<<" took "<<s<<" arrow from blue "
                    <<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" in city "<<c<<endl;
                }
            }
        }
    }
}
void cheer(int c){
    if(city[c][0]&&red.warrior[city[c][0]-1]->kind==0&&red.warrior[city[c][0]-1]->HP>0){
        print_time();cout<<"red dragon "<<red.warrior[city[c][0]-1]->num<<" yelled in city "<<c<<endl;
    }
    if(city[c][1]&&blue.warrior[city[c][1]-1]->kind==0&&blue.warrior[city[c][1]-1]->HP>0){
        print_time();cout<<"blue dragon "<<blue.warrior[city[c][1]-1]->num<<" yelled in city "<<c<<endl;
    }    
}
void fight(){
    for(int c=1;c<=sum_citys;c++){
        int first=0;
        if(city[c][0]&&city[c][1]){
            first=c%2;
            Warrior* invader;
            Warrior* victim;
            int red_num=0,blue_num=0,red_kind=0,blue_kind=0;
            int red0=red.warrior[city[c][0]-1]->weapon[0],red1=red.warrior[city[c][0]-1]->weapon[1],red2=red.warrior[city[c][0]-1]->weapon[2],red3=red.warrior[city[c][0]-1]->weapon[3];
            int blue0=blue.warrior[city[c][1]-1]->weapon[0],blue1=blue.warrior[city[c][1]-1]->weapon[1],blue2=blue.warrior[city[c][1]-1]->weapon[2],blue3=blue.warrior[city[c][1]-1]->weapon[3];
            int u_red1=0,u_red2=0,u_red3=0,u_blue1=0,u_blue2=0,u_blue3=0;
            int i_kind;
            int r=0,e=red.warrior[city[c][0]-1]->sum_of_equipment+blue.warrior[city[c][1]-1]->sum_of_equipment;
            for(;;){
                if(r>e*5)break;
                //决定使用什么武器               
                if(first%2==1){
                    invader=red.warrior[city[c][0]-1];victim=blue.warrior[city[c][1]-1];
                    for(;;){
                        red_num++;
                        if(red_kind==0){
                            if(red_num<=red0){break;}
                            else red_kind++;
                        }
                        if(red_kind==1){
                            if(red_num<=red0+red1){u_red1++;break;}
                            else red_kind=3;
                        }
                        if(red_kind==3){
                            if(red_num<=red0+red1+red3){u_red3++;break;}
                            else red_kind=2;
                        }
                        if(red_kind==2){
                            if(red_num<=red0+red1+red2+red3){u_red2++;break;}
                        }
                        if(red_num>invader->sum_of_equipment){
                            red_num-=(invader->sum_of_equipment+1);
                            red_kind=0;red1=0;red3=red2;red2=0;
                            u_red1=0;u_red2=0;u_red3=0;
                            invader->sum_of_equipment=red0+red3;
                            invader->weapon[1]=0;invader->weapon[2]=0;
                            invader->weapon[3]=red3;
                        }
                        if(invader->sum_of_equipment==0)break;
                    }
                    i_kind=red_kind;
                }
                else{
                    invader=blue.warrior[city[c][1]-1];victim=red.warrior[city[c][0]-1];
                    for(;;){
                        blue_num++;
                        if(blue_kind==0){
                            if(blue_num<=blue0)break;
                            else blue_kind++;
                        }
                        if(blue_kind==1){
                            if(blue_num<=blue0+blue1){u_blue1++;break;}
                            else blue_kind=3;
                        }
                        if(blue_kind==3){
                            if(blue_num<=blue0+blue1+blue3){u_blue3++;break;}
                            else blue_kind=2;
                        }
                        if(blue_kind==2){
                            if(blue_num<=blue0+blue1+blue2+blue3){u_blue2++;break;}
                        }
                        if(blue_num>invader->sum_of_equipment){
                            blue_num-=(invader->sum_of_equipment+1);
                            blue_kind=0;blue1=0;blue3=blue2;blue2=0;
                            u_blue1=0;u_blue2=0;u_blue3=0;
                            invader->sum_of_equipment=blue0+blue3;
                            invader->weapon[1]=0;invader->weapon[2]=0;
                            invader->weapon[3]=blue3;
                        }
                        if(invader->sum_of_equipment==0)break;
                    }
                    i_kind=blue_kind;
                }
                if(invader->sum_of_equipment==0){
                    r++;first++;continue;
                }
                int loss;//记录生命值
                switch(i_kind){
                case 0:loss=invader->attack*2/10;break;
                case 1:loss=invader->attack*4/10;break;
                case 2:loss=invader->attack*3/10;break;
                case 3:loss=invader->attack*3/10;break;
                }
                victim->HP-=loss;
                if(i_kind==1&&invader->kind!=1)invader->HP-=loss/2;
                //是否死亡？---city[c][*]的值改变，alive改变，
                if(invader->HP<=0)invader->alive=false;
                if(victim->HP<=0)victim->alive=false;
                if(!(invader->alive&&victim->alive))break;
                if(i_kind==0&&loss==0)r++;//检测状态是否改变，以及状态未改变的回合数  
                else r=0;           
                first++;
            }
            //是否平局？谁获胜了？汇报！除你武器！
            if(invader->alive&&victim->alive){
                //000:40 both red iceman 1 and blue lion 12 died in city 2
                print_time();cout<<"both red "<<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]
                <<" and blue "<<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]
                <<" were alive in city "<<c<<endl;
            }
            else if((!invader->alive)&&(!victim->alive)){
                print_time();cout<<"both red "<<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]
                <<" and blue "<<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]
                <<" died in city "<<c<<endl;
                city[c][0]=0;city[c][1]=0;
            }
            else if(red.warrior[city[c][0]-1]->alive&&(!blue.warrior[city[c][1]-1]->alive)){
                red1-=u_red1;red3=red3-u_red3+u_red2;red2-=u_red2;blue1-=u_blue1;blue3=blue3-u_blue3+u_blue2;blue2-=u_blue2;
                int rob=10-red0-red1-red2-red3,temp=0;
                if(rob>0){temp=min(rob,blue0);rob-=temp;red.warrior[city[c][0]-1]->weapon[0]=red0+temp;}
                if(rob>0){temp=min(rob,blue1);rob-=temp;red.warrior[city[c][0]-1]->weapon[1]=red1+temp;}
                if(rob>0){temp=min(rob,blue2);rob-=temp;red.warrior[city[c][0]-1]->weapon[2]=red2+temp;}
                if(rob>0){temp=min(rob,blue3);rob-=temp;red.warrior[city[c][0]-1]->weapon[3]=red3+temp;}
                red.warrior[city[c][0]-1]->sum_of_equipment=red.warrior[city[c][0]-1]->weapon[0]+red.warrior[city[c][0]-1]->weapon[1]+red.warrior[city[c][0]-1]->weapon[2]+red.warrior[city[c][0]-1]->weapon[3];
                print_time();cout<<"red "<<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" killed blue "
                <<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" in city "<<c
                <<" remaining "<<red.warrior[city[c][0]-1]->HP<<" elements"<<endl;
                city[c][1]=0;
            }
            else if(blue.warrior[city[c][1]-1]->alive&&(!red.warrior[city[c][0]-1]->alive)){
                red1-=u_red1;red3=red3-u_red3+u_red2;red2-=u_red2;blue1-=u_blue1;blue3=blue3-u_blue3+u_blue2;blue2-=u_blue2;
                int rob=10-blue0-blue1-blue2-blue3,temp=0;
                if(rob>0){temp=min(rob,red0);rob-=temp;blue.warrior[city[c][1]-1]->weapon[0]=blue0+temp;}
                if(rob>0){temp=min(rob,red1);rob-=temp;blue.warrior[city[c][1]-1]->weapon[1]=blue1+temp;}
                if(rob>0){temp=min(rob,red2);rob-=temp;blue.warrior[city[c][1]-1]->weapon[2]=blue2+temp;}
                if(rob>0){temp=min(rob,red3);rob-=temp;blue.warrior[city[c][1]-1]->weapon[3]=blue3+temp;}
                blue.warrior[city[c][1]-1]->sum_of_equipment=blue.warrior[city[c][1]-1]->weapon[0]+blue.warrior[city[c][1]-1]->weapon[1]+blue.warrior[city[c][1]-1]->weapon[2]+blue.warrior[city[c][1]-1]->weapon[3];
                print_time();cout<<"blue "<<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" killed red "
                <<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" in city "<<c
                <<" remaining "<<blue.warrior[city[c][1]-1]->HP<<" elements"<<endl;
                city[c][0]=0;
            }
            cheer(c);
        }
    }
}
void report_elements(){
    print_time();
    cout<<red.elements<<" elements in red headquarter"<<endl;
    print_time();
    cout<<blue.elements<<" elements in blue headquarter"<<endl;
}
void warrior_report(){
    for(int c=1;c<=sum_citys;c++){
        if(city[c][0]){
            print_time();cout<<"red "<<monsters_name[red.warrior[city[c][0]-1]->kind]<<' '<<city[c][0]<<" has "
            <<red.warrior[city[c][0]-1]->weapon[0]<<" sword "<<red.warrior[city[c][0]-1]->weapon[1]<<" bomb "
            <<red.warrior[city[c][0]-1]->weapon[2]+red.warrior[city[c][0]-1]->weapon[3]<<" arrow and "<<red.warrior[city[c][0]-1]->HP<<" elements"<<endl;
        }
        if(city[c][1]){
            print_time();cout<<"blue "<<monsters_name[blue.warrior[city[c][1]-1]->kind]<<' '<<city[c][1]<<" has "
            <<blue.warrior[city[c][1]-1]->weapon[0]<<" sword "<<blue.warrior[city[c][1]-1]->weapon[1]<<" bomb "
            <<blue.warrior[city[c][1]-1]->weapon[2]+blue.warrior[city[c][1]-1]->weapon[3]<<" arrow and "<<blue.warrior[city[c][1]-1]->HP<<" elements"<<endl;
        }
    }
}
int main(){
    int t,M,N,K,T;
    cin>>t;
    for(int cyc=1;cyc<=t;cyc++){
        hour=0;minute=0;game_end=false;
        cout<<"Case "<<cyc<<":"<<endl;
        cin>>M>>N>>K>>T;
        for(int i=0;i<22;i++)for(int j=0;j<3;j++)city[i][j]=0;memset(monsters_element,0,sizeof(monsters_element));memset(monsters_attack,0,sizeof(monsters_attack));
        red.set_orders(2,3,4,1,0);blue.set_orders(3,0,1,2,4);
        red.elements=M;blue.elements=M;sum_citys=N;lion_loyalty_loss=K;red.name="red";blue.name="blue";red.army_num=0;blue.army_num=1;
        for(int i=0;i<5;i++)cin>>monsters_element[i];for(int i=0;i<5;i++)cin>>monsters_attack[i];
        for(;;){
            switch(minute){
            case 0:_create_monster();break;
            case 5:lion_escape();break;
            case 10:march();break;
            case 35:wolf_rob();break;
            case 40:fight();break;
            case 50:report_elements();break;
            case 55:warrior_report();break;
            }
            minute++;
            if(minute==60){minute=0;hour++;}
            if(hour*60+minute>T||game_end)break;
        }
        red=Army();blue=Army();
    }
    return 0;
}