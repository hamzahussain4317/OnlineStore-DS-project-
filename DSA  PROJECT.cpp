#include<iostream>
#include<stdlib.h>
#include <conio.h> 
#include <time.h>
#include <windows.h>
#include <ctime>
#include<vector>
//#include<SFML/Graphics.hpp>
#include<fstream>
using namespace std;

//macros/constants
#define maxcart 4
#define sections 6
//Classes Predefinition
class Item;
class Section;
class Path;
class Store;
class Product;
class Cart;
class Cart_Item;
class Admin;
class Consumer;
class Stack;
class StackItem;
//classes definition
//HashMap FUNCTION For PatternMatching
bool HashMatch(string name, char* input)
{
	int a = name.length();
	int b = strlen(input);
	if (b > a)
		return false;
	float power = b - 1;
	double hash1 = 0;
	double hash2 = 0;
	for (int i = 0; i < b && i < a; i++)
	{
		hash1 += (name[i] * pow(10, power));
		hash2 += (input[i] * pow(10, power));
		power--;
	}
	//cout <<"TEXT : "<< hash1 << endl;
	//cout <<"Pattern : "<< hash2 << endl;

	if (hash1 == hash2)
	{
		return true;

	}
	return false;
}
class StackItem {
public:
	string name, id;
	StackItem* next;
	StackItem()
	{
		next = NULL;
	}
	StackItem(string item_name, string item_id)
	{
		this->name = item_name;
		this->id = item_id;
		this->next = NULL;
	}

};
class Stack {
	StackItem* top;
public:
	Stack()
	{
		top = NULL;
	}
	void push(string name, string id)
	{
		StackItem* insert = new StackItem(name, id);
		if (!top)
		{
			top = insert;
		}
		else
		{
			insert->next = top;
			top = insert;
		}
	}
	string peek_name()
	{
		if (isEmpty())
			return "";
		return top->name;
	}
	string peek_id()
	{
		if (isEmpty())
			return "";
		return top->id;
	}
	string pop()
	{
		string ret_name = top->name;
		top = top->next;
		return ret_name;
	}
	bool isEmpty()
	{
		if (!top)
			return 1;
		return 0;
	}
	bool isFull()
	{
		if (new StackItem())
			return 0;
		return 1;
	}
	void ShowList()
	{
		if (top == NULL)
		{
			cout << "No Such Item Present in Our Store Sorry for Inconvenience!" << endl;
			return;
		}
		StackItem* iter = top;
		while (iter)
		{
			cout << iter->name << " (" << iter->id << ")" << endl;
			iter = iter->next;
		}
		cout << endl;
	}
	void clean()
	{
		delete top;
		top = NULL;
	}
	bool isAvailable(string n)
	{
		StackItem* iter = top;
		while (iter)
		{
			if (iter->name == n)
				return true;
			iter = iter->next;
		}
		return false;
	}
};
class Consumer {

	string id;
	string password;
	string name;
	float current_balance;

public:
	Consumer() {
		current_balance = 0;
		id = "CUS-0000";
		password = name = "customer";
	}
	Consumer(string id, string name, string pass, double balance = 1000) {
		this->id = "CUS-0000";
		this->password = pass;
		this->name = name;
		this->current_balance = balance;
		setid(id);
	}
	bool operator==(const Consumer c1)
	{
		if (this->id == c1.id && this->name == c1.name)
			return true;
		else
			return false;
	}
	void setname(string nam)
	{
		this->name = nam;
	}
	float get_balance_amount() {
		return current_balance;
	}
	void set_balance_amount(float m) {
		this->current_balance += m;
	}
	void update_balance_amount(float m) {
		this->current_balance -= m;
	}
	void setid(string ID)
	{
		int val = 0;
		int pos = 1;
		for (int i = 7; i >= 4; i--)
		{
			val = (ID[i] - 48) * pos + val;
			pos *= 10;
		}
		val++;
		for (int i = 7; i >= 4; i--)
		{
			id[i] = (val % 10) + 48;
			val /= 10;
		}
	}
	void setpassword(string nam)
	{
		this->password = nam;
	}
	string getID()
	{
		return id;
	}
	string getName()
	{
		return name;
	}
	string getPass()
	{
		return password;
	}
	void display()
	{
		cout << "CUSTOMER DETAILS" << endl;
		cout << "ID -->" << id << endl;
		cout << "Name -->" << name << endl;
		cout << "Password -->" << password << endl;
	}
};
class Node {
public:
	Consumer value;
	Node* next;
	Node()
	{
		next = NULL;
	}
	Node(Consumer val)
	{
		this->value = val;
		this->next = NULL;
	}
};
class LLQueue {
public:
	Node* front, * rear;
	LLQueue()
	{
		front = rear = NULL;
	}
	bool isEmpty()
	{
		if (front)
			return false;
		return true;
	}
	bool isFull()
	{
		Node* check = new Node();
		if (check)
			return false;
		delete check;
		check = NULL;
		return true;
	}
	void Enqueue(Consumer val)
	{
		if (isFull())
			cout << "Queue is Full" << endl;
		else
		{
			if (front == NULL)
				rear = front = new Node(val);
			else
			{
				Node* ins = new Node(val);
				rear->next = ins;
				rear = ins;
			}
		}
	}
	Consumer Dequeue()
	{
		if (!isEmpty())
		{
			Node* delte = front;
			Consumer del = front->value;
			front = front->next;
			delete delte;
			return del;
		}
		else
			cout << "Queue is Empty" << endl;
	}
	//void Print()
	//{
	//	Node* temp = front;
	//	while (temp)
	//	{
	//		cout << temp->value << " ";
	//		temp = temp->next;
	//	}
	//	cout << endl;
	//}
};

