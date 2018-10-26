#include "object.h"

#include <stack>

#pragma once

namespace goat
{
	class g_instruction
	{
	public:
		virtual ~g_instruction();
		virtual g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) = 0;
	};

	class g_i_load : public g_instruction
	{
	public:
		g_object *key;
		g_instruction *next;

		g_i_load();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_store : public g_instruction
	{
	public:
		g_object *key;
		g_instruction *next;

		g_i_store();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_increment : public g_instruction
	{
	public:
		g_instruction *next;

		g_i_increment();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_load_integer : public g_instruction
	{
	public:
		g_integer value;
		g_instruction *next;

		g_i_load_integer();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_less : public g_instruction
	{
	public:
		g_instruction *next;

		g_i_less();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_if : public g_instruction
	{
	public:
		g_instruction *if_true;
		g_instruction *if_false;

		g_i_if();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};

	class g_i_less_integer : public g_instruction
	{
	public:
		g_object *key;
		g_integer value;
		g_instruction *next;

		g_i_less_integer();
		g_instruction *exec(g_object *scope, std::stack<g_primitive> *stack) override;
	};
}
