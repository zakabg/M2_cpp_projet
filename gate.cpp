#include "gate.h"
#include <vector>
using namespace std;

void Gate::set_input(const int in, const int in_index)
{
	inputs[in_index] = in;
}

int Gate::get_output()
{
	return s;
}

And::And(int size)
{

	in_index = 0;
	inputs.resize(size);
}

Or::Or(int size)
{

	inputs.resize(size);
	in_index = 0;
}

Not::Not(int size)
{

	inputs.resize(size);
	in_index = 0;
}

Xor::Xor(int size)
{

	inputs.resize(size);
	in_index = 0;
}

void And::print_info()
{

	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << " ";
	}
	calculate_output();
	cout << endl;
}

void Or::print_info()
{

	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << " ";
	}
	calculate_output();
	cout << endl;
}

void Not::print_info()
{

	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << " ";
	}
	calculate_output();
	cout << endl;
}

void Xor::print_info()
{

	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << " ";
	}
	calculate_output();
	cout << endl;
}

void And::calculate_output()
{
	s = 1;
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		s *= inputs[i];
	}
}

void Xor::calculate_output()
{
	s = 0;
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		s ^= bool(inputs[i]);
	}
}

void Or::calculate_output()
{
	s = 0;
	for (unsigned int i = 0; i < inputs.size(); i++)
	{
		s |= inputs[i];
	}
}

void Not::calculate_output()
{
	s = !inputs[0];
}