class Item {
public:
	int quantity;
	string name;
	string id;
	double weight;
	double price;
	int discount;
public:
	Item()
	{
		quantity = 0;
		name = id = " ";
		weight = price = 0;
		discount = 0;
	}
	Item(int no, string id, string name, double weight, double price)
	{
		this->quantity = no;
		this->name = name;
		this->id = id;
		this->weight = weight;
		this->price = price;
		this->discount = 0;
	}
	Item(const Item* temp) {
		this->discount = temp->discount;
		this->id = temp->id;
		this->weight = temp->weight;
		this->price = temp->price;
		this->name = temp->name;
		this->quantity = temp->quantity;
	}
	void updte_stock(int q) {
		this->quantity += q;
	}
	bool operator>(Item item)
	{
		if (this->id > item.id)
			return true;
		return false;
	}
	bool operator<(Item item)
	{
		if (this->id < item.id)
			return true;
		return false;
	}
	bool operator==(Item item)
	{
		if (this->id == item.id)
			return true;
		return false;
	}
	void operator<<(ostream& out)
	{
		out << "=============================" << endl;
		out << "Item_Id : " << this->id << endl;
		out << "Item_Name : " << this->name << endl;
		out << "Quantity : " << this->quantity << endl;
		out << "Price per Quantity : " << this->price << endl;
		out << "Weight per Quantity : " << this->weight << endl;
		out << "Discount : " << this->discount << "%" << endl;
		out << "=============================" << endl;
	}
};
//class Path {
//public:
//	int distance;
//	Section* ending_vertex;
//	Path* nxt;
//};

//Product as a node class for AVL Tree
class Product {
public:
	Item item;
	Product* left;
	Product* right;

