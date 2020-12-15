#pragma once

#include <iostream>
#include <vector>

class Gate
{
public:
	virtual void print_info() = 0;
	virtual void calculate_output() = 0;
	int get_output();
	void set_input(const int in, const int in_index);

protected:
	std::vector<int> inputs;
	int s, in_index;
};

class And : public Gate
{
public:   
	And(int); 																	
	virtual void calculate_output(); 						
	virtual void print_info(); 
};

class Or : public Gate
{

public:
	Or(int);
	virtual void calculate_output();
	virtual void print_info();
};

class Not : public Gate
{

public:
	Not(int);
	virtual void calculate_output();
	virtual void print_info();
};

class Xor : public Gate
{

public:
	Xor(int);
	virtual void calculate_output();
	virtual void print_info();
};
