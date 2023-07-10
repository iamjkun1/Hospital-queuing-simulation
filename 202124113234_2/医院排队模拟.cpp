#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>


//定义date结构体
typedef  struct  date {
//本程序模拟的是14天的情况
	int  d;//哪一天，直接用一个整数表示

	int  h, m; //几点几分


} date;

//随机生成一个日期,这就是用来实现每个病人就诊消耗的时间应在某个范围内（随机值）的,用随机函数
void  setDate(date *d, int  i) {
	srand(time(0) + i * 100);

	d->d = rand() % 14 + 1; //1-14
	d->h = rand() % 10 + 8; //8-17
	d->m = rand() % 60; //0-59


}



//用来计算病人的结束看病时间,时间d再过min分钟是哪一个时间
date  getDate(date  a, int  min) {
	int  ta = a.d * 24 * 60 + a.h * 60 + a.m; //转成分钟
	ta += min;

//把分钟转换成时间
	a.d = ta / (24 * 60);
	ta = ta % (24 * 60);

	a.h = ta / 60;
	a.m = ta % 60;

	return  a;

}

//显示某个时间
void  showDate(date  d) {
	printf("%02d-%02d:%02d    ", d.d, d.h, d.m);

}



//比较a  b的大小，就是判断两个病人的到来状态。报告有说明
int cmp(date   a, date  b) {
	if (a.d > b.d)
		return  1;
	if (a.d < b.d)
		return  -1;

	if (a.h > b.h)
		return  1;
	if (a.h < b.h)
		return  -1;

	if (a.m > b.m)
		return  1;
	if (a.m < b.m)
		return  -1;


	return  0;

}



//用来计算的，返回a b之间差了多少分钟

int  getMin(date  a, date  b) {
	int  ta = a.d * 24 * 60 + a.h * 60 + a.m; //转成分钟
	int  tb = b.d * 24 * 60 + b.h * 60 + b.m; //转成分钟

	return  ta - tb;//ta 是大于等于tb的

}


///定义病人结构体
//包含一个指针域，用来构建链表
typedef  struct  patient {

	int  num;//序号，按添加时的序号


	date  cometime;//挂号的时间

	int    needtime;//需要的看病分钟数，整数

	date   endtime;//看完病的时间
	struct  patient *next;//指针域


} patient, node, *pointer;


//生成一个节点，并返回
pointer  fun() {
	int  m = sizeof(node);
	pointer  p = (pointer)malloc(m);

	p->next = 0; //指针域刚开始为空
	return  p;
}


//定义一个链表队列
typedef  struct  queue {
	pointer  head;//头节点的链表，方便计算
} queue;



//进队,加入一个病人
void  push(queue *q, pointer  p) {
	pointer  pre = q->head;

//寻找最后一个节点
	while (pre->next)
		pre = pre->next;

//尾插法
	pre->next = p;


}


//获取q这个队列的人数
int  size(queue  q) {
	int k = 0;
	pointer  p = q.head->next;



//计数
	while (p) {
		k++;
		p = p->next;
	}


	return   k;

}

//出队
pointer    pop(queue *p) {

//出队的那个元素
	pointer  pnext = p->head->next;

	if (!pnext)
		return  0;//队空


//指向下一个
	p->head->next = pnext->next;


	return  pnext;//返回该出队的那个元素


}



//定以医生结构体
typedef  struct  Doctor {
	char  name[100];//医生名字
	pointer  arr[200];//存放该医生这14天看的病人
	int  top;//病人个数


} Doctor;



//定义科室结构体
typedef  struct    Department {
	char name[100];//科室名字
	Doctor  arr[10];//医生
	int  top;//医生个数


} Department;



///主菜单
int  menu();

//返回a  b之间的选项
int  get(int a, int b);



//增加病人
void  addPatient();



//显示所有病人
void   showPatient();


//显示所有的科室，科室下面是医生
void   showDepartment();





//统计功能
void  sta();



//保存数据
void  save();


//读取数据
void  open();

//清理
void   cls();

// 所有的科室
Department  drr[30];
int  dtop;//科室数量

patient  prr[1000];//所有的病人
int  ptop;//病人数量



//主函数
int main() {


	int flag;


	while (1) {

		open();//读取数据

		flag = menu();
		switch (flag) {
			case  1:
				addPatient();  ///增加病人
				break;


			case 2:
				showDepartment();  ////显示科室医生信息
				break;

			case 3:
				showPatient();    ////显示病人排队看病信息
				break;


			case  4:
				sta();      ////统计
				break;

			case  0:
				return  0;

		}

		save();   ////保存信息在文本文档
		cls();   ///清屏


	}

	return 0;
}


//清屏函数
void  cls() {
	system("pause");

	system("cls");
}


