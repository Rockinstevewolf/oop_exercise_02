//Barannikov Stepan M8o-201b
/*
* ========================
* Создать класс IPAddress для работы с адресом в интернет.
* Класс состоит из четырех чисел unsigned char (a,b,c,d).
* Реализовать арифметические операции сложения, вычитания,
* а также операции сравнения (для сравнение на больше/меньше считать,
* что левые байты главнее т.е. вначале сравниваются первые байты, потом вторые и т.д.).
* Так же реализовать функцию, которая будет определять принадлежность адреса к подсети
* по адресу подсети (a1,b1,c1,d1) и битовой маске подсети (a2,b2,c2,d2).
*  Например, адрес 192.168.1.30 принадлежит подсети 192.168.0.0 с маской 255.255.0.0.
* 
* Операции сложения, вычитания и сравнения необходимо реализовать в виде перегрузки операторов.
* 
* Необходимо реализовать пользовательский литерал для работы с константами типа IPAddress.
* ========================
*/
//Использование пользовательского литерала находится в конце программы (закоментировано)

#include <iostream>
using namespace std;
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct ipv4bytes {
	unsigned char d,c,b,a;
};
union ipv4 {
	ipv4bytes  bytes;
	unsigned int number;
};
ipv4 operator "" _ip(const char* saddr, size_t size){
	ipv4 result, reverse;
	in_addr num_ip;
	inet_aton(saddr, &num_ip);
	reverse.number = num_ip.s_addr;
	result.bytes.a = reverse.bytes.d;
	result.bytes.b = reverse.bytes.c;
	result.bytes.c = reverse.bytes.b;
	result.bytes.d = reverse.bytes.a;
	return result;
}

class IPAddress{
private:
	ipv4 data;
public:
	IPAddress(){
		data.bytes = {0,0,0,0};
	}
	IPAddress(ipv4 x){
		setData(x);
	}
	ipv4 getData(){
		return data;
	}
	void setData(ipv4 x){
		data = x;
	}
	void setData(IPAddress &x){
		setData(x.getData());
	}

	IPAddress& operator= (const IPAddress &x){
		setData(x.data);
		return *this;
	}
	IPAddress& operator& (const IPAddress &y){
		return And(y);
	}
	IPAddress& operator- (const IPAddress &y){
		return minus(y);
	}
	IPAddress& operator+ (const IPAddress &y){
		return plus(y);
	}
	bool operator< (IPAddress &y){
		bool l = less(data, y.data);
		return l;
	}
	bool operator> (IPAddress &y){
		bool m = more(data, y.data);
		return m;
	}
	bool operator== (IPAddress &y){
		bool eq = equal(data, y.data);
		return eq;
	}
	friend ostream& operator<< (ostream& stream, const IPAddress &x){
		in_addr numeric_ip;
		ipv4 save;
		save.bytes.a = x.data.bytes.d;
		save.bytes.b = x.data.bytes.c;
		save.bytes.c = x.data.bytes.b;
		save.bytes.d = x.data.bytes.a;
		numeric_ip.s_addr = save.number;
		stream << inet_ntoa(numeric_ip);
		return stream;
	}

	IPAddress &plus(const IPAddress &y){
		IPAddress *sol = new(IPAddress);
		sol->data.number = data.number + y.data.number;
		return *sol;
	}
	IPAddress &minus(const IPAddress &y){
		IPAddress *sol = new(IPAddress);
		sol->data.number = data.number - y.data.number;
		return *sol;
	}
	IPAddress &And(const IPAddress &y){
		IPAddress *sol = new(IPAddress);
		sol->data.number = data.number & y.data.number;
		return *sol;
	}

	//sravneniye
	bool less(ipv4 x, ipv4 y){
		return (x.number < y.number);
	}
	bool more(ipv4 x, ipv4 y){
		return (x.number > y.number);
	}
	bool equal(ipv4 x, ipv4 y){
		return (x.number == y.number);
	}
	bool includes(IPAddress &netw,const IPAddress &mask){
		IPAddress x = data;
		if((x & mask) == (netw & mask))
			return true;
		else
			return false;
	}
};


