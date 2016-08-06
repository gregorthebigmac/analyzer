#pragma once
#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;

class stock {
public:
	stock();
	~stock();

	// getters
	string get_name() { return m_name; }
	int get_days() { return m_number_of_continuous_running_days; }
	string get_symbol() { return m_symbol; }
	float get_size_of_change() { return m_change.size(); }
	float get_change();
	int get_num_errors() { return m_err_report.size(); }
	float get_current_price();
	float get_percent_change();

	// setters
	void set_name(string symbol) { m_symbol = symbol; }

	// todo
	void load_data();
	void parse_data();
	void bad_data(string data);
	float calculate_daily_avg_percentage_diff();
	void make_a_date();

	// debug
	void dump_data();
	void print_error_report();
	void write_error_log(ofstream &fout);
	void write_element_sizes_to_file(ofstream& fout);

private:
	// easiest way to create an integer date from the string m_str_date
	struct date_stamp {
		int year;
		int month;
		int day;
	};

	int m_number_of_continuous_running_days;
	vector<string> m_err_report;	// this is used for internal errors and exception handling
	vector<string> m_data;	// this will be used for getting raw data from files as strings. temp storage ONLY!!
							// m_data will be used in method void parse_data()
	// member variables are listed in the order in which they are received in the yahoo csv file.
	// refer to reference.txt for explanations of data
	string m_str_date;
	vector<date_stamp> m_date;
	string m_error;		// error report from yahoo, in case the stock moved or no longer exists
	vector<float> m_ask;
	vector<int> m_average_daily_volume;
	vector<int> m_ask_size;
	vector<float> m_bid;
	vector<float> m_book_value;
	vector<int> m_bid_size;
	vector<float> m_percent_change;
	vector<float> m_change;
	vector<float> m_dividend_share;
	vector<string> m_last_trade_date;
	vector<float> m_earnings_share;
	vector<float> m_eps_estimate_current_year;
	vector<float> m_eps_estimate_next_year;
	vector<float> m_eps_estimate_next_quarter;
	vector<string> m_float_shares; // float--as in the economic definition--not the data type
	vector<float> m_day_low;
	vector<float> m_day_high;
	vector<float> m_52_week_low;
	vector<string> m_market_capitalization;
	vector<string> m_shares_outstanding;
	vector<string> m_EBITDA;
	vector<float> m_change_from_52_week_low;
	vector<float> m_percent_change_from_52_week_low;
	vector<float> m_52_week_high;
	vector<int> m_last_trade_size;
	vector<float> m_change_from_52_week_high;
	vector<float> m_percent_change_from_52_week_high;
	vector<float> m_last_trade_price;
	vector<string> m_day_range;
	vector<float> m_50_day_moving_average;
	vector<float> m_200_day_moving_average;
	vector<float> m_change_from_200_day_moving_average;
	vector<float> m_percent_change_from_200_day_moving_average;
	vector<float> m_change_from_50_day_moving_average;
	vector<float> m_percent_change_from_50_day_moving_average;
	vector<float> m_open;
	vector<float> m_previous_close;
	vector<float> m_change_in_percent;	// fix m_data[7]
	vector<float> m_price_sales;
	vector<float> m_price_book;
	vector<string> m_ex_dividend_date;
	vector<float> m_pe_ratio;
	vector<string> m_dividend_pay_date;
	vector<float> m_peg_ratio;
	vector<float> m_price_of_eps_estimate_current_year;
	vector<float> m_price_of_eps_estimate_next_year;
	string m_symbol;	// this data will never change, so it doesn't need to be a vector
	vector<string> m_revenue;
	vector<float> m_short_ratio;
	vector<string> m_last_trade_time;
	vector<float> m_1_yr_target_price;
	vector<int> m_volume;
	vector<string> m_52_week_range;
	string m_stock_exchange;	// this data will never change, so it doesn't need to be a vector
	vector<float> m_dividend_yield;
	string m_name;	// this data will never change, so it doesn't need to be a vector
};

#endif // !STOCK_H