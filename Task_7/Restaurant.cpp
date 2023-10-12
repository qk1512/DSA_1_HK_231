#include "main.h"

class imp_res : public Restaurant
{
	class TimeInRestaurant;
private:
	customer * Queue_of_Customer;
	customer * customerX; 

	int sizeCustomerInDesk; 
	int sizeQueue_of_Customer; 

	TimeInRestaurant * Head_TimeInRestaurant; 
	TimeInRestaurant * Tail_TimeInRestaurant; 

private:

	//tìm khách hàng ngồi lâu nhất
	TimeInRestaurant* findCustomerDelete()
	{	

		TimeInRestaurant* CustomerToDelete = Head_TimeInRestaurant;
		
		for(int i = 0; i < sizeQueue_of_Customer + sizeCustomerInDesk; i++)
		{
			if(CustomerToDelete -> inDesk == true) break;
			CustomerToDelete = CustomerToDelete->next;
		}

		//TH chỉ có 1 khách
		if(sizeQueue_of_Customer + sizeCustomerInDesk == 1)
		{
			Head_TimeInRestaurant = Tail_TimeInRestaurant = nullptr;
		}
		//TH khách là đầu tiền
		else if(CustomerToDelete == Head_TimeInRestaurant)
		{
			CustomerToDelete -> next -> prev = nullptr;
			Head_TimeInRestaurant = Head_TimeInRestaurant -> next;
		}
		//TH khách là cuối cùng
		else if(CustomerToDelete == Tail_TimeInRestaurant)
		{
			CustomerToDelete -> prev -> next = nullptr;
			Tail_TimeInRestaurant = Tail_TimeInRestaurant -> prev;
		}
		//TH khách ở giữa
		else
		{
			CustomerToDelete -> next -> prev = CustomerToDelete -> prev;
			CustomerToDelete -> prev -> next = CustomerToDelete -> next;
		}

		return CustomerToDelete;	
	}

	void deleteTimeInRestaurant(TimeInRestaurant* CustomerToDelete)
	{
		//khách trong bàn
		if(CustomerToDelete->inDesk == true)
		{
			if(sizeCustomerInDesk == 1)
			{
				sizeCustomerInDesk = 0;
				customerX = nullptr;
			}
			else
			{
				customer* customerDelete = CustomerToDelete->data;
				customerDelete -> next -> prev = customerDelete -> prev;
				customerDelete -> prev -> next = customerDelete -> next;

				//cập nhật lại customerX
				if(customerDelete->energy > 0)
				{
					customerX = customerDelete -> next;
				}
				else
				{
					customerX = customerDelete -> prev;
				}
				sizeCustomerInDesk--; //cập nhật size trong bàn
			}
		}
		//khách trong hàng chờ
		else
		{
			//đuổi khách hàng trong hàng chờ khi chỉ có 1 khách hàng
			if(sizeQueue_of_Customer == 1)
			{
				sizeQueue_of_Customer = 0;
				Queue_of_Customer = nullptr;
			}
			//đuổi khách hàng trong hàng chờ
			else
			{
				customer* customerDelete = CustomerToDelete->data;
				//cập nhật tại khách hàng phía trước và khách hàng phía sau
				customerDelete -> next -> prev = customerDelete -> prev;
				customerDelete -> prev -> next = customerDelete -> next;

				//cập nhật lại khách hàng đầu tiên khi khách hàng đầu tiên trong hàng chờ bị xóa
				if(customerDelete == Queue_of_Customer) Queue_of_Customer = Queue_of_Customer->next;
				sizeQueue_of_Customer--; //cập nhật size trong bàn
			}
		}

		delete CustomerToDelete; 
		
	}

