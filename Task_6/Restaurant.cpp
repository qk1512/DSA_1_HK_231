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
		customerTime* customerTimeDelete = CustomerTimeHead;
		//* Bước 1 Tìm khách hàng đang ở trong bàn đầu tiên (sử dụng inDisk)
		//* A(isdisk = false) -> B(isdisk = true) -> C(isdisk = false), thì tìm B rồi break
		for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
		{
			//TODO: tìm điều kiện break;
			customerTimeDelete = customerTimeDelete->next;
		}

		//* Bước 2 Xóa khỏi danh sách hàng customerTime
		//* TH khách danh sách customerTime chỉ có 1 khách hàng nên xóa hết khách rồi
		if(sizeCustomerQueue + sizeCustomerInDesk == 1)
		{
			//TODO: cập nhật CustomerTimeHead, CustomerTimeTail gán về nullptr xóa danh sách liên kết đôi
		}
		//* TH khách danh sách customerTime đang xóa khách hàng là khách đầu tiên
		else if(customerTimeDelete == CustomerTimeHead)
		{
			//TODO: cập nhật CustomerTimeHead và prev của node trước đó xóa danh sách liên kết đôi
		}
		//* TH khách danh sách customerTime đang xóa là khách hàng cuối cùng
		else if(customerTimeDelete == CustomerTimeTail)
		{
			//TODO: cập nhật CustomerTimeTail và next của node sau đó xóa danh sách liên kết đôi
		}
		//* TH khách danh sách customerTime đang xóa là khách hàng giữa
		else
		{
			//TODO: cập nhật node trước và sau của node cần xóa danh sách liên kết đôi
		}

		return customerTimeDelete;	
	}

	//! xóa khách hàng customerTimeDelete
	void delteCustomerTime(customerTime* customerTimeDelete)
	{
		//* khách trong bàn
		if(customerTimeDelete->inDisk == true)
		{
			//* Bước 1 đuổi khách hàng trong bàn ăn khi chỉ có 1 khách hàng
			if(sizeCustomerInDesk == 1)
			{
				sizeCustomerInDesk = 0;
				customerX = nullptr;
			}
			//* bước 2 đuổi khách hàng với số khách lớn hơn 2 này giống task2
			else
			{
				customer* customerDelete = customerTimeDelete->data;
				//TODO cập nhật tại khách hàng phía trước và khách hàng phía sau


				//* cập nhật lại khách hàng x thầy mô tả trong thread khi đang xóa khách hàng trong bàn
				if(customerDelete->energy > 0)
				{
					//TODO code you
				}
				else
				{
					//TODO code you
				}
				sizeCustomerInDesk--; //! cập nhật size trong bàn
			}
		}
		//* khách trong hàng chờ
		else
		{
			//* Bước 1 đuổi khách hàng trong hàng chờ khi chỉ có 1 khách hàng
			if(sizeCustomerQueue == 1)
			{
				sizeCustomerQueue = 0;
				customerQueue = nullptr;
			}
			//* bước 2 đuổi khách hàng trong hàng chờ
			else
			{
				customer* customerDelete = customerTimeDelete->data;

				//TODO cập nhật tại khách hàng phía trước và khách hàng phía sau


				//* cập nhật lại khách hàng đầu tiên khi khách hàng đầu tiên trong hàng chờ bị xóa
				if(customerDelete == customerQueue) customerQueue = customerQueue->next;
				sizeCustomerQueue--; //! cập nhật size trong bàn
			}
		}

		delete customerTimeDelete; //! né thằng này ra :< chỉnh nó là mệt chuyện
	}

	//! đưa khách hàng từ hàng chờ vào bàn ăn
	void insertCustomerQueueToInDisk()
	{
		
		while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
		{
			//* bước 1 đưa khách hàng đầu ra khỏi hàng chờ
			customer* newCustomer = customerQueue;

			//* bước 1.1 tìm khách hàng trong danh sách CustomerTime và cập nhật inDisk trừ false sang true nghĩa là từ hàng chờ sang bàn
			customerTime* temp = CustomerTimeHead; //! vị trí của khách hàng trong Time
			for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
			{
				//TODO: cập nhật inDisk, bằng cách so sánh data với customerQueue

				temp = temp->next;
			}
			//* Bước 1.2 xóa khách hàng trong hàng chờ 
			if(sizeCustomerQueue == 1) customerQueue = nullptr;
			else
			{
				//TODO xóa khách hàng trong hàng chờ là khách hàng đầu tiên trong customerQueue
				//TODO: cập nhật customerQueue, prev node trước ủa customerQueue và next node sau customerQueue
				
			}
			sizeCustomerQueue --;

			//* bước 2 thêm khách hàng vào bàn ăn, cập nhật size này code của bài 1 thôi
			if(sizeCustomerInDesk == 0)
			{
				customerX = newCustomer;
				newCustomer->next = newCustomer->prev = newCustomer;
			}
			else 
			{
				//* xét thử khách hàng tìm X
				if(sizeCustomerInDesk >= MAXSIZE / 2)
				{
					//TODO CODE YOU task 1 bước 6
				}
				//* thêm khách hàng mới vào phía trước khác hàng X
				if(newCustomer->energy >= customerX->energy)
				{
					//TODO CODE YOU task 1 bước 7
				}
				//*thêm khách hàng mới vào phía sau khác hàng X
				else
				{
					//TODO CODE YOU task 1 bước 7
				}
			}
			customerX = newCustomer;
			sizeCustomerInDesk ++;	
		}	
	}

	//! print ra khách hàng đến gần nhất đến lâu nhất trong bàn
	void print_reverse(customerTime* head)
	{
		if(head != nullptr){
			print_reverse(head->next);
			head->data->print();
		}
	}

	//! swap thôi
	void swap(customer* head, customer * tail)
	{
		//TODO code your
	}	