//主菜单
int  menu() {

	printf("1  增加若干病人\n");
	printf("2  显示所有科室\n");
	printf("3  显示所有病人\n");
	printf("4  进行统计\n");
	printf("0  退出程序\n");
	return  get(0, 4);


}

//返回a  b之间的选项
int  get(int a, int b) {
	int k;
	while (1) {
		printf("请输入%d-%d选择: ", a, b);
		scanf("%d", &k);
		if (a <= k && k <= b) //
			return  k;
	}

}



//看一下是否有该科室
int searchDrr(char name[]) {
	int i;
	for (i = 0; i < dtop; i++)
		if (strcmp(name, drr[i].name) == 0)
			return  i;


	return  -1;
}

//看一下科室d是否已经有了该医生,用来判断的
int  searchD(Department  d, char name[]) {
	int i;
	for (i = 0; i < d.top; i++)
		if (strcmp(d.arr[i].name, name) == 0)
			return  i;


	return  -1;

}

//给某个科室增加一个医生
void  pushD(Department *pd, Doctor d) {
	int  top = pd->top;
	pd->arr[top] = d;
	pd->top++;

}

//增加一个医生,d是科室名字,name是医生名字


void   addOne(char d[], char name[]) {

	Department  dd;
	int  flag, index;

	flag = searchDrr(d);
	if (flag < 0) {
//printf("没有该科室\n");
		strcpy(dd.name, d);
		dd.top = 0;
		drr[dtop++] = dd; //增加该科室

	}

	flag = searchDrr(d); //刷新flag

	index = searchD(drr[flag], name);
	if (index >= 0)
		return;


//增加一个医生
	Doctor  doc;
	strcpy(doc.name, name);
	pushD(&drr[flag], doc);


}


//增加一个病人
int  addOnePatient() {
	patient  p;
	date  d;
	printf("请输入病人挂号时间(如1（第一天） 9（时） 25（分）): ");
	scanf("%d %d %d", &d.d, &d.h, &d.m);
	if (d.d < 1 || d.d > 14) {
		printf("日期不合法\n");
		return   0;
	}

	if (d.h < 8 || d.h > 17) {
		printf("小时不合法\n");
		return   0;
	}

	if (d.m < 0 || d.m > 59) {
		printf("分钟不合法\n");
		return   0;
	}


	p.num = ptop;
	p.cometime = d;
	srand(time(0));//随机生成看病时间

	p.needtime = rand() % 5 + 10; //看病时间

	p.endtime = d;

	prr[ptop++] = p;
	printf("成功增加一个病人\n\n");
	return  1;

}

//增加病人
void  addPatient() {
	int flag;
	while (1) {
		flag = addOnePatient();

		if (flag == 0)
			return  ;

	}

}

//显示某个病人
void  showP(patient p) {
	printf("编号: %-3d ", p.num);
	printf("挂号: ");
	showDate(p.cometime);

	printf("看病(min): %-2d     ", p.needtime);
	printf("结束: ");
	showDate(p.endtime);

	printf("\n");

}


//显示所有病人
void   showPatient() {
	int i;

//所有病人如下
	for (i = 0; i < ptop; i++)
		showP(prr[i]);


}



//显示某个科室
void   showD(Department d) {
//显示科室医生
	int i;
	printf("科室: %s\n", d.name);
	for (i = 0; i < d.top; i++)
		printf("\t%s\n", d.arr[i].name);


	printf("\n");

}

//显示所有的科室，科室下面是医生

void   showDepartment() {
	int i;

	for (i = 0; i < dtop; i++)
		showD(drr[i]);

}


void  savePrr() { //保存病人
	int i;
	FILE *fp;
	date d;
	fp = fopen("病人.txt", "w");
	if (!fp)
		return;

//保存病人个数
	fprintf(fp, "%d\n", ptop);
//保存每一个病人的数据
	for (i = 0; i < ptop; i++) {
		fprintf(fp, "%d ", prr[i].num);

		d = prr[i].cometime;
		fprintf(fp, "%d %d %d ", d.d, d.h, d.m);


		fprintf(fp, "%d ", prr[i].needtime);

		d = prr[i].endtime;
		fprintf(fp, "%d %d %d\n", d.d, d.h, d.m);

	}


	fclose(fp);

}


void  saveDrr() { //保存科室
	int i;
	int j;
	FILE *fp;
	date d;
	fp = fopen("科室医生.txt", "w");
	if (!fp)
		return;


//保存科室和医生
	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			fprintf(fp, "%s %s\n", drr[i].name, drr[i].arr[j].name);


	fclose(fp);

}


//保存数据
void  save() {
	savePrr();//保存病人
	saveDrr();//保存科室

}