	//đưa khách hàng từ hàng chờ vào bàn ăn
	void insertCustomerfromQueueToDesk()
	{
		while(sizeQueue_of_Customer != 0 && sizeCustomerInDesk != MAXSIZE)
		{
			customer* newCustomer = Queue_of_Customer;

			TimeInRestaurant* temp = Head_TimeInRestaurant; 
			for(int i = 0; i < sizeQueue_of_Customer + sizeCustomerInDesk; i++)
			{
				if(temp -> data == newCustomer) temp -> inDesk = true; 
				temp = temp->next;
			}
			if(sizeQueue_of_Customer == 1) Queue_of_Customer = nullptr;
			else
			{
				newCustomer -> next -> prev = newCustomer -> prev;
				newCustomer -> prev -> next = newCustomer -> next;

				Queue_of_Customer -> next -> prev = Queue_of_Customer -> prev;
				Queue_of_Customer -> prev -> next = Queue_of_Customer -> next;
				Queue_of_Customer = Queue_of_Customer -> next;

			}
			sizeQueue_of_Customer --;

			if(sizeCustomerInDesk == 0)
			{
				customerX = newCustomer;
				newCustomer->next = newCustomer->prev = newCustomer;
			}
			else 
			{
				//xét thử khách hàng tìm X
				if(sizeCustomerInDesk >= MAXSIZE / 2)
				{
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
				//thêm khách hàng mới vào phía trước khác hàng X
				if(newCustomer -> energy >= customerX -> energy)
				{
					newCustomer -> prev = customerX;
					newCustomer -> next = customerX -> next;
					customerX -> next -> prev = newCustomer;
					customerX -> next = newCustomer;
				}
				//thêm khách hàng mới vào phía sau khác hàng X
				else
				{
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

	void print_reverse(TimeInRestaurant* head)
	{
		
		if(head != nullptr){
			print_reverse(head -> next);
			head -> data -> print();
		}
	}

	void swap(customer* head, customer * tail)
	{
		customer* temp = new customer();

		head -> next -> prev = temp;
		head -> prev -> next = temp;
		temp -> next = head -> next;
		temp -> prev = head -> prev;
		head -> next = head -> prev = nullptr;

		//đổi head với tail
		head -> next = tail -> next;
		head -> prev = tail -> prev;
		tail -> next -> prev = head;
		tail -> prev -> next = head;
		tail -> next = tail -> prev = nullptr;

		//đổi tail với temp
		tail -> next = temp -> next;
		tail -> prev = temp -> prev;
		temp -> next -> prev = tail;
		temp -> prev -> next = tail;
		temp -> next = temp -> prev = nullptr;

		delete temp;
	}	

	customer* getCustomer_at_index(customer* x, int index)
	{
		for(int i = 0; i < index; i++) x = x->next;
		return x;
	}

	int inssort2(customer* head, int n, int incr) {
		int count_to_delete = 0; //sô lượng swap
		for(int i = incr; i < n; i += incr)
		{
			for(int j = i; j >= incr; j -= incr)
			{
				//* lấy phần tử so sánh
				customer* a = this->getCustomer_at_index(head, j);
				customer* b = this->getCustomer_at_index(head, j - incr);

				//TODO tìm điệu kiện dừng
				if(abs(a -> energy) <= abs(b -> energy)) break;

				swap(a, b);
				count_to_delete++;

				//xét trường hợp b = Queue_of_Customer or head thì phải đưa head về a
				if (b == Queue_of_Customer && b == head){
					Queue_of_Customer = a;
					head = a;
				}
				
			}
		}
		return count_to_delete;
	}

public:	
	imp_res() {
		customerX = Queue_of_Customer =  nullptr;
		sizeQueue_of_Customer = sizeCustomerInDesk = 0;
		Head_TimeInRestaurant = Tail_TimeInRestaurant = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	
	void PURPLE();

	~imp_res(){  
		while(Head_TimeInRestaurant)
		{
			TimeInRestaurant* temp = Head_TimeInRestaurant;	 
			Head_TimeInRestaurant = Head_TimeInRestaurant->next;
			delete temp;
		}
	}
private:
	class TimeInRestaurant{
	public:
		customer * data;
		TimeInRestaurant* next;
		TimeInRestaurant* prev;
		bool inDesk; //xem thử khách hàng có trong bàn hay không
	public:
		TimeInRestaurant(customer * data, bool inDesk, TimeInRestaurant* next = nullptr, TimeInRestaurant* prev = nullptr)
		:data(data),next(next),prev(prev), inDesk(inDesk) {}
		~TimeInRestaurant(){delete data;}
	};
};

void imp_res::RED(string name, int energy)
{
	
	//đuổi về nếu không phải Thuật sư hay oán linh
	if(energy == 0) return;
	//khàng chờ đã đầy đuổi về
	else if(sizeCustomerInDesk + sizeQueue_of_Customer >= MAXSIZE * 2) return;
	//"thiên thượng thiên hạ, duy ngã độc tôn" : cùng tên đuổi về
	else
	{
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++){
			if(temp -> name == name) return;
			temp = temp -> next;
		}
		temp = Queue_of_Customer;
		for(int i = 0; i < sizeQueue_of_Customer; i++){
			if(temp -> name == name) return;
			temp = temp -> next;
		}
	}

	//đưa vào hàng chờ nếu full chỗ trong bàn 
	if(sizeCustomerInDesk == MAXSIZE)
	{
		customer* newCustomer = new customer(name, energy, nullptr, nullptr);
		
		if(sizeQueue_of_Customer == 0)
		{
			
			Queue_of_Customer = newCustomer;
			Queue_of_Customer -> next = Queue_of_Customer -> prev = Queue_of_Customer;
		}
		
		else
		{
			customer* tail = Queue_of_Customer -> prev;
			newCustomer -> prev = tail;
			newCustomer -> next = tail -> next;
			tail -> next -> prev = newCustomer;
			tail -> next = newCustomer;

		}
		sizeQueue_of_Customer ++;

		//cập nhật vị trí trong Time
		TimeInRestaurant* newTimeInRestaurant = new TimeInRestaurant (newCustomer, false);
		
		Tail_TimeInRestaurant->next = newTimeInRestaurant;
		newTimeInRestaurant->prev = Tail_TimeInRestaurant;
		Tail_TimeInRestaurant = Tail_TimeInRestaurant->next;
		return;
	}
	
	//khách hàng đầu tiên vào nhà hàng
	else if(sizeCustomerInDesk == 0)
	{
		customer * newCustomer = new customer(name,energy,nullptr,nullptr);
		
		customerX = newCustomer;
		customerX -> next = customerX;
		customerX -> prev = customerX;
		sizeCustomerInDesk++;
		// vì đang trong bàn ăn nên inDesk = true
		Tail_TimeInRestaurant = Head_TimeInRestaurant = new TimeInRestaurant (customerX, true);
		
		return;
	}


	//TH mà sizeCustomerInDesk >= MAXSIZE / 2.0 -> tìm vị trí mới của customerX
	if(sizeCustomerInDesk >= MAXSIZE / 2)
	{
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
	//trường hợp chèn theo chiều kim đồng hồ
	if(energy >= customerX->energy)
	{
		newCustomer -> prev = customerX;
		newCustomer -> next = customerX -> next;
		customerX -> next -> prev = newCustomer;
		customerX -> next = newCustomer;
	}
	//trương hợp chèn ngược chiều kim đồng hồ
	else
	{
		newCustomer -> next = customerX;
		newCustomer -> prev = customerX -> prev;
		customerX -> prev -> next = newCustomer;
		customerX -> prev = newCustomer;
	}

	customerX = newCustomer;
	sizeCustomerInDesk ++;

	// cập nhật Time
	// vì đang trong bàn ăn nên inDesk = true
	TimeInRestaurant* newTimeInRestaurant = new TimeInRestaurant (newCustomer, true);
	
	Tail_TimeInRestaurant->next = newTimeInRestaurant;
	newTimeInRestaurant->prev = Tail_TimeInRestaurant;
	Tail_TimeInRestaurant = Tail_TimeInRestaurant->next;
	return;
}

void imp_res::BLUE(int num)
{
	
	//Không có khách
	if(sizeCustomerInDesk == 0) return;

	//số lượng khách hàng bị đuổi
	for(int i = 0; i < num && sizeCustomerInDesk != 0; i++)
	{
		//tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
		TimeInRestaurant* CustomerToDelete = this->findCustomerDelete();

		//đuổi khách 
		this->deleteTimeInRestaurant(CustomerToDelete);
	}

	//thêm khách từ hàng đợi vào bàn
	this->insertCustomerfromQueueToDesk();
	return;
}

void imp_res::PURPLE()
{
	int removeBLUE = 0;

	//tìm vị trí của max abs(energy)
	int n = 0; //kích thước danh sách cần sort
	customer* temp = Queue_of_Customer;
	customer* max = Queue_of_Customer;
	for(int i = 0; i < sizeQueue_of_Customer; i++)
	{
		if(abs(temp->energy) >= abs(max->energy))
		{
			max = temp;
			n = i + 1;
		}
		temp = temp->next;
	}

	//sort theo hàm shell sort được mô tả
	for(int i = n / 2; i > 2; i /= 2)
	{
		for(int j = 0; j < i; j++)
		{
			removeBLUE += inssort2(this->getCustomer_at_index(Queue_of_Customer, j), n - j, i);
		}
	}
	removeBLUE += inssort2(Queue_of_Customer, n, 1);

	//xóa
	this->BLUE(removeBLUE % MAXSIZE);
}


void imp_res::DOMAIN_EXPANSION()
{
	//Không có khách
		if(sizeCustomerInDesk == 0) return;

	//tính tổng của thuật sư và oán linh
		int total_Customer_of_Gojo = 0; //tổng thuật sư
		int total_Customer_of_Sukuna = 0; //tổng oán linh

		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++){
			if(temp -> energy > 0) total_Customer_of_Gojo += temp -> energy;
			else total_Customer_of_Sukuna += temp -> energy;
			temp = temp -> next;
		}

		temp = Queue_of_Customer;
		for(int i = 0; i < sizeQueue_of_Customer; i++){
			if(temp -> energy > 0) total_Customer_of_Gojo += temp -> energy;
			else total_Customer_of_Sukuna += temp -> energy;
			temp = temp -> next;
		}


		TimeInRestaurant* Customer_of_Gojo_Tail = nullptr; //thuật sư lưu danh sách các thuật sư
		TimeInRestaurant* Customer_of_Sukuna_Tail = nullptr; //oán linh lưu danh sách các oán linh
		TimeInRestaurant* Customer_of_Gojo_Head = nullptr; //node đầu của thuật sư
		TimeInRestaurant* Customer_of_Sukuna_Head = nullptr; //node đầu của oán linh
		//tách làm 2 danh sách oán linh và thuật sư 
		TimeInRestaurant* tempTime = Head_TimeInRestaurant;		
		for(int i = 0; i < sizeCustomerInDesk + sizeQueue_of_Customer;i++)
		{
			//thuật sư
			if(tempTime->data->energy > 0)
			{
				if(Customer_of_Gojo_Head == nullptr)
				{
					Customer_of_Gojo_Head = Customer_of_Gojo_Tail = tempTime;	
				}
				else
				{
					Customer_of_Gojo_Tail -> next = tempTime;
					Customer_of_Gojo_Tail -> next -> prev = Customer_of_Gojo_Tail;
					Customer_of_Gojo_Tail = tempTime;					
				}
			}
			//oán linh
			else 
			{
				if(Customer_of_Sukuna_Head == nullptr)
				{
					Customer_of_Sukuna_Head = Customer_of_Sukuna_Tail = tempTime;
				}
				else
				{
					Customer_of_Sukuna_Tail -> next = tempTime;
					Customer_of_Sukuna_Tail -> next -> prev = Customer_of_Sukuna_Tail;
					Customer_of_Sukuna_Tail = tempTime;	
				}
			}
			
			tempTime = tempTime->next;
		}
		

		//! cập nhật TimeHead, TimeTail
		if(Customer_of_Sukuna_Head != nullptr && Customer_of_Sukuna_Tail != nullptr) {
			Customer_of_Sukuna_Head -> prev = nullptr;
			Customer_of_Sukuna_Tail -> next = nullptr;
		}
		if(Customer_of_Gojo_Head != nullptr && Customer_of_Gojo_Tail != nullptr) {
			Customer_of_Gojo_Head -> prev = nullptr;
			Customer_of_Gojo_Tail -> next = nullptr;
		}
		

		//xóa danh sách oán linh trong bàn ăn 
		if(abs(total_Customer_of_Sukuna) <= total_Customer_of_Gojo)
		{
			print_reverse(Customer_of_Sukuna_Head);
			while(Customer_of_Sukuna_Tail != nullptr)
			{
				TimeInRestaurant* CustomerToDelete;
				CustomerToDelete = Customer_of_Sukuna_Tail;
				Customer_of_Sukuna_Tail = Customer_of_Sukuna_Tail -> prev;
				
				this->deleteTimeInRestaurant(CustomerToDelete);
			}

			//cập nhật Head_TimeInRestaurant và Tail_TimeInRestaurant vì đã đuổi hết oán linh
			Head_TimeInRestaurant = Customer_of_Gojo_Head;
			Tail_TimeInRestaurant = Customer_of_Gojo_Tail;
			
		}
		// xóa thuật sư
		else{
			print_reverse(Customer_of_Gojo_Head);
			while(Customer_of_Gojo_Tail != nullptr)
			{
				TimeInRestaurant* CustomerToDelete;
				CustomerToDelete = Customer_of_Gojo_Tail;
				Customer_of_Gojo_Tail = Customer_of_Gojo_Tail -> prev;

				this->deleteTimeInRestaurant(CustomerToDelete);
			}

			//cập nhật Head_TimeInRestaurant và Tail_TimeInRestaurant vì đã đuổi hết thuật sư
			Head_TimeInRestaurant = Customer_of_Sukuna_Head;
			Tail_TimeInRestaurant = Customer_of_Sukuna_Tail;
		}

		// đưa khách hàng mới vào bàn
		this->insertCustomerfromQueueToDesk();
}

void imp_res::REVERSAL()
{
		
	// số lượng khách không đủ để đảo
	if(sizeCustomerInDesk <= 1) return;			

	customer* head = nullptr; 
	customer* tail = nullptr;

	//đảo oán linh
	//tìm head ngược theo chiều kim đồng hồ 
	head = customerX;
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		if(head -> energy < 0) break;
		head = head -> prev;
	}

	//tìm tail bằng cách duyệt theo chiều kim đồng hồ từ khách hàng trước X tìm oán linh
	tail = customerX->next; //! NHƯNG PHẢI KHÁC khách hàng x duyệt lần đầu
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		//Todo: tìm tail
		if(tail -> energy < 0) break;
		tail = tail -> next;
	}
			
	//chỉ có 2 khách hàng là oán linh trở lên mới đảo
	if(head->energy < 0 && head != tail){

	
	for(int i = 0; i < sizeCustomerInDesk / 2; i++)
	{
		this->swap(head, tail); // đổi địa chỉ không đổi đata

		//đảo lại head và temp
		customer* temp = head;
		head = tail;
		tail = temp;
					
		//tìm head tiếp theo
		head = head->prev;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			if(head -> energy < 0) break;
			head = head -> prev;

		}

		//đổi xong rồi nếu TH chẵn

		if(head == tail) break;		

		//tìm tail tiếp theo

		tail = tail->next;
		for(int i = 0; i < sizeCustomerInDesk ; i++)
		{
			if(tail -> energy < 0) break;
			tail = tail -> next;
		}	
			//đổi xong rồi nếu TH lẽ
			if(head == tail) break;	
		}
	}
			
	// đảo thuật sư như đảo oán linh
		head = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			if(head -> energy > 0) break;
			head = head -> prev;
		}

			
		tail = customerX->next; 
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			if(tail -> energy > 0) break;
			tail = tail -> next;
		}
			