	Product(Item item1)
	{
		this->item = item1;
		left = right = NULL;
	}
	int getHeight()
	{
		if (!this)
			return 0;
		int left = this->left->getHeight();
		int right = this->right->getHeight();
		if (left > right)
			return left + 1;
		else
			return right + 1;
	}
	//PART (e)
	int getSize()
	{
		if (!this)
			return 0;
		return this->left->getSize() + this->right->getSize() + 1;
	}
	int getBalanceFactor()
	{
		if (!this)
		{
			if (!this->left && !this->right)
				return 0;

			return this->left->getHeight() - this->right->getHeight();
		}
		return 0;
	}
	Product* rotateleft()
	{
		Product* newnode = this->right;
		Product* left = newnode->left;
		newnode->left = this;
		this->right = left;
		return newnode;
	}
	Product* rotateright()
	{
		Product* newnode = this->left;
		Product* right = newnode->right;
		newnode->right = this;
		this->left = right;
		return newnode;
	}
	//insertion function
	Product* add_to_stock(Item item1)
	{
		if (!this)
			return new Product(item1);
		if (this->item == item1)
		{
			return this;
		}
		else if (this->item > item1)
		{
			this->left = this->left->add_to_stock(item1);
		}
		else if (this->item < item1)
		{
			this->right = this->right->add_to_stock(item1);
		}
		int bf = getBalanceFactor();

		//rotations
		if (bf > 1 && item1 < this->left->item)
		{
			return this->rotateright();
		}
		if (bf < -1 && item1 > this->right->item)
		{
			return this->rotateleft();

		}
		if (bf > 1 && item1 > this->left->item)
		{
			this->left = this->left->rotateleft();
			return this->rotateright();
		}
		if (bf < -1 && item1 < this->right->item)
		{
			this->right = this->right->rotateright();
			return this->rotateleft();
		}

		return this;

	}
	//deletions functions
	Product* findpre()
	{
		Product* temp = this;
		temp = temp->left;
		Product* prev = NULL;
		while (temp->right != NULL)
		{
			prev = temp;
			temp = temp->right;
		}
		if (prev)
			prev->right = NULL;
		return temp;
	}
	Product* Remove_from_stock(Item item1)
	{
		if (this)
		{
			if (this->item == item1)
			{
				//flag = 1;
				Product* ret = NULL;
				if (!this->right && !this->left)
				{
					delete this;
					return ret;
				}
				if (!this->right)
				{
					ret = this->left;
				}
				else if (!this->left)
				{
					ret = this->right;
				}
				else {
					ret = this->findpre();
					//link the right of deleted node to the right of predecessor node
					ret->right = this->right;

					//setting the left of deleted node to the most left of the predecessor node
					Product* iter = ret;
					if (iter != this->left)
					{
						while (iter->left != NULL)
						{
							iter = iter->left;
						}
						iter->left = this->left;
					}
				}
				delete this;
				return ret;
			}
			//recursive calls
			if (this->item > item1)
				this->left = this->left->Remove_from_stock(item1);
			else if (this->item < item1)
				this->right = this->right->Remove_from_stock(item1);
		}


		//rotations
		int left_bf = this->left->getBalanceFactor();
		int right_bf = this->right->getBalanceFactor();
		int bf = this->getBalanceFactor();
		if (bf > 1 && left_bf < 0) {
			this->left = this->left->rotateleft();
			return this->rotateright();
		}
		else if (bf < 1 && right_bf>0) {
			this->right = this->right->rotateright();
			return this->rotateleft();
		}
		else if (bf > 1) {
			return this->rotateright();
		}
		else if (bf < -1) {
			return this->rotateleft();
		}
		return this;
	}
	void extract_stock()
	{
		if (!this)
			return;
		this->left->extract_stock();
		this->item << cout;
		this->right->extract_stock();
	}
	void fillItemList(Item* item1, int& index)
	{
		if (this)
		{
			this->left->fillItemList(item1, index);
			item1[index++] = this->item;
			this->right->fillItemList(item1, index);
		}
		return;
	}
	Item search(string id) {
		Item* temp = new Item();
		if (this) {
			if (this->item.id == id) {
				if (this->item.quantity <= 0) {
					return temp;
				}

				int quant=0;
				Item* temp = new Item(this->item);
				cout << "Item Details : " << endl;
				this->item << cout;
				while (1)
				{
					cout << "Enter No of quantity You want : " << endl;
					cin >> quant;
					if (quant > this->item.quantity)
					{
						cout << "Enough Quantity !" << endl;
						continue;

					}
					this->item.quantity = this->item.quantity - quant;
					temp->quantity = quant;
					break;
				}
				return temp;
			}
			else if (this->item.id > id) {
				return this->left->search(id);
			}
			else
			{
				return this->right->search(id);
			}
		}
		return temp;
	}
	void searching(string id, int q) {
		if (this) {
			if (this->item.id == id) {
				this->item.quantity += q;

			}
			else if (this->item.id > id) {
				this->left->searching(id, q);
			}
			else
			{
				this->right->searching(id, q);
			}
		}
	}
	void GetMatch1(Stack& l, Stack& undo,char* ch)
	{
		if (!this)
			return;
		if (HashMatch(this->item.name, ch))
		{
			l.push(this->item.name, this->item.id);
			undo.push(this->item.name, this->item.id);
		}
		this->left->GetMatch1(l, undo, ch);
		this->right->GetMatch1(l, undo, ch);
	}
	void GetMatch2(Stack& l, Stack& undo, char* ch)
	{
		if (!this)
			return;
		if (HashMatch(this->item.name, ch))
		{
			if (!l.isAvailable(this->item.name))
			{
				l.push(this->item.name, this->item.id);
				undo.push(this->item.name, this->item.id);
			}
		}
		this->left->GetMatch2(l, undo, ch);
		this->right->GetMatch2(l, undo, ch);
	}
};
//section as an AVL TREE for LOG(N) search for product
class Section {
public:
	int items;
	string name;
	//product as a root of tree
	Product* product;
	//next pointer is for making linked list of all sections rather than array
	//Section* next;
	Section()
	{
		items = 0;
		name = " ";
		product = NULL;
		
	}
	Section(string name)
	{
		this->items = 0;
		this->name = name;
		product = NULL;
		
	}
	Section(int items, string name)
	{
		this->items = items;
		this->name = name;
		product = NULL;
		
	}
	//this function is for setting product's data after reading from file(updated data)
	void SetProductsStock(Item* item, int items,string name)
	{
		this->items = items;
		this->name = name;
		for (int i = 0; i < items; i++)
		{
			product = product->add_to_stock(item[i]);
		}
	}
	void setProduct(Item item1)
	{
		if (product)
			product = product->add_to_stock(item1);
		else
			product = new Product(item1);
		items++;
	}
	void DisplayStock()
	{
		product->extract_stock();
	}
	void extractItems(Item* item)
	{
		int i = 0;
		product->fillItemList(item, i);
	}
	void update(string id, int q) {
		product->searching(id, q);

	}
	Item search(string id) {
		return product->search(id);
	}
	void GetMatch1(Stack& l,Stack& undo,char* ch)
	{
		product->GetMatch1(l, undo,ch);
	}
	void GetMatch2(Stack& l, Stack& undo, char* ch)
	{
		product->GetMatch2(l, undo, ch);
	}
};

