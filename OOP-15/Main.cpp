#include <iostream>
#include <string>
#include <vector>
#include <array>

//Шаблонные классы 
//Два вида:
/*	-Определенное количество аргументов
	-Неопределенное количество аргументов (variadic template) (tuple - кортеж)
  Варианты аргументов шаблона:
	-Неопределенные
	-Вычисляемые
	Всегда передаются типы данных!
	-Аргумент-параметр
   */

template <typename Type, const int _size>
class myClass {
public:

	Type& operator[](int i) {
		return data_[i];
	}

	const Type& operator[](int i)const {
		return data_[i];
	}

	auto at(int i)->Type & {
		return data_[i];
	}

	auto at(int i)const ->const Type& {
		return data_[i];
	}

	int size()const {
		return size_;
	}

	class iterator {
	public:
		iterator() = delete;
		iterator(Type *data):data_(data){ }

		iterator &operator++(){
			data_++;
			return *this;
		}

		iterator& operator++(int) {
			iterator tmp(*this);
			data_++;
			return tmp;
		}

		bool operator==(const iterator& obj)const {
			return this->data_ == obj.data_;
		}

		bool operator!=(const iterator& obj)const {
			return !this->operator==(obj);
			//такой стиль применим, если условия проверки содержат сложные условия/вызовы функций
		}

		Type& operator*() {
			return *data_;
		}

	private:
		Type* data_;
	};

	iterator begin() {
		return iterator(data_);
	}

	iterator end() {
		return iterator(data_ + size_);
	}

private:
	Type data_[_size];
	const int size_{ _size };
};

void f01(myClass<int, 10> a) {
	for (size_t i = 0; i < a.size(); i++) {
		std::cout << a[i] << ' ';
	};
}

int main() {
	setlocale(LC_ALL, "Russian");
	myClass<int, 10> a;
	for (size_t i = 0; i < a.size(); i++) {
		a[i] = i + 1;
	}
	f01(a);

	int arr[10];
	for (size_t i = 0; i < std::size(arr); i++) {
		arr[i] = i + 1;
	}
	std::cout << std::endl;
	for (const auto &el : arr) {
		std::cout << el << ' ';
	}
	std::array<int, 10> arrObj;
	for (size_t i = 0; i < std::size(arrObj); i++) {
		arrObj[i] = i + 1;
	}
	std::cout << std::endl;

	for (auto it = arrObj.begin();
		it != arrObj.end();
		++it){
		const auto& el = *it;
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	for (const auto& el : a) {
		std::cout << el << ' ';
	}

	return 0;
}