		if(head->energy > 0 && head != tail){

			for(int i = 0; i < sizeCustomerInDesk / 2; i++)
			{
				this->swap(head, tail); 
				customer* temp = head;
				head = tail;
				tail = temp;

				head = head->prev;
				for(int i = 0; i < sizeCustomerInDesk; i++)
				{
					if(head -> energy > 0) break;
					head = head -> prev;
					}
					

					if(head == tail) break;		

					tail = tail->next;
					for(int i = 0; i < sizeCustomerInDesk ; i++)
					{
						if(tail -> energy > 0) break;
						tail = tail -> next;

					}	
			
					if(head == tail) break;	
		}
	}
	return;
}

void imp_res::UNLIMITED_VOID()
{
	
	if(sizeCustomerInDesk <= 3) return;

	int MIN_TOTAL = 2147483615; // vì không biết giá trị có thể được thêm nên gán một số siêu to
	customer* head = nullptr, * tail = nullptr; //! node đầu cuối dãy nhỏ nhất

	customer* temp_1 = customerX;
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		int TOTAL = 0;  
		customer* temp_2 = temp_1; 
		int count_node = 0;
		for(int j = 0; j < sizeCustomerInDesk; j++)
		{
			count_node++;
			TOTAL += temp_2 -> energy;
		
			if(MIN_TOTAL >= TOTAL && count_node >= 4){
				MIN_TOTAL = TOTAL;
				head = temp_1;
				tail = temp_2;
			}
			temp_2 = temp_2->next;
		}
		temp_1 = temp_1 -> next;
	}	

	customer* min = head;
	customer* temp = head->next; //vì duyệt qua next nên sizeHeadToTail = sizeHeadToMin = 1
	int sizeHeadToMin = 1, sizeHeadToTail = 1;
	//tìm min energy đầu tiên, tính sizeHeadToMin và sizeHeadToTail
	while(temp != tail->next)
	{
		//cập nhật min, sizeHeadToTail, sizeHeadToMin
		if(temp -> energy < min -> energy) min = temp;
			temp = temp->next;
			sizeHeadToTail++;
		}
		temp = head -> next;
		while(temp != min -> next){
			temp = temp -> next;
			sizeHeadToMin++;
		}
		//print từ min -> tail bao gồm min và tail
		for(int i = 0; i <= sizeHeadToTail - sizeHeadToMin; i++)
		{	
			min -> print();
			min = min -> next;
		}
			
		//print từ head -> min không bao gồm min
		for(int i = 0; i < sizeHeadToMin - 1; i++)
		{
			head -> print();
			head = head -> next;
		}
	return;
}

void imp_res::LIGHT(int num)
{
	
	//print hàng chờ Queue_of_Customer
	if(num == 0 && sizeQueue_of_Customer != 0)
	{
		customer* temp = Queue_of_Customer;
		for(int i = 0; i < sizeQueue_of_Customer; i++){
			temp -> print();
			temp = temp -> next;
		}
	}
	//print hàng trong bàn customerX theo chiều kim đồng hồ
	else if (num > 0)
	{	
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++){
			temp -> print();
			temp = temp -> next;
		}
	}
	//print hàng trong bàn customerX ngược chiều kim đồng hồ
	else if (num < 0)
	{
		customer* temp = customerX;
		for(int i = 0; i< sizeCustomerInDesk; i++){
			temp -> print();
			temp = temp -> prev;
		}
	}
}