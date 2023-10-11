#include "main.h"

class imp_res : public Restaurant
{
	class customerTime;
private:
	customer * customerQueue;
	customer * customerX; 

	int sizeCustomerInDesk; 
	int sizeCustomerQueue; 

	customerTime * CustomerTimeHead; 
	customerTime * CustomerTimeTail; 

private:

	//! Tìm khách hàng đến lâu nhất ngồi lì nên đuổi nó về
	customerTime* findCustomerDelete()
	{
		//TODO CODE YOU
	}

	//! xóa khách hàng customerTimeDelete
	void delteCustomerTime(customerTime* customerTimeDelete)
	{
		//TODO CODE YOU
	}

	//! đưa khách hàng từ hàng chờ vào bàn ăn
	void insertCustomerQueueToInDisk()
	{
		//TODO CODE YOU
	}

	//! print ra khách hàng đến gần nhất đến lâu nhất trong bàn
	void print_reverse(customerTime* head)
	{
		//TODO CODE YOU
	}

	//! swap thôi
	void swap(customer* head, customer * tail)
	{
		//TODO code your
	}	
	customer* getCustomerAt(customer* x, int index)
	{
		for(int i = 0; i < index; i++) x = x->next;
		return x;
	}

	//* Insertion sort với A[0], A[incr], A[incr*2], ...
	int inssort2(customer* head, int n, int incr) {
		int COUNT = 0; //! sô lượng swap
		for(int i = incr; i < n; i += incr)
		{
			for(int j = i; j >= incr; j -= incr)
			{
				//* lấy phần tử so sánh
				customer* a = this->getCustomerAt(head, j);
				customer* b = this->getCustomerAt(head, j - incr);

				//TODO tìm điệu kiện dừng
				if() break;

				swap(a, b);
				COUNT++;

				//TODO xét trường hợp b = customerQueue or head thì án lại bằng a
			}
		}
		return COUNT;
	}

	void PURPLE()
	{
		int removeBLUE = 0;

		//* bước 1 tìm vị trí của max abs(energy)
		int n = 0; //! kích thước danh sách cần sort
		customer* temp = customerQueue;
		customer* max = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++)
		{
			if(abs(temp->energy) >= abs(max->energy))
			{
				//* cập nhật max và n 
				max = temp;
				n = i + 1;
			}
			temp = temp->next;
		}

		//* bước 2 sort
		for(int i = n / 2; i > 2; i /= 2)
		{
			//* phần tử bắt đầu của sort từ 0 -> i 	
			for(int j = 0; j < i; j++)
			{
				//* tiến hành sort với index bắt đầu customerQueue[j]
				//* mỗi bước nhảy là i -> nghĩa là so sánh Q[j], Q[j+i], ...
				//* n - j là kích thước của mảng hiện tại
				removeBLUE += inssort2(this->getCustomerAt(customerQueue, j), n - j, i);
			}
		}
		removeBLUE += inssort2(customerQueue, n, 1);

		//* BƯỚC 3 XÓA
		this->BLUE(removeBLUE % MAXSIZE);
	}



public:	
	imp_res() {
		customerX = customerQueue =  nullptr;
		sizeCustomerQueue = sizeCustomerInDesk = 0;
		CustomerTimeHead = CustomerTimeTail = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	

	~imp_res(){  
		//TODO CODE YOU
	}
private:
	class customerTime{
	public:
		customer * data;
		customerTime* next;
		//^ Chỉnh
		customerTime* prev;
		bool inDisk; //! xem thử khách hàng có trong bàn hay không
	public:
		customerTime(customer * data, bool inDisk, customerTime* next = nullptr, customerTime* prev = nullptr)
		:data(data),next(next),prev(prev), inDisk(inDisk) {}
		~customerTime(){delete data;}
	};
};

void imp_res::RED(string name, int energy)
{
	//TODO CODE YOU
	return;
}

void imp_res::BLUE(int num)
{
	//TODO CODE YOU
}



void imp_res::DOMAIN_EXPANSION()
{
	//TODO CODE YOU
}

void imp_res::REVERSAL()
{
	//TODO CODE YOU	
}

void imp_res::UNLIMITED_VOID()
{
	//TODO CODE YOU
}

void imp_res::LIGHT(int num)
{
	//TODO CODE YOU
}



