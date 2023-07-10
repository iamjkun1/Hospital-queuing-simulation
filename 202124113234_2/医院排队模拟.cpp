#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>


//����date�ṹ��
typedef  struct  date {
//������ģ�����14������
	int  d;//��һ�죬ֱ����һ��������ʾ

	int  h, m; //���㼸��


} date;

//�������һ������,���������ʵ��ÿ�����˾������ĵ�ʱ��Ӧ��ĳ����Χ�ڣ����ֵ����,���������
void  setDate(date *d, int  i) {
	srand(time(0) + i * 100);

	d->d = rand() % 14 + 1; //1-14
	d->h = rand() % 10 + 8; //8-17
	d->m = rand() % 60; //0-59


}



//�������㲡�˵Ľ�������ʱ��,ʱ��d�ٹ�min��������һ��ʱ��
date  getDate(date  a, int  min) {
	int  ta = a.d * 24 * 60 + a.h * 60 + a.m; //ת�ɷ���
	ta += min;

//�ѷ���ת����ʱ��
	a.d = ta / (24 * 60);
	ta = ta % (24 * 60);

	a.h = ta / 60;
	a.m = ta % 60;

	return  a;

}

//��ʾĳ��ʱ��
void  showDate(date  d) {
	printf("%02d-%02d:%02d    ", d.d, d.h, d.m);

}



//�Ƚ�a  b�Ĵ�С�������ж��������˵ĵ���״̬��������˵��
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



//��������ģ�����a b֮����˶��ٷ���

int  getMin(date  a, date  b) {
	int  ta = a.d * 24 * 60 + a.h * 60 + a.m; //ת�ɷ���
	int  tb = b.d * 24 * 60 + b.h * 60 + b.m; //ת�ɷ���

	return  ta - tb;//ta �Ǵ��ڵ���tb��

}


///���岡�˽ṹ��
//����һ��ָ����������������
typedef  struct  patient {

	int  num;//��ţ������ʱ�����


	date  cometime;//�Һŵ�ʱ��

	int    needtime;//��Ҫ�Ŀ���������������

	date   endtime;//���겡��ʱ��
	struct  patient *next;//ָ����


} patient, node, *pointer;


//����һ���ڵ㣬������
pointer  fun() {
	int  m = sizeof(node);
	pointer  p = (pointer)malloc(m);

	p->next = 0; //ָ����տ�ʼΪ��
	return  p;
}


//����һ���������
typedef  struct  queue {
	pointer  head;//ͷ�ڵ�������������
} queue;



//����,����һ������
void  push(queue *q, pointer  p) {
	pointer  pre = q->head;

//Ѱ�����һ���ڵ�
	while (pre->next)
		pre = pre->next;

//β�巨
	pre->next = p;


}


//��ȡq������е�����
int  size(queue  q) {
	int k = 0;
	pointer  p = q.head->next;



//����
	while (p) {
		k++;
		p = p->next;
	}


	return   k;

}

//����
pointer    pop(queue *p) {

//���ӵ��Ǹ�Ԫ��
	pointer  pnext = p->head->next;

	if (!pnext)
		return  0;//�ӿ�


//ָ����һ��
	p->head->next = pnext->next;


	return  pnext;//���ظó��ӵ��Ǹ�Ԫ��


}



//����ҽ���ṹ��
typedef  struct  Doctor {
	char  name[100];//ҽ������
	pointer  arr[200];//��Ÿ�ҽ����14�쿴�Ĳ���
	int  top;//���˸���


} Doctor;



//������ҽṹ��
typedef  struct    Department {
	char name[100];//��������
	Doctor  arr[10];//ҽ��
	int  top;//ҽ������


} Department;



///���˵�
int  menu();

//����a  b֮���ѡ��
int  get(int a, int b);



//���Ӳ���
void  addPatient();



//��ʾ���в���
void   showPatient();


//��ʾ���еĿ��ң�����������ҽ��
void   showDepartment();





//ͳ�ƹ���
void  sta();



//��������
void  save();


//��ȡ����
void  open();

//����
void   cls();

