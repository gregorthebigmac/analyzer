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
void get_size_of_elements();

int main()
{
	cout << "setting stock symbols..." << endl;
	set_stock_symbols();
	cout << "setting stock symbols...[ok]" << endl;
	cout << "Loading stock data..." << endl;
	load_stock_data();
	analyze_stocks();
	get_size_of_elements();
	dump_errors();
    return 0;
}

void set_stock_symbols() {
	struct stocks {
		vector<string> stock_names;
	} all;

	ifstream fin;
	fin.open("U:\\html\\ggi_root\\home2\\greyhau1\\scraper\\py\\stock.csv");
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
		//system("PAUSE");
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
	cout << "...[ok]" << endl;
}

void dump_errors() {
	time_t t = time(0);   // get current date
	struct tm now;
	localtime_s(&now, &t);
	string date = boost::lexical_cast<string>(now.tm_year + 1900) + "-" + boost::lexical_cast<string>(now.tm_mon + 1) + "-" + boost::lexical_cast<string>(now.tm_mday);
	
	string filename = "U:\\html\\ggi_root\\home2\\greyhau1\\scraper\\err_log\\" + date + "_error_log" + ".txt";
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
		std::cout.precision(2);
		for (int i = 0; i < st.size(); i++) {
			cout << "iteration [" << i << "] " << endl;
			st[i].print_error_report();
		}
		cout << "[done]" << endl;
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
		unsorted_avg.push_back(st[i].calculate_daily_avg_percentage_diff());
	}
	for (int i = 0; i < sorted_avg.size(); i++) {
		for (int x = 0; x < unsorted_avg.size(); x++) {
			if (unsorted_avg[x] > sorted_avg[i]) {
				sorted_avg[i] = unsorted_avg[x];
				tracker[i] = x;
			}
		}
		unsorted_avg.erase(unsorted_avg.begin() + tracker[i]);
	}
	unsorted_avg.clear();
	vector<float> sorted_high_risk;
	vector<int> tracker2;
	sorted_high_risk.resize(10);
	tracker2.resize(10);
	vector<float> unsorted_high_risk;
	for (int i = 0; i < st.size(); i++) {
		unsorted_high_risk.push_back(st[i].get_percent_change());
	}
	for (int i = 0; i < sorted_high_risk.size(); i++) {
		for (int x = 0; x < unsorted_high_risk.size(); x++) {
			if (unsorted_high_risk[x] > sorted_high_risk[i]) {
				sorted_high_risk[i] = unsorted_high_risk[x];
				tracker2[i] = x;
			}
		}
		unsorted_high_risk.erase(unsorted_high_risk.begin() + tracker2[i]);
	}
	unsorted_high_risk.clear();
	
	time_t t = time(0);   // get current date
	struct tm now;
	localtime_s(&now, &t);
	string date = boost::lexical_cast<string>(now.tm_year + 1900) + "-"
		+ boost::lexical_cast<string>(now.tm_mon + 1) + "-"
		+ boost::lexical_cast<string>(now.tm_mday);
	string filename = "U:\\html\\ggi_root\\home2\\greyhau1\\scraper\\st_log\\analyze\\"
		+ date + ".csv";
	ofstream fout;
	cout << "Writing data to file...";
	fout.open(filename.c_str());
	if (fout.is_open()) {
		cout << "[ok]" << endl;
		cout << "Top 10 avg % increase over the last [" << days << "] days:" << endl;
		fout << "Top 10 avg % increase over the last [" << days << "] days:" << endl;
		cout << "i/Stock name/Percent Increase/Current Price" << endl;
		fout << "Stock Name,Percent Increase,Current Price," << endl;
		for (int i = 0; i < 10; i++) {
			cout << tracker[i] << "/" << st[tracker[i]].get_symbol() << "/" << sorted_avg[i] << "%/"
				<< "$" << st[tracker[i]].get_current_price() << endl;
			fout << st[tracker[i]].get_symbol() << "," << sorted_avg[i] << "%,"
				<< "$" << st[tracker[i]].get_current_price() << "," << endl;
		}
		cout << "Top 10 high risk/high return stocks of the day:" << endl;
		cout << "i  /  Stock name/Percent Increase/Current Price" << endl;
		fout << "Top 10 high risk/high return stocks of the day:" << endl;
		fout << "Stock Name,Percent Increase,Current Price," << endl;
		for (int i = 0; i < sorted_high_risk.size(); i++) {
			cout << tracker2[i] << "/" << st[tracker2[i]].get_symbol() << "/" << sorted_high_risk[i] << "%/"
				<< "$" << st[tracker2[i]].get_current_price() << endl;
			fout << st[tracker2[i]].get_symbol() << "," << sorted_high_risk[i] << "%,"
				<< "$" << st[tracker2[i]].get_current_price() << "," << endl;
		}
	}
	else {
		cout << "[fail]" << endl;
	}
	fout.close();
}

void get_size_of_elements() {
	ofstream fout;
	fout.open("U:\\html\\ggi_root\\home2\\greyhau1\\scraper\\st_log\\analyze\\element_comparison2.csv");
	if (fout.is_open()) {
		fout << "Stock Symbol-Element->,"
			/*date from python,*/
			<< "Ask,Average Daily Volume,Ask Size,Bid,Book Value,Bid Size,"
			<< "Change & Percent Change,Change,Dividend/Share,Last Trade Date,Earnings/Share,EPS Estimate Current Year,EPS Estimate Next Year,"
			<< "EPS Estimate Next Quarter,Float Shares,Day’s Low,Day’s High,52-week Low,Market Capitalization,Shares Outstanding,EBITDA,"
			<< "Change From 52-week Low,Percent Change From 52-week Low,52-week High,Last Trade Size,Change From 52-week High,"
			<< "Percent Change From 52-week High,Last Trade (Price Only),Day’s Range,50-day Moving Average,200-day Moving Average,"
			<< "Change From 200-day Moving Average,Percent Change From 200-day Moving Average,Change From 50-day Moving Average,"
			<< "Percent Change From 50-day Moving Average,Open,Previous Close,Change in Percent,Price/Sales,Price/Book,Ex-Dividend Date,P/E Ratio,"
			<< "Dividend Pay Date,PEG Ratio,Price/EPS Estimate Current Year,Price/EPS Estimate Next Year,Revenue,Short Ratio,Last Trade Time,"
			<< "1 yr Target Price,Volume,52-week Range,Dividend Yield," << endl;
		for (int i = 0; i < st.size(); i++) {
			st[i].write_element_sizes_to_file(fout);
			fout << endl;
		}
		fout.close();
	}
	
}