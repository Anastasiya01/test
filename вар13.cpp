#include "stdafx.h"
#include <iostream>
using namespace std;

//структуры для списка/очереди/стека и для двоичного дерева
struct list{				//1. Создать тип данных, описывающий звено двусвязного списка.
	double value;
	list *next, *prev;
};
struct tree{
	double key;
	tree *r, *l;
};
int h1; //высота дерева
//функции для заполнения информацией
void addInfo(list *d){	//ввод информации
	cout << "Введите число: ";
	cin >> d->value;
}
void initialize(list *d){	//инициализация
	cout << "Введите число: ";
	cin >> d->value;
	d->next = d;
	d->prev = d;
}

//функции вставки
void addlistNext(list *d){	//добавление в конец списка
	list *head = d;
	while(d->next != head)
		d = d->next;
	list *s = new list;
	addInfo(s);
	s->next = d->next;
	s->prev = d;
	d->next = s;
	s->next->prev = s;
}
list* addlistInBegin(list *d){//добавление в начало списка
	list *s = new list;
	list *end = d->prev;
	addInfo(s);
	s->next = d;
	end->next = s;
	s->prev = end;
	d->prev = s;
	return s;
}

//фунции для вывода информации на экран
void outInfo(list *d){	//вывод на экран значения поля структуры
		cout << d->value << " ";
}
void outlist(list *d){	//проход по всему списку/очереди для вывода информации на экран
	list *head = d;  
	bool first = true;
	while(d != head || first == true){
		outInfo(d);
		first = false;
		d = d->next;
	}
	cout << endl;
}
list* read(list *d){	//функция для извлечения значения из начала списка
	cout << d->value << endl;
	if(d->next == d && d->prev == d){
		d->value = ' ';
		cout << "Пусто" << endl;
		return d;
	}
	else{
		list *end = d->prev;
		end->next = d->next;
		d->next->prev = end;
		delete d;
		return end->next;
	}
}

//функции для удаления
void dellist(list *d){ //удаление звена
	list *t = d->next;
	d->next = d->next->next;
	delete t;
}
list* dellistHead(list *d){//удаление главного звена 
	list *a = d->next;
	a->prev = d->prev;
	d->prev->next = a;
	delete d;
	return a;
}
void dellistEnd(list *d){ //удаление последнего звена
	list *e = d->prev;
	e->prev->next = d;
	d->prev = e->prev;
	delete e;  
}
void searDel(list *d){//удаление звена из середины,  используя операцию поиска данных в списке
	char c;
	bool f = false;
	cout << "Введите число для удаления из середины: ";
	cin >> c;
	list *head = d;
	while(d->next != head){
		if(d->next->value == c){
			dellist(d);
			f = true;
			break;
		}
		d = d->next;
	}
	if(f == true)
		cout << "Удаление прошло успешно." << endl;
	else
		cout << "Искомый элемент не найден" << endl;
}
void delAll(list *d){//удаление всех звеньев
	list *head = d;
	while(d->next != head){
			dellist(d);
		d = d->next;
	}
	delete d;
	cout << "Все звенья удалены!" << endl;
}
//=================Функции для работы с деревом
void appendInfo(tree *&Tree){ //функция ввода информации в узел
		if (Tree!=NULL) //Пока не встретится пустое звено
	{
	   appendInfo(Tree->l); //Рекурсивная функция для вывода левого поддерева
	   appendInfo(Tree->r); //Рекурсивная функци для вывода правого поддерева
	   	   cout << "Ключ: " << Tree->key << endl;
	}
}

void add_node(double node, tree *&Tree){ //добавление узла с известным ключом
	if(Tree == NULL){
		Tree = new tree;
		Tree->key = node;
		Tree->l = NULL;
		Tree->r = NULL;
	}
	if(node < Tree->key){
			add_node(node, Tree->l);
	}
	if(node > Tree->key){
			add_node(node, Tree->r);
	}
}
void add_node(tree *&Tree){	//добавление узла с неизвестным ключом
	double node;
	cout << "Введите ключ: ";
	cin >> node;
	if(Tree == NULL){
		Tree = new tree;
		Tree->key = node;
		Tree->l = NULL;
		Tree->r = NULL;
	}
	if(node < Tree->key){
			add_node(node, Tree->l);
	}
	if(node > Tree->key){
			add_node(node, Tree->r);
	}
}

