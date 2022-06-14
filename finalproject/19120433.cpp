#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Tokenizer
{
public:
	static vector<string> split(string haystack, string needle = " ")
	{
		vector<string> result;

		int startPos = 0;
		size_t foundPos = 0;

		while (true)
		{
			foundPos = haystack.find(needle, startPos);

			if (foundPos != string::npos)
			{
				string token = haystack.substr(startPos, foundPos - startPos);
				result.push_back(token);
				startPos = foundPos + needle.length();
			}
			else
			{
				string token = haystack.substr(startPos, needle.length() - startPos);
				result.push_back(token);
				break;
			}

		}

		return result;
	}
};

class Laptop
{
private:
	int _id;
	string _name;
	string _cpu;
	string _ram;
	string _storage;
	string _graphicCard;
	long _price;
	long _sellPrice;
	int _totalProduct;
public:
	//Properties
	int id()
	{
		return _id;
	}

	void setId(int value)
	{
		_id = value;
	}

	string name()
	{
		return _name;
	}

	void setName(string value)
	{
		_name = value;
	}

	string cpu()
	{
		return _cpu;

	}

	void setCpu(string value)
	{
		_cpu = value;
	}

	string ram()
	{
		return _ram;

	}

	void setRam(string value)
	{
		_ram = value;
	}

	string storage()
	{
		return _storage;

	}

	void setStorage(string value)
	{
		_storage = value;
	}

	string graphicCard()
	{
		return _graphicCard;

	}

	void setGraphicCard(string value)
	{
		_graphicCard = value;
	}

	long price()
	{
		return _price;

	}

	void setPrice(long value)
	{
		_price = value;
	}

	long sellPrice()
	{
		return _sellPrice;

	}

	void setSellPrice(long value)
	{
		_sellPrice = value;
	}

	int totalProduct()
	{
		return _totalProduct;

	}

	void setTotalProduct(int value)
	{
		_totalProduct = value;
	}
public:
	//Constructor and Destructor
	Laptop() {}

	Laptop(int id, string name, string cpu, string ram, string storage, string graphicCard, long price, long sellPrice, int totalProduct)
	{
		_id = id;
		_name = name;
		_cpu = cpu;
		_ram = ram;
		_storage = storage;
		_graphicCard = graphicCard;
		_price = price;
		_sellPrice = sellPrice;
		_totalProduct = totalProduct;
	}

	//Copy constructor
	Laptop(const Laptop& other)
	{
		_id = other._id;
		_name = other._name;
		_cpu = other._cpu;
		_ram = other._ram;
		_storage = other._storage;
		_graphicCard = other._graphicCard;
		_price = other._price;
		_sellPrice = other._sellPrice;
		_totalProduct = other._totalProduct;
	}

	~Laptop() {}
public:
	string toString()
	{
		stringstream builder;
		builder << _id << "," << _name << "," << _cpu << "," << _ram << "," << _storage << "," << _graphicCard
			<< "," << _price << "," << _sellPrice << "," << _totalProduct;
		return builder.str();
	}

	friend ostream& operator<<(ostream& out, const Laptop& lt)
	{
		out << lt._id;
		out << ",";
		out << lt._name;
		out << ",";
		out << lt._cpu;
		out << ",";
		out << lt._ram;
		out << ",";
		out << lt._storage;
		out << ",";
		out << lt._graphicCard;
		out << ",";
		out << lt._price;
		out << ",";
		out << lt._sellPrice;
		out << ",";
		out << lt._totalProduct;
		out << endl;
		return out;
	}

	const Laptop& operator=(const Laptop& other)
	{
		_id = other._id;
		_name = other._name;
		_cpu = other._cpu;
		_ram = other._ram;
		_storage = other._storage;
		_graphicCard = other._graphicCard;
		_price = other._price;
		_sellPrice = other._sellPrice;
		_totalProduct = other._totalProduct;

		return *this;
	}

	static shared_ptr<Laptop> parse(string buffer)
	{
		vector<string> tokens = Tokenizer::split(buffer, ",");
		
		int id = stoi(tokens[0]);
		long price = stol(tokens[6]);
		long sellPrice = stol(tokens[7]);
		int totalProduct = stoi(tokens[8]);
		auto  result = make_shared<Laptop>(id, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], price, sellPrice, totalProduct);
		
