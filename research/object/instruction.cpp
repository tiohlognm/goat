#include "instruction.h"

namespace goat
{
	g_instruction::~g_instruction()
	{
	}



	g_i_load::g_i_load()
		: key(nullptr), next(nullptr)
	{
	}

	g_instruction *g_i_load::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive *value = scope->find(key);
		if (!value)
			return nullptr;
		stack->push(*value);
		return next;
	}



	g_i_store::g_i_store()
		: key(nullptr), next(nullptr)
	{
	}

	g_instruction *g_i_store::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive value = stack->top();
		stack->pop();
		scope->insert(key, value);
		return next;
	}



	g_i_increment::g_i_increment()
		: next(nullptr)
	{
	}

	g_instruction *g_i_increment::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive value = stack->top().increment();
		stack->pop();
		stack->push(value);
		return next;
	}




	g_i_load_integer::g_i_load_integer()
		: value(0), next(nullptr)
	{
	}

	g_instruction *g_i_load_integer::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive pri;
		pri.set(value);
		stack->push(pri);
		return next;
	}



	g_i_less::g_i_less()
		: next(nullptr)
	{
	}

	g_instruction *g_i_less::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive left = stack->top();
		stack->pop();
		g_primitive right = stack->top();
		stack->pop();
		stack->push(left.less(&right));
		return next;
	}



	g_i_if::g_i_if()
		: if_true(nullptr), if_false(nullptr)
	{
	}

	g_instruction *g_i_if::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive condition = stack->top();
		stack->pop();
		if (condition.data.boolean)
			return if_true;
		else
			return if_false;
	}



	g_i_less_integer::g_i_less_integer()
		: key(nullptr), value(0), next(nullptr)
	{
	}

	g_instruction *g_i_less_integer::exec(g_object *scope, std::stack<g_primitive> *stack)
	{
		g_primitive *left = scope->find(key);
		if (!left)
			return nullptr;
		g_primitive right;
		right.set(value);
		stack->push(left->less(&right));
		return next;
	}
}