void del1(tree *&r,tree *&q)	//удаление узла
{
  if(r->r == NULL)
  {
    q->key=r->key;
   // q->y=r->y; переместить информацию
    q=r;
    r=r->l;
  }
  else
    del1(r->r ,q);
}
void delnode(tree *& d,int key)	//удаление элемента с заданным ключом
{
  tree *q;
  if(d==NULL)
    return;
  else
    if(key <d->key)
      delnode(d->l,key);
    else
      if(key >d->key)
	     delnode(d->r,key);
      else
      {
	     q=d;
	     if(q->r==NULL)
	       d=q->l;
	     else
	       if(q->l==NULL)
	         d=q->r;
	       else
		 del1(q->l,q);
	     delete q;
      }
}
void delAlllist(tree *&Tree){	//удаление всего дерева
   if (Tree!=NULL) //Пока не встретится пустое звено
	{
	   delAlllist(Tree->l); //Рекурсивная функция прохода по левому поддереву
	   delAlllist(Tree->r); //Рекурсивная функци для прохода по правому поддереву
	   delete Tree; //Убиваем конечный элемент дерева
	   Tree = NULL; //Может и не обязательно, но плохого не будет
	}
 
}

void Height(tree* t, int p, int &h)//определение высоты
{
  if(t == NULL) return;
  p++;
  if(t->l == NULL && t->r == NULL)
    if(p>h)
      h=p;
  Height(t->l,p,h);
  Height(t->r,p,h);
}
void inorder(tree *r){	//последовательный вывод
	if(r == NULL) return;
	inorder(r->l);
	cout << r->key <<  " ";
	inorder(r->r);
}
void preorder(tree *r){		//вывод в нисходящем порядке
	if(r == NULL) return;
	cout << r->key << " ";
	preorder(r->l);
	preorder(r->r);
}
void postorder(tree *r){	//вывод в восходящем порядке
	if(!r) return;
	postorder(r->l);
	postorder(r->r);
	cout << r->key << " ";
}

