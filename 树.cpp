#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#define OVERFLOW -1
#define OK 1
#define ERROR 0

typedef char ElemType;
using namespace std;

typedef struct BiTNode {          //������
	ElemType data;           //������,�洢�������
	struct BiTNode* lchild, * rchild;   //���Һ���ָ��
}BiTNode, * BinTree;

typedef struct CSNode {           //���ӡ��ֵܶ�������ṹ����
	ElemType data;              //������,�洢�������
	struct CSNode* firstchild, * nextsibling;  //����ָ������ֵ�ָ����
}CSNode, * CSTree;

BinTree creatbintree() {      //������������
	BinTree BT;
	ElemType ch;
	while ((ch = getchar()) == '\n');
	if (ch == '#')
		BT = NULL;
	else {
		BT = (BiTNode*)malloc(sizeof(BiTNode));
		if (!BT)
			exit(OVERFLOW);
		BT->data = ch;
		BT->lchild = creatbintree();
		BT->rchild = creatbintree();
	}
	return BT;
}

void CreateCSTree(CSTree& CT) { 	  // �������ӡ��ֵܶ�������ṹ����
	char c[20];           // ��ʱ��ź��ӽ��(�費����20��)��ֵ
	CSTree p, p1;
	queue<CSTree> q;
	int i, l;
	cout << "����������: ";
	scanf("%c%*c", &c[0]);      //%*c�Ե��س�������Ȼֱ��������ִ������������
	if (c[0]) {   // �ǿ���
		CT = (CSTree)malloc(sizeof(CSNode)); // ���������
		CT->data = c[0];
		CT->nextsibling = NULL;
		q.push(CT); // ��Ӹ�����ָ��
		while (!q.empty()) {    // �Ӳ���
			p = q.front();
			q.pop(); // ����һ������ָ��
			cout << "�밴����˳��������" << p->data << "�����к���(�޺�����ֱ�Ӱ��س���): ";
			scanf("%s", c);   //�Ӽ��̽���һ���ַ��������飬�Իس�����
			l = strlen(c);
			if (l > 0) {    // �к���
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode)); // �������ӽ��
				p1->data = c[0];
				for (i = 1; i < l; i++) {
					p1->nextsibling = (CSTree)malloc(sizeof(CSNode)); // ������һ���ֵܽ��
					q.push(p1); // �����һ�����
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;
				q.push(p1); // ������һ�����
			}
			else
				p->firstchild = NULL; // ����ָ��Ϊ��
		}
	}
	else
		CT = NULL; // ����
}

int ExchangeToBiTree(CSTree& CT, BinTree& BT) {      //��һ���ö��������ʾ����ͨ��ת��Ϊ������
	if (!CT) {
		BT = NULL;
	}
	else {
		if (!(BT = (BiTNode*)malloc(sizeof(BiTNode)))) {
			exit(OVERFLOW);
		}
		BT->data = CT->data;
		ExchangeToBiTree(CT->firstchild, BT->lchild);
		ExchangeToBiTree(CT->nextsibling, BT->rchild);
	}
	return OK;
}

void PreorderTraversal(BinTree BT) {        //����ݹ����������
	if (BT) {
		cout << BT->data << " ";
		PreorderTraversal(BT->lchild);
		PreorderTraversal(BT->rchild);
	}
}

void PreOrder(CSTree CT) {       //����ݹ�������ӡ��ֵܶ�������ṹ����CT
	if (CT) {
		cout << CT->data << " ";
		PreOrder(CT->firstchild);
		PreOrder(CT->nextsibling);
	}
}

void InorderTraversal(BinTree BT) {      //����ݹ����������
	if (BT) {
		InorderTraversal(BT->lchild);
		cout << BT->data << " ";
		InorderTraversal(BT->rchild);
	}
}

void PostorderTraversal(BinTree BT) {    //����ݹ����������
	if (BT) {
		PostorderTraversal(BT->lchild);
		PostorderTraversal(BT->rchild);
		cout << BT->data << " ";
	}
}

void PostOrderTraverse(CSTree CT) {      // ����ݹ�������ӡ��ֵܶ�������ṹ����CT
	CSTree p;
	if (CT) {
		if (CT->firstchild) {   // // �г���
			PostOrderTraverse(CT->firstchild); // ����������ӵ�����
			p = CT->firstchild->nextsibling; // pָ���ӵ���һ���ֵ�
			while (p) {
				PostOrderTraverse(p); // ���������һ���ֵ�����
				p = p->nextsibling; // pָ������һ���ֵ�
			}
		}
		cout << CT->data << " ";// �����ʸ����
	}
}

void LevelorderTraversal(BinTree BT) {     //�������������
	BinTree Q[100];
	BinTree p;
	int front = -1;
	int rear = -1;
	if (!BT)
		return;
	if (BT) {
		Q[++rear] = BT;
		while (front != rear) {
			p = Q[++front];     //��ֵ����
			cout << p->data << " ";
			if (p->lchild)
				Q[++rear] = p->lchild;
			if (p->rchild)
				Q[++rear] = p->rchild;
		}
	}
}

void LevelOrderTraverse(CSTree CT) { // ����������ӡ��ֵܶ�������ṹ����CT
	CSTree p;
	queue<CSTree> q;
	if (CT) {
		cout << CT->data << " "; // �ȷ��ʸ����
		q.push(CT); // ��Ӹ�����ָ��
		while (!q.empty()) {    // �Ӳ���
			p = q.front();    //��ȡ��ͷԪ��
			q.pop(); // ����һ������ָ��
			if (p->firstchild) {  // �г���
				p = p->firstchild;
				cout << p->data << " "; // ���ʳ��ӽ��
				q.push(p); // ��ӳ��ӽ���ָ��
				while (p->nextsibling) {// ����һ���ֵ�
					p = p->nextsibling;
					cout << p->data << " "; // ������һ���ֵ�
					q.push(p); // ����ֵܽ���ָ��
				}
			}
		}
	}
}