int main()
{
	IPAddress x,y,mask;
	ipv4 ip1, ip2, ip3;
	int a,b,c,d;
	int k = -1;
	cout << "Введите основной IP в виде 'x.x.x.x':\n";
	scanf("%d.%d.%d.%d", &a, &b, &c, &d);
	ip1 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
	x = ip1;
	cout << "Вы ввели:\n\t" << x << endl;
	cout <<
	"--------------------------------------------\n" <<
	"Меню:\n" <<
	"--------------------------------------------\n" <<
	"1. Сложение адресов\n" <<
	"2. Вычитание адресов\n" <<
	"3. Сравнение адресов\n" <<
	"4. Логическое умножение адресов\n" <<
	"5. Проверка основного адреса на принадлежность к подстети\n" <<
	"6. Замена основного числа\n" <<
	"7. Вывод МЕНЮ\n" <<
	"--------------------------------------------\n" <<
	"0. ВЫХОД ИЗ ПРОГРАММЫ\n" <<
	"--------------------------------------------\n";
	while(k!=0){
		cout << "Введите номер меню: ";
		cin >> k;
		switch(k){
			case(1):
				cout << "Введите еще один IP в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip2 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				y = ip2;
				cout << "\t" << x << "\n\t+\n\t" << y << "\n\t=\n\t" << (x+y) << endl;
				cout << "--------------------------------------------\n";
				break;
			case(2):
				cout << "Введите еще один IP в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip2 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				y = ip2;
				cout << "\t" << x << "\n\t-\n\t" << y << "\n\t=\n\t" << (x-y) << endl;
				cout << "--------------------------------------------\n";
				break;
			case(3):
				cout << "Введите еще один IP в виде 'x.x.x.x':\n";			
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip2 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				y = ip2;
				if(x<y)
					cout << "\t" << x << " < " << y << endl;
				else if(x>y)
					cout << "\t" << x << " > " << y << endl;
				else if(x==y)
					cout << "\t" << x << " = " << y << endl;
				cout << "--------------------------------------------\n";
				break;
			case(4):
				cout << "Введите еще один IP в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip2 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				y = ip2;
				cout << "\t" << x << "\n\t&\n\t" << y << "\n\t=\n\t" << (x&y) << endl;
				cout << "--------------------------------------------\n";
				break;
			case(5):
				cout << "Введите адрес IP подсети в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip2 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				y = ip2;
				cout << "Введите маску подсети в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip3 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				mask = ip3;
				cout << "Основной IP:\n\t" << x << "\nIP подсети:\n\t" << y << "\nМаска подсети:\n\t" << mask << endl;
				if(!((y&mask) == y)){
					cout << " Неправильные адрес подсети и маска!\n";
					cout << "--------------------------------------------\n";
					break;
				}
				else{
					bool check = x.includes(y,mask);
					if(check)
						cout << " IP адрес " << x << "  Принадлежит подсети  " << y << endl;
					else
						cout << " IP адрес " << x << "  НЕ принадлежит подсети  " << y << endl;
					cout << "--------------------------------------------\n";
					break;
				}
			case(6):
				cout << "Введите основной IP в виде 'x.x.x.x':\n";
				scanf("%d.%d.%d.%d", &a, &b, &c, &d);
				ip1 = {(unsigned char)d,(unsigned char)c,(unsigned char)b,(unsigned char)a};
				x = ip1;
				cout << "Вы ввели:\n\t" << x << endl;
				cout << "--------------------------------------------\n";
				break;
			case(7):
				cout <<
				"--------------------------------------------\n" <<
				"Меню:\n" <<
				"--------------------------------------------\n" <<
				"1. Сложение адресов\n" <<
				"2. Вычитание адресов\n" <<
				"3. Сравнение адресов\n" <<
				"4. Логическое умножение адресов\n" <<
				"5. Проверка основного адреса на принадлежность к подстети\n" <<
				"6. Замена основного числа\n" <<
				"7. Вывод МЕНЮ\n" <<
				"--------------------------------------------\n" <<
				"0. ВЫХОД ИЗ ПРОГРАММЫ\n" <<
				"--------------------------------------------\n";
				break;
		}
	}

/*
	ipv4 ip="192.168.1.30"_ip;
	cout << "Hello," << ip.number << " !\n";
	cout << "Hi," << (int)ip1.bytes.a << "." << (int)ip1.bytes.b << "." << (int)ip1.bytes.c << "." << (int)ip1.bytes.d << endl;
*/

	return 0;
}