// ���еĿ���
Department  drr[30];
int  dtop;//��������

patient  prr[1000];//���еĲ���
int  ptop;//��������



//������
int main() {


	int flag;


	while (1) {

		open();//��ȡ����

		flag = menu();
		switch (flag) {
			case  1:
				addPatient();  ///���Ӳ���
				break;


			case 2:
				showDepartment();  ////��ʾ����ҽ����Ϣ
				break;

			case 3:
				showPatient();    ////��ʾ�����Ŷӿ�����Ϣ
				break;


			case  4:
				sta();      ////ͳ��
				break;

			case  0:
				return  0;

		}

		save();   ////������Ϣ���ı��ĵ�
		cls();   ///����


	}

	return 0;
}


//��������
void  cls() {
	system("pause");

	system("cls");
}


//���˵�
int  menu() {

	printf("1  �������ɲ���\n");
	printf("2  ��ʾ���п���\n");
	printf("3  ��ʾ���в���\n");
	printf("4  ����ͳ��\n");
	printf("0  �˳�����\n");
	return  get(0, 4);


}

//����a  b֮���ѡ��
int  get(int a, int b) {
	int k;
	while (1) {
		printf("������%d-%dѡ��: ", a, b);
		scanf("%d", &k);
		if (a <= k && k <= b) //
			return  k;
	}

}



//��һ���Ƿ��иÿ���
int searchDrr(char name[]) {
	int i;
	for (i = 0; i < dtop; i++)
		if (strcmp(name, drr[i].name) == 0)
			return  i;


	return  -1;
}

//��һ�¿���d�Ƿ��Ѿ����˸�ҽ��,�����жϵ�
int  searchD(Department  d, char name[]) {
	int i;
	for (i = 0; i < d.top; i++)
		if (strcmp(d.arr[i].name, name) == 0)
			return  i;


	return  -1;

}

//��ĳ����������һ��ҽ��
void  pushD(Department *pd, Doctor d) {
	int  top = pd->top;
	pd->arr[top] = d;
	pd->top++;

}

//����һ��ҽ��,d�ǿ�������,name��ҽ������


void   addOne(char d[], char name[]) {

	Department  dd;
	int  flag, index;

	flag = searchDrr(d);
	if (flag < 0) {
//printf("û�иÿ���\n");
		strcpy(dd.name, d);
		dd.top = 0;
		drr[dtop++] = dd; //���Ӹÿ���

	}

	flag = searchDrr(d); //ˢ��flag

	index = searchD(drr[flag], name);
	if (index >= 0)
		return;


//����һ��ҽ��
	Doctor  doc;
	strcpy(doc.name, name);
	pushD(&drr[flag], doc);


}


//����һ������
int  addOnePatient() {
	patient  p;
	date  d;
	printf("�����벡�˹Һ�ʱ��(��1����һ�죩 9��ʱ�� 25���֣�): ");
	scanf("%d %d %d", &d.d, &d.h, &d.m);
	if (d.d < 1 || d.d > 14) {
		printf("���ڲ��Ϸ�\n");
		return   0;
	}

	if (d.h < 8 || d.h > 17) {
		printf("Сʱ���Ϸ�\n");
		return   0;
	}

	if (d.m < 0 || d.m > 59) {
		printf("���Ӳ��Ϸ�\n");
		return   0;
	}


	p.num = ptop;
	p.cometime = d;
	srand(time(0));//������ɿ���ʱ��

	p.needtime = rand() % 5 + 10; //����ʱ��

	p.endtime = d;

	prr[ptop++] = p;
	printf("�ɹ�����һ������\n\n");
	return  1;

}

//���Ӳ���
void  addPatient() {
	int flag;
	while (1) {
		flag = addOnePatient();

		if (flag == 0)
			return  ;

	}

}

//��ʾĳ������
void  showP(patient p) {
	printf("���: %-3d ", p.num);
	printf("�Һ�: ");
	showDate(p.cometime);

	printf("����(min): %-2d     ", p.needtime);
	printf("����: ");
	showDate(p.endtime);

	printf("\n");

}


