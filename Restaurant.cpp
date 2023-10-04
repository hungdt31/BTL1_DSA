#include "main.h"
extern int MAXSIZE;
class imp_res : public Restaurant
{
public:
	customer *head;
	customer *q; // hàng đợi
	customer *arrival;
	customer *x; // khách hàng ở vị trí x
	int cus_count;
	int q_count;
	imp_res()
	{
		arrival = nullptr;
		q = nullptr;
		head = nullptr;
		q_count = 0;
		cus_count = 0;
	};
	void printQueue()
	{
		if(!q) return;
		customer *cur = q;
		while (cur->next != nullptr)
		{
			cur = cur->next;
		}
		while(cur != nullptr){
			cout << cur->name << "(" << cur->energy << ") ";
			cur = cur->prev;
		}
	}
	void lightNext()
	{
		customer *current = x;
		if (!current)
		{
			return;
		}
		do
		{
			cout << current->name << "-" << current->energy <<"\n";
			current = current->next;
		} while (current != x);
	}
	void lightPrev(){
		customer *current = x;
		if (!current)
		{
			return;
		}
		do
		{
			cout << current->name << "-" << current->energy << "\n";
			current = current->prev;
		} while (current != x);
	}
	bool checkName(string name)
	{
		customer *cur = q;
		if (cur == nullptr)
			return 0;
		while (cur != nullptr)
		{
			if (cur->name == name)
				return 1;
			cur = cur->next;
		}
		customer *curr = head;
		if (curr == nullptr)
			return 0;
		do
		{
			if (curr->name == name)
				return 1;
			curr = curr->next;
		} while (curr != head);
		return 0;
	}
	void addArrival(customer *cus){
		customer *curr = arrival;
		if(!arrival){
			arrival = cus;
			curr = arrival;
		}
		else{
			while(curr->next != nullptr){
				curr = curr->next;
			}
			curr->next = cus;
			cus->prev = curr;
		}
	}
	void addFront(customer *temp, customer *cus)
	{
		customer *y = temp->prev;
		customer *k = temp;
		y->next = cus;
		cus->prev = y;
		cus->next = k;
		k->prev = cus;
		x = cus;
		cus_count++;
	}
	void addBack(customer *temp, customer *cus)
	{
		customer *y = temp->next;
		customer *k = temp;
		k->next = cus;
		cus->prev = k;
		cus->next = y;
		y->prev = cus;
		x = cus;
		cus_count++;
	}
	void pushQueue(customer *cus)
	{
		if (q_count + 1 > MAXSIZE)
			return;
		if (q == nullptr)
		{
			q = cus;
		}
		else
		{
			cus->next = q;
			q->prev = cus;
			q = cus;
		}
		q_count++;
	}
	// void deleteAll(){
	// 	customer *temp = head;
	// 	do{
	// 		if(temp != head) {
	// 			customer *deletedCus = temp;
	// 			delete deletedCus;
	// 		}
	// 		temp = temp->next;
	// 	}while(temp != head);
	// 	delete temp;
	// }
	int findRed(customer *cus)
	{
		customer *current = head;
		int res;
		if (!current)
		{
			return 0;
		}
		do
		{
			int k;
			if (current == head)
				res = abs(cus->energy - current->energy);
			else
			{
				k = abs(cus->energy - current->energy);
				if (k > res)
					res = k;
			}
			current = current->next;
		} while (current != head);
		return res;
	}
	void addRed(customer *cus)
	{
		customer *current2 = head;
		customer *temp = nullptr;
		int res = findRed(cus);
		do
		{
			if (abs(cus->energy - current2->energy) == res)
			{
				temp = current2;
				break;
			}
			current2 = current2->next;
		} while (current2 != head);
		if (cus->energy - temp->energy < 0)
		{
			addFront(temp, cus);
		}
		else
		{
			addBack(temp, cus);
		}
	}
	void RED(string name, int energy)
	{
		customer *cus = new customer(name, energy, nullptr, nullptr);
		if (checkName(cus->name))
			return;
		if (cus_count < MAXSIZE / 2)
		{
			if (!head)
			{
				head = cus;
				head->next = head;
				head->prev = head;
				x = head;
				cus_count++;
			}
			else
			{
				if (x->energy <= cus->energy)
				{
					addBack(x, cus);
				}
				else
				{
					addFront(x, cus);
				}
			}
			addArrival(cus);
		}
		else if (cus_count >= MAXSIZE / 2 && cus_count < MAXSIZE)
		{
			addRed(cus);
			addArrival(cus);
		}
		else
		{
			pushQueue(cus);
		}
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		if(num > 0){
			lightNext();
		}
		else if(num < 0){
			lightPrev();
		}
		else printQueue();
	}
};