		return result;
	}
};

class Order
{
private:
	int _id;
	string _name;
	int _productId;
	int _quantity;
	int _total;
	bool _isPaid;
public:
	int quantity()
	{
		return _quantity;
	}
	bool isPaid()
	{
		return _isPaid;
	}
	int productId()
	{
		return _productId;
	}
	int total()
	{
		return _total;
	}
public:
	Order(){}

	Order(int id, string name, int productId, int quantity, int total, bool isPaid)
	{
		_id = id;
		_name = name;
		_productId = productId;
		_quantity = quantity;
		_total = total;
		_isPaid = isPaid;
	}

	//Copy constructor
	Order(const Order& other)
	{
		_id = other._id;
		_name = other._name;
		_productId = other._productId;
		_quantity = other._quantity;
		_total = other._total;
		_isPaid = other._isPaid;
	}

	~Order() {}
public:
	string toString()
	{
		stringstream builder;
		builder << _id << "," << _name << "," << _productId << "," << _quantity << "," << _total << "," << _isPaid;
		return builder.str();
	}


	const Order& operator=(const Order& other)
	{
		_id = other._id;
		_name = other._name;
		_productId = other._productId;
		_quantity = other._quantity;
		_total = other._total;
		_isPaid = other._isPaid;

		return *this;
	}

	static shared_ptr<Order> parse(string buffer)
	{
		vector<string> tokens = Tokenizer::split(buffer, ",");

		int id = stoi(tokens[0]);
		int productId = stoi(tokens[2]);
		int quantity = stoi(tokens[3]);
		int total = stoi(tokens[4]);
		bool isPaid = stoi(tokens[5]);
		auto  result = make_shared<Order>(id, tokens[1], productId, quantity, total, isPaid);

		return result;
	}
};

