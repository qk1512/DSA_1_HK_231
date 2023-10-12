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
		customerTime* customerTimeDelete = CustomerTimeHead;
		//* Bước 1 Tìm khách hàng đang ở trong bàn đầu tiên (sử dụng inDisk)
		//* A(isdisk = false) -> B(isdisk = true) -> C(isdisk = false), thì tìm B rồi break
		for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
		{
			//TODO: tìm điều kiện break;
			if(customerTimeDelete -> inDisk == true) break;
			customerTimeDelete = customerTimeDelete->next;
		}

		//* Bước 2 Xóa khỏi danh sách hàng customerTime
		//* TH khách danh sách customerTime chỉ có 1 khách hàng nên xóa hết khách rồi
		if(sizeCustomerQueue + sizeCustomerInDesk == 1)
		{
			//TODO: cập nhật CustomerTimeHead, CustomerTimeTail gán về nullptr xóa danh sách liên kết đôi
			CustomerTimeHead = CustomerTimeTail = nullptr;
		}
		//* TH khách danh sách customerTime đang xóa khách hàng là khách đầu tiên
		else if(customerTimeDelete == CustomerTimeHead)
		{
			//TODO: cập nhật CustomerTimeHead và prev của node trước đó xóa danh sách liên kết đôi
			customerTimeDelete -> next -> prev = nullptr;
			CustomerTimeHead = CustomerTimeHead -> next;
		}
		//* TH khách danh sách customerTime đang xóa là khách hàng cuối cùng
		else if(customerTimeDelete == CustomerTimeTail)
		{
			//TODO: cập nhật CustomerTimeTail và next của node sau đó xóa danh sách liên kết đôi
			customerTimeDelete -> prev -> next = nullptr;
			CustomerTimeTail = CustomerTimeTail -> prev;
		}
		//* TH khách danh sách customerTime đang xóa là khách hàng giữa
		else
		{
			//TODO: cập nhật node trước và sau của node cần xóa danh sách liên kết đôi
			customerTimeDelete -> next -> prev = customerTimeDelete -> prev;
			customerTimeDelete -> prev -> next = customerTimeDelete -> next;
		}

		return customerTimeDelete;	
	}

	//! xóa khách hàng customerTimeDelete
	void deleteCustomerTime(customerTime* customerTimeDelete)
	{
		//TODO CODE YOU
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
				customerDelete -> next -> prev = customerDelete -> prev;
				customerDelete -> prev -> next = customerDelete -> next;

				//* cập nhật lại khách hàng x thầy mô tả trong thread khi đang xóa khách hàng trong bàn
				if(customerDelete->energy > 0)
				{
					//TODO code you
					customerX = customerDelete -> next;
				}
				else
				{
					//TODO code you
					customerX = customerDelete -> prev;
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
				customerDelete -> next -> prev = customerDelete -> prev;
				customerDelete -> prev -> next = customerDelete -> next;

				//* cập nhật lại khách hàng đầu tiên khi khách hàng đầu tiên trong hàng chờ bị xóa
				if(customerDelete == customerQueue) customerQueue = customerQueue->next;
				sizeCustomerQueue--; //! cập nhật size trong bàn
			}
		}

		delete customerTimeDelete; //! né thằng này ra :< chỉnh nó là mệt chuyện
		COUNTDELETE++;
	}

	//! đưa khách hàng từ hàng chờ vào bàn ăn
	void insertCustomerQueueToInDisk()
	{
		//TODO CODE YOU
		while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
		{
			//* bước 1 đưa khách hàng đầu ra khỏi hàng chờ
			customer* newCustomer = customerQueue;

			//* bước 1.1 tìm khách hàng trong danh sách CustomerTime và cập nhật inDisk trừ false sang true nghĩa là từ hàng chờ sang bàn
			customerTime* temp = CustomerTimeHead; //! vị trí của khách hàng trong Time
			for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
			{
				//TODO: cập nhật inDisk, bằng cách so sánh data với customerQueue
				if(temp -> data == newCustomer) temp -> inDisk = true; 
				temp = temp->next;
			}
			//* Bước 1.2 xóa khách hàng trong hàng chờ 
			if(sizeCustomerQueue == 1) customerQueue = nullptr;
			else
			{
				//TODO xóa khách hàng trong hàng chờ là khách hàng đầu tiên trong customerQueue
				newCustomer -> next -> prev = newCustomer -> prev;
				newCustomer -> prev -> next = newCustomer -> next;
				//TODO: cập nhật customerQueue, prev node trước ủa customerQueue và next node sau customerQueue
				customerQueue -> next -> prev = customerQueue -> prev;
				customerQueue -> prev -> next = customerQueue -> next;
				customerQueue = customerQueue -> next;

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
					customer* temp;
					temp = customerX;
					int max = 0;
					for(int i = 0; i < sizeCustomerInDesk; i++){
						int RES = abs(newCustomer -> energy - temp -> energy);
						if(max < RES){
							max = RES;
							customerX = temp;
						}
						temp = temp -> next;
					}
				}
				//* thêm khách hàng mới vào phía trước khác hàng X
				if(newCustomer -> energy >= customerX -> energy)
				{
					//TODO CODE YOU task 1 bước 7
					newCustomer -> prev = customerX;
					newCustomer -> next = customerX -> next;
					customerX -> next -> prev = newCustomer;
					customerX -> next = newCustomer;
				}
				//*thêm khách hàng mới vào phía sau khác hàng X
				else
				{
					//TODO CODE YOU task 1 bước 7
					newCustomer -> next = customerX;
					newCustomer -> prev = customerX -> prev;
					customerX -> prev -> next = newCustomer;
					customerX -> prev = newCustomer;
				}
			}
			customerX = newCustomer;
			sizeCustomerInDesk ++;	
		}
		return;
	}

	//! print ra khách hàng đến gần nhất đến lâu nhất trong bàn
	void print_reverse(customerTime* head)
	{
		//TODO CODE YOU
		if(head != nullptr){
			print_reverse(head -> next);
			head -> data -> print();
		}
	}

	//! swap thôi
	void swap(customer* head, customer * tail)
	{
		//TODO code your
		customer* temp = new customer();

		head -> next -> prev = temp;
		head -> prev -> next = temp;
		temp -> next = head -> next;
		temp -> prev = head -> prev;
		head -> next = head -> prev = nullptr;

		//TODO : đổi head với tail
		head -> next = tail -> next;
		head -> prev = tail -> prev;
		tail -> next -> prev = head;
		tail -> prev -> next = head;
		tail -> next = tail -> prev = nullptr;

		//TODO : đổi tail với temp
		tail -> next = temp -> next;
		tail -> prev = temp -> prev;
		temp -> next -> prev = tail;
		temp -> prev -> next = tail;
		temp -> next = temp -> prev = nullptr;

		delete temp;
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
				if(abs(a -> energy) <= abs(b -> energy)) break;

				swap(a, b);
				COUNT++;

				//TODO xét trường hợp b = customerQueue or head thì án lại bằng a
				if (b == customerQueue && b == head){
					customerQueue = a;
					head = a;
				}
				
			}
		}
		return COUNT;
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
	void PURPLE();

	~imp_res(){  
		//TODO CODE YOU
		while(CustomerTimeHead)
		{
			customerTime* temp = CustomerTimeHead;	 
			CustomerTimeHead = CustomerTimeHead->next;
			delete temp;
			COUNTDELETE++;
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
		~customerTime(){delete data; COUNTDELETE++;}
	};
};