//��ʾ���в���
void   showPatient() {
	int i;

//���в�������
	for (i = 0; i < ptop; i++)
		showP(prr[i]);


}



//��ʾĳ������
void   showD(Department d) {
//��ʾ����ҽ��
	int i;
	printf("����: %s\n", d.name);
	for (i = 0; i < d.top; i++)
		printf("\t%s\n", d.arr[i].name);


	printf("\n");

}

//��ʾ���еĿ��ң�����������ҽ��

void   showDepartment() {
	int i;

	for (i = 0; i < dtop; i++)
		showD(drr[i]);

}


void  savePrr() { //���没��
	int i;
	FILE *fp;
	date d;
	fp = fopen("����.txt", "w");
	if (!fp)
		return;

//���没�˸���
	fprintf(fp, "%d\n", ptop);
//����ÿһ�����˵�����
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


void  saveDrr() { //�������
	int i;
	int j;
	FILE *fp;
	date d;
	fp = fopen("����ҽ��.txt", "w");
	if (!fp)
		return;


//������Һ�ҽ��
	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			fprintf(fp, "%s %s\n", drr[i].name, drr[i].arr[j].name);


	fclose(fp);

}


//��������
void  save() {
	savePrr();//���没��
	saveDrr();//�������

}

void  openDrr() { //��ȡ����
	char  d[100];//��������
	char  name[100];//ҽ������

	FILE *fp;

	fp = fopen("����ҽ��.txt", "r");
	dtop = 0; //�տ�ʼdtopΪ0


	if (!fp)
		return;


	while (fscanf(fp, "%s %s", d, name) != EOF)//���ϵĶ�ȡ
		addOne(d, name);

	fclose(fp);


}

void  openPrr() { //��ȡ����
	int i;
	FILE *fp;
	date d;
	fp = fopen("����.txt", "r");
	if (!fp)
		return;

//��ȡ���˸���
	fscanf(fp, "%d", &ptop);
//��ȡÿһ�����˵�����
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

//��ȡ����
void  open() {
	openDrr();//��ȡ����
	openPrr();//��ȡ����


}

//ͳ��ģ��Ŀ¼
int  staMenu();


//ͳ������֮�����������
void  staAP();

//ͳ��������14���
void  staDay();


//������ͳ�ƴ�����
void  staDepartment();

//��ҽ��ͳ�ƴ�����
void   staDocotor();


//������ͳ��ƽ����ҽʱ��
void  staDepartmentTime();

//��ҽ��ͳ��ƽ����ҽʱ��
void   staDocotorTime();


//���㲡�˵�ƽ���ȴ�ʱ��
void  staPatient();



//���˿���
void  run();


//ͳ��ģ�飬����ʵ��ͳ�ƹ���
void  sta() {
	int  flag;


	run();//���˵ķ���

	while (1) {
		flag = staMenu();

		switch (flag) {
			case  1:
				staAP(); //ͳ������֮�����������
				break;

			case  2:
				staDay(); //ͳ��������14���
				break;

			case  3:
				staDepartment();//������ͳ�ƴ�����
				break;

			case  4:
				staDocotor();//��ҽ��ͳ�ƴ�����
				break;


			case  5:
				staDepartmentTime();//������ͳ��ƽ����ҽʱ��
				break;

			case  6:
				staDocotorTime();//��ҽ��ͳ��ƽ����ҽʱ��
				break;

			case  7:
				staPatient();
				break;//������ͳ��ƽ����ҽʱ��

			case  0:
				return  ;

		}

		cls();

	}


}


//ͳ�����е�ҽ��
int  getAll() {
	int  sum = 0;
	int i;
	for (i = 0; i < dtop; i++)
		sum += drr[i].top;

	return  sum;

}



//��ĳ�����˷����ĳ��ҽ��
void  pushPD(Doctor *pd, patient *pp) {

	int  top = pd->top;

	pd->arr[top] = pp;

	pd->top++;

}


//�����i������
//ҽ����������һ��һ��
void  set(int a) {
	int  k = getAll();
	int b = a % k;

//ȷ���ò���Ӧ�÷�����ĸ�ҽ��
	int  flag;
	int i, j;

	k = 0;
	flag = 1;

	for (i = 0; i < dtop; i++) {

		for (j = 0; j < drr[i].top; j++) {
			if (k == b) { //˵����ʱ��i  j��Ӧ���Ǹ�ҽ���Ϳ��Է��䵽�ò���
				flag = 0;
				break;
			}
			k++;
		}

		if (flag == 0)
			break;

	}

//�Ѹò��˷������ҽ��
	pushPD(&drr[i].arr[j], &prr[a]);

}



//ҽ����ʼ����
void  work(Doctor *d) {

	//printf("%s %d\n",d->name,d->top);
	//return;

	queue  q;//����
	q.head = fun(); //��ʼ��һ������
	int i;

//��ÿ�����˶����뵽����
	for (i = 0; i < d->top; i++) {
//printf("push\n");
//d->arr[i]->next=0;

		push(&q, d->arr[i]);
	}
	pointer  p;
	date  dd;//��¼ʱ��
	date  tt;
	if (size(q) == 0) //�������Ϊ��
		return;//ֱ�ӷ��ؼ���



//���ӵ�һ��һ������
	p = pop(&q);

//��һ�����ˣ����˾��ܿ��������ԣ�
//����ֱ�Ӽ������Ŀ�������ʱ��
	tt = getDate(p->cometime, p->needtime);
	p->endtime = tt;
	dd = tt; //dd��¼���µ�ʱ���



//���ţ�ֻҪ���в�Ϊ�գ�ҽ������Ϊ�������
	while (size(q) > 0) {
		p = pop(&q); //����һ������
		if (cmp(dd, p->cometime) < 0) //˵��ҽ��������һ�������Ժ�
//����һ���������˲���
			tt = getDate(p->cometime, p->needtime);


		else//���˵���ʱ�򣬸�ҽ�����ڹ���
			tt = getDate(dd, p->needtime);



//��¼p�Ľ���ʱ��
		p->endtime = tt;
		dd = tt;


	}


//printf("2222\n\n");


}



//������������
void  swap(pointer  a, pointer  b) {
	patient  t;
	t = *a;
	*a = *b;
	*b = t;

}


//���չҺ�ʱ����������(ð�ݷ�)

void  sort() {
	int i, j;

//ð������
	for (i = 0; i < ptop - 1; i++)
		for (j = 0; j < ptop - 1 - i; j++)
			if (cmp(prr[j].cometime, prr[j + 1].cometime) > 0)
				swap(&prr[j], &prr[j + 1]);



}

//���˿���
void  run() {
	int i, j;

//�տ�ʼÿ��ҽ����û�в���
	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			drr[i].arr[j].top = 0;


	sort();//���в��˰��Һ�ʱ����������

	for (i = 0; i < ptop; i++)
		prr[i].next = 0;


	for (i = 0; i < ptop; i++)
		set(i);

//printf("���䲡��\n");


//ÿ��ҽ����ԵĲ��˶���һ������

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++) {
//printf("222\n");

			work(&drr[i].arr[j]);

		}


}


//ͳ��
int  staMenu() {
	printf("1  ��������ͳ�ƴ�����\n");
	printf("2  ����ͳ�ƴ�����\n");
	printf("3  ������ͳ�ƴ�����\n");
	printf("4  ��ҽ��ͳ�ƴ�����\n");
	printf("5  ������ͳ��ƽ����ҽʱ��\n");
	printf("6  ��ҽ��ͳ��ƽ����ҽʱ��\n");
	printf("7  ͳ�Ʋ���ƽ���ȴ�ʱ��\n");
	printf("0  �˳�ͳ��ģ��\n");


	return  get(0, 7);


}



//ͳ��14����֮�����������
void  staAP() {
	int i;
	date  dd;
	int  a, b; //a��¼����
//b��¼����


	a = 0;
	b = 0;

//���չҺ�ʱ����ͳ��
	for (i = 0; i < ptop; i++)

//13����ǰ�Һŵģ���������
//
		if (prr[i].cometime.h <= 12)
			a++;
		else
			b++;

	printf("���紦����: %d\n", a);
	printf("���紦����: %d\n", b);


}


//ͳ�Ƶ�k��Ĵ�����
int  staOneDay(int k) {
	int  i;
	int  sum = 0;

	for (i = 0; i < ptop; i++)
		if (prr[i].cometime.d == k) //��k��Һŵ�
			sum++;


	printf("��%2d�촦����: %d\n", k, sum);

	return  sum;


}

//ͳ��������14���
//1-7�ǵ�һ��
//8-14�ǵڶ���
void  staDay() {
	int i;
	int  sum = 0;
//ͳ�Ƶ�һ��
	for (i = 1; i < 8; i++)
		sum += staOneDay(i);
	printf("��һ�ܴ�����: %d\n\n\n", sum);


	sum = 0;
//ͳ�Ƶ�2��
	for (i = 8; i < 15; i++)
		sum += staOneDay(i);
	printf("�ڶ��ܴ�����: %d\n\n", sum);


}


//ͳ�Ƶ�a������
void  staD(int a) {
	int i;
	int  sum = 0;
	Department dd;
	dd = drr[a];
	for (i = 0; i < dd.top; i++)
		sum += dd.arr[i].top; //��ÿ��ҽ���Ĵ���������������

	printf("����: %s\t  ������: %d\n", dd.name, sum);


}


//������ͳ�ƴ�����

void  staDepartment() {
	int  i;
	for (i = 0; i < dtop; i++)
		staD(i);


}

//ͳ��ҽ��i j�Ĵ�����
void  staDoc(int i, int  j) {
	Department dd;
	dd = drr[i];
	printf("%s\t %s\t �������� %d\n", dd.name, dd.arr[j].name, dd.arr[j].top);
}



//��ҽ��ͳ�ƴ�����
void   staDocotor() {
	int i, j;

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			staDoc(i, j);


}



//ͳ�Ƶ�a�����ҵ�ƽ����ҽʱ��
void  staDTime(int a) {
	int i, j;
	int  sum = 0;
	int  alltime = 0; //�ܵþ�ҽʱ��
	Department dd;
	dd = drr[a];
	for (i = 0; i < dd.top; i++) {
		sum += dd.arr[i].top; //��ÿ��ҽ���Ĵ���������������
		for (j = 0; j < dd.arr[i].top; j++)
			alltime += dd.arr[i].arr[j]->needtime;


	}

//ƽ����ҽʱ��
	float  f = 1.0 * alltime / sum;
	printf("%s\t ƽ����ҽʱ��(min)�� %.2f\n", dd.name, f);

}



//������ͳ��ƽ����ҽʱ��
void  staDepartmentTime() {
	int i;
	for (i = 0; i < dtop; i++)
		staDTime(i);

}

//ͳ��i jҽ����ƽ����ҽʱ��
void  staDocTime(int i, int  j) {
	Department dd;
	dd = drr[i];
	Doctor   doc = drr[i].arr[j];
	int  top = doc.top; //��ҽ�����Ĳ�������
	float  sum = 0; //��¼�ܵþ�ҽʱ��
	int  k;

	for (k = 0; k < top; k++)
		sum += doc.arr[k]->needtime;

	printf("%s\t %s\t ƽ����ҽʱ��(min)�� %.2f\n", dd.name, doc.name, sum / top);


}

//��ҽ��ͳ��ƽ����ҽʱ��
void   staDocotorTime() {
	int i, j;

	for (i = 0; i < dtop; i++)
		for (j = 0; j < drr[i].top; j++)
			staDocTime(i, j);

}


//���㲡�˵�ƽ���ȴ�ʱ��
void  staPatient() {
	int i;
	float  sum = 0; //�ܵõȴ�ʱ��
	for (i = 0; i < ptop; i++)
		sum += getMin(prr[i].endtime, prr[i].cometime);

	printf("���˵�ƽ���ȴ�ʱ��(min): %.2f\n", sum / ptop);

}