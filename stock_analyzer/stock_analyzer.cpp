// stock_analyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include "stock.h"

using namespace std;

vector<stock> st;	// making a vector of objects from the stock class (see stock.h and stock.cpp)

void set_stock_symbols();
void load_stock_data();
void dump_errors();
void analyze_stocks();

int main()
{
	cout << "setting stock symbols..." << endl;
	set_stock_symbols();
	cout << "setting stock symbols...[ok]" << endl;
	cout << "Loading stock data..." << endl;
	cout << "...[ok]" << endl;
	//analyze_stocks();
	dump_errors();
    return 0;
}

void set_stock_symbols() {
	struct stocks {
		vector<string> stock_names;
	} all;

	ifstream fin;
	fin.open("U:\\html\\ggi_root\\home\\greyhau1\\scraper\\py\\stock.csv");
	cout << "Opening file [stock.csv]...";
	if (fin.is_open()) {
		cout << "[ok]" << endl;
		string temp;
		getline(fin, temp);
		fin.close();
		while (temp.size() > 0) {
			int found = temp.find(",");
			if (found != string::npos) {
				all.stock_names.push_back(temp.substr(0, found));
				found++;
				temp.erase(0, found);
			}
			else {
				break;
			}
		}
	}
	else {
		cout << "[fail]" << endl;
		system("PAUSE");
	}
	st.resize(all.stock_names.size());
	for (int i = 0; i < all.stock_names.size(); i++) {
		st[i].set_name(all.stock_names[i]);
	}
}

void load_stock_data() {
	for (int i = 0; i < st.size(); i++) {
		st[i].load_data();
	}
}

void dump_errors() {
	time_t t = time(0);   // get current date
	struct tm now;
	localtime_s(&now, &t);
	string date = boost::lexical_cast<string>(now.tm_year + 1900) + "-" + boost::lexical_cast<string>(now.tm_mon + 1) + "-" + boost::lexical_cast<string>(now.tm_mday);
	
	string filename = "U:\\html\\ggi_root\\home\\greyhau1\\scraper\\err_log\\" + date + "_error_log" + ".txt";
	ofstream fout;
	fout.open(filename.c_str());
	if (fout.is_open()) {
		cout << "[ok]" << endl << "Dumping error logs to file [" << filename << "].txt...";
		for (int i = 0; i < st.size(); i++) {
			if (st[i].get_num_errors() > 1) {
				fout << "iteration [" << i << "] " << endl;
				st[i].write_error_log(fout);
			}
		}
		cout << "[done]" << endl;
		cout << "Closing file...";
		fout.close();
		cout << "[done]" << endl;
	}
	else {
		cout << "[fail]. Printing error logs (make sure your screencap is working, because this will go REALLY fast)..." << endl
			<< "I'll wait while you get it setup. Let me know when you're ready!" << endl;
		system("PAUSE");
		for (int i = 0; i < st.size(); i++) {
			cout << "iteration [" << i << "] " << endl;
			st[i].print_error_report();
		}
		cout << "[done]" << endl;
		system("PAUSE");
	}
}

void analyze_stocks() {
	int days = 0;
	for (int i = 0; i < st.size(); i++) {
		if (days < st[i].get_days()) {
			days = st[i].get_days();
		}
	}
	if (days == 0) {
		return;
	}
	vector<int> tracker;
	tracker.resize(10);
	vector<float> sorted_avg;
	sorted_avg.resize(10);
	vector<float> unsorted_avg;
	for (int i = 0; i < st.size(); i++) {
		unsorted_avg.push_back(st[i].calculate_daily_avg_price_diff());
		cout << i << ": " << st[i].get_symbol() << ": " << " $" << unsorted_avg[i] << endl;
	}
	for (int i = 0; i < sorted_avg.size(); i++) {
		for (int x = 0; x < unsorted_avg.size(); x++) {
			if (unsorted_avg[x] > sorted_avg[i]) {
				cout << "sorted_avg[" << i << "] = [" << sorted_avg[i] << "] unsorted_avg[" << x << "] = [" << unsorted_avg[x] << "]" << endl;
				sorted_avg[i] = unsorted_avg[x];
				cout << "Placed unsorted_avg[" << x << "] in sorted_avg[" << i << "]" << endl;
				tracker[i] = x;
				cout << "Tracker[" << i << "] = [" << tracker[i] << "]" << endl << endl;
			}
		}
		unsorted_avg.erase(unsorted_avg.begin() + tracker[i]);
	}
	cout << "Top 10 avg increase over the last [" << days << "] days:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << tracker[i] << ": " << st[tracker[i]].get_symbol() << ": $" << sorted_avg[i] << endl;
	}
	system("PAUSE");
	
	time_t t = time(0);   // get current date
	struct tm now;
	localtime_s(&now, &t);

	string date = boost::lexical_cast<string>(now.tm_year + 1900) + "-" + boost::lexical_cast<string>(now.tm_mon + 1) + "-" + boost::lexical_cast<string>(now.tm_mday);
	string filename = "U:\\html\\ggi_root\\home\\greyhau1\\scraper\\st_log\\analyze\\" + date + ".csv";
	ofstream fout;
	cout << "Writing data to file...";
	fout.open(filename.c_str());
	if (fout.is_open()) {
		cout << "[ok]" << endl;
		fout << "Top 10 avg increase over the last [" << days << "] days:" << endl;
		for (int i = 0; i < 10; i++) {
			fout << tracker[i] << ": " << st[tracker[i]].get_symbol() << ": $" << sorted_avg[i] << endl;
		}
	}
	else {
		cout << "[fail]" << endl;
	}
	fout.close();
}