int main()
{
	string manufacturerSName;
	int id;
	string name;
	string cpu;
	string ram;
	string storage;
	string graphicCard;
	long price;
	long sellPrice;
	int totalProduct;


	int countManufacturers;							//Total number of manufacturers
	vector<string> manufacturers;					//Name of the manufaturers
	vector<int> countProducts;						//Count the model quantity of the same index(0,1,2...) manufacturer
	vector<vector<shared_ptr<Laptop>>> datas;		//Data of all the laptops
	string buffer;									//Buffer string
	vector<string> tempData;						//Temp data to convert string to int -> countProducts
	ifstream data("data.txt");						//File input
	//input countManufacturers
	getline(data, buffer);
	countManufacturers = stoi(buffer);
	//input all the Manufacturers
	getline(data, buffer);
	manufacturers = Tokenizer::split(buffer, ",");
	//input the countProducts for each manufacturer
	getline(data, buffer);
	tempData = Tokenizer::split(buffer, ",");
	for (int i = 0; i < countManufacturers; i++)
	{
		countProducts.push_back(stoi(tempData[i]));
	}

	//input data
	for (int i = 0; i < 20; i++)
	{
		datas.push_back(vector<shared_ptr<Laptop>>());
	}

	for (int i = countManufacturers; i < 20; i++)
	{
		countProducts[i] = 0;
	}

	for (int i = 0; i < countManufacturers; i++)
	{
		for (int j = 0; j < countProducts[i]; j++)
		{
			getline(data, buffer);
			datas[i].push_back(Laptop::parse(buffer));
		}
	}

	//cout << countManufacturers << endl;
	//
	//for (int i = 0; i < countManufacturers; i++)
	//{
	//	cout << manufacturers[i] << endl;
	//	for (int j = 0; j < countProducts[i]; j++)
	//	{
	//		cout << datas[i][j]->toString() << endl;
	//	}
	//}

	data.close();

	int oid;
	string oname;
	int oproductId;
	int oquantity;
	int ototal;
	bool oisPaid;

	int countCustomers;
	vector<shared_ptr<Order>> orders;

	ifstream in("order.txt");
	getline(in, buffer);
	countCustomers = stoi(buffer);
	for (int i = 0; i < countCustomers; i++)
	{
		getline(in, buffer);
		orders.push_back(Order::parse(buffer));
	}

	//--------------------------

	int menu_item = 0, x = 4;
	bool running = true;

	gotoXY(8, 4); cout << "->";

	while (running)
	{
		gotoXY(8, 2); cout << "LAPTOP STORE";

		gotoXY(10, 4);  cout << "MANUFACTURERS";
		gotoXY(10, 5);  cout << "ORDERS";
		gotoXY(10, 6); cout << "STATISTICS";
		gotoXY(10, 7); cout << "EXIT";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 7) //down button pressed
		{
			gotoXY(8, x); cout << "  ";
			x++;
			gotoXY(8, x); cout << "->";
			menu_item++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && x != 4) //up button pressed
		{
			gotoXY(8, x); cout << "  ";
			x--;
			gotoXY(8, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed

			switch (menu_item)
			{

			case 0:
			{
				//MANUFACTURERS
				int sub_menu_item1 = 0, x1 = 10;
				bool running1 = true;
				int pos1 = 19;

				gotoXY(10, 10); cout << "->";

				while (running1)
				{
					gotoXY(10, 9); cout << "MANUFACTURERS";

					gotoXY(12, 10); cout << "SEE ALL THE MANUFACTURERS";
					gotoXY(12, 11); cout << "ADD A MANUFACTURER";
					gotoXY(12, 12); cout << "DELETE A MANUFACTURER";
					gotoXY(12, 13); cout << "EDIT A MANUFACTURER";
					gotoXY(12, 14); cout << "ADD A LAPTOP";
					gotoXY(12, 15); cout << "DELETE A LAPTOP";
					gotoXY(12, 16); cout << "EDIT A LAPTOP";
					gotoXY(12, 17); cout << "EXIT";


					system("pause>nul"); // the >nul bit causes it the print no message

					if (GetAsyncKeyState(VK_DOWN) && x1 != 17) //down button pressed
					{
						gotoXY(10, x1); cout << "  ";
						x1++;
						gotoXY(10, x1); cout << "->";
						sub_menu_item1++;
						continue;
					}

					if (GetAsyncKeyState(VK_UP) && x1 != 10) //up button pressed
					{
						gotoXY(10, x1); cout << "  ";
						x1--;
						gotoXY(10, x1); cout << "->";
						sub_menu_item1--;
						continue;
					}

					if (GetAsyncKeyState(VK_RETURN))
					{ // Enter key pressed

						switch (sub_menu_item1)
						{

						case 0:
						{
							//SEE ALL THE MANUFACTURERS
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//------------------------------
							int sub_menu_item4 = 0, x4 = pos1;
							bool running4 = true;

							gotoXY(12, pos1); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos1) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos1 + 4 + countManufacturers);
										cout << manufacturers[sub_menu_item4 - 2] << " : " << countProducts[sub_menu_item4 - 2];
										if (countProducts[sub_menu_item4 - 2] > 0)
										{
											for (int i = 0; i < countProducts[sub_menu_item4 - 2]; i++)
											{
												gotoXY(16, pos1 + 5 + countManufacturers + i);
												cout << datas[sub_menu_item4 - 2][i]->toString();
											}
										}

										system("pause>nul");

										gotoXY(14, pos1 + 4 + countManufacturers);
										cout << "                                                            ";

										if (countProducts[sub_menu_item4 - 2] > 0)
										{
											for (int i = 0; i < countProducts[sub_menu_item4 - 2]; i++)
											{
												gotoXY(16, pos1 + 5 + countManufacturers + i);
												cout << "                                                                                                                                            ";
											}
										}
									}

									}

								}

							}

							break;
						}

						case 1:
						{
							//ADD A MANUFACTURER
							gotoXY(14, pos1);
							cout << "Input a manufacturer's name: ";
							getline(cin, manufacturerSName);
							manufacturers.push_back(manufacturerSName);
							countManufacturers++;
							gotoXY(14, pos1 + 1);
							cout << "A manufacturer has been added!";
							break;
						}

						case 2:
						{
							//DELETE A MANUFACTURER
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//--------------------

							int sub_menu_item4 = 0, x4 = pos1;
							bool running4 = true;

							gotoXY(12, pos1); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos1) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos1 + 4 + countManufacturers);
										vector<string>::iterator it = manufacturers.begin() + sub_menu_item4 - 2;
										manufacturers.erase(it);
										countManufacturers--;

										//for (int i = 0; i < countProducts[sub_menu_item4 - 2]; i++)
										//{
										//	datas[sub_menu_item4 - 2][i].reset();
										//}

										//vector<shared_ptr<Laptop>>::iterator lits = datas[sub_menu_item4 - 2].begin();
										//vector<shared_ptr<Laptop>>::iterator lite = datas[sub_menu_item4 - 2].end();

										//datas[sub_menu_item4 - 2].erase(lits, lite);

										//vector<int>::iterator iit = countProducts.begin() + sub_menu_item4 - 2;
										//countProducts.erase(iit);

										cout << "A manufacturer has been removed!";
										running4 = false;
										break;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}

							break;
						}

						case 3:
						{
							//EDIT A MANUFACTURER
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//--------------------

							int sub_menu_item5 = 0, x5 = pos1;
							bool running5 = true;

							gotoXY(12, pos1); cout << "->";

							while (running5)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x5 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x5); cout << "  ";
									x5++;
									gotoXY(12, x5); cout << "->";
									sub_menu_item5++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x5 != pos1) //up button pressed
								{
									gotoXY(12, x5); cout << "  ";
									x5--;
									gotoXY(12, x5); cout << "->";
									sub_menu_item5--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item5)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running5 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos1 + 4 + countManufacturers);
										string newname;
										cout << "Input new name: ";
										getline(cin, newname);
										manufacturers[sub_menu_item5 - 2] = newname;
										gotoXY(14, pos1 + 5 + countManufacturers);
										cout << "A manufacturer's name has been changed!";
										running5 = false;
										break;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}


							break;
						}

						case 4:
						{
							//ADD A LAPTOP
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//------------------------------
							int sub_menu_item4 = 0, x4 = pos1;
							bool running4 = true;

							gotoXY(12, pos1); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos1) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos1 + 4 + countManufacturers);
										cout << "Input id: "; cin >> id;
										cin.ignore();
										gotoXY(14, pos1 + 5 + countManufacturers);
										cout << "Input name: "; getline(cin, name);
										gotoXY(14, pos1 + 6 + countManufacturers);
										cout << "Input cpu: "; getline(cin, cpu);
										gotoXY(14, pos1 + 7 + countManufacturers);
										cout << "Input ram: "; getline(cin, ram);
										gotoXY(14, pos1 + 8 + countManufacturers);
										cout << "Input storage: "; getline(cin, storage);
										gotoXY(14, pos1 + 9 + countManufacturers);
										cout << "Input graphic card: "; getline(cin, graphicCard);
										gotoXY(14, pos1 + 10 + countManufacturers);
										cout << "Input price: "; cin >> price;
										gotoXY(14, pos1 + 11 + countManufacturers);
										cout << "Input sell price: "; cin >> sellPrice;
										gotoXY(14, pos1 + 12 + countManufacturers);
										cout << "Input total product: "; cin >> totalProduct;
										cin.ignore();

										datas[sub_menu_item4 - 2].push_back(make_shared<Laptop>(id, name, cpu, ram, storage, graphicCard, price, sellPrice, totalProduct));
										countProducts[sub_menu_item4 - 2]++;
										gotoXY(14, pos1 + 13 + countManufacturers);
										cout << "A new laptop has been added!";

										running4 = false;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}

							break;

						}

						case 5:
						{
							//DELETE A LAPTOP
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//------------------------------
							int sub_menu_item4 = 0, x4 = pos1;
							bool running4 = true;

							gotoXY(12, pos1); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos1) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(16, pos1 + 4 + countManufacturers);
										cout << "EXIT";

										if (countProducts[sub_menu_item4 - 2] > 0)
										{
											for (int i = 0; i < countProducts[sub_menu_item4 - 2]; i++)
											{
												gotoXY(16, pos1 + 6 + countManufacturers + i);
												cout << datas[sub_menu_item4 - 2][i]->toString();
											}
										}

										
										gotoXY(14, pos1);
										cout << "EXIT";
										for (int i = 0; i < countManufacturers; i++)
										{
											gotoXY(14, pos1 + 2 + i);
											cout << manufacturers[i];
										}

										//------------------------------
										int sub_menu_item5 = 0, x5 = pos1 + 4 + countManufacturers;
										bool running5 = true;

										gotoXY(14, pos1 + 4 + countManufacturers); cout << "->";

										while (running5)
										{

											system("pause>nul"); // the >nul bit causes it the print no message

											if (GetAsyncKeyState(VK_DOWN) && x5 != pos1 + 4 + countManufacturers + 1 + countProducts[sub_menu_item4 - 2]) //down button pressed
											{
												gotoXY(14, x5); cout << "  ";
												x5++;
												gotoXY(14, x5); cout << "->";
												sub_menu_item5++;
												continue;
											}

											if (GetAsyncKeyState(VK_UP) && x5 != pos1 + 4 + countManufacturers) //up button pressed
											{
												gotoXY(14, x5); cout << "  ";
												x5--;
												gotoXY(14, x5); cout << "->";
												sub_menu_item5--;
												continue;
											}

											if (GetAsyncKeyState(VK_RETURN))
											{ // Enter key pressed

												switch (sub_menu_item5)
												{

												case 0:
												{
													//EXIT
													gotoXY(14, pos1 + 4 + countManufacturers);
													running4 = false;
													break;
												}

												case 1:
												{
													//Do nothing
													break;
												}

												default:
												{
													//Any other cases
													gotoXY(18, pos1 + 4 + countManufacturers + 4 + countManufacturers);
													vector<shared_ptr<Laptop>>::iterator it = datas[sub_menu_item4 - 2].begin() + sub_menu_item5 - 2;
													datas[sub_menu_item4 - 2].erase(it);
													countProducts[sub_menu_item4 - 2]--;
													cout << "A laptop has been removed!";
													running5 = false;
													break;


												}

												}

												//system("pause>nul");
												//system("cls");


											}

										}


										running4 = false;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}

							break;

						}

						case 6:
						{
							//EDIT A LAPTOP
							gotoXY(14, pos1);
							cout << "EXIT";
							for (int i = 0; i < countManufacturers; i++)
							{
								gotoXY(14, pos1 + 2 + i);
								cout << manufacturers[i];
							}

							//------------------------------
							int sub_menu_item4 = 0, x4 = pos1;
							bool running4 = true;

							gotoXY(12, pos1); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos1 + 1 + countManufacturers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos1) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos1 + 4 + countManufacturers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(16, pos1 + 4 + countManufacturers);
										cout << "EXIT";

										if (countProducts[sub_menu_item4 - 2] > 0)
										{
											for (int i = 0; i < countProducts[sub_menu_item4 - 2]; i++)
											{
												gotoXY(16, pos1 + 6 + countManufacturers + i);
												cout << datas[sub_menu_item4 - 2][i]->toString();
											}
										}


										gotoXY(14, pos1);
										cout << "EXIT";
										for (int i = 0; i < countManufacturers; i++)
										{
											gotoXY(14, pos1 + 2 + i);
											cout << manufacturers[i];
										}

										//------------------------------
										int sub_menu_item5 = 0, x5 = pos1 + 4 + countManufacturers;
										bool running5 = true;

										gotoXY(14, pos1 + 4 + countManufacturers); cout << "->";

										while (running5)
										{

											system("pause>nul"); // the >nul bit causes it the print no message

											if (GetAsyncKeyState(VK_DOWN) && x5 != pos1 + 4 + countManufacturers + 1 + countProducts[sub_menu_item4 - 2]) //down button pressed
											{
												gotoXY(14, x5); cout << "  ";
												x5++;
												gotoXY(14, x5); cout << "->";
												sub_menu_item5++;
												continue;
											}

											if (GetAsyncKeyState(VK_UP) && x5 != pos1 + 4 + countManufacturers) //up button pressed
											{
												gotoXY(14, x5); cout << "  ";
												x5--;
												gotoXY(14, x5); cout << "->";
												sub_menu_item5--;
												continue;
											}

											if (GetAsyncKeyState(VK_RETURN))
											{ // Enter key pressed

												switch (sub_menu_item5)
												{

												case 0:
												{
													//EXIT
													gotoXY(14, pos1 + 4 + countManufacturers);
													running5 = false;
													break;
												}

												case 1:
												{
													//Do nothing
													break;
												}

												default:
												{
													//Any other cases
													gotoXY(18, pos1 + 4 + countManufacturers + 4 + countManufacturers);
													cout << "Input new id: "; cin >> id;
													cin.ignore();
													gotoXY(18, pos1 + 5 + countManufacturers + 4 + countManufacturers);
													cout << "Input new name: "; getline(cin, name);
													gotoXY(18, pos1 + 6 + countManufacturers + 4 + countManufacturers);
													cout << "Input new cpu: "; getline(cin, cpu);
													gotoXY(18, pos1 + 7 + countManufacturers + 4 + countManufacturers);
													cout << "Input new ram: "; getline(cin, ram);
													gotoXY(18, pos1 + 8 + countManufacturers + 4 + countManufacturers);
													cout << "Input new storage: "; getline(cin, storage);
													gotoXY(18, pos1 + 9 + countManufacturers + 4 + countManufacturers);
													cout << "Input new graphic card: "; getline(cin, graphicCard);
													gotoXY(18, pos1 + 10 + countManufacturers + 4 + countManufacturers);
													cout << "Input new price: "; cin >> price;
													gotoXY(18, pos1 + 11 + countManufacturers + 4 + countManufacturers);
													cout << "Input new sell price: "; cin >> sellPrice;
													gotoXY(18, pos1 + 12 + countManufacturers + 4 + countManufacturers);
													cout << "Input new total product: "; cin >> totalProduct;
													cin.ignore();

													datas[sub_menu_item4 - 2][sub_menu_item5 - 2] = make_shared<Laptop>(id, name, cpu, ram, storage, graphicCard, price, sellPrice, totalProduct);
													gotoXY(18, pos1 + 13 + countManufacturers + 4 + countManufacturers);
													cout << "A laptop has been updated!";

													running5 = false;
													break;


												}

												}

												//system("pause>nul");
												//system("cls");


											}

										}


										running4 = false;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}

							break;
						}

						case 7:
						{
							//EXIT
							gotoXY(14, 16);
							running1 = false;
							break;
						}

						}

						system("pause>nul");
						system("cls");


					}

				}

				break;
			}

			case 1:
			{
				//ORDERS
				int sub_menu_item2 = 0, x2 = 10;
				bool running2 = true;
				int pos2 = 16;

				gotoXY(10, 10); cout << "->";

				while (running2)
				{
					gotoXY(10, 9); cout << "ORDERS";

					gotoXY(12, 10);  cout << "SEE ALL THE ORDERS";
					gotoXY(12, 11);  cout << "ADD A ORDER";
					gotoXY(12, 12); cout << "DELETE A ORDER";
					gotoXY(12, 13); cout << "EDIT A ORDER";
					gotoXY(12, 14); cout << "EXIT";


					system("pause>nul"); // the >nul bit causes it the print no message

					if (GetAsyncKeyState(VK_DOWN) && x2 != 14) //down button pressed
					{
						gotoXY(10, x2); cout << "  ";
						x2++;
						gotoXY(10, x2); cout << "->";
						sub_menu_item2++;
						continue;
					}

					if (GetAsyncKeyState(VK_UP) && x2 != 10) //up button pressed
					{
						gotoXY(10, x2); cout << "  ";
						x2--;
						gotoXY(10, x2); cout << "->";
						sub_menu_item2--;
						continue;
					}

					if (GetAsyncKeyState(VK_RETURN))
					{ // Enter key pressed

						switch (sub_menu_item2)
						{

						case 0:
						{
							//SEE ALL THE ORDERS
							gotoXY(14, pos2);
							cout << "EXIT";
							for (int i = 0; i < countCustomers; i++)
							{
								gotoXY(14, pos2 + 2 + i);
								cout << orders[i]->toString();
							}

							break;
						}

						case 1:
						{
							//ADD AN ORDER
							gotoXY(14, pos2);
							cout << "Input id: "; cin >> oid;
							cin.ignore();
							gotoXY(14, pos2 + 1);
							cout << "Input customer's name: ";
							getline(cin, oname);
							gotoXY(14, pos2 + 2);
							cout << "Input product's id: "; cin >> oproductId;
							gotoXY(14, pos2 + 3);
							cout << "Input quantity: "; cin >> oquantity;
							gotoXY(14, pos2 + 4);
							cout << "Input the total price: "; cin >> ototal;
							gotoXY(14, pos2 + 5);
							cout << "Pay now(1:yes/0:no): "; cin >> oisPaid;
							cin.ignore();

							orders.push_back(make_shared<Order>(oid, oname, oproductId, oquantity, ototal, oisPaid));
							countCustomers++;
							gotoXY(14, pos2 + 7);
							cout << "An order has been added!";

							break;
						}

						case 2:
						{
							//DELETE AN ORDER
							gotoXY(14, pos2);
							cout << "EXIT";
							for (int i = 0; i < countCustomers; i++)
							{
								gotoXY(14, pos2 + 2 + i);
								cout << orders[i]->toString();
							}

							//--------------------

							int sub_menu_item4 = 0, x4 = pos2;
							bool running4 = true;

							gotoXY(12, pos2); cout << "->";

							while (running4)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x4 != pos2 + 1 + countCustomers) //down button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4++;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x4 != pos2) //up button pressed
								{
									gotoXY(12, x4); cout << "  ";
									x4--;
									gotoXY(12, x4); cout << "->";
									sub_menu_item4--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item4)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos2 + 4 + countCustomers);
										running4 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos2 + 4 + countCustomers);
										vector<shared_ptr<Order>>::iterator it = orders.begin() + sub_menu_item4 - 2;
										orders.erase(it);
										countCustomers--;
										cout << "An order has been removed!";
										running4 = false;
										break;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}

							break;
						}

						case 3:
						{
							//EDIT AN ORDER
							gotoXY(14, pos2);
							cout << "EXIT";
							for (int i = 0; i < countCustomers; i++)
							{
								gotoXY(14, pos2 + 2 + i);
								cout << orders[i]->toString();
							}

							//--------------------

							int sub_menu_item5 = 0, x5 = pos2;
							bool running5 = true;

							gotoXY(12, pos2); cout << "->";

							while (running5)
							{

								system("pause>nul"); // the >nul bit causes it the print no message

								if (GetAsyncKeyState(VK_DOWN) && x5 != pos2 + 1 + countCustomers) //down button pressed
								{
									gotoXY(12, x5); cout << "  ";
									x5++;
									gotoXY(12, x5); cout << "->";
									sub_menu_item5++;
									continue;
								}

								if (GetAsyncKeyState(VK_UP) && x5 != pos2) //up button pressed
								{
									gotoXY(12, x5); cout << "  ";
									x5--;
									gotoXY(12, x5); cout << "->";
									sub_menu_item5--;
									continue;
								}

								if (GetAsyncKeyState(VK_RETURN))
								{ // Enter key pressed

									switch (sub_menu_item5)
									{

									case 0:
									{
										//EXIT
										gotoXY(14, pos2 + 4 + countCustomers);
										running5 = false;
										break;
									}

									case 1:
									{
										//Do nothing
										break;
									}

									default:
									{
										//Any other cases
										gotoXY(14, pos2 + 4 + countCustomers);
										cout << "Input new id: "; cin >> oid;
										cin.ignore();
										gotoXY(14, pos2 + 5 + countCustomers);
										cout << "Input new customer's name: ";
										getline(cin, oname);
										gotoXY(14, pos2 + 6 + countCustomers);
										cout << "Input new product's id: "; cin >> oproductId;
										gotoXY(14, pos2 + 7 + countCustomers);
										cout << "Input new quantity: "; cin >> oquantity;
										gotoXY(14, pos2 + 8 + countCustomers);
										cout << "Input new the total price: "; cin >> ototal;
										gotoXY(14, pos2 + 9 + countCustomers);
										cout << "Pay now(1:yes/0:no): "; cin >> oisPaid;
										cin.ignore();

										orders[sub_menu_item5 - 2] = make_shared<Order>(oid, oname, oproductId, oquantity, ototal, oisPaid);
										gotoXY(14, pos2 + 11 + countCustomers);
										cout << "An order has been changed!";
										running5 = false;
										break;
									}

									}

									//system("pause>nul");
									//system("cls");


								}

							}


							break;
						}

						case 4:
						{
							//EXIT
							gotoXY(14, 16);
							running2 = false;
							break;
						}

						}

						system("pause>nul");
						system("cls");


					}


				}

				break;

			}

			case 2:
			{
				//STATISTICS
				int sub_menu_item3 = 0, x3 = 10;
				bool running3 = true;
				int pos3 = 19;

				gotoXY(10, 10); cout << "->";

				while (running3)
				{
					gotoXY(10, 9); cout << "STATISTICS";

					gotoXY(12, 10);  cout << "ABOUT TO RUN OUT OF STOCK";
					gotoXY(12, 11);  cout << "MOST SOLD";
					gotoXY(12, 12); cout << "REVENUE AND PROFIT OF THE MONTH";
					gotoXY(12, 13); cout << "EXIT";


					system("pause>nul"); // the >nul bit causes it the print no message

					if (GetAsyncKeyState(VK_DOWN) && x3 != 13) //down button pressed
					{
						gotoXY(10, x3); cout << "  ";
						x3++;
						gotoXY(10, x3); cout << "->";
						sub_menu_item3++;
						continue;
					}

					if (GetAsyncKeyState(VK_UP) && x3 != 10) //up button pressed
					{
						gotoXY(10, x3); cout << "  ";
						x3--;
						gotoXY(10, x3); cout << "->";
						sub_menu_item3--;
						continue;
					}

					if (GetAsyncKeyState(VK_RETURN))
					{ // Enter key pressed

						switch (sub_menu_item3)
						{

						case 0:
						{
							//ABOUT TO RUN OUT OF STOCK
							int increase = 0;
							for (int i = 0; i < countManufacturers; i++)
							{
								
								for (int j = 0; j < countProducts[i]; j++)
								{
									
									if (datas[i][j]->totalProduct() < 10)
									{
										gotoXY(14, pos3 + increase);
										cout << datas[i][j]->toString();
										increase++;
									}
								}
							}

							break;
						}

						case 1:
						{
							//MOST SOLD
							int mostSold = -1;
							int id = -1;
							for (int i = 0; i < countCustomers; i++)
							{
								if (orders[i]->quantity() > mostSold && orders[i]->isPaid() == TRUE)
								{
									mostSold = orders[i]->quantity();
									id = orders[i]->productId();
								}
							}
							gotoXY(14, pos3);
							cout << "Most sold of the month: " << mostSold;
							gotoXY(14, pos3 + 1);
							for (int i = 0; i < countManufacturers; i++)
							{

								for (int j = 0; j < countProducts[i]; j++)
								{

									if (datas[i][j]->id() == id)
									{
										cout << datas[i][j]->toString();
									}
								}
							}

							break;
						}

						case 2:
						{
							int revenue = 0;
							int sum = 0;
							//REVENUE AND PROFIT OF THE MONTH
							for (int i = 0; i < countCustomers; i++)
							{
								revenue += orders[i]->total();
								sum += orders[i]->quantity();
							}
							gotoXY(14, pos3);
							cout << "Revenue of the month: " << revenue;
							gotoXY(14, pos3 + 1);
							cout << "Profit of the month: " << sum*3000000;

							break;
						}

						case 3:
						{
							//EXIT
							gotoXY(14, 16);
							running3 = false;

							break;
						}

						}

						system("pause>nul");
						system("cls");


					}

				}

				break;
			}

			case 3:
			{
				//EXIT
				gotoXY(10, 10);
				running = false;
				break;
			}

			}

			system("pause>nul");
			system("cls");
		}

	}

	ofstream out("data.txt");
	out << countManufacturers << endl;
	for (int i = 0; i < countManufacturers; i++)
	{
		if (i < countManufacturers - 1)
		{
			out << manufacturers[i] << ",";

		}
		else
		{
			out << manufacturers[i] << endl;
		}
	}

	for (int i = 0; i < countManufacturers; i++)
	{
		if (i < countManufacturers - 1)
		{
			out << countProducts[i] << ",";

		}
		else
		{
			out << countProducts[i] << endl;
		}
	}

	for (int i = 0; i < countManufacturers; i++)
	{
		for (int j = 0; j < countProducts[i]; j++)
		{
			out << datas[i][j]->toString() << endl;
		}
	}

	out.close();

	ofstream out2("order.txt");
	out2 << countCustomers << endl;
	for (int i = 0; i < countCustomers; i++)
	{
		out2 << orders[i]->toString() << endl;
	}

	out2.close();

	gotoXY(50, 10);
	cout << "GOODBYE!" << endl;
	system("pause>nul");
	return 0;
}