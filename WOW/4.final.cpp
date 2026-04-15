#include<iostream>
#include<cassert>
using namespace std;
char colWord[2][5]={"red","blue"};
char typeWord[5][7]={"dragon","ninja","iceman","lion","wolf"};
int bornred[]={0,2,3,4,1},bornblue[]={4,3,0,1,2};
int M,N,R,K,T,current,isEnd;
int inithp[5],initatk[5];
class Enemy
{
public:
	int type,col,id,hp,atk,sword,bomb,arrow,place;
	Enemy(int _type,int _col,int _id)
	{
		type=_type,col=_col,id=_id;
		hp=inithp[type],atk=initatk[type];
		sword=bomb=arrow=0;
		if(type==0)
		{
			if(id%3==0) sword=atk/5;
			else if(id%3==1) bomb=1;
			else arrow=3;
		}
		else if(type==1)
		{
			if(id%3==0) sword=atk/5;
			else if(id%3==1) bomb=1;
			else arrow=3;
			if((id+1)%3==0) sword=atk/5;
			else if((id+1)%3==1) bomb=1;
			else arrow=3;
		}
		else if(type==2)
		{
			if(id%3==0) sword=atk/5;
			else if(id%3==1) bomb=1;
			else arrow=3;
		}
		if(col==0) place=0;
		else place=N+1;
	}
	int alive() {return hp>0;}
	virtual int runaway() {return 0;}
	virtual void move()
	{
		if(col==0) place++;
		else place--;
	}
	void usearrow(Enemy *p)
	{
		if(arrow==0) return ;
		p->hp-=R,arrow--;
		if(p->hp<=0) printf("%03d:35 %s %s %d shot and killed %s %s %d\n",current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id);
		else printf("%03d:35 %s %s %d shot\n",current/60,colWord[col],typeWord[type],id);
	}
	void usebomb(Enemy *p)
	{
		if(bomb==0) return ;
		printf("%03d:38 %s %s %d used a bomb and killed %s %s %d\n",current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id);
		hp=0,p->hp=0;
	}
	void report()
	{
		printf("%03d:55 %s %s %d has ",current/60,colWord[col],typeWord[type],id);
		if(sword==0&&bomb==0&&arrow==0) printf("no weapon");
		int fl=0;
		if(arrow) printf("%sarrow(%d)",fl?",":"",arrow),fl=1;
		if(bomb) printf("%sbomb",fl?",":""),fl=1;
		if(sword) printf("%ssword(%d)",fl?",":"",sword),fl=1;
		printf("\n");
	}
	void dying()
	{
		printf("%03d:40 %s %s %d was killed in city %d\n",current/60,colWord[col],typeWord[type],id,place);
	}
	virtual void fightback(Enemy *p)
	{
		printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
			current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id,place);
		p->hp-=atk/2+sword;
		if(p->hp<=0)
		{
			if(p->type==3) hp+=p->hp+atk/2+sword;
			p->dying();
		}
		sword=sword*4/5;
	}
	virtual void attack(Enemy *p)
	{
		printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
			current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id,place,hp,atk);
		p->hp-=atk+sword;
		if(p->hp<=0)
		{
			// printf("** %d %d %d\n",p->col,p->id,p->hp+atk+sword);
			if(p->type==3) hp+=p->hp+atk+sword;
			p->dying();
		}
		else p->fightback(this);
		sword=sword*4/5;
	}
	virtual void yell(int win,int output) {}
	virtual void steal(Enemy *p) {}
	void earn();
};
class City
{
public:
	Enemy* enemy[2];
	int element,flag,lastwin,borncnt;
	int reach,id,vis;
	City(int _id=0) {enemy[0]=enemy[1]=NULL,element=0,flag=-1,lastwin=-1,borncnt=0,reach=0,id=_id,vis=0;}
	int first() // who attack first
	{
		if(flag==-1) return id%2==0;
		else return flag;
	}
	void addfight(int win)
	{
		if(win==-1) lastwin=-1;
		else
		{
			if(lastwin==win)
			{
				if(win!=flag)
				{
					printf("%03d:40 %s flag raised in city %d\n",current/60,colWord[win],id);
					flag=win;
				}
			}
			else lastwin=win;
		}
	}
};
City city[25];
void Enemy::earn()
{
	printf("%03d:40 %s %s %d earned %d elements for his headquarter\n",current/60,colWord[col],typeWord[type],id,city[place].element);
	city[col*(N+1)].element+=city[place].element,city[place].element=0;
}
class Dragon : public Enemy
{
public:
	double morale;
	Dragon(int _col,int _id): Enemy(0,_col,_id)
	{
		if(col==0) morale=(double)(city[0].element-hp)/hp;
		else morale=(double)(city[N+1].element-hp)/hp;
		printf("%03d:00 %s dragon %d born\n",current/60,colWord[col],id);
		printf("Its morale is %.2lf\n",morale);
	}
	void yell(int win,int output) override
	{
		if(win) morale+=0.2;
		else morale-=0.2;
		if(output) if(morale>0.8+1e-8) printf("%03d:40 %s %s %d yelled in city %d\n",current/60,colWord[col],typeWord[type],id,place);
	}
};
class Ninja : public Enemy
{
public:
	Ninja(int _col,int _id): Enemy(1,_col,_id)
	{
		printf("%03d:00 %s ninja %d born\n",current/60,colWord[col],id);
	}
	void fightback(Enemy *p) override {}
};
class Iceman : public Enemy
{
public:
	int movetime;
	Iceman(int _col,int _id): Enemy(2,_col,_id)
	{
		movetime=0;
		printf("%03d:00 %s iceman %d born\n",current/60,colWord[col],id);
	}
	void move() override
	{
		if(col==0) place++;
		else place--;
		movetime++;
		if(movetime==2) movetime=0,hp=max(hp-9,1),atk+=20;
	}
};
class Lion : public Enemy
{
public:
	int loyalty;
	Lion(int _col,int _id): Enemy(3,_col,_id)
	{
		if(col==0) loyalty=(double)city[0].element-hp;
		else loyalty=(double)city[N+1].element-hp;
		printf("%03d:00 %s lion %d born\n",current/60,colWord[col],id);
		printf("Its loyalty is %d\n",loyalty);
	}
	int runaway() override
	{
		if(place==(1-col)*(N+1)) return 0;
		return loyalty<=0;
	}
	void fightback(Enemy *p) override
	{
		printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
			current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id,place);
		p->hp-=atk/2+sword;
		if(p->hp<=0)
		{
			if(p->type==3) hp+=p->hp+atk/2+sword;
			p->dying();
		}
		else loyalty-=K;
		sword=sword*4/5;
	}
	void attack(Enemy *p) override
	{
		printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
			current/60,colWord[col],typeWord[type],id,colWord[p->col],typeWord[p->type],p->id,place,hp,atk);
		p->hp-=atk+sword;
		if(p->hp<=0)
		{
			if(p->type==3) hp+=p->hp+atk+sword;
			p->dying();
		}
		else loyalty-=K,p->fightback(this);
		sword=sword*4/5;
	}
};
class Wolf : public Enemy
{
public:
	Wolf(int _col,int _id): Enemy(4,_col,_id)
	{
		printf("%03d:00 %s wolf %d born\n",current/60,colWord[col],id);
	}
	void steal(Enemy *p) override
	{
		if(!sword) sword=p->sword;
		if(!bomb) bomb=p->bomb;
		if(!arrow) arrow=p->arrow;
	}
};
pair<int,int> simulatefight(Enemy *p,Enemy *q) // whether p, q will die
{
	if(q->hp<=p->atk+p->sword) return {0,1};
	if(q->type!=1&&p->hp<=q->atk/2+q->sword) return {1,0};
	return {0,0};
}
void born()
{
	if(city[0].element>=inithp[bornred[(city[0].borncnt+1)%5]])
	{
		int bornid=bornred[(city[0].borncnt+1)%5];
		if(bornid==0) city[0].enemy[0]=new Dragon(0,++city[0].borncnt);
		else if(bornid==1) city[0].enemy[0]=new Ninja(0,++city[0].borncnt);
		else if(bornid==2) city[0].enemy[0]=new Iceman(0,++city[0].borncnt);
		else if(bornid==3) city[0].enemy[0]=new Lion(0,++city[0].borncnt);
		else if(bornid==4) city[0].enemy[0]=new Wolf(0,++city[0].borncnt);
		city[0].element-=city[0].enemy[0]->hp;
	}
	if(city[N+1].element>=inithp[bornblue[(city[N+1].borncnt+1)%5]])
	{
		int bornid=bornblue[(city[N+1].borncnt+1)%5];
		if(bornid==0) city[N+1].enemy[1]=new Dragon(1,++city[N+1].borncnt);
		else if(bornid==1) city[N+1].enemy[1]=new Ninja(1,++city[N+1].borncnt);
		else if(bornid==2) city[N+1].enemy[1]=new Iceman(1,++city[N+1].borncnt);
		else if(bornid==3) city[N+1].enemy[1]=new Lion(1,++city[N+1].borncnt);
		else if(bornid==4) city[N+1].enemy[1]=new Wolf(1,++city[N+1].borncnt);
		city[N+1].element-=city[N+1].enemy[1]->hp;
	}
}
void runaway()
{
	for(int i=0;i<=N+1;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(city[i].enemy[j]!=NULL&&city[i].enemy[j]->runaway())
			{
				printf("%03d:05 %s lion %d ran away\n",current/60,colWord[j],city[i].enemy[j]->id);
				city[i].enemy[j]=NULL;
			}
		}
	}
}
void move()
{
	for(int i=N;i>=0;i--) if(city[i].enemy[0]!=NULL) city[i+1].enemy[0]=city[i].enemy[0],city[i].enemy[0]=NULL,city[i+1].enemy[0]->move();
	for(int i=1;i<=N+1;i++) if(city[i].enemy[1]!=NULL) city[i-1].enemy[1]=city[i].enemy[1],city[i].enemy[1]=NULL,city[i-1].enemy[1]->move();
	if(city[0].enemy[1]!=NULL) if(city[0].vis!=city[0].enemy[1]->id)
	{
		printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
			current/60,typeWord[city[0].enemy[1]->type],city[0].enemy[1]->id,city[0].enemy[1]->hp,city[0].enemy[1]->atk);
		city[0].vis=city[0].enemy[1]->id,city[0].reach++;
	}
	if(city[0].reach==2) isEnd=1,printf("%03d:10 red headquarter was taken\n",current/60);
	for(int i=1;i<=N;i++)
	{
		if(city[i].enemy[0]!=NULL) printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
				current/60,typeWord[city[i].enemy[0]->type],city[i].enemy[0]->id,i,city[i].enemy[0]->hp,city[i].enemy[0]->atk);
		if(city[i].enemy[1]!=NULL) printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
				current/60,typeWord[city[i].enemy[1]->type],city[i].enemy[1]->id,i,city[i].enemy[1]->hp,city[i].enemy[1]->atk);
	}
	if(city[N+1].enemy[0]!=NULL) if(city[N+1].vis!=city[N+1].enemy[0]->id)
	{
		printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
			current/60,typeWord[city[N+1].enemy[0]->type],city[N+1].enemy[0]->id,city[N+1].enemy[0]->hp,city[N+1].enemy[0]->atk);
		city[N+1].vis=city[N+1].enemy[0]->id,city[N+1].reach++;
	}
	if(city[N+1].reach==2) isEnd=1,printf("%03d:10 blue headquarter was taken\n",current/60);
}
void addelement()
{
	for(int i=1;i<=N;i++) city[i].element+=10;
}
void getelement()
{
	for(int i=1;i<=N;i++)
	{
		if(city[i].enemy[0]!=NULL&&city[i].enemy[1]==NULL)
		{
			printf("%03d:30 red %s %d earned %d elements for his headquarter\n",
				current/60,typeWord[city[i].enemy[0]->type],city[i].enemy[0]->id,city[i].element);
			city[0].element+=city[i].element,city[i].element=0;
		}
		if(city[i].enemy[1]!=NULL&&city[i].enemy[0]==NULL)
		{
			printf("%03d:30 blue %s %d earned %d elements for his headquarter\n",
				current/60,typeWord[city[i].enemy[1]->type],city[i].enemy[1]->id,city[i].element);
			city[N+1].element+=city[i].element,city[i].element=0;
		}
	}
}
void shotarrow()
{
	for(int i=0;i<=N+1;i++)
	{
		if(i!=N+1&&city[i].enemy[0]!=NULL&&city[i+1].enemy[1]!=NULL) city[i].enemy[0]->usearrow(city[i+1].enemy[1]);
		if(i!=0&&city[i].enemy[1]!=NULL&&city[i-1].enemy[0]!=NULL) city[i].enemy[1]->usearrow(city[i-1].enemy[0]);
	}
}
void chkbomb()
{
	for(int i=1;i<=N;i++)
	{
		if(city[i].enemy[0]!=NULL&&city[i].enemy[1]!=NULL)
		{
			if(city[i].enemy[0]->alive()&&city[i].enemy[1]->alive())
			{
				int fst=city[i].first();
				auto [pdead,qdead]=simulatefight(city[i].enemy[fst],city[i].enemy[fst^1]);
				if(pdead) city[i].enemy[fst]->usebomb(city[i].enemy[fst^1]);
				if(qdead) city[i].enemy[fst^1]->usebomb(city[i].enemy[fst]);
			}
		}
	}
	for(int i=1;i<=N;i++)
	{
		if(city[i].enemy[0]!=NULL&&city[i].enemy[1]!=NULL)
		{
			if(!city[i].enemy[0]->alive()&&!city[i].enemy[1]->alive()) city[i].enemy[0]=city[i].enemy[1]=NULL;
		}
	}
}
void fight()
{
	int origred=city[0].element,origblue=city[N+1].element;
	for(int i=0;i<=N+1;i++)
	{
		if(city[i].enemy[0]==NULL||city[i].enemy[1]==NULL) continue;
		int fst=city[i].first();
		if(city[i].enemy[0]->alive()&&city[i].enemy[1]->alive())
		{
			city[i].enemy[fst]->attack(city[i].enemy[fst^1]);
		}
		if(city[i].enemy[fst]->alive()) city[i].enemy[fst]->yell(!city[i].enemy[fst^1]->alive(),1);
		if(city[i].enemy[fst^1]->alive()) city[i].enemy[fst^1]->yell(!city[i].enemy[fst]->alive(),0);
		if(city[i].enemy[fst]->alive()&&!city[i].enemy[fst^1]->alive()) city[i].enemy[fst]->steal(city[i].enemy[fst^1]);
		if(city[i].enemy[fst^1]->alive()&&!city[i].enemy[fst]->alive()) city[i].enemy[fst^1]->steal(city[i].enemy[fst]);
		if(city[i].enemy[0]->alive()&&!city[i].enemy[1]->alive()) city[i].enemy[0]->earn();
		if(city[i].enemy[1]->alive()&&!city[i].enemy[0]->alive()) city[i].enemy[1]->earn();
		int o=city[i].enemy[0]->alive(),p=city[i].enemy[1]->alive();
		if(o==1&&p==1) city[i].addfight(-1);
		else if(o==0&&p==1) city[i].addfight(1);
		else if(o==1&&p==0) city[i].addfight(0);
		else assert(0);
	}
	for(int i=N+1;i>=0;i--)
	{
		if(city[i].enemy[0]==NULL||city[i].enemy[1]==NULL) continue;
		if(city[i].enemy[0]->alive()&&!city[i].enemy[1]->alive())
		{
			if(origred>=8) origred-=8,city[0].element-=8,city[i].enemy[0]->hp+=8;
		}
	}
	for(int i=0;i<=N+1;i++)
	{
		if(city[i].enemy[0]==NULL||city[i].enemy[1]==NULL) continue;
		if(city[i].enemy[1]->alive()&&!city[i].enemy[0]->alive())
		{
			if(origblue>=8) origblue-=8,city[N+1].element-=8,city[i].enemy[1]->hp+=8;
		}
	}
	for(int i=0;i<=N+1;i++)
	{
		if(city[i].enemy[0]!=NULL&&!city[i].enemy[0]->alive()) city[i].enemy[0]=NULL;
		if(city[i].enemy[1]!=NULL&&!city[i].enemy[1]->alive()) city[i].enemy[1]=NULL;
	}
}
void headquarterreport()
{
	printf("%03d:50 %d elements in red headquarter\n",current/60,city[0].element);
	printf("%03d:50 %d elements in blue headquarter\n",current/60,city[N+1].element);
}
void enemyreport()
{
	for(int i=0;i<=N+1;i++) if(city[i].enemy[0]!=NULL) city[i].enemy[0]->report();
	for(int i=0;i<=N+1;i++) if(city[i].enemy[1]!=NULL) city[i].enemy[1]->report();
}
void work()
{
	current=0;
	isEnd=0;
	cin>>M>>N>>R>>K>>T;
	for(int i=0;i<5;i++) cin>>inithp[i];
	for(int i=0;i<5;i++) cin>>initatk[i];
	for(int i=0;i<25;i++) city[i]=City(i);
	city[0].element=city[N+1].element=M;
	while(current<=T)
	{
		// time : 00
		born();
		current+=5;
		// time : 05
		if(current>T) break;
		runaway();
		current+=5;
		// time : 10
		if(current>T) break;
		move();
		if(isEnd) break;
		current+=10;
		// time:20
		if(current>T) break;
		addelement();
		current+=10;
		// time:30
		if(current>T) break;
		getelement();
		current+=5;
		// time:35
		if(current>T) break;
		shotarrow();
		current+=3;
		// time:38
		if(current>T) break;
		chkbomb();
		current+=2;
		// time:40
		if(current>T) break;
		fight();
		current+=10;
		// time:50
		if(current>T) break;
		headquarterreport();
		current+=5;
		// time:55
		if(current>T) break;
		enemyreport();
		current+=5;
	}
	// city[0].red=new Lion(0,1);
}
signed main()
{
	int T; cin>>T;
	for(int i=1;i<=T;i++)
	{
		printf("Case %d:\n",i);
		work();
	}
	return 0;
}