void poisk(tree* t, double skey, tree*& f,int p)
{
  if(t==NULL || p==1) return;
  if(t->key==skey)
  {  
	  cout << t->key << endl;
	  f = t;
	  p=1; 
	  return; 
  }
  poisk(t->l, skey,f,p);
  poisk(t->r, skey,f,p);
}
//===================================Основные функции
list* List(list *d){
	outlist(d);						//5. Просмотреть содержимое списка.
	bool fl = true;
	int key;

	while(fl){
		cout << "1-Просмотреть содержимое списка" << endl;
		cout << "2-Удалить звено следующее за ведущим" << endl;
		cout << "3-Удалить звено из середины списка" << endl;
		cout << "4-Выход" << endl;
		cout << "\n>>";
		cin >> key;
		switch(key){
		case 1:
			outlist(d);						//Просмотреть содержимое списка.
			break;
		case 2:
			dellist(d);						//6. Удалить звено, следующее за ведущим.
			cout << "Результат удаления звена следующего за ведущим: " << endl;
			outlist(d);						//7. Просмотреть содержимое списка
			break;
		case 3:
			searDel(d);						//8. Удалить звено из середины списка, используя операцию поиска данных в списке.
			outlist(d);						//9. Просмотреть содержимое списка.
			break;
		case 4:
			fl = false;
			break;
		}
	}
	return d;
}
list* Stack(list *d){
	outlist(d);						//Просмотреть содержимое
	bool fl = true;
	int key;
	while(fl){
		cout << "1-Добавить 1 звено в начало списка" << endl;
		cout << "2-Просмотреть содержимое списка" << endl;
		cout << "3-Считать данные из вершины стека " << endl;
		cout << "4-Выход" << endl;
		cout << "\n>>";
		cin >> key;
		switch(key){
		case 1:
			d = addlistInBegin(d);			//10. Добавить 1 звено в начало списка
			break;
		case 2:
			outlist(d);						//11. Просмотреть содержимое списка.
			break;
		case 3:
			cout << "Число считанное из вершины: ";
			d = read(d);					//12. Считать данные из вершины стека 
			break;
		case 4:
			fl = false;
			break;
		}
	}
	return d;
}
list* Enqueue(list *d){
	outlist(d);						// Просмотреть содержимое списка.
	bool fl = true;
	int key;

	while(fl){
		cout << "1-Просмотреть содержимое очереди" << endl;
		cout << "2-Добавить 1 звено в конец очереди" << endl;
		cout << "3-Считать число из вершины" << endl;
		cout << "4-Выход" << endl;
		cout << "\n>>";
		cin >> key;
		switch(key){
		case 1:
			outlist(d);						//Просмотреть содержимое списка.
			break;
		case 2:
			addlistNext(d);			//17. Добавить 1 звено в конец очереди					
			break;
		case 3:
			cout << "Сивол считанный из вершины: ";
			d = read(d);					//12. Считать данные из вершины стека 
			break;
		case 4:
			fl = false;
			break;
		}
	}	
	return d;
}
list* Dec(list *d){
	outlist(d);						// Просмотреть содержимое списка.
	bool fl = true;
	int key;

	while(fl){
		cout << "1-Просмотреть содержимое очереди" << endl;
		cout << "2-Добавить 1 звено в конец очереди" << endl;
		cout << "3-Удалить звено из начала очереди" << endl;
		cout << "4-Добавить 1 звено в начало очереди" << endl;
		cout << "5-Удалить звено из конца очереди" << endl;
		cout << "6-Удалить все звенья из списка" << endl;
		cout << "7-Выход" << endl;
		cout << "\n>>";
		cin >> key;
		switch(key){
		case 1:
			outlist(d);						//Просмотреть содержимое списка.
			break;
		case 2:
			addlistNext(d);//24. Добавить 1 звено в конец очереди 	
			break;
		case 3:
			d = dellistHead(d);//27. Удалить звено из начала очереди 
			break;
		case 4:
			d = addlistInBegin(d);	//29. Добавить 1 звено в начало очереди
			break;
		case 5:
			dellistEnd(d);//32. Удалить звено из конца очереди.
			break;
		case 6:
			delAll(d);//34. Удалить все звенья из списка." << endl;
			break;
		case 7:
			fl = false;
			break;
		}
	}	
	return d;	
}
void TREE(){
	tree *t = NULL;		//создание дерева
	double a;
	int n;
	cout << "Число элементов в дереве: ";
	cin >> n;
	cout << "Заполните дерево: " << endl;
	for(int i = 0; i < n; i++){//добавление ветвей в дерево
		cout << "Ключ: ";
		cin >> a;
		add_node(a, t);		   //Создать двоичное дерево поиска пут?м ввода данных (не менее 7 элементов).
	}

	cout << "Последовательный порядок: " << endl;	
	inorder(t);				//последовательный порядок
	cout << endl;				//38. Выполнить просмотр дерева в последовательном порядке

	cout << "Нисходящий порядок: " << endl;
	preorder(t);				//нисходящий порядок
	cout << endl;				//39. Выполнить просмотр дерева в нисходящем порядке

	cout << "Введите ключ для поиска: ";
	cin >> a;

	tree *s = 0;
	poisk(t, a, s, 0);//40. Выполнить поиск данных в дереве

	h1 = 0;
	Height(t,0,h1);//41. Определить высоту дерева.
	cout << "\nВысота дерева: " << h1 << endl;

	cout << "Дерево удалено" << endl;
	delAlllist(t);			//удаление дерева

	system("pause");

}
//================меню==========
void menu(){
	bool flag = true;
	int key;                 

	list *d = new list;			//3. Создать ведущее звено кольцевого двусвязного списка.

	while(flag){
	system("cls");
	cout << "0-Инициализировать список" << endl;
	cout << "1-Программа работы со связным списком" << endl;	cout << "2-Работа со списком как со стеком" << endl;	cout << "3-Работа со списком как с очередью" << endl;	cout << "4-Работа со списком как с двухвходовой очередью" << endl;	cout << "5-Работа с двоичным деревом поиска" << endl;
	cout << "6-Выход" << endl << endl << ">>";
	cin >> key;
		switch(key){
		case 0:
			cout << "Добавление N элементов в список " << endl;
			int n;
			cout << "N = ";
			cin >> n;
			initialize(d);
			for(int i = 0; i < n-1; i++)		//4. Заполнить список данными, 
				addlistNext(d);
			break;
		case 1:
			d = List(d);
			break;
		case 2:
			d = Stack(d);
			break;
		case 3:
			d = Enqueue(d);
			break;
		case 4:
			d = Dec(d);
			break;
		case 5:
			TREE();
			break;
		case 6:
			flag = false;
			break;
		}
	}

}
//===============================

//======начало======
int main()
{
	setlocale(LC_ALL, "");
	menu();
	system("pause");
	return 0;
}