public:	
	imp_res() {
		customerX = customerQueue =  nullptr;
		sizeCustomerQueue = sizeCustomerInDesk = 0;
		CustomerTimeHead = CustomerTimeTail = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void PURPLE();
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	

	~imp_res(){  
		while(CustomerTimeHead)
		{
			customerTime* temp = CustomerTimeHead;	 
			CustomerTimeHead = CustomerTimeHead->next;
			delete temp;
		}
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
	//* Bước 1 đuổi về không phải Thuật sư hay oán linh
	if(energy == 0) return;
	//* Bước 2  hàng chờ đã đầy đuổi về
	else if(sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
	//* Bước 3 "thiên thượng thiên hạ, duy ngã độc tôn" : chung tên đuổi về
	else
	{
		//TODO : code you
	}

	//* Bước 4 đưa vào hàng chờ 
	//^ Chỉnh biến danh sách vòng thành vòng đôi như trong bàn
	if(sizeCustomerInDesk == MAXSIZE)
	{
		//^ Chỉnh chèn đầu danh sách liên kết đôi vòng khi không có phần tử nào
		customer* newCustomer = new customer(name, energy, nullptr, nullptr);
		if(sizeCustomerQueue == 0)
		{
			//TODO: gán node thành danh sách liên kết đôi vong Queue
		}
		//^ Chỉnh chèn cuối danh sách liên kết đôi vòng vị trí hiện tại CustomerQueue là đầu danh sách
		else
		{
			//TODO: này là danh sách vòng đôi tail = Queue->prev, thêm cuối cập nhật  Queue->prev, tail->next, giống cái chèn sau của bước 7
		}
		sizeCustomerQueue ++;


		//^ Chỉnh biến quản lý thời gian khách hàng nào đến trước thêm vào cuối
		//^ vì đang trong bàn ăn nên inDisk = false
		//^ này code của anh khuyến khích bạn code khách đi nha
		customerTime* newCustomerTime = new customerTime (newCustomer, false);
		CustomerTimeTail->next = newCustomerTime;
		newCustomerTime->prev = CustomerTimeTail;
		CustomerTimeTail = CustomerTimeTail->next;
		return;
	}
	
	//* Bước 5 khách hàng đầu tiên vào nhà hàng này là danh sách liên kết đôi vòng
	//* giá trị next = prev = chính nó và cập nhật sizeCustomerInDesk
	else if(sizeCustomerInDesk == 0)
	{
		//TODO : code you

		//^ chỉnh biến quản lý thời gian khách hàng nào đến trước
		//^ vì đang trong bàn ăn nên inDisk = true
		CustomerTimeTail = CustomerTimeHead = new customerTime (customerX, true);
		return;
	}


	//* Bước 6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2.0 ta phải tìm vị trí mới của customerX
	//* tìm vị trí mới đễ dễ dàng insert customer mới
	if(sizeCustomerInDesk >= MAXSIZE / 2)
	{
		//TODO : code you
	}

	customer* newCustomer = new customer (name, energy, nullptr, nullptr); //! khách hàng mới
	//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
	if(energy >= customerX->energy)
	{
		//TODO : code you
	}
	//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
	else
	{
		//TODO : code you
	}

	customerX = newCustomer;
	sizeCustomerInDesk ++;

	//^ Chỉnh biến quản lý thời gian khách hàng nào đến trước thêm vào cuối
	//^ vì đang trong bàn ăn nên inDisk = true
	//^ này code của anh khuyến khích bạn code khách đi nha
	customerTime* newCustomerTime = new customerTime (newCustomer, true);
	CustomerTimeTail->next = newCustomerTime;
	newCustomerTime->prev = CustomerTimeTail;
	CustomerTimeTail = CustomerTimeTail->next;
	return;
}

void imp_res::BLUE(int num)
{
	//* Không có khách lấy gì xóa :<
	if(sizeCustomerInDesk == 0) return;

	//* Bước 1 số lượng khách hàng bị đuổi
	for(int i = 0; i < num && sizeCustomerInDesk != 0; i++)
	{
		//* Bước 1.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
		customerTime* customerTimeDelete = this->findCustomerDelete();

		//* Bước 1.2 đuổi khách 
		this->delteCustomerTime(customerTimeDelete);
	}

	//* Bước 2 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
	this->insertCustomerQueueToInDisk();
}

void imp_res::PURPLE()
{
	
}

void imp_res::DOMAIN_EXPANSION()
{
	//* Không có khách để đuổi
		if(sizeCustomerInDesk == 0) return;

	//* Bước 1 tính tổng của thuật sư và oán linh
		int total_Wizard = 0; //! Tổng thuật sư
		int total_Spirit = 0; //! Tổng oán linh
		//TODO : Code you

	//* Bước 2 đuổi khách xem thử đuổi bên nào và print ra luôn đuổi trong hàng bàng
		customerTime* WizardTail = nullptr; //! Thuật sư lưu danh sách các thuật sư
		customerTime* SpiritTail = nullptr; //! oán linh lưu danh sách các oán linh
		customerTime* WizardHead = nullptr; //! node đầu của thuật sư
		customerTime* SpiritHead = nullptr; //! node đầu của oán linh
		//* Bước 2.1 tách làm 2 danh sách oán linh và thuật sư
		customerTime* tempTime = CustomerTimeHead;
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++)
		{
			//TODO thuật sư
			if(tempTime->data->energy > 0)
			{
				
				if(WizardHead == nullptr)
				{
					//TODO cập nhật danh sách liên kết đôi ban đầu chưa có phần tử nào
				}
				else
				{
					//TODO cập nhật danh sách liên kết đôi Wizard tail thêm node của cuối danh sách đôi thôi
				}
			}
			//TODO oán linh
			else
			{
				if(SpiritHead == nullptr)
				{
					//TODO cập nhật danh sách liên kết đôi ban đầu chưa có phần tử nào
				}
				else
				{
					//TODO cập nhật danh sách liên kết đôi Wizard tail thêm node của cuối danh sách đôi thôi
				}
			}

			tempTime = tempTime->next;
		}


		//! cập nhật TimeHead, TimeTail
		if(SpiritHead != nullptr) SpiritHead->prev = SpiritTail->next = nullptr;
		if(WizardHead != nullptr) WizardHead->prev = WizardTail->next = nullptr;
		
		//* Bước 2.2 xóa danh sách oán linh trong bàn ăn 
		if(abs(total_Spirit) <= total_Wizard)
		{
			print_reverse(SpiritHead);
			while(SpiritHead != nullptr)
			{
				customerTime* customerTimeDelete;
				//TODO xác định khách chuẩn bị đuổi SpiritHead, cập nhật WizardHead
				

				//* Bước 1.2 đuổi khách 
				this->delteCustomerTime(customerTimeDelete);
			}

			//* cập nhật CustomerTimeHead và CustomerTimeTail
			CustomerTimeHead = WizardHead;
			CustomerTimeTail = WizardTail;
		}
		//* Bước 2.2 xóa danh sách Thuật sư  trong bàn ăn 
		else{
			print_reverse(WizardHead);
			while(WizardHead != nullptr)
			{
				customerTime* customerTimeDelete;
				//TODO xác định khách chuẩn bị đuổi WizardHead, cập nhật WizardHead

				//* Bước 1.2 đuổi khách 
				this->delteCustomerTime(customerTimeDelete);
			}

			//* cập nhật CustomerTimeHead và CustomerTimeTail
			CustomerTimeHead = SpiritHead;
			CustomerTimeTail = SpiritTail;
		}

	//* Bước 3 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
		this->insertCustomerQueueToInDisk();
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