void  openDrr() { //读取科室
	char  d[100];//科室名字
	char  name[100];//医生名字

	FILE *fp;

	fp = fopen("科室医生.txt", "r");
	dtop = 0; //刚开始dtop为0


	if (!fp)
		return;


	while (fscanf(fp, "%s %s", d, name) != EOF)//不断的读取
		addOne(d, name);

	fclose(fp);


}

void  openPrr() { //读取病人
	int i;
	FILE *fp;
	date d;
	fp = fopen("病人.txt", "r");
	if (!fp)
		return;

//读取病人个数
	fscanf(fp, "%d", &ptop);
//读取每一个病人的数据
	for (i = 0; i < ptop; i++) {

		fscanf(fp, "%d", &prr[i].num);


		fscanf(fp, "%d%d%d ", &d.d, &d.h, &d.m);
		prr[i].cometime = d;

		fscanf(fp, "%d", &prr[i].needtime);


		fscanf(fp, "%d%d%d ", &d.d, &d.h, &d.m);
		prr[i].endtime = d;



	}


	fclose(fp);

}

//读取数据
void  open() {
	openDrr();//读取科室
	openPrr();//读取病人


}

//统计模块目录
int  staMenu();


//统计两周之内上午下午的
void  staAP();

//统计这两周14天的
void  staDay();


//按科室统计处理量
void  staDepartment();

//按医生统计处理量
void   staDocotor();


//按科室统计平均就医时间
void  staDepartmentTime();

//按医生统计平均就医时间
void   staDocotorTime();


//计算病人的平均等待时间
void  staPatient();



//病人看病
void  run();


//统计模块，用来实现统计功能
void  sta() {
	int  flag;


	run();//病人的分配

	while (1) {
		flag = staMenu();

		switch (flag) {
			case  1:
				staAP(); //统计两周之内上午下午的
				break;

			case  2:
				staDay(); //统计这两周14天的
				break;

			case  3:
				staDepartment();//按科室统计处理量
				break;

			case  4:
				staDocotor();//按医生统计处理量
				break;


			case  5:
				staDepartmentTime();//按科室统计平均就医时间
				break;

			case  6:
				staDocotorTime();//按医生统计平均就医时间
				break;

			case  7:
				staPatient();
				break;//按病人统计平均就医时间

			case  0:
				return  ;

		}

		cls();

	}


}


//统计所有的医生
int  getAll() {
	int  sum = 0;
	int i;
	for (i = 0; i < dtop; i++)
		sum += drr[i].top;

	return  sum;

}



//把某个病人分配给某个医生
void  pushPD(Doctor *pd, patient *pp) {

	int  top = pd->top;

	pd->arr[top] = pp;

	pd->top++;

}


//分配第i个病人
//医生轮流来，一人一个
void  set(int a) {
	int  k = getAll();
	int b = a % k;

//确定该病人应该分配给哪个医生
	int  flag;
	int i, j;

	k = 0;
	flag = 1;

	for (i = 0; i < dtop; i++) {

		for (j = 0; j < drr[i].top; j++) {
			if (k == b) { //说明此时的i  j对应的那个医生就可以分配到该病人
				flag = 0;
				break;
			}
			k++;
		}

		if (flag == 0)
			break;

	}

//把该病人分配给该医生
	pushPD(&drr[i].arr[j], &prr[a]);

}



//医生开始工作
void  work(Doctor *d) {

	//printf("%s %d\n",d->name,d->top);
	//return;

	queue  q;//队列
	q.head = fun(); //初始化一个队列
	int i;

//把每个病人都加入到队列
	for (i = 0; i < d->top; i++) {
//printf("push\n");
//d->arr[i]->next=0;

		push(&q, d->arr[i]);
	}
	pointer  p;
	date  dd;//记录时间
	date  tt;
	if (size(q) == 0) //如果队列为空
		return;//直接返回即可



//出队第一个一个病人
	p = pop(&q);

//第一个病人，来了就能看病，所以，
//可以直接计算他的看病结束时间
	tt = getDate(p->cometime, p->needtime);
	p->endtime = tt;
	dd = tt; //dd记录最新的时间点



//接着，只要队列不为空，医生继续为人民服务
	while (size(q) > 0) {
		p = pop(&q); //出队一个病人
		if (cmp(dd, p->cometime) < 0) //说明医生看完上一个病人以后
//过了一会儿这个病人才来
			tt = getDate(p->cometime, p->needtime);


		else//病人到的时候，该医生还在工作
			tt = getDate(dd, p->needtime);



//记录p的结束时间
		p->endtime = tt;
		dd = tt;


	}


//printf("2222\n\n");


}



//交换两个病人
void  swap(pointer  a, pointer  b) {
	patient  t;
	t = *a;
	*a = *b;
	*b = t;

}


//按照挂号时间升序排序(冒泡法)

