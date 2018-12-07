#include <string>
#include <sstream>
#include <iostream>

class g_token_list;

class g_token
{
public:
	g_token() : refs(0), list(nullptr), prev(nullptr), next(nullptr)
	{
	}
	virtual ~g_token();
	virtual std::string to_string() = 0;

	void release()
	{
		if (!(--refs))
			delete this;
	}

	int refs;
	g_token_list *list;
	g_token *prev, *next;
};

class g_token_list
{
public:
	g_token_list() : first(nullptr), last(nullptr), count(0)
	{
	}
	~g_token_list();
	void add(g_token *token);
	std::string to_string();

	g_token *first, *last;
	int count;

};

class g_rule
{
public:
	virtual ~g_rule();
	virtual bool check (g_token *token) = 0;
};

class g_token_symbol : public g_token
{
public:
	g_token_symbol(char _value) : value(_value)
	{
	}
	std::string to_string() override;

	char value;
};



g_token::~g_token()
{
}

g_token_list::~g_token_list()
{
	g_token *token = first;
	while(token)
	{
		g_token *next = token->next;
		token->release();
		token = next;
	}
}

void g_token_list::add(g_token *token)
{
	token->list = this;
	token->prev = last;
	token->next = nullptr;

	if (last)
		last->next = token;
	else
		first = token;
	last = token;
	token->refs++;
	count++;
}

std::string g_token_list::to_string()
{
	std::stringstream ss;
	ss << '{';
	g_token *token = first;
	while(token)
	{
		if (token->prev)
			ss << ", ";
		ss << token->to_string();
		token = token->next;
	}
	ss << '}';
	return ss.str();
}

g_rule::~g_rule()
{
}

std::string g_token_symbol::to_string()
{
	char tmp[2] = { value, 0 };
	return tmp;
}


int main(void)
{
	g_token_list l;
	std::string s = "ABCDE";
	for (char c : s)
	{
		l.add(new g_token_symbol(c));
	}

	std::cout << l.to_string();

	return 0;
}