void imp_res::RED(string name, int energy)
{
	//TODO CODE YOU
	//* Bước 1 đuổi về không phải Thuật sư hay oán linh
	if(energy == 0) return;
	//* Bước 2  hàng chờ đã đầy đuổi về
	else if(sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
	//* Bước 3 "thiên thượng thiên hạ, duy ngã độc tôn" : chung tên đuổi về
	else
	{
		//TODO : code you
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++){
			if(temp -> name == name) return;
			temp = temp -> next;
		}
		temp = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++){
			if(temp -> name == name) return;
			temp = temp -> next;
		}
		
	}

	//* Bước 4 đưa vào hàng chờ 
	//^ Chỉnh biến danh sách vòng thành vòng đôi như trong bàn
	if(sizeCustomerInDesk == MAXSIZE)
	{
		//^ Chỉnh chèn đầu danh sách liên kết đôi vòng khi không có phần tử nào
		customer* newCustomer = new customer(name, energy, nullptr, nullptr);
		COUNTDELETE--;
		if(sizeCustomerQueue == 0)
		{
			//TODO: gán node thành danh sách liên kết đôi vong Queue
			customerQueue = newCustomer;
			customerQueue -> next = customerQueue -> prev = customerQueue;
		}
		//^ Chỉnh chèn cuối danh sách liên kết đôi vòng vị trí hiện tại CustomerQueue là đầu danh sách
		else
		{
			//TODO: này là danh sách vòng đôi tail = Queue->prev, thêm cuối cập nhật  Queue->prev, tail->next, giống cái chèn sau của bước 7
			customer* tail = customerQueue -> prev;
			newCustomer -> prev = tail;
			newCustomer -> next = tail -> next;
			tail -> next -> prev = newCustomer;
			tail -> next = newCustomer;

		}
		sizeCustomerQueue ++;


		//^ Chỉnh biến quản lý thời gian khách hàng nào đến trước thêm vào cuối
		//^ vì đang trong bàn ăn nên inDisk = false
		//^ này code của anh khuyến khích bạn code khách đi nha
		customerTime* newCustomerTime = new customerTime (newCustomer, false);
		COUNTDELETE--;
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
		customer * newCustomer = new customer(name,energy,nullptr,nullptr);
		COUNTDELETE--;
		customerX = newCustomer;
		customerX -> next = customerX;
		customerX -> prev = customerX;
		sizeCustomerInDesk++;
		//^ chỉnh biến quản lý thời gian khách hàng nào đến trước
		//^ vì đang trong bàn ăn nên inDisk = true
		CustomerTimeTail = CustomerTimeHead = new customerTime (customerX, true);
		COUNTDELETE--;
		return;
	}


	//* Bước 6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2.0 ta phải tìm vị trí mới của customerX
	//* tìm vị trí mới đễ dễ dàng insert customer mới
	if(sizeCustomerInDesk >= MAXSIZE / 2)
	{
		//TODO : code you
		customer* temp; 
		temp = customerX;
		int max = 0;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			int RES = abs(energy - temp -> energy);
			if(max < RES){
			max = RES;
			customerX = temp;
			}
			temp = temp -> next;
		}
	}

	customer* newCustomer = new customer (name, energy, nullptr, nullptr); //! khách hàng mới
	COUNTDELETE--;
	//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
	if(energy >= customerX->energy)
	{
		//TODO : code you
		newCustomer -> prev = customerX;
		newCustomer -> next = customerX -> next;
		customerX -> next -> prev = newCustomer;
		customerX -> next = newCustomer;
	}
	//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
	else
	{
		//TODO : code you
		newCustomer -> next = customerX;
		newCustomer -> prev = customerX -> prev;
		customerX -> prev -> next = newCustomer;
		customerX -> prev = newCustomer;
	}

	customerX = newCustomer;
	sizeCustomerInDesk ++;

	//^ Chỉnh biến quản lý thời gian khách hàng nào đến trước thêm vào cuối
	//^ vì đang trong bàn ăn nên inDisk = true
	//^ này code của anh khuyến khích bạn code khách đi nha
	customerTime* newCustomerTime = new customerTime (newCustomer, true);
	COUNTDELETE--;
	CustomerTimeTail->next = newCustomerTime;
	newCustomerTime->prev = CustomerTimeTail;
	CustomerTimeTail = CustomerTimeTail->next;
	return;
}