void  sort() {
	int i, j;

//冒泡排序
	for (i = 0; i < ptop - 1; i++)
		for (j = 0; j < ptop - 1 - i; j++)
			if (cmp(prr[j].cometime, prr[j + 1].cometime) > 0)
				swap(&prr[j], &prr[j + 1]);



}

//病人看病
void  run() {
	int i, j;

//刚开始每个医生都没有病人
	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			drr[i].arr[j].top = 0;


	sort();//所有病人按挂号时间升序排序

	for (i = 0; i < ptop; i++)
		prr[i].next = 0;


	for (i = 0; i < ptop; i++)
		set(i);

//printf("分配病人\n");


//每个医生面对的病人都是一个队列

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++) {
//printf("222\n");

			work(&drr[i].arr[j]);

		}


}


//统计
int  staMenu() {
	printf("1  按上下午统计处理量\n");
	printf("2  按天统计处理量\n");
	printf("3  按科室统计处理量\n");
	printf("4  按医生统计处理量\n");
	printf("5  按科室统计平均就医时间\n");
	printf("6  按医生统计平均就医时间\n");
	printf("7  统计病人平均等待时间\n");
	printf("0  退出统计模块\n");


	return  get(0, 7);


}



//统计14天内之内上午下午的
void  staAP() {
	int i;
	date  dd;
	int  a, b; //a记录上午
//b记录下午


	a = 0;
	b = 0;

//按照挂号时间来统计
	for (i = 0; i < ptop; i++)

//13点以前挂号的，就算上午
//
		if (prr[i].cometime.h <= 12)
			a++;
		else
			b++;

	printf("上午处理量: %d\n", a);
	printf("下午处理量: %d\n", b);


}


//统计第k天的处理量
int  staOneDay(int k) {
	int  i;
	int  sum = 0;

	for (i = 0; i < ptop; i++)
		if (prr[i].cometime.d == k) //第k天挂号的
			sum++;


	printf("第%2d天处理量: %d\n", k, sum);

	return  sum;


}

//统计这四周14天的
//1-7是第一周
//8-14是第二周
void  staDay() {
	int i;
	int  sum = 0;
//统计第一周
	for (i = 1; i < 8; i++)
		sum += staOneDay(i);
	printf("第一周处理量: %d\n\n\n", sum);


	sum = 0;
//统计第2周
	for (i = 8; i < 15; i++)
		sum += staOneDay(i);
	printf("第二周处理量: %d\n\n", sum);


}


//统计第a个科室
void  staD(int a) {
	int i;
	int  sum = 0;
	Department dd;
	dd = drr[a];
	for (i = 0; i < dd.top; i++)
		sum += dd.arr[i].top; //把每个医生的处理量加起来即可

	printf("科室: %s\t  处理量: %d\n", dd.name, sum);


}


//按科室统计处理量

void  staDepartment() {
	int  i;
	for (i = 0; i < dtop; i++)
		staD(i);


}

//统计医生i j的处理量
void  staDoc(int i, int  j) {
	Department dd;
	dd = drr[i];
	printf("%s\t %s\t 处理量： %d\n", dd.name, dd.arr[j].name, dd.arr[j].top);
}



//按医生统计处理量
void   staDocotor() {
	int i, j;

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			staDoc(i, j);


}



//统计第a个科室的平均就医时间
void  staDTime(int a) {
	int i, j;
	int  sum = 0;
	int  alltime = 0; //总得就医时间
	Department dd;
	dd = drr[a];
	for (i = 0; i < dd.top; i++) {
		sum += dd.arr[i].top; //把每个医生的处理量加起来即可
		for (j = 0; j < dd.arr[i].top; j++)
			alltime += dd.arr[i].arr[j]->needtime;


	}

//平均就医时间
	float  f = 1.0 * alltime / sum;
	printf("%s\t 平均就医时间(min)： %.2f\n", dd.name, f);

}



//按科室统计平均就医时间
void  staDepartmentTime() {
	int i;
	for (i = 0; i < dtop; i++)
		staDTime(i);

}

//统计i j医生的平均就医时间
void  staDocTime(int i, int  j) {
	Department dd;
	dd = drr[i];
	Doctor   doc = drr[i].arr[j];
	int  top = doc.top; //该医生看的病人数量
	float  sum = 0; //记录总得就医时间
	int  k;

	for (k = 0; k < top; k++)
		sum += doc.arr[k]->needtime;

	printf("%s\t %s\t 平均就医时间(min)： %.2f\n", dd.name, doc.name, sum / top);


}

//按医生统计平均就医时间
void   staDocotorTime() {
	int i, j;

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			staDocTime(i, j);

}


//计算病人的平均等待时间
void  staPatient() {
	int i;
	float  sum = 0; //总得等待时间
	for (i = 0; i < ptop; i++)
		sum += getMin(prr[i].endtime, prr[i].cometime);

	printf("病人的平均等待时间(min): %.2f\n", sum / ptop);

}