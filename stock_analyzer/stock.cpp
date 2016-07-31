#include "stdafx.h"
#include "stock.h"


stock::stock() {	// ctor
	m_number_of_continuous_running_days = 0;
}
stock::~stock() {}	// dtor

// getters
void stock::get_change() {
	cout << "List of daily price changes for [" << m_symbol << "]:" << endl;
	for (int i = 0; i < m_change.size(); i++) {
		cout << "[" << m_last_trade_date[i] << "] [" << m_change[i] << "]" << endl;
	}
}
// setters

// todo---------------------------------------------------------------------------------------------//
void stock::load_data() {
	ifstream fin;
	string filename = "U:\\html\\ggi_root\\home\\greyhau1\\scraper\\st_log\\" + m_symbol + ".csv";
	fin.open(filename.c_str());
	if (fin.is_open()) {
		m_number_of_continuous_running_days = 0;
		vector<string> temp;
		while (!fin.eof()) {
			string temp2;
			getline(fin, temp2);
			temp.push_back(temp2);
		}
		fin.close();
		for (int i = 0; i < temp.size(); i++) {
			string temp2 = temp[i];
			for (int i = 0; i < 57; i++) {
				int found = temp2.find(",");
				if (found != string::npos) {
					m_data.push_back(temp2.substr(0, found));
					found++;
					temp2.erase(0, found);
				}
				else {
					cout << "[" << i << "]" << " data not found!" << endl;
					bad_data(temp2);
					break;
				}
			}
			if (m_data.size() == 57) {
				m_number_of_continuous_running_days++;
				parse_data();
			}
		}
	}
	else {
		cout << "Opening file [" << m_symbol << ".csv]...";
		cout << "[fail]" << endl;
		system("PAUSE");
	}
}