void imp_res::BLUE(int num)
{
	//TODO CODE YOU
	//* Không có khách lấy gì xóa :<
	if(sizeCustomerInDesk == 0) return;

	//* Bước 1 số lượng khách hàng bị đuổi
	for(int i = 0; i < num && sizeCustomerInDesk != 0; i++)
	{
		//* Bước 1.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
		customerTime* customerTimeDelete = this->findCustomerDelete();

		//* Bước 1.2 đuổi khách 
		this->deleteCustomerTime(customerTimeDelete);
	}

	//* Bước 2 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
	this->insertCustomerQueueToInDisk();
	return;
}

void imp_res::PURPLE()
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


void imp_res::DOMAIN_EXPANSION()
{
	//* Không có khách để đuổi
		if(sizeCustomerInDesk == 0) return;

	//* Bước 1 tính tổng của thuật sư và oán linh
		int total_Wizard = 0; //! Tổng thuật sư
		int total_Spirit = 0; //! Tổng oán linh
		//TODO : Code you
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++){
			if(temp -> energy > 0) total_Wizard += temp -> energy;
			else total_Spirit += temp -> energy;
			temp = temp -> next;
		}

		temp = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++){
			if(temp -> energy > 0) total_Wizard += temp -> energy;
			else total_Spirit += temp -> energy;
			temp = temp -> next;
		}

	//* Bước 2 đuổi khách xem thử đuổi bên nào và print ra luôn đuổi trong hàng bàng
		customerTime* WizardTail = nullptr; //! Thuật sư lưu danh sách các thuật sư
		customerTime* SpiritTail = nullptr; //! oán linh lưu danh sách các oán linh
		customerTime* WizardHead = nullptr; //! node đầu của thuật sư
		customerTime* SpiritHead = nullptr; //! node đầu của oán linh
		//* Bước 2.1 tách làm 2 danh sách oán linh và thuật sư
		customerTime* tempTime = CustomerTimeHead;		
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue;i++)
		{
			//TODO thuật sư
			if(tempTime->data->energy > 0)
			{
				if(WizardHead == nullptr)
				{
					//TODO cập nhật danh sách liên kết đôi ban đầu chưa có phần tử nào
					WizardHead = WizardTail = tempTime;	
				}
				else
				{
					//TODO cập nhật danh sách liên kết đôi Wizard tail thêm node của cuối danh sách đôi thôi	
					WizardTail -> next = tempTime;
					WizardTail -> next -> prev = WizardTail;
					WizardTail = tempTime;					
				}
			}
			//TODO oán linh
			else 
			{
				if(SpiritHead == nullptr)
				{
					//TODO cập nhật danh sách liên kết đôi ban đầu chưa có phần tử nào
					SpiritHead = SpiritTail = tempTime;
				}
				else
				{
					//TODO cập nhật danh sách liên kết đôi Wizard tail thêm node của cuối danh sách đôi thôi
					SpiritTail -> next = tempTime;
					SpiritTail -> next -> prev = SpiritTail;
					SpiritTail = tempTime;	
				}
			}
			
			tempTime = tempTime->next;
		}
		

		//! cập nhật TimeHead, TimeTail
		if(SpiritHead != nullptr && SpiritTail != nullptr) {
			SpiritHead -> prev = nullptr;
			SpiritTail -> next = nullptr;
		}
		if(WizardHead != nullptr && WizardTail != nullptr) {
			WizardHead -> prev = nullptr;
			WizardTail -> next = nullptr;
		}
		

		//* Bước 2.2 xóa danh sách oán linh trong bàn ăn 
		if(abs(total_Spirit) <= total_Wizard)
		{
			print_reverse(SpiritHead);
			while(SpiritTail != nullptr)
			{
				customerTime* customerTimeDelete;
				//TODO xác định khách chuẩn bị đuổi SpiritHead, cập nhật WizardHead
				customerTimeDelete = SpiritTail;
				SpiritTail = SpiritTail -> prev;
				
				//* Bước 1.2 đuổi khách 
				this->deleteCustomerTime(customerTimeDelete);
			}

			//* cập nhật CustomerTimeHead và CustomerTimeTail
			CustomerTimeHead = WizardHead;
			CustomerTimeTail = WizardTail;
			
		}
		//* Bước 2.2 xóa danh sách Thuật sư  trong bàn ăn 
		else{
			print_reverse(WizardHead);
			while(WizardTail != nullptr)
			{
				customerTime* customerTimeDelete;
				//TODO xác định khách chuẩn bị đuổi WizardHead, cập nhật WizardHead
				customerTimeDelete = WizardTail;
				WizardTail = WizardTail -> prev;
				//* Bước 1.2 đuổi khách 
				this->deleteCustomerTime(customerTimeDelete);
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
	//* Không có khách mà đảo gì, 1 khách sao đảo :<
	if(sizeCustomerInDesk <= 1) return;			

	//^ hàm blue, DOMAIN_EXPANSION thiết kê thêm class làm khá dễ nhưng phần này nhược điểm :<

	customer* head = nullptr; 
	customer* tail = nullptr;

	//* Đảo oán linh trước đi 

	//* Bước 1 tìm head và tail
	//* : tìm head bằng cách duyệt theo ngược chiều kim đồng hồ từ khách hàng X tìm oán linh
	head = customerX;
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		//Todo: tìm head
		if(head -> energy < 0) break;
		head = head -> prev;
	}

	//* : tìm tail bằng cách duyệt theo chiều kim đồng hồ từ khách hàng trước X tìm oán linh
	tail = customerX->next; //! NHƯNG PHẢI KHÁC khách hàng x duyệt lần đầu
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		//Todo: tìm tail
		if(tail -> energy < 0) break;
		tail = tail -> next;
	}
			
	//! chỉ có 2 khách hàng là oán linh trở lên mới đảo
	if(head->energy < 0 && head != tail){

	//* Bước 2 hoán đổi không thể nào hoán đổi name được vì CustomerTime đang giữ con trỏ
	//* nên phải hoán đổi luôn địa chỉ bằng hàm swap
	for(int i = 0; i < sizeCustomerInDesk / 2; i++)
	{
		this->swap(head, tail); //! đổi giá trị bên trong con trỏ

		//TODO swap HEAD VÀ TAIL
		customer* temp = head;
		head = tail;
		tail = temp;
					
		//TODO : tìm head tiếp theo
		head = head->prev;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			//Todo: tìm head
			if(head -> energy < 0) break;
			head = head -> prev;

		}

		//! đổi xong rồi nếu TH chẵn

		if(head == tail) break;		

		//TODO : tìm tail tiếp theo

		tail = tail->next;
		for(int i = 0; i < sizeCustomerInDesk ; i++)
		{
			//Todo: tìm tail
			if(tail -> energy < 0) break;
			tail = tail -> next;
		}	
			//! đổi xong rồi nếu TH lẽ
			if(head == tail) break;	
		}
	}
			
	//* Đảo thuật sư giống trên thôi
	//* Bước 1 tìm head và tail
	//* : tìm head bằng cách duyệt theo ngược chiều kim đồng hồ từ khách hàng X tìm oán linh
		head = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			//Todo: tìm head
			if(head -> energy > 0) break;
			head = head -> prev;
		}

			
		//* : tìm tail bằng cách duyệt theo chiều kim đồng hồ từ khách hàng trước X tìm oán linh
		tail = customerX->next; //! NHƯNG PHẢI KHÁC khách hàng x duyệt lần đầu
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			//Todo: tìm tail
			if(tail -> energy > 0) break;
			tail = tail -> next;
		}
			
		//! chỉ có 2 khách hàng là oán linh trở lên mới đảo
		if(head->energy > 0 && head != tail){

			//* Bước 2 hoán đổi không thể nào hoán đổi name được vì CustomerTime đang giữ con trỏ
			//* nên phải hoán đổi luôn địa chỉ bằng hàm swap
			for(int i = 0; i < sizeCustomerInDesk / 2; i++)
			{
				this->swap(head, tail); //! đổi giá trị bên trong con trỏ
				//TODO swap HEAD VÀ TAIL
				customer* temp = head;
				head = tail;
				tail = temp;

				//TODO : tìm head tiếp theo
				head = head->prev;
				for(int i = 0; i < sizeCustomerInDesk; i++)
				{
					//Todo: tìm head
					if(head -> energy > 0) break;
					head = head -> prev;
					}
					

					//! đổi xong rồi nếu TH chẵn
					if(head == tail) break;		

					//TODO : tìm tail tiếp theo
					tail = tail->next;
					for(int i = 0; i < sizeCustomerInDesk ; i++)
					{
						//Todo: tìm tail
						if(tail -> energy > 0) break;
						tail = tail -> next;

					}	
			
					//! đổi xong rồi nếu TH lẽ
					if(head == tail) break;	
		}
	}
	return;
}

