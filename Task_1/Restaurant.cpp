#include "main.h"

class imp_res : public Restaurant
{
	private:
		int sizeCustomerInDesk; //! số lượng khách hàng trong bàn
		customer * customerQueue; //! mô tả danh sách khách hàng đang trong hàng đợi chỉ sử dung next
		int sizeCustomerQueue; //! số lượng khách hàng trong hàng chờ
		customer * customerX; //! lưu trữ danh sách khách hàng đang ở trong bàn gần nhất

	public:
		class customerTime{
		public:
			customer * data;
			customerTime* next;
		public:
			customerTime(customer * data, customerTime* next = nullptr):data(data),next(next) {}
		};
	private:
		customerTime * CustomerTime; //! biến lưu thứ tự thời gian
	public:	
		imp_res() {
			customerX = customerQueue =  nullptr;
			sizeCustomerQueue = sizeCustomerInDesk = 0;
			CustomerTime = nullptr;
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
					if(temp -> name == name) return ;
					temp = temp -> next;
				}

				//TODO : xem thử khác hàng đang chờ có chung tên không
				temp = customerQueue; 
				for(int i = 0; i < sizeCustomerQueue; i++){
					if(temp -> name == name) return ;
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
				//^ biến quản lý thời gian khách hàng nào đến trước
				CustomerTime = new customerTime (customerX);
				customer* temp = new customer(name,energy,nullptr,nullptr);
				customerX = temp;
				customerX -> next = customerX;
				customerX -> prev = customerX;
				sizeCustomerInDesk++;
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

			//^ biến quản lý thời gian khách hàng nào đến trước
			CustomerTime = new customerTime (customerX);
			return;
		}
		
		//^ ĐỘ PHỨC TẠP O(N)
		void BLUE(int num)
		{

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
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
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
				//delete temp;

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
				//delete temp;
			}
			//* print hàng trong bàn customerX ngược chiều kim đồng hồ
			else if (num < 0)
			{
				//TODO: dùng vòng lặp for dựa trên sizeCustomerInDesk và prev sử dụng hàm print trong class custome
				customer* temp = customerX;
				for(int i = 0; i < sizeCustomerInDesk; i++){
					temp -> print();
					temp = temp -> prev;
				}
				//delete temp;
			}
		}
};