void stock::parse_data() {
	// first, we purge unnecessary characters from each string
	for (int i = 0; i < m_data.size(); i++) {
		int found = m_data[i].find("\"");
		if (found != string::npos) {
			if (found == 0) {
				m_data[i].erase(0, 1);
				found = m_data[i].find("\"");
				if (found != string::npos) {
					m_data[i].erase(found, 1);
				}
			}
		}
	}
	int d = 0;	// Tracking which makes changes to the function easier.
	string sd;
	

	// commented out for debugging!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//m_str_date = m_data[d];		// adding the date to each entry for better tracking purposes
	//make_a_date();				// converting the string "date" to a struct of ints, using struct date_stamp{}
	//sd = boost::lexical_cast<string>(++d);	// incrementing d and converting it to a string for error reporting
	// end of commented out section for debugging!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	// d = 1
	m_error = m_data[d];		// error report from yahoo, in case the stock moved or no longer exists
	sd = boost::lexical_cast<string>(++d);
	// d = 2
	try {
		m_ask.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_ask failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd +  "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 3
	try {
		m_average_daily_volume.push_back(boost::lexical_cast<int>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_average_daily_volume failed to cast from string to int.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd  + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 4
	try {
		m_ask_size.push_back(boost::lexical_cast<int>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_ask_size failed to cast from string to int.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 5
	try {
		m_bid.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_bid failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 6
	try {
		m_book_value.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_book_value failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 7
	try {
		m_bid_size.push_back(boost::lexical_cast<int>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_bid_size failed to cast from string to int.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 8
	string temp = m_data[d];
	if (temp[0] == '+' || temp[0] == '-') {
		temp.erase(0, 1);
		int found = temp.find("-");
		if (found != string::npos) {
			temp.erase(0, (found + 2));
			found = temp.find("%");
			if (found != string::npos) {
				try {
					m_percent_change.push_back(boost::lexical_cast<float>(temp.substr(0, found)));
				}
				catch (boost::bad_lexical_cast) {
					if (m_data[d] != "N/A") {
						string temp = "[" + m_symbol + "]" + ".csv: m_percent_change failed to cast from string to float.";
						temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
						m_err_report.push_back(temp);
					}
				}
			}
		}
	}
	else {
		if (temp != "N/A") {
			cout << "I don't know what's going on here. I'm writing an error report." << endl;
			string temp2 = "Somehow, neither a + or - was found at the beginning of [" + temp + "] in m_data[" + sd + "]. You should probably look into this.";
			m_err_report.push_back(temp2);
			temp2 = "temp = [" + temp + "]";
			m_err_report.push_back(temp2);
			temp2 = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp2);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 9
	try {
		m_change.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_change failed to cast from string to float.";
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 10
	try {
		m_dividend_share.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_dividend_share failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 11
	m_last_trade_date.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 12
	try {
		m_earnings_share.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_earnings_share failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 13
	try {
		m_eps_estimate_current_year.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_eps_estimate_current_year failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 14
	try {
		m_eps_estimate_next_year.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_eps_estimate_next_year failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 15
	try {
		m_eps_estimate_next_quarter.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_eps_estimate_next_quarter failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 16
	m_float_shares.push_back(m_data[d]); // float--as in the economic definition--not the data type
	sd = boost::lexical_cast<string>(++d);
	// d = 17
	try {
		m_day_low.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_day_low failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 18
	try {
		m_day_high.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_day_high failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 19
	try {
		m_52_week_low.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_52_week_low failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 20
	m_market_capitalization.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 21
	m_shares_outstanding.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 22
	m_EBITDA.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 23
	try {
		m_change_from_52_week_low.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_change_from_52_week_low failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 24
	temp = m_data[d];
	int found = temp.find("%");
	if (found != string::npos) {
		temp.erase(found, 1);
		try {
			m_percent_change_from_52_week_low.push_back(boost::lexical_cast<float>(temp));
		}
		catch (boost::bad_lexical_cast) {
			if (m_data[d] != "N/A") {
				string temp = "[" + m_symbol + "]" + ".csv: m_percent_change_from_52_week_low failed to cast from string to float.";
				m_err_report.push_back(temp);
				temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
				m_err_report.push_back(temp);
			}
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 25
	try {
		m_52_week_high.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_52_week_high failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 26
	try {
		m_last_trade_size.push_back(boost::lexical_cast<int>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_last_trade_size failed to cast from string to int.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 27
	try {
		m_change_from_52_week_high.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_change_from_52_week_high failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 28
	temp = m_data[d];
	found = temp.find("%");
	if (found != string::npos) {
		temp.erase(found, 1);
		try {
			m_percent_change_from_52_week_high.push_back(boost::lexical_cast<float>(temp));
		}
		catch (boost::bad_lexical_cast) {
			if (m_data[d] != "N/A") {
				string temp = "[" + m_symbol + "]" + ".csv: m_percent_change_from_52_week_high failed to cast from string to float.";
				m_err_report.push_back(temp);
				temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
				m_err_report.push_back(temp);
			}
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 29
	try {
		m_last_trade_price.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_last_trade_price failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 30
	m_day_range.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 31
	try {
		m_50_day_moving_average.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_50_day_moving_average failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 32
	try {
		m_200_day_moving_average.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_200_day_moving_average failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 33
	try {
		m_change_from_200_day_moving_average.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_change_from_200_day_moving_average failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 34
	temp = m_data[d];
	found = temp.find("%");
	if (found != string::npos) {
		temp.erase(found, 1);
		try {
			m_percent_change_from_200_day_moving_average.push_back(boost::lexical_cast<float>(temp));
		}
		catch (boost::bad_lexical_cast) {
			if (m_data[d] != "N/A") {
				string temp = "[" + m_symbol + "]" + ".csv: m_percent_change_from_200_day_moving_average failed to cast from string to float.";
				m_err_report.push_back(temp);
				temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
				m_err_report.push_back(temp);
			}
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 35

	try {
		m_change_from_50_day_moving_average.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_change_from_50_day_moving_average failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 36
	temp = m_data[d];
	found = temp.find("%");
	if (found != string::npos) {
		temp.erase(found, 1);
		try {
			m_percent_change_from_50_day_moving_average.push_back(boost::lexical_cast<float>(temp));
		}
		catch (boost::bad_lexical_cast) {
			if (m_data[d] != "N/A") {
				string temp = "[" + m_symbol + "]" + ".csv: m_percent_change_from_50_day_moving_average failed to cast from string to float.";
				m_err_report.push_back(temp);
				temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
				m_err_report.push_back(temp);
			}
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 37
	try {
		m_open.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_open failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 38
	try {
		m_previous_close.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_previous_close failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 39
	temp = m_data[d];
	found = temp.find("%");
	if (found != string::npos) {
		temp.erase(found, 1);
		try {
			m_change_in_Percent.push_back(boost::lexical_cast<float>(temp));
		}
		catch (boost::bad_lexical_cast) {
			if (m_data[d] != "N/A") {
				string temp = "[" + m_symbol + "]" + ".csv: m_change_in_Percent failed to cast from string to float.";
				m_err_report.push_back(temp);
				temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
				m_err_report.push_back(temp);
			}
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 40
	try {
		m_price_sales.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_price_sales failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 41
	try {
		m_price_book.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_price_book failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 42
	m_ex_dividend_date.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 43
	try {
		m_pe_ratio.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_pe_ratio failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 44
	m_dividend_pay_date.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 45
	try {
		m_peg_ratio.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_peg_ratio failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 46
	try {
		m_price_of_eps_estimate_current_year.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_price_of_eps_estimate_current_year failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 47
	try {
		m_price_of_eps_estimate_next_year.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_price_of_eps_estimate_next_year failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 48
	m_symbol = m_data[d];	// this data will never change, so it doesn't need to be a vector
	sd = boost::lexical_cast<string>(++d);
	// d = 49
	m_revenue.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 50
	try {
		m_short_ratio.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_short_ratio failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 51
	m_last_trade_time.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 52
	try {
		m_1_yr_target_price.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_1_yr_target_price failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 53
	try {
		m_volume.push_back(boost::lexical_cast<int>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_volume failed to cast from string to int.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 54
	m_52_week_range.push_back(m_data[d]);
	sd = boost::lexical_cast<string>(++d);
	// d = 55
	m_stock_exchange = m_data[d];	// this data will never change, so it doesn't need to be a vector
	sd = boost::lexical_cast<string>(++d);
	// d = 56
	try {
		m_dividend_yield.push_back(boost::lexical_cast<float>(m_data[d]));
	}
	catch (boost::bad_lexical_cast) {
		if (m_data[d] != "N/A") {
			string temp = "[" + m_symbol + "]" + ".csv: m_dividend_yield failed to cast from string to float.";
			m_err_report.push_back(temp);
			temp = "m_data[" + sd + "] = [" + m_data[d] + "]";
			m_err_report.push_back(temp);
		}
	}
	sd = boost::lexical_cast<string>(++d);
	// d = 57
	m_name = m_data[d];	// this data will never change, so it doesn't need to be a vector
	d = 0;
	m_data.resize(d);
	//cout << "So far, so good..." << endl;
	//system("PAUSE");
}

void stock::bad_data(string data) {
	m_err_report.push_back(data);
}

float stock::calculate_daily_avg_price_diff() {
	float avg = 0.0;
	if (m_change.size() > 0) {
		cout << "[" << m_symbol << "] listing of m_change: " << endl;
		for (int i = 1; i < (m_change.size() - 1); i++) {		// this loop starts at 1 to avoid a "vector out of range" error
			avg = m_change[i] + avg;
			cout << "avg = [" << avg << "]" << endl;
		}
		avg = avg / m_change.size();
		cout << "average returned = [" << avg << "]" << endl;
		return avg;
	}
	else {
		return 0;
	}
}

void stock::make_a_date() {
	int x = m_date.size();
	string iteration = boost::lexical_cast<string>(x);
	m_date.resize((x+1));
	int found = m_str_date.find("-");
	if (found != string::npos) {
		string temp = m_str_date.substr(0, found);
		m_str_date.erase(0, (found + 1));
		try {
			m_date[x].year = (boost::lexical_cast<int>(temp));
		}
		catch (boost::bad_lexical_cast) {
			string temp2 = "Year in m_date[" + iteration + "] in " + m_symbol + " failed to cast from string to int:";
			m_err_report.push_back(temp2);
			m_err_report.push_back(temp);
		}
	}
	found = m_str_date.find("-");
	if (found != string::npos) {
		string temp = m_str_date.substr(0, found);
		m_str_date.erase(0, (found + 1));
		try {
			m_date[x].month = (boost::lexical_cast<int>(temp));
		}
		catch (boost::bad_lexical_cast) {
			string temp2 = "Month in m_date[" + iteration + "] in " + m_symbol + "failed to cast from string to int.";
			m_err_report.push_back(temp2);
			m_err_report.push_back(temp);
		}
	}
	try {
		m_date[x].day = (boost::lexical_cast<int>(m_str_date));
	}
	catch (boost::bad_lexical_cast) {
		string temp = "Day in m_date[" + iteration + "] in " + m_symbol + "failed to cast from string to int.";
		m_err_report.push_back(temp);
		m_err_report.push_back(m_str_date);
	}
}

// debug------------------------------------------------------------------------------------------------------//
void stock::dump_data() {
	cout << "Dumping contents of m_data: " << endl;
	for (int i = 0; i < m_data.size(); i++) {
		cout << "[" << i << "] [" << m_data[i] << "]" << endl;
	}
}

void stock::print_error_report() {
	for (int i = 0; i < m_err_report.size(); i++) {
		cout << m_err_report[i] << endl;
	}
}

void stock::write_error_log(ofstream &fout) {
	if (fout.is_open()) {
		for (int i = 0; i < m_err_report.size(); i++) {
			fout << m_err_report[i] << endl;
		}
	}
	else {
		cout << "the fout you passed to stock::write_error_log didn't take. Check it out." << endl;
	}
}