void preOrder1(BinTree BT) {    //�ǵݹ��������������
	stack<BinTree> s;
	BinTree p = BT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			cout << p->data << " ";
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty()) {
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

void preOrder2(CSTree CT) {    //����ǵݹ�������ӡ��ֵܶ�������ṹ����CT
	stack<CSTree> s;
	CSTree p = CT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			cout << p->data << " ";
			s.push(p);
			p = p->firstchild;
		}
		if (!s.empty()) {
			p = s.top();
			s.pop();
			p = p->nextsibling;
		}
	}
}

void inOrder1(BinTree BT) {    //�ǵݹ��������������
	stack<BinTree> s;
	BinTree p = BT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty()) {
			p = s.top();
			cout << p->data << " ";
			s.pop();
			p = p->rchild;
		}
	}
}

void postOrder1(BinTree BT) {   //�ǵݹ�������������
	stack<BinTree> s;
	BinTree cur;                      //��ǰ���
	BinTree pre = NULL;                 //ǰһ�η��ʵĽ��
	s.push(BT);
	while (!s.empty()) {
		cur = s.top();
		if ((cur->lchild == NULL && cur->rchild == NULL) ||
			(pre != NULL && (pre == cur->lchild || pre == cur->rchild))) {
			cout << cur->data << " ";  //�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�
			s.pop();
			pre = cur;
		}
		else {
			if (cur->rchild != NULL)
				s.push(cur->rchild);
			if (cur->lchild != NULL)
				s.push(cur->lchild);
		}
	}
}

void  postOrder2(CSTree CT) {       //����ǵݹ�������ӡ��ֵܶ�������ṹ����CT
	stack<CSTree> s;
	while (CT || !s.empty()) {
		while (CT) {
			s.push(CT);
			CT = CT->firstchild;
		}
		CT = s.top(); s.pop();//STLҪ����������
		cout << CT->data << " ";
		CT = CT->nextsibling;//CT����Ϊ�յ�
	}
}

void destoryBinTree(BinTree BT) {        //���ٶ�����
	if (!BT)
		return;
	if (BT->lchild)
		destoryBinTree(BT->lchild);//����������
	if (BT->rchild)
		destoryBinTree(BT->rchild);//����������
	free(BT);//�ͷŵ�ǰ���
}

void clock_delay() {       //ʱ����ʱ����
	clock_t tm;
	tm = clock();
	while (clock() < tm + 1000);
}

void menu() {
	char ch;
	cout << endl << endl << endl << "                                                �� �� �� ��" << endl << endl;
	cout << "                                      *********************************" << endl << endl;
	cout << "                                                 1.������" << endl << endl;
	cout << "                                                 2.��ͨ��" << endl << endl;
	cout << "                                                 3.�˳�ϵͳ" << endl << endl;
	cout << "                                      *********************************" << endl << endl;
}

int main() {
	system("color b0");
	while (1) {
		system("cls");
		menu();
		cout << "��ѡ���Ӧ�˵���(1-3):";
		int cho;
		cin >> cho;
		switch (cho) {
		case 1: {
			system("cls");
			system("color b0");
			cin.clear();
			cin.sync();
			cout << "�밴������������������#Ϊ��:" << endl;
			BinTree BT = creatbintree();
			cout << "����������:"; PreorderTraversal(BT); cout << endl;
			cout << "����������:"; InorderTraversal(BT);   cout << endl;
			cout << "����������:"; PostorderTraversal(BT); cout << endl;
			cout << "����������:"; LevelorderTraversal(BT); cout << endl;
			cout << "����ǵݹ�:"; preOrder1(BT); cout << endl;
			cout << "����ǵݹ�:";  inOrder1(BT); cout << endl;
			cout << "����ǵݹ�:";  postOrder1(BT); cout << endl;
			cout << "�������ٶ�����...";  destoryBinTree(BT); cout << endl;
			clock_delay();
			cout << "������ɣ�" << endl << endl;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			system("color b0");
			cin.clear();
			cin.sync();
			CSTree CT;
			BinTree BT;
			CreateCSTree(CT);
			cout << endl << "ǰ��������:"; PreOrder(CT);   cout << endl;
			cout << "ǰ��ǵݹ�������:"; preOrder2(CT);   cout << endl;
			cout << "����������:"; PostOrderTraverse(CT);   cout << endl;
			cout << "����ǵݹ�������:"; postOrder2(CT);   cout << endl;
			cout << "��α������:"; LevelOrderTraverse(CT);  cout << endl << endl;
			cout << "���ڽ��������ת��Ϊ���Ӧ�Ķ�����..." << endl;
			clock_delay();
			ExchangeToBiTree(CT, BT);
			cout << "ת������ִ�����!" << endl;
			cout << "ת����Ķ�����������������:"; PreorderTraversal(BT); cout << endl;
			cout << "ת����Ķ�����������������:"; InorderTraversal(BT);   cout << endl << endl;
			cout << "�ɴ˿ɼ�������ǰ�������Ӧ��������ǰ����������ĺ��������Ӧ���������������!" << endl << endl;
			system("pause");
			break;
		}
		case 3: {
			cout << "�����˳�ϵͳ...";
			clock_delay();
			return 0;
		}
		default:return 0;
		}
	}
	return 0;
}