/*

Copyright (C) 2017, 2018 Ivan Kniazkov

This file is part of interpreter of programming language
codenamed "Goat" ("Goat interpreter").

Goat interpreter is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Goat interpreter is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with Goat interpreter.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "DeclareVariable.h"
#include "StringBuilder.h"
#include "ObjectUndefined.h"

namespace goat {

	DeclareVariable::DeclareVariable(Identifier *_tokName, Expression *_initExpr) {
		loc = _tokName->loc;
		name = _tokName->name;
		init = _initExpr;
	}

	void DeclareVariable::trace() {
		if (init) {
			init->mark();
		}
	}

	DeclareVariable * DeclareVariable::toDeclareVariable() {
		return this;
	}

	State * DeclareVariable::createState(State *_prev) {
		return new StateImpl(_prev, this);
	}

	State * DeclareVariable::StateImpl::next() {
		if (decl->init != nullptr && init.isEmpty()) {
			return decl->init->createState(this);
		}
		else {
			scope->objects.insert(Object::createIndex(decl->name), !init.isEmpty() ? init : *ObjectUndefined::getContainer());
			State *p = prev;
			delete this;
			return p;
		}
	}

	void DeclareVariable::StateImpl::ret(Container *value) {
		if (decl->init != nullptr && init.isEmpty()) {
			init = *value;
		}
		else {
			throw NotImplemented();
		}
	}

	void DeclareVariable::StateImpl::trace() {
		init.mark();
	}

	String DeclareVariable::toString() {
		StringBuilder b;
		b << "var " << name;
		if (init) {
			b << " = " << init->toString();
		}
		b << ';';
		return b.toString();
	}

	Token * DeclareVariable::StateImpl::token() {
		return decl;
	}

	State::DebugMode DeclareVariable::StateImpl::stop() {
		if (decl->init != nullptr) {
			return !init.isEmpty() ? SKIP : OVER;
		}
		return SKIP;
	}
}
