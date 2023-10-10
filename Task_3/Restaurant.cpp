#include "main.h"

class imp_res : public Restaurant
{
	private:
		int sizeCustomerInDesk; //! số lượng khách hàng trong bàn
		customer * customerQueue; //! mô tả danh sách khách hàng đang trong hàng đợi chỉ sử dung next
		int sizeCustomerQueue; //! số lượng khách hàng trong hàng chờ
		customer * customerX; //! lưu trữ danh sách khách hàng đang ở trong bàn gần nhất

	public:
		//! CLASS này dùng để lưu khách hàng nào đến trước đến sau
		class customerTime{
		public:
			customer * data; //! khách hàng
			customerTime* next;
		public:
			customerTime(customer * data, customerTime* next = nullptr):data(data),next(next) {}
		};
	private:
		customerTime * CustomerTimeHead; //! khách hàng đến lâu nhât
		customerTime * CustomerTimeTail; //! khách hàng đến mới nhất
	public:	
		imp_res() {
			customerX = customerQueue =  nullptr;
			sizeCustomerQueue = sizeCustomerInDesk = 0;
			CustomerTimeHead = CustomerTimeTail = nullptr;
		};

		//^ ĐỘ PHỨC TẠP O(N)
		void RED(string name, int energy)
		{
			//* B1 đuổi về không phải Thuật sư hay oán linh
			if(energy == 0) return;
			//* B2  hàng chờ đã đầy đuổi về
			else if(sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
			//* B3 "thiên thượng thiên hạ, duy ngã độc tôn" : chung tên đuổi về
			else
			{	
				//TODO : xem thử khác hàng dùng bữa có chung tên không
				customer* temp = customerX;
				for(int i = 0; i < sizeCustomerInDesk; i++){
					if(temp -> name == name)return;
					temp = temp -> next;
				}
				//TODO : xem thử khác hàng đang chờ có chung tên không
				temp = customerQueue;
				for(int i = 0; i< sizeCustomerQueue; i++){
					if(temp -> name == name)return;
					temp = temp -> next;
				}

	
			}

			//* B4 đưa vào hàng chờ 
			if(sizeCustomerInDesk == MAXSIZE)
			{
				//TODO: chèn phần tử vào đầu dánh sách khách hàng chờ customerQueue cập nhật sizeCustomerQueue
				//^ chèn đầu danh sách liên kết vòng khi không có phần tử nào
				customer* newCustomer = new customer(name, energy, nullptr,nullptr);
				if(sizeCustomerQueue == 0)
				{
					customerQueue = newCustomer;
					customerQueue -> next = customerQueue;
				}
				//^ chèn cuối danh sách liên kết vòng
				else{
					customer* temp = customerQueue;
					customer* tail = customerQueue;
					for(int i = 0; i < sizeCustomerQueue - 1; i++){
						tail = tail -> next;
					}
					tail -> next = newCustomer;
					newCustomer -> next = temp;
					tail = newCustomer;
				}
				sizeCustomerQueue ++;
				return;
			}
			
			//*B5 khách hàng đầu tiên vào nhà hàng này là danh sách liên kết đôi vòng
			//* giá trị next = prev = chính nó và cập nhật sizeCustomerInDesk
			else if(sizeCustomerInDesk == 0)
			{
				//TODO:
				customer* temp = new customer(name,energy,nullptr,nullptr);
				customerX = temp;
				customerX -> next = customerX;
				customerX -> prev = customerX;
				sizeCustomerInDesk++;
				//^Thêm biến quản lý thời gian khách hàng nào đến trước bước 5
				CustomerTimeTail = CustomerTimeHead = new customerTime (customerX);
				return;
			}
		

			//* B6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2.0 ta phải tìm vị trí mới của customerX
			//* tìm vị trí mới đễ dễ dàng insert customer mới
			if(sizeCustomerInDesk >= MAXSIZE / 2.0)
			{
				//TODO : tìm kiếm khách hàng customerX dùng for để tìm giá trị lớn nhất dựa trên sizeCustomerInDesk
				//* customerX sẽ lưu vị trí lớn nhất
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
			//* B7 trường hợp chèn theo chiều kim đồng hồ
			if(energy >= customerX->energy)
			{
				//TODO: thêm khách hàng mới vào phía trước khác hàng X
				//^ gợi ý sử dụng customerX->next
				newCustomer->prev = customerX;
        		newCustomer->next = customerX->next;
        		customerX->next->prev = newCustomer;
        		customerX->next = newCustomer;
				
			}
			//* B7 trương hợp chèn ngược chiều kim đồng hồ
			else
			{
				//TODO: thêm khách hàng mới vào phía sang khác hàng X
				//^ gợi ý sử dụng customerX->prev
				newCustomer->next = customerX;
        		newCustomer->prev = customerX->prev;
        		customerX->prev->next = newCustomer;
        		customerX->prev = newCustomer;
			}
			//! cập nhật khác hàng x
			customerX = newCustomer;
			sizeCustomerInDesk ++;

			//^Thêm biến quản lý thời gian khách hàng nào đến trước, cuối hàm
			CustomerTimeTail->next = new customerTime (customerX,nullptr);
			CustomerTimeTail = CustomerTimeTail->next;
			return;
		}
		
		//^ ĐỘ PHỨC TẠP O(N)
		void BLUE(int num)
		{
			//* Không có khách lấy gì xóa :<
			if(sizeCustomerInDesk == 0) return;

			//* Bước 1 số lượng khách hàng bị đuổi
			for(int i = 0; i < num; i++)
			{
				//* Bước 1.1 đuổi khách hàng cuối cùng :<
				if(sizeCustomerInDesk == 1)
				{
					//TODO xóa node trong CustomerTime, cập nhật size
					//TODO cập nhật lại khách hàng x và  CustomerTime  gán về nullptr
					CustomerTimeHead -> data = nullptr;
					CustomerTimeHead = CustomerTimeTail = nullptr;
					sizeCustomerInDesk = 0;
					break;
				}
				
				//* Bước 1.2 Đuổi khách hàng
				customer* customerDelete = CustomerTimeHead->data;
				//TODO cập nhật tại khách hàng phía trước và khách hàng phía sau
				customerDelete -> next -> prev = customerDelete -> prev;
				customerDelete -> prev -> next = customerDelete -> next;
				//TODO cập nhật lại khách hàng x thầy mô tả trong thread
				if(customerDelete->energy > 0)
				{
					customerX = customerDelete -> next;
				}
				else
				{
					customerX = customerDelete -> prev;
				}

				//TODO xóa node trong CustomerTime nhớ delete, cập nhật size
				customerTime* temp = CustomerTimeHead -> next;
				delete CustomerTimeHead;
				CustomerTimeHead = temp;
				sizeCustomerInDesk--;
			}
			//* Bước 2 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
			//* XỬ lí đến khi nào trong hàng chờ hết người hoặc bàn đầy người
			while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
			{
				//TODO Lấy đầu danh sách hàng đợi vào thêm vào hàng chính, giảm size
				customer* temp = customerQueue;
				customerQueue = customerQueue -> next;
				sizeCustomerQueue--;
				RED(temp -> name,temp -> energy);
				//delete temp; //^ phần này code thầy hình như bị nhầm
				if(sizeCustomerQueue == 0) customerQueue = nullptr;
			}	
			return;
		}


		//! print ra khách hàng đến gần nhất đến lâu nhất trong bàn
		void print_reverse_In_Disk(customerTime* head)
		{
			if(head == nullptr) return;
			print_reverse_In_Disk(head->next);
			head->data->print();
		}

		//! print ra khách hàng đến gần nhất đến lâu nhất trong hàng chờ
		void print_reverse_In_Queue(customer* head)
		{
			if(head == nullptr) return;
			print_reverse_In_Queue(head->next);
			head->print();
		}
		
		//^ O(n)
		void DOMAIN_EXPANSION()
		{
			//* Không có khách để đuổi
			if(sizeCustomerInDesk == 0) return;
		
			//* Bước 1 tính tổng của thuật sư và oán linh trong bàn ăn và hàng chờ
			int total_Wizard = 0; //! Tổng thuật sư
			int total_Spirit = 0; //! Tổng oán linh
			//TODO : tính trong bàn ăn
			customer* temp = customerX;
			for(int i = 0 ; i < sizeCustomerInDesk; i++){
				if(temp -> energy > 0) total_Wizard += temp -> energy;
				else total_Spirit += temp -> energy;
				temp = temp -> next;
			}

			//TODO : tính trong hàng chờ
			temp = customerQueue;
			for(int i = 0; i < sizeCustomerQueue; i++){
				if(temp -> energy > 0) total_Wizard += temp -> energy;
				else total_Spirit += temp -> energy;
				temp = temp -> next;
			}

	//* Bước 2 xử lí khách hàng trong hàng chờ giống bước 3 thôi đuổi trong hàng chờ Queue
			customer* WizardQueueTail = nullptr; //! Thuật sư lưu danh sách các thuật sư trong hàng chờ
			customer* SpiritQueueTail = nullptr; //! oán linh lưu danh sách các oán linh trong hàng chờ
			customer* WizardQueueHead = nullptr; //! node đầu của thuật sư trong hàng chờ
			customer* SpiritQueueHead = nullptr; //! node đầu của oán linh trong hàng chờ
			//TODO: Bước 2.1 tách làm 2 danh sách oán linh và thuật sư
			customer* tempQueueTime =  sizeCustomerQueue ? customerQueue : nullptr;
			for(int i = 0; i < sizeCustomerQueue; i++)
			{
				//TODO thuật sư
				if(tempQueueTime->energy > 0)
				{
					//TODO nhớ xet TH WizardQueueHead == nullptr
					if(WizardQueueHead == nullptr){
						WizardQueueHead = WizardQueueTail = tempQueueTime;
					}else{
						WizardQueueTail -> next = tempQueueTime;
						WizardQueueTail = tempQueueTime;
					}
				}
				//TODO oán linh
				else
				{	
					//TODO nhớ xet TH SpiritQueueHead == nullptr
					if(SpiritQueueHead == nullptr){
						SpiritQueueHead = SpiritQueueTail = tempQueueTime;
					}else{
						SpiritQueueTail -> next = tempQueueTime;
						SpiritQueueTail = tempQueueTime;
					}
				}

				tempQueueTime = tempQueueTime->next;
			}

			//! cập nhật tail
			if(SpiritQueueTail != nullptr) SpiritQueueTail->next = nullptr;
			if(WizardQueueTail != nullptr) WizardQueueTail->next = nullptr;

			//TODO: Bước 3.2 xóa danh sách oán linh trong hàng chờ
			if(abs(total_Spirit) <= total_Wizard)
			{
				//TODO xóa giống bước 1 task2 nhưng dễ hơn chỉ cần xóa node head thôi
				print_reverse_In_Queue(SpiritQueueHead);
				while(SpiritQueueHead != nullptr)
				{
					//TODO xóa node đầu tiên của SpiritQueueHead
					customer* customerDelete = SpiritQueueHead;
					SpiritQueueHead = SpiritQueueHead -> next;
					delete customerDelete;
					sizeCustomerQueue--;

					// delete temp; //^ phần này code thầy hình như bị nhầm
				}

				//! cập nhật customerQueue danh sách vòng khi có phần tử
				if(WizardQueueTail != nullptr){
					WizardQueueTail->next = WizardQueueHead;
					customerQueue = WizardQueueHead;
				}
				else customerQueue = nullptr;
			}
			//TODO : Bước 2.2 xóa danh sách Thuật sư  trong bàn ăn và trong hàng chờ
			else{
				//TODO xóa giống bước 1 task2 nhưng dễ hơn chỉ cần xóa node head thôi
				print_reverse_In_Queue(WizardQueueHead);
				while(WizardQueueHead != nullptr)
				{
					//TODO xóa node đầu tiên của WizardQueueHead
					customer* customerDelete = WizardQueueHead;
					WizardQueueHead = WizardQueueHead -> next;
					delete customerDelete;
					sizeCustomerQueue--;

					// delete temp; //^ phần này code thầy hình như bị nhầm

				}

				//! cập nhật customerQueue danh sách vòng khi có phần tử
				if(SpiritQueueHead != nullptr){
					SpiritQueueTail->next = SpiritQueueHead;
					customerQueue = SpiritQueueHead;
				}
				else customerQueue = nullptr;
			}

		//^ kết quả của bước này sẽ có CustomerQueue khi xóa thành công trong hàng chờ

			
			//* Bước 3 đuổi khách xem thử đuổi bên nào và print ra luôn
			customerTime* WizardTail = nullptr; //! Thuật sư lưu danh sách các thuật sư
			customerTime* SpiritTail = nullptr; //! oán linh lưu danh sách các oán linh
			customerTime* WizardHead = nullptr; //! node đầu của thuật sư
			customerTime* SpiritHead = nullptr; //! node đầu của oán linh
			//TODO: Bước 2.1 tách làm 2 danh sách oán linh và thuật sư
			customerTime* tempTime = CustomerTimeHead;
			for(int i = 0; i < sizeCustomerInDesk; i++)
			{
				//TODO thuật sư
				if(tempTime->data->energy > 0)
				{
					//TODO nhớ xet TH WizardHead == nullptr
					if(WizardHead == nullptr){
						WizardHead = WizardTail = tempTime;
					}
					else{
						WizardTail -> next = tempTime;
						WizardTail = tempTime;
					}
				}
				//TODO oán linh
				else
				{
					//TODO nhớ xet TH SpiritHead == nullptr
					if(SpiritHead == nullptr){
						SpiritHead = SpiritTail = tempTime;
					}
					else{
						SpiritTail -> next = tempTime;
						SpiritTail = tempTime;
					}
				}

				tempTime = tempTime->next;
			}

			//! cập nhật tail
			if(SpiritTail != nullptr) SpiritTail->next = nullptr;
			if(WizardTail != nullptr) WizardTail->next = nullptr;


			//TODO: Bước 2.2 xóa danh sách oán linh
			if(abs(total_Spirit) <= total_Wizard)
			{
				//! print các khách hàng chuẩn bị xóa
				print_reverse_In_Disk(SpiritHead);
				//TODO xóa giống bước 1 task2
				while(SpiritHead != nullptr && SpiritHead != SpiritTail->next)
				{
					//TODO giống bước 1 task2 nhưng đang xóa trên SpiritHead
					customer* customerDelete = SpiritHead -> data;
					customerDelete -> next -> prev = customerDelete -> prev;
					customerDelete -> prev -> next = customerDelete -> next;
					customerX = customerDelete -> prev;

					customerTime* temp_delete = SpiritHead;
					SpiritHead = SpiritHead -> next;
					delete temp_delete;
					sizeCustomerInDesk--;
				}

				//! cập nhật CustomerTimeHead và CustomerTimeTail
				CustomerTimeHead = WizardHead;
				CustomerTimeTail = WizardTail;
			}
			//TODO : Bước 2.2 xóa danh sách oán linh giống phần trên
			else{
				//! print các khách hàng chuẩn bị xóa
				print_reverse_In_Disk(WizardHead);
				//TODO xóa giống bước 1 task2
				while(WizardHead != nullptr && WizardHead != WizardTail->next)
				{
					//TODO giống bước 1 task2 nhưng đang xóa trên WizardHead
					customer* customerDelete = WizardHead -> data;
					customerDelete -> next -> prev = customerDelete -> prev;
					customerDelete -> prev -> next = customerDelete -> next;
					customerX = customerDelete -> next;
					
					customerTime* temp_delete = WizardHead;
					WizardHead = WizardHead -> next;
					delete temp_delete;
					sizeCustomerInDesk--;
				}

				//! cập nhật CustomerTimeHead và CustomerTimeTail
				CustomerTimeHead = SpiritHead;
				CustomerTimeTail = SpiritTail;
			}

			
			//* Bước 3 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
			//* giống bước 2 phần BLUE đưa code vào
			
			//TODO code bước 2 trong phần BLUE
			while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
			{
				//TODO Lấy đầu danh sách hàng đợi vào thêm vào hàng chính, giảm size
				customer* temp = customerQueue;
				customerQueue = customerQueue -> next;
				sizeCustomerQueue--;
				RED(temp -> name,temp -> energy);
				//delete temp; //^ phần này code thầy hình như bị nhầm
				if(sizeCustomerQueue == 0) customerQueue = nullptr;
			}	
			return;

		}
	

		void PURPLE()
		{


			cout << "purple"<< endl;
		}
		void REVERSAL()
		{

		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void LIGHT(int num)
		{
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
};