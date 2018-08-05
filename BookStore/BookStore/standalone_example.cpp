
/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
Include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/tokenizer.hpp>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	cout << endl;
	//cout << "Let's have MySQL count from 10 to 1..." << endl;

	try {
		sql::Driver *driver;
		sql::Connection *con;

		sql::ConnectOptionsMap connection_properties;

		connection_properties["hostName"] = "tcp://127.0.0.1/";
		connection_properties["port"] = 3306;
		connection_properties["OPT_RECONNECT"] = true;

		sql::Statement *stmt;
		sql::ResultSet *res, *res1;
		sql::PreparedStatement *pstmt, *pstmt1;

		if (argc >= 3) {
			connection_properties["password"] = argv[2];
		} 
		 if (argc >= 2) {
			connection_properties["userName"] = argv[1];
		} else {
			connection_properties["userName"] = "root";
		}
		
		/* Create a connection */
		driver = get_driver_instance();
		//con = driver->connect("tcp://127.0.0.1:3306", user, pw);
		con = driver->connect(connection_properties);
		/* Connect to the MySQL test database */

		con->setSchema("bookstore");
		int i = 0;
		string date1, date2, year;
		int n, max, id, book_id;
		float book_price, sum, discount;
		char buf[100];
		std::string title;
				
		while (i != 99)
		{
			system("cls");
			cout << "Menu" << endl << endl;
			cout << "1.  Books in stock" << endl;
			cout << "2.  Open orders" << endl;
			cout << "3.  Customers who have bought at least one book" << endl;
			cout << "4.  Suppliers" << endl;
			cout << "5.  Orders between two dates" << endl;
			cout << "6.  Books with global discount" << endl;
			cout << "7.  Check if a book is in stock" << endl;
			cout << "8.  Suppliers of a book" << endl;
			cout << "9.  Number of copies of a book sold since a given date" << endl;
			cout << "10. Number of books bought by a specific customer since a given date" << endl;
			cout << "11. The customer who bought the largest amount of books since a given date" << endl;
			cout << "12. The supplier who supplied the largest amount of books since a given date" << endl;
			cout << "13. Number of customer orders between two dates" << endl;
			cout << "14. Number of commited customer orders between two dates" << endl;
			cout << "15. Discount a specific customer got since a given date" << endl;
			cout << "16. Quarterly income before discount for a given year" << endl;
			cout << "17. Number of new customers who joined since a given date" << endl;
			cout << "18. Total sum of purchases from a given supplier between given dates" << endl;
			cout << "19. Total sales of a given employee between given dates" << endl;
			cout << "20. Top 10 bestsellers between given dates" << endl;
			cout << "99. Exit" << endl << endl;
			cout << "Choose an option: ";
			cin >> i;
			switch (i) {
				case 1:
					cout << "Books in stock:" << endl << endl;

					pstmt = con->prepareStatement("Select * from books where quantity_in_stock > 0");
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("book_id") << "\t" << res->getString("title") << "\t" << res->getString("author") << endl;
					break;
				case 2:
					cout << "Open orders:" << endl << endl;
					//pstmt = con->prepareStatement("Select order_id, end_status, description from orders, status_codes where end_status=status_code and end_status<>1");
					pstmt = con->prepareStatement("Select order_id, end_status, description from orders, status_codes where end_status=status and end_status<>1");
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("order_id") << "\t" << res->getString("description") << endl;
					break;
				case 3:
					cout << "Customers who have bought at least one book:" << endl << endl;
					//select only customers who have any end_status=1 in the orders table. only them have bought something.
					pstmt = con->prepareStatement("Select * from customers where customer_id in (select customer_id from orders where end_status=1)");
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("customer_id") << "\t" << res->getString("lname") << "\t" << res->getString("fname") << endl;
					break;
				case 4:
					cout << "Suppliers:" << endl << endl;
					pstmt = con->prepareStatement("Select * from suppliers");
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("supplier_id") << "\t" << res->getString("supplier_name") << endl;
					break;
				case 5:
					cout << "Orders between two dates:" << endl << endl;
					cout << "enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select * from orders where date between ? and ?");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("order_id") << endl;
					break;
				case 6:
					cout << "Books with global discount:" << endl << endl;
					pstmt = con->prepareStatement("Select * from books where global_discount > 0");
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("book_id") << "\t" << res->getString("title") << "\t" << res->getString("author") << endl;
					break;
				case 7:
					cout << "Check if a book is in stock:" << endl << endl;
					cout << "Enter book title: ";
					cin.getline(buf, sizeof(buf));
					if (strlen(buf) == 0)
						cin.getline(buf, sizeof(buf));
					title = string(buf);
					//cin >> title;
					pstmt = con->prepareStatement("Select * from books where title = ?");
					pstmt->setString(1, title);
					res = pstmt->executeQuery();
					//res->beforeFirst();
					if (res->rowsCount() > 0)
						cout << "Book is in stock." << endl;
					else
						cout<< "Book isn't in stock." << endl;
					break;
				case 8:
					cout << "Suppliers of a book:" << endl << endl;
					cout << "Enter book title: ";
					cin.getline(buf, sizeof(buf));
					if (strlen(buf) == 0)
						cin.getline(buf, sizeof(buf));
					title = string(buf);
					//cin >> title;
					pstmt = con->prepareStatement("Select * from books where title = ?");
					pstmt->setString(1, title);
					res = pstmt->executeQuery();
					if (res->rowsCount() == 0) {
						cout << "No supplier supplies this book." << endl;
						break;
					}
					res->beforeFirst();
					res->first();
					n = res->getInt("book_id");
					delete pstmt;
					delete res;
					pstmt = con->prepareStatement("Select * from suppliers where supplier_id in (select supplier_id from booksuppliers where book_id = ?)");
					pstmt->setInt(1, n);
					res = pstmt->executeQuery();
					while (res->next())
						cout << res->getString("supplier_name") << endl;
					break;
				case 9:
					cout << "Number of copies of a book sold since a given date:" << endl << endl;
					cout << "Enter title: ";
					cin.getline(buf, sizeof(buf));
					if(strlen(buf)==0)
						cin.getline(buf, sizeof(buf));
					title = string(buf);
					//cin>>title;
					cout << endl << "Enter date (YYYY-MM-DD): ";
					cin >> date1;
					pstmt = con->prepareStatement("Select * from books where title = ?");
					pstmt->setString(1, title);
					res = pstmt->executeQuery();
					res->first();
					n = res->getInt("book_id");
					delete pstmt;
					delete res;
					pstmt = con->prepareStatement("Select sum(quantity) as copies from orderdetails where book_id = ? and order_id in(select order_id from orders where end_status = 1 and date > ?)");
					pstmt->setInt(1, n);
					pstmt->setString(2, date1);
					res = pstmt->executeQuery();
					//res->beforeFirst();
					res->first();
					cout << res->getInt("copies") << endl;
					break;
				case 10:
					cout << "Number of books bought by a specific customer since a given date:" << endl << endl;
					cout << "Enter customer id: ";
					cin >> n;
					cout << endl << "Enter date (YYYY-MM-DD): ";
					cin >> date1;
					pstmt = con->prepareStatement("Select sum(quantity) as copies from orderdetails where order_id in (select order_id from orders where customer_id = ? and end_status = 1 and date > ?)");
					pstmt->setInt(1, n);
					pstmt->setString(2, date1);
					res = pstmt->executeQuery();
					//res->beforeFirst();
					res->first();
					cout << res->getInt("copies") << endl;
					break;
				case 11:
					//use case 10. run a loop over all customers, find the one who bought largest amount and get his details.
					cout << "The customer who bought the largest amount of books since a given date:" << endl << endl;
					max = 0;
					cout << endl << "Enter date (YYYY-MM-DD): ";
					cin >> date1;
					pstmt1 = con->prepareStatement("Select customer_id from customers");
					res1 = pstmt1->executeQuery();
					res1->beforeFirst();
					while (res1->next()) {
						n = res1->getInt("customer_id");
						pstmt = con->prepareStatement("Select sum(quantity) as copies from orderdetails where order_id in (select order_id from orders where customer_id = ? and end_status = 1 and date > ?)");
						pstmt->setInt(1, n);
						pstmt->setString(2, date1);
						res = pstmt->executeQuery();
						res->first();
						n = res->getInt("copies");
						if (n > max) {
							max = n;
							id = res1->getInt("customer_id");
						}
					}
					delete pstmt1;
					delete res1;
					pstmt1 = con->prepareStatement("Select * from customers where customer_id = ?");
					pstmt1->setInt(1, id);
					res1 = pstmt1->executeQuery();
					res1->first();
					cout << res1->getInt("customer_id") << "\t" << res1->getString("lname") << "\t" << res1->getString("fname") << endl << endl;
					break;
				case 12:
					cout << "The supplier who supplied the largest amount of books since a given date:" << endl << endl;
					max = 0;
					cout << endl << "Enter date (YYYY-MM-DD): ";
					cin >> date1;
					pstmt1 = con->prepareStatement("Select supplier_id from suppliers");
					res1 = pstmt1->executeQuery();
					res1->beforeFirst();
					while (res1->next()) {
						n = res1->getInt("supplier_id");
						pstmt = con->prepareStatement("Select sum(quantity) as copies from ordersfromsuppliersdetails where order_id in (select order_id from orders_from_suppliers where supplier_id = ? and status = 1 and date > ?)");
						pstmt->setInt(1, n);
						pstmt->setString(2, date1);
						res = pstmt->executeQuery();
						res->first();
						n = res->getInt("copies");
						if (n > max) {
							max = n;
							id = res1->getInt("supplier_id");
						}
					}
					delete pstmt1;
					delete res1;
					pstmt1 = con->prepareStatement("Select * from suppliers where supplier_id = ?");
					pstmt1->setInt(1, id);
					res1 = pstmt1->executeQuery();
					res1->first();
					cout << res1->getInt("supplier_id") << "\t" << res1->getString("supplier_name") << endl << endl;
					break;
				case 13:
					cout << "Number of customer orders between two dates:" << endl << endl;
					cout << "enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select count(*) as num_orders from orders where date between ? and ?");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->first();
					cout << res->getInt("num_orders") << endl;
					break;
				case 14:
					cout << "Number of commited customer orders between two dates:" << endl << endl;
					cout << "enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select count(*) as num_orders from orders where end_status=1 and date between ? and ?");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->first();
					cout << res->getInt("num_orders") << endl;
					break;
				case 15:
					//find first the full price of the books purchased, then calculate the discount.
					cout << "Discount a specific customer got since a given date:" << endl << endl;
					cout << "Enter customer id: ";
					cin >> id;
					cout << "Enter date: ";
					cin >> date1;
					//find discount percent for this customer
					pstmt1 = con->prepareStatement("Select * from customers where customer_id = ?");
					pstmt1->setInt(1, id);
					res1 = pstmt1->executeQuery();
					res1->first();
					discount = res1->getDouble("discount");
					delete pstmt1;
					delete res1;
					//now find all relevant rows in orderdetails
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where customer_id = ? and end_status=1 and date >= ?)");
					pstmt->setInt(1, id);
					pstmt->setString(2, date1);
					res = pstmt->executeQuery();
					res->beforeFirst();
					//now we have a row for every book bought by the customer starting with the given date.
					//get quantity from the row, use book_id to find the book price from the book table, multiply and add to the sum.
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select * from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << "Total discount: " << sum*discount/100 << endl << endl;
					break;
				case 16:
					cout << "Quarterly income before discount for a given year:" << endl << endl;
					cout << "enter year (YYYY): ";
					cin >> year;
					//Q1 income
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where end_status=1 and date between ? and ?)");
					date1 = year;
					date2 = year;
					date1.append("-01-01");
					date2.append("-03-30");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select * from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << "Q1: " << sum << endl;
					delete pstmt;
					delete res;
					
					//Q2 income
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where end_status=1 and date between ? and ?)");
					date1 = year;
					date2 = year;
					date1.append("-04-01");
					date2.append("-06-30");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select * from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << "Q2: " << sum << endl;
					delete pstmt;
					delete res;

					//Q3 income
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where end_status=1 and date between ? and ?)");
					date1 = year;
					date2 = year;
					date1.append("-07-01");
					date2.append("-09-30");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select * from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << "Q3: " << sum << endl;
					delete pstmt;
					delete res;

					//Q4 income
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where end_status=1 and date between ? and ?)");
					date1 = year;
					date2 = year;
					date1.append("-10-01");
					date2.append("-12-30");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select * from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << "Q4: " << sum << endl;
					delete pstmt;
					delete res;
					break;
				case 17:
					cout << "Number of new customers who joined since a given date:" << endl << endl;
					cout << "enter date (YYYY-MM-DD): ";
					cin >> date1;
					pstmt = con->prepareStatement("Select count(*) as num_customers from customers where join_date >= ?");
					pstmt->setString(1, date1);
					res = pstmt->executeQuery();
					res->first();
					cout << res->getInt("num_customers") << endl;
					break;
				case 18:
					cout << "Total sum of purchases from a given supplier between given dates:" << endl << endl;
					cout << "Enter supplier id: ";
					cin >> id;
					cout << "Enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "Enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select * from ordersfromsuppliersdetails where order_id in (Select order_id from orders_from_suppliers where supplier_id = ? and date between ? and ?)");
					pstmt->setInt(1, id);
					pstmt->setString(2, date1);
					pstmt->setString(3, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select price from booksuppliers where book_id = ? and supplier_id = ?");
						pstmt1->setInt(1, book_id);
						pstmt1->setInt(2, id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << sum << endl;
					break;
				case 19:
					cout << "Total sales of a given employee between given dates:" << endl << endl;
					cout << "Enter employee id: ";
					cin >> id;
					cout << "Enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "Enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select * from orderdetails where order_id in (select order_id from orders where employee_id = ? and end_status = 1 and date between ? and ?)");
					pstmt->setInt(1, id);
					pstmt->setString(2, date1);
					pstmt->setString(3, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					sum = 0;
					while (res->next()) {
						book_id = res->getInt("book_id");
						n = res->getInt("quantity");
						pstmt1 = con->prepareStatement("Select price from books where book_id = ?");
						pstmt1->setInt(1, book_id);
						res1 = pstmt1->executeQuery();
						res1->first();
						book_price = res1->getDouble("price");
						sum += n * book_price;
						delete pstmt1;
						delete res1;
					}
					cout << sum << endl;
					break;
				case 20:
					cout << "Top 10 bestsellers between given dates:" << endl << endl;
					cout << "Enter first date (YYYY-MM-DD): ";
					cin >> date1;
					cout << "Enter second date (YYYY-MM-DD): ";
					cin >> date2;
					pstmt = con->prepareStatement("Select book_id, count(quantity) as sold from orderdetails where order_id in(select order_id from orders where end_status = 1 and date between ? and ?) group by book_id order by sold desc limit 10");
					pstmt->setString(1, date1);
					pstmt->setString(2, date2);
					res = pstmt->executeQuery();
					res->beforeFirst();
					while (res->next())
						cout << res->getInt("book_id")<<endl;
					break;
				case 99:
					exit(0);
			}
			cout << endl << "Enter any number to continue: ";
			cin >> i;
		}



		/* Select in ascending order */
		pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC");
		res = pstmt->executeQuery();
		
		/* Fetch in reverse = descending order! */
		res->afterLast();
		while (res->previous())
			cout << "\t... MySQL counts: " << res->getInt("id") << endl;
		delete res;

		delete pstmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;
	getchar();
	return EXIT_SUCCESS;
}
