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

#include "Prefix.h"
#include "ObjectBuiltIn.h"
#include "ObjectFunction.h"
#include "ObjectException.h"
#include "Resource.h"
#include "Identifier.h"
#include "StringBuilder.h"

namespace goat {

	Prefix::Prefix(Operator *_oper, Expression *_right) {
		loc = _oper->loc;
		oper = _oper;
		operIndex = Object::createIndex(oper->value);
		right = _right;
	}

	Prefix * Prefix::toPrefix() {
		return this;
	}

	void Prefix::trace() {
		oper->mark();
		right->mark();
	}

	State *Prefix::createState(State *_prev) {
		return new StateImpl(_prev, this);
	}

	State * Prefix::StateImpl::next() {
		switch (step) {
		case GET_RIGHT:
			return expr->right->createState(this);
		case EXECUTE: {
			step = DONE;
			if (right.isEmpty() || right.isUndefined()) {
				return throw_(new CanNotReadOperatorOfUndefined(expr->oper->value));
			}
			if (right.isPrimitive()) {
				throw NotImplemented();
			}
			else {
				Object *robj = right.data.obj;
				Container *ctr = robj->find(expr->operIndex);
				if (ctr->isPrimitive()) {
					throw NotImplemented();
				}
				Object *obj = ctr->data.obj;
				if (obj->toObjectUndefined()) {
					return throw_(new OperatorIsNotDefined(expr->oper->value));
				}
				ObjectFunction *of = obj->toObjectFunction();
				if (of) {
					changeScope(of->context->clone());
					scope->this_ = robj;
					scope->arguments = new ObjectArray();
					scope->objects.insert(Resource::i_arguments(), scope->arguments->toContainer());
					if (of->function->args) {
						unsigned int i = 0, count = scope->arguments->vector.len();
						Token *name = of->function->args->first;
						while (name && i < count) {
							scope->objects.insert(Object::createIndex(name->toIdentifier()->name), scope->arguments->vector[i]);
							i++;
							name = name->next;
						}
					}
					return of->function->createState(this);
				}
				ObjectBuiltIn *obi = obj->toObjectBuiltIn();
				if (obi) {
					cloneScope();
					scope->this_ = robj;
					return obi->createState(this);
				}
				return throw_(new IsNotAFunction(expr->oper->value));
			}
		}
		case DONE:
			State * p = prev;
			delete this;
			return p;
		}
		throw NotImplemented();
	}

	void Prefix::StateImpl::ret(Container *value) {
		switch (step) {
		case GET_RIGHT:
			right = *value;
			step = EXECUTE;
			return;
		case DONE:
			prev->ret(value);
			return;
		default:
			throw NotImplemented();
		}
	}

	void Prefix::StateImpl::trace() {
		right.mark();
	}

	String Prefix::toString() {
		return (StringBuilder() << oper->value << right->toString()).toString();
	}

	Token * Prefix::StateImpl::token() {
		return expr;
	}
}