void imp_res::UNLIMITED_VOID()
{
	//TODO CODE YOU
	if(sizeCustomerInDesk <= 3) return;

	int MIN_TOTAL = 2147483647; //! đáp án
	customer* head = nullptr, * tail = nullptr; //! node đầu cuối dãy nhỏ nhất

	//* Bước 1 ý tưởng cho i j chạy theo hình tròn tìm min nhỏ nhất và xa khách hàng x nhất
	customer* tempi = customerX; //! khách hàng i
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		int TOTAL = 0;  //! tổng từ chạy i -> i + sizeCustomerInDesk
		customer* tempj = tempi; //! khách hàng j
		int count_node = 0;
		for(int j = 0; j < sizeCustomerInDesk; j++)
		{
		//TODO: tính tổng TOTAL, cập nhật head và tail khi số khách > 4 và TOTAL nhỏ bằng min
			count_node++;
			TOTAL += tempj -> energy;
		
			if(MIN_TOTAL >= TOTAL && count_node >= 4){
				MIN_TOTAL = TOTAL;
				head = tempi;
				tail = tempj;
			}
			tempj = tempj->next;
		}
		tempi = tempi -> next;
	}	
	//* Bước 2: print
	//TODO: print ra khách hàng từ min -> tail và head->min

	customer* min = head;
	customer* temp = head->next; //! vì duyệt qua next nên sizeHeadToTail = sizeHeadToMin = 1
	int sizeHeadToMin = 1, sizeHeadToTail = 1;
	//* tìm min energy đầu tiên, tính sizeHeadToMin và sizeHeadToTail
	while(temp != tail->next)
	{
		//TODO: cập nhật min, sizeHeadToTail, sizeHeadToMin
		if(temp -> energy < min -> energy) min = temp;
			temp = temp->next;
			sizeHeadToTail++;
		}
		temp = head -> next;
		while(temp != min -> next){
			temp = temp -> next;
			sizeHeadToMin++;
		}
		//* print từ min -> tail bao gồm min và tail
		for(int i = 0; i <= sizeHeadToTail - sizeHeadToMin; i++)
		{	
			min -> print();
			min = min -> next;
		}
			
		//* print từ head -> min không bao gồm min
		for(int i = 0; i < sizeHeadToMin - 1; i++)
		{
			head -> print();
			head = head -> next;
		}
	return;
}

void imp_res::LIGHT(int num)
{
	//TODO CODE YOU
	//* print hàng chờ customerQueue
	if(num == 0 && sizeCustomerQueue != 0)
	{
	//TODO: dùng vòng lặp for dựa trên sizeCustomerQueue sử dụng hàm print trong class custome
		customer* temp = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++){
		temp -> print();
		temp = temp -> next;
		}

	}
	//* print hàng trong bàn customerX theo chiều kim đồng hồ
	else if (num > 0)
	{	
	//TODO: dùng vòng lặp for dựa trên sizeCustomerInDesk và next sử dụng hàm print trong class custome
	customer* temp = customerX;
	for(int i = 0; i < sizeCustomerInDesk; i++){
		temp -> print();
		temp = temp -> next;
	}
	}
	//* print hàng trong bàn customerX ngược chiều kim đồng hồ
	else if (num < 0)
	{
	//TODO: dùng vòng lặp for dựa trên sizeCustomerInDesk và prev sử dụng hàm print trong class custome
		customer* temp = customerX;
		for(int i = 0; i< sizeCustomerInDesk; i++){
		temp -> print();
		temp = temp -> prev;
		}
	}
}