//due to real time experience we implement stack on on our cart class
//also we have a weight variable in cart class that is max_weight
class Cart_Item {
public:
	Item id;
	Cart_Item* nxt_item;

	Cart_Item() {
		nxt_item = NULL;
	}
	Cart_Item(Item it) {
		this->id = it;
		nxt_item = NULL;
	}
};
class Cart {
	float weight;
	Cart_Item* top;
public:
	Cart() {
		weight = 0;
		top = NULL;
	}
	bool isFull(float w8)
	{
		if (weight + w8 > maxcart)
			return true;
		return false;
	}

	bool isEmpty()
	{
		if (top == NULL)
			return true;
		return false;
	}

	void add_to_cart(Item* t1)
	{
		if (isFull(t1->weight)) {
			cout << "Your shopping cart is full" << endl;
			return;
		}
		else {
			if (t1->quantity == 0) {
				cout << "Product is out of stock" << endl;
				return;
			}
			else {
				weight = weight + t1->weight;
				Cart_Item* temp = new Cart_Item(t1);
				if (top == NULL) {
					top = temp;
				}
				else {
					temp->nxt_item = top;
					top = temp;
				}
			}

		}
		show();
	}
	int pop() {
		if (isEmpty()) {
			cout << "your cart is empty" << endl;
			return NULL;
		}
		else {
			Cart_Item* temp = top;
			top = top->nxt_item;
			int value = temp->id.price;
			//delete [] temp;
			temp = NULL;
			return value;
		}
	}
	Item front() {
		return top->id;
	}
	void show() {
		cout << endl << "Your stack contain: " << endl;
		Cart_Item* temp = top;
		while (temp != NULL) {
			temp->id << cout;
			cout << endl;
			temp = temp->nxt_item;
		}
	}
};
void welcomepage(Store& st);
class Store {
public:
	int sectionno;
	//section as a starting vertex of graph(source)
	Section* section;
	Store()
	{
		sectionno = 0;
		section = NULL;
	}
	Store(int sectionno)
	{
		this->sectionno = sectionno;
		section = new Section[sections];
	}
	void setstock()
	{

	}
	Item search(string id, int index) {
		return section[index].search(id);
	}
	//these functions are for initial set stock data very first
	Item* GetGroccery()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "G-0001", "potato", 1, 119.99);
		item[1] = Item(3, "G-0010", "carrot", 1, 99.99);
		item[2] = Item(5, "G-0200", "onions", 1, 149.99);
		item[3] = Item(15, "G-0003", "ponam rice", 1, 39.99);
		item[4] = Item(1, "G-0003", "ponia rice", 1, 39.99);
		item[5] = Item(5, "G-0003", "cabbage", 1, 39.99);
		return item;
	}
	Item* GetSports()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "S-0001", "bat", 1, 1199.99);
		item[1] = Item(3, "S-0010", "ball", 1, 99.99);
		item[2] = Item(5, "S-0200", "football", 1, 1049.99);
		item[3] = Item(15, "S-0003", "basketball", 1, 1139.99);
		item[4] = Item(5, "S-0003", "tennis", 1, 1139.99);
		item[5] = Item(1, "S-0003", "badminton", 1, 1139.99);
		return item;

	}
	Item* GetGarment()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "Ga-0001", "underwear", 1, 119.99);
		item[1] = Item(3, "Ga-0010", "gloves", 1, 99.99);
		item[2] = Item(5, "Ga-0200", "socks", 1, 149.99);
		item[3] = Item(15, "Ga-0003", "tshirt", 1, 39.99);
		item[4] = Item(15, "Ga-0030", "pants", 1, 39.99);
		item[5] = Item(15, "Ga-0020", "trousers", 1, 39.99);
		return item;

	}
	Item* GetCosmetics()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "C-0001", "lipstick", 1, 119.99);
		item[1] = Item(3, "C-0010", "earring", 1, 99.99);
		item[2] = Item(5, "C-0200", "eyelashes", 1, 149.99);
		item[3] = Item(15, "C-0003", "necklace", 1, 39.99);
		item[4] = Item(15, "C-0004", "necklace", 1, 39.99);
		item[5] = Item(15, "C-0100", "necklace", 1, 39.99);

		return item;

	}
	Item* GetFruits()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "F-0001", "strawberry", 1, 119.99);
		item[1] = Item(3, "F-0010", "banana", 1, 99.99);
		item[2] = Item(5, "F-0200", "apple", 1, 149.99);
		item[3] = Item(15, "F-0003", "orange", 1, 39.99);
		item[4] = Item(15, "F-0030", "apricot", 1, 39.99);
		item[5] = Item(15, "F-0020", "blueberry", 1, 39.99);
		return item;

	}
	Item* GetFrozen()
	{
		Item* item = new Item[6];
		item[0] = Item(5, "G-0001", "paratha", 1, 119.99);
		item[1] = Item(3, "G-0010", "chocolates", 1, 99.99);
		item[2] = Item(5, "G-0200", "spaghetti", 1, 149.99);
		item[3] = Item(15, "G-0003", "cheese", 1, 1299.99);
		item[4] = Item(15, "G-0030", "pizza", 1, 1299.99);
		item[5] = Item(15, "G-0020", "sandwich", 1, 1299.99);
		return item;

	}
	void forfirstuse()
	{
		section = new Section[sections];
		this->sectionno = sections;
		Item* items = GetGroccery();
		section[0].SetProductsStock(items, 6,"Grocery");
		items = GetGarment();
		section[1].SetProductsStock(items, 6,"Garments");
		items = GetCosmetics();
		section[2].SetProductsStock(items, 6,"Cosmetics");
		items = GetSports();
		section[3].SetProductsStock(items, 6,"Sports");
		items = GetFruits();
		section[4].SetProductsStock(items, 6,"Fruits");
		items = GetFrozen();
		section[5].SetProductsStock(items, 6,"Frozen");


		string filename[6] = { "grocery.txt", "garment.txt", "cosmetics.txt","sports.txt","fruits.txt" ,"frozen.txt", };
		ofstream f1;
		for (int i = 0; i < sections; i++)
		{
			f1.open(filename[i], ios::out | ios::binary);
			Item* t1 = new Item[section[i].items];
			section[i].extractItems(t1);
			for (int i = 0; i < section[i].items; i++)
			{
				f1.write((char*)&t1[i], sizeof(Item));
			}
			f1.close();
		}

	}

	void bill_counter(Cart* c11, Consumer* cc1) {
		Cart ct;
		float total_price = 0;
		Item temp;
		cout << "============================" << endl;
		cout << "\tCustomer BILL" << endl;
		cout << "============================" << endl;
		cout << "Item ID \t Item Name \t Item Price \t Quantity \t TotalPrice" << endl;
		while (!c11->isEmpty()) {
			Item  ci = c11->front();

			cout << ci.id << "\t\t  " << ci.name << "\t\t" << ci.price << "\t\t"<<ci.quantity<<"\t\t"<<ci.price*ci.quantity<<endl;
			total_price = total_price + (ci.price * ci.quantity);
			c11->pop();
		}
		int opt;
		if (cc1->get_balance_amount() < total_price) {
			cout << "your current balance is not enough" << endl;
			cout << "1.for add balance" << endl;
			cin >> opt;
			if (opt == 1) {
				float am;
				cout << "how much amount you want to add: " << endl;
				cin >> am;
				cc1->set_balance_amount(am);
			}
		}
		cc1->update_balance_amount(total_price);
		cout << "==============================================" << endl;

		cout << "ID: " << cc1->getID() << endl;
		cout << "Name: " << cc1->getName() << endl;
		cout << "total bill : " << total_price << endl;
		cout << "Your current balance: " << cc1->get_balance_amount() << endl;
		cout << "==============================================" << endl;

		return;
	}
	void Open()
	{
		//reading data from file of different sections and load into the STOCK
		string filename[6] = { "grocery.txt", "garment.txt", "cosmetics.txt","sports.txt","fruits.txt" ,"frozen.txt", };
		Item t1;
		section = new Section[sections];
		ifstream f1;

		for (int i = 0; i < sections; i++)
		{
			f1.open(filename[i], ios::in | ios::binary);
			while (f1.read((char*)&t1, sizeof(Item)))
			{
				/*if(t1.id != " " && t1.name != " ")*/
				section[i].setProduct(t1);
				if (f1.eof())
					break;
			}
			f1.close();
		}
		//cout << "SECTIONS DISPLAY" << endl;
		//for (int i = 0; i < sections; i++)
		//{
		//	section[i].DisplayStock();
		//}

		welcomepage(*this);
		exit(0);
	}
	void Shopping(Consumer& cc1)
	{
		Cart c1;
		int opt;
		while (1)
		{
			cout << "want to see section list or search item by name" << endl;
			cout << "1.Section List" << endl;
			cout << "2.Search item" << endl;
			cout << "3.Exit" << endl;
			cin >> opt;
			int flag;
			int batao, cont, hn;

			switch (opt)
			{
			case 1:
				ShowSectionList();
				cin >> batao;
				DisplaySectionProducts(batao - 1);
				cout << "Want to buy(1/0) " << endl;
				cin >> cont;
				if (cont == 1)
				{
					cout << "Enter the id of product you want to buy : " << endl;
					string id;
					cin >> id;
					//search item by id//
					Item t1 = search(id, batao - 1);

					c1.add_to_cart(&t1);
				}
				else
				{
					cout << "Want to go to the billing counter or another section: (1/0)" << endl;
					cout << "1.Billing counter" << endl;
					cout << "2.Proceed to Shopping" << endl;
					cin >> hn;
					if (hn == 2) {
						continue;
					}
					else {
						//billing counter working
						bill_counter(&c1, &cc1);
						break;
					}
				}
				break;
			case 2:
				SEO();
				cout << "Want to buy(1/0) " << endl;
				cin >> cont;
				if (cont == 1)
				{
					cout << "Enter the id of product you want to buy : " << endl;
					string id;
					cin >> id;
					//search item by id//
					Item t1;
					for (int i = 0; i < sections; i++)
					{
						t1 = search(id, i);
						if (t1.id == " " && t1.name == " ")
							continue;
						else
							break;
					}
					c1.add_to_cart(&t1);
				}
				else
				{
					cout << "Want to go to the billing counter or another section: (1/0)" << endl;
					cout << "1.Billing counter" << endl;
					cout << "2.Proceed to Shopping" << endl;
					cin >> hn;
					if (hn == 2) {
						continue;
					}
					else {
						//billing counter working
						bill_counter(&c1, &cc1);
						break;
					}
				}
				break;
			case 3:
				Close(cc1);
				exit(0);
				break;
			default:
				break;
			}
		}
	}
	void DisplaySectionProducts(int i)
	{
		section[i].DisplayStock();
	}
	void update_stock(int i, int q, string id) {
		section[i].update(id, q);
	}
	void ShowSectionList()
	{
		cout << "1.Grocery" << endl;
		cout << "2.Garments" << endl;
		cout << "3.Cosmetics" << endl;
		cout << "4.Sports" << endl;
		cout << "5.Fruits" << endl;
		cout << "6.Frozen" << endl;
	}
	void Close(Consumer c1)
	{
		//writing updated data of store items
		string filename[6] = { "grocery.txt", "garment.txt", "cosmetics.txt","sports.txt","fruits.txt" ,"frozen.txt", };
		ofstream f1;
		for (int i = 0; i < sections; i++)
		{
			f1.open(filename[i], ios::out | ios::binary);
			Item* t1 = new Item[section[i].items];
			section[i].extractItems(t1);
			for (int i = 0; i < section[i].items; i++)
			{
				f1.write((char*)&t1[i], sizeof(Item));
			}
			f1.close();
		}
		f1.close();
		//writing updated data of consumer doing shopping using QUEUE data structure
		LLQueue q1;
		ifstream f2;
		f2.open("Consumer.txt", ios::in | ios::binary);
		Consumer c2;
		while (f2.read((char*)&c2, sizeof(c2)))
		{
			if (c1 == c2)
			{
				q1.Enqueue(c1);
			}
			else
			{
				q1.Enqueue(c2);
			}
		}
		f2.close();

		ofstream f3;
		f3.open("Consumer.txt", ios::binary | ios::app);
		while (!q1.isEmpty())
		{
			Consumer temp = q1.Dequeue();
			f3.write((char*)&temp, sizeof(temp));

		}
		f3.close();
	}
	
	void PatternMatchBackSpace(Stack& undo, Stack& l1, Stack& l2)
	{
		if (l1.isEmpty())
		{
			while (!undo.isEmpty())
			{
				string id = undo.peek_id();
				l2.push(undo.pop(), id);
			}
		}
		else
		{
			while (!undo.isEmpty())
			{
				string id = undo.peek_id();
				l1.push(undo.pop(), id);
			}
		}
	}
	//function extracting items from sections to any of the lists
	//or from one list to another list also to undo stack(if not match)
	void PatternMatchingCharacter(Stack& undo, Stack& l1, Stack& l2, char* ch)
	{
		if (l1.isEmpty() && l2.isEmpty())
		{
			for (int i = 0; i < sections; i++)
			{
				section[i].GetMatch1(l1, undo,ch);
			}
			return;
		}
		else if (l1.isEmpty())
		{
			while (!l2.isEmpty())
			{
				string id = l2.peek_id();
				string name = l2.peek_name();
				if (HashMatch(name, ch))
					l1.push(name, id);
				else
					undo.push(name, id);
				l2.pop();
			}
		}
		else if (l2.isEmpty())
		{
			while (!l1.isEmpty())
			{
				string id = l1.peek_id();
				string name = l1.peek_name();
				if (HashMatch(name, ch))
					l2.push(name, id);
				else
					undo.push(name, id);
				l1.pop();
			}
		}
	}
	void PatternMatchingNewCharacter(Stack& undo, Stack& l, char* ch)
	{
		int flag = 0;
		while (!undo.isEmpty())
		{
			string name = undo.peek_name();
			string id = undo.peek_id();
			if (HashMatch(name, ch))
			{
				flag = 1;
				l.push(name, id);
			}
			undo.pop();
		}
		if (flag != 0)
		{
			return;
		}
		else
		{
			for (int i = 0; i < sections; i++)
			{
				section[i].GetMatch2(l, undo,ch);
			}

			return;
		}
	}

	void SEO()
	{
		cout << "This search algorithm continues Until you press enter" << endl;
		cout << "If you found your search item, press enter and then enter id of your item" << endl;
		Stack list1, list2;
		Stack* undo = new Stack[15];
		char ch[15]{ '\0' };
		int i = 0;
		int cnt_history = -1;
		bool cnt_backspace = 0;
		while ((ch[i] = _getch()) != 13 && i < 15)
		{
			system("cls");
			//if person presses backspace
			if (ch[i] == 8)
			{
				if (cnt_history < 0)
				{
					continue;
				}
				else
				{
					//this extract from undo to list "that is not empty"
					cnt_backspace = true;
					if (cnt_history > 0)
					{
						PatternMatchBackSpace(undo[cnt_history], list1, list2);
					}
					else
					{
						cnt_backspace = false;
						list1.clean();
						list2.clean();
					}
					ch[i] = '\0';
					cnt_history--;
				}
				i -= 2;
			}

			else
			{
				if (cnt_backspace == false)
				{
					PatternMatchingCharacter(undo[++cnt_history], list1, list2, ch);
				}
				else
				{
					if (list1.isEmpty())
					{
						PatternMatchingNewCharacter(undo[++cnt_history], list2, ch);
						PatternMatchingCharacter(undo[cnt_history], list1, list2, ch);
					}
					else
					{
						PatternMatchingNewCharacter(undo[++cnt_history], list1, ch);
						PatternMatchingCharacter(undo[cnt_history], list1, list2, ch);
					}

				}
			}
			//showing list
			if (list1.isEmpty())
			{
				list2.ShowList();
			}
			else
			{
				list1.ShowList();
			}
			//printing characters
			for (int j = 0; j <= i; j++)
			{
				cout << ch[j];
			}
			i++;
		}
	}
};
//HELPING FUNCTIONS
void signup(Store& st);
void signin(Store& st);
//main shopping function
void customer(Store& st) {

	while (1)
	{
		int opt = 0;
		cout << "1-SignIn()" << endl;
		cout << "2-SignUp()" << endl;
		cout << "3-Back()" << endl;
		cin >> opt;
		system("cls");
		switch (opt)
		{
		case 1:
			signin(st);
			break;
		case 2:

			signup(st);

			break;
		case 3:

			return;
		default:

			continue;
		}
	}
}
void signup(Store& st)
{
	string nam, pass, id = "CUS-0000";
	cout << "Enter name : ";
	cin >> nam;

	cout << "Enter paswword : ";
	cin >> pass;

	ifstream file1;
	Consumer s1;
	if (!file1.eof())
	{
		file1.open("Consumer.txt", ios::app | ios::binary);
		int size = sizeof(Consumer);
		file1.seekg(-size, ios::end);
		file1.read((char*)&s1, sizeof(s1));
		id = s1.getID();
		cout << id << endl;
	}
	file1.close();

	Consumer c1(id, nam, pass, 1000);
	c1.display();
	ofstream file2;
	file2.open("Consumer.txt", ios :: binary | ios::app);
	file2.write((char*)&c1, sizeof(Consumer));
	file2.close();
	st.Shopping(c1);
}
void signin(Store& st)
{
	string nam, id, pass;
	cout << "Enter ID : ";
	cin >> id;
	cout << "Enter paswword : ";
	cin >> pass;
	bool flag = 0;
	ifstream file1;
	file1.open("Consumer.txt", ios::binary | ios::app);
	Consumer s1;
	while (!file1.eof()) {
		file1.read((char*)&s1, sizeof(s1));
		if (s1.getID() == id && s1.getPass() == pass)
		{
			flag = 1;
			cout << "WELCOME TO GHG" << endl;
			st.Shopping(s1);
		}
	}
	file1.close();
	if (flag != 1)
	{
		cout << "Invalid ID or Password" << endl;
		cout << "Please sign up first if you not signedup "<<endl;
		customer(st);
	}
}
void admin(Store& st)
{
	char ch;
	string username;
A:
	cout << "Enter Username: ";
	cin >> username;
	if (username == "admin123") {
	B:
		string password;
		cout << "enter the password" << endl;
		ch = _getch();
		while (ch != 13) {
			password.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		if (password == "vohra123") {
			cout << endl << "Enter successfully" << endl;
			system("pause");
		}
		else {
			cout << endl << "Incorrect Password" << endl;
			cout << "pasword: " << password << endl;
			ch = NULL;
			goto B;
		}
	}
	else {
		cout << "Incorrect Username! " << endl;
		goto A;
	}
	int opt1;
	string idd;
	while (1)
	{
		cout << " what you want: " << endl;
		cout << "1-Add Stock" << endl;
		cout << "2-Show Data" << endl;
		cout << "3-Back" << endl;
		cin >> opt1;
		switch (opt1) {
		case 1:
			int opt2, q;
			st.ShowSectionList();
			cout << "enter the section no: " << endl;
			cin >> opt2;
			st.DisplaySectionProducts(opt2 - 1);
			cout << "enter the id of the item you want to update: " << endl;
			cin >> idd;
			cout << "enter the quantity you want to add: " << endl;
			cin >> q;
			st.update_stock(opt2 - 1, q, idd);
			break;
		case 2:
			int opt;
			st.ShowSectionList();
			cin >> opt;
			st.DisplaySectionProducts(opt - 1);
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
		system("pause");
	}

}
void welcomepage(Store& st) {
	system("cls");
	int opt;
	cout << "1-Admin" << endl;
	cout << "2-Consumer" << endl;
	cout << "3-Exit" << endl;
	cin >> opt;
	switch (opt)
	{
	case 1:
		admin(st);
		break;
	case 2:
		customer(st);
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
	welcomepage(st);
}


int main() {
	Store st;
	st.Open();
	//st.forfirstuse();
}