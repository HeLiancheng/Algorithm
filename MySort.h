/*****************************************************************//**
 * \file   MySort.h
 * \brief  
 * Three classic sorting algorithms including heapSort, quickSort, mergeSort
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<vector>
using namespace std;
void heapSort(vector<int> &v);
void quickSort(vector<int>& v, int l, int r);
void mergeSort(vector<int>& v, vector<int>& v2, int l, int r);