/*****************************************************************//**
 * \file   Kmp.h
 * \brief  
 * This is a sample of KMP, determining whether a string is a substring of another.
 * \author Liancheng He
 * \date   January 2024
 *********************************************************************/
#pragma once
#include<string>
constexpr int MAX_LEN = 10000;
using namespace std;

class KMP {
public:
	bool isPart(char source[], char partition[] ) {
		string s = source, p = partition;
		int sLen = s.size(), pLen = p.size();
		getNext(partition);
		int i = 0, j = 0;
		while (i < sLen && j < pLen) {
			if (j == -1 || s[i] == p[j]) ++i, ++j;
			else j = next[j];
		}	
		return j >= pLen ? true : false;
	}
private:
	int next[MAX_LEN];

	/**
	 * Calculate the maximum length of the same prefix and suffix.
	 *
	 * \param tmp Input string
	 */
	void getNext(string tmp) {
		next[0] = -1;
		int i = 0, j = -1, len = tmp.size() - 1;
		while (i < len) {
			if (j == -1 || tmp[i] == tmp[j]) {
				++i, ++j;
				next[i] = j;
			}
			else j = next[j];
		}
	}

	/**
	 * Optimize the next array, due to the redundant comparisons in KMP algorithm.
	 * The details can be found in https://www.cnblogs.com/dusf/p/kmp.html
	 * \param tmp Input string
	 */
	void getNextOptimize(string tmp) {
		next[0] = -1;
		int i = 0, j = -1, len = tmp.size();
		while (i < len) {
			if (j == -1 || tmp[i] == tmp[j]) {
				++i, ++j;
				next[i] = tmp[i] == tmp[j] ? tmp[j] : j;
			}
			else j = next[j];
		}
	}
};
