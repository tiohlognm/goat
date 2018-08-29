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

#pragma once

#include "Map.h"
#include "Vector.h"
#include "PlainVector.h"
#include "String.h"
#include "WideString.h"
#include "RawBuffer.h"
#include "List.h"
#include "MultiList.h"
#include "Type.h"
#include "Pool.h"
#include "StringIndex.h"

namespace goat {

	class Object;
	class ObjectString;
	class ObjectFunction;
	class ObjectThread;
	class ObjectArray;
	class ObjectBuiltIn;
	class ObjectInteger;
	class ObjectReal;
	class ObjectException;
	class ObjectBoolean;
	class ObjectChar;
	class ObjectVoid;
	class ObjectNull;
	class ObjectUndefined;
	class ObjectFile;
	class ObjectStringBuilder;
	class ObjectByteArray;
	class PrimitiveHandler;
	class Container;

	class PrimitiveHandler {
	public:
		virtual ~PrimitiveHandler() {
		}

		virtual Object * toObject(Container *ctr) = 0;
		virtual bool equals(Container *left, Container *right) = 0;
		virtual WideString toWideString(Container *ctr) = 0;
		virtual WideString toWideStringNotation(Container *ctr) {
			return toWideString(ctr);
		}
	};

	class Container {
	public:
		PrimitiveHandler *handler;
		union {
			Object *obj;
			bool    B;
			wchar   C;
			lint    I;
			ldouble R;
		} data;

		static Container create() {
			Container ctr;
			ctr.handler = nullptr;
			ctr.data.obj = nullptr;
			return ctr;
		}

		inline bool isEmpty();
		inline bool isPrimitive();
		inline bool isUndefined();
		inline bool equals(Container *right);
		inline Object *toObject();
		inline ObjectArray *toObjectArray();
		inline ObjectString *toObjectString();
		inline void mark();
		inline WideString toWideString();
		inline WideString toWideStringNotation();
		bool getBoolean(bool *value);
		bool getChar(wchar *value);
		bool getInteger(lint *value);
		bool getReal(ldouble *value);
		bool getString(WideString *value);
	};

	class Object {
	public:

		Container toContainer() {
			Container ctr;
			ctr.handler = nullptr;
			ctr.data.obj = this;
			return ctr;
		}

		class Pair {
		public:
			Container key;
			Container value;

			Pair() : key(Container::create()), value(Container::create()) {
			}

			Pair(Container _key, Container _value) : key(_key), value(_value) {
			}
		};

		enum Status {
			MARKED = 1,
			PERMANENT = 2,
			LOCKED = 4
		};
		void *list;
		Object *prev, *next;
		uint32 status;
		Map<int32, Container> objects;
		List<Pair> chain;
		PlainVector<Object *> proto;
		static StringIndex indexes;

		Object();
		Object(bool builtIn);
		Object(Object *_proto);
		virtual ~Object();
		void mark();
		void mark_2();
		virtual void trace();
		static inline int32 createIndex(String key);
		static inline int32 searchIndex(String key);
		static inline String getKey(int32 index);
	private:
		Container *find_(int32 index);
		Container *find_(WideString key);
		Container *find_(Container *key);
	public:
		Container *find(int32 index);
		Container *find(WideString key);
		Container *find(Container *key);
		void insert(int32 index, Container value);
		void insert(Container *key, Container value);
		bool replace(int32 index, Container repl);
		void clone(Object *_clone);
		virtual bool equals(Container *ctr);
		bool instanceOf(Object *_obj);
		void findAll(String key, PlainVector<Object *> *vector);
		void findUnique(String key, PlainVector<Object *> *vector);
		virtual void flat(Object *fobj);
		void enumerate(Vector<Pair> *vector);

		virtual WideString toWideString();
		virtual WideString toWideStringNotation();
		virtual RawString toRawString();

		virtual ObjectString * toObjectString();
		virtual ObjectFunction * toObjectFunction();
		virtual ObjectThread * toObjectThread();
		virtual ObjectArray * toObjectArray();
		virtual ObjectBuiltIn * toObjectBuiltIn();
		virtual ObjectInteger * toObjectInteger();
		virtual ObjectReal * toObjectReal();
		virtual ObjectException *toObjectException();
		virtual ObjectBoolean *toObjectBoolean();
		virtual ObjectChar *toObjectChar();
		virtual ObjectVoid *toObjectVoid();
		virtual ObjectNull *toObjectNull();
		virtual ObjectUndefined *toObjectUndefined();
		virtual ObjectFile *toObjectFile();
		virtual ObjectStringBuilder *toObjectStringBuilder();
		virtual ObjectByteArray * toObjectByteArray();

		void *operator new (__size size);
		void operator delete (void *ptr);
	};


	bool Container::isEmpty() {
		return handler == nullptr && data.obj == nullptr;
	}

	bool Container::isPrimitive() {
		return handler != nullptr;
	}

	bool Container::isUndefined() {
		return handler == nullptr && data.obj->toObjectUndefined() != nullptr;
	}

	bool Container::equals(Container *right) {
		if (handler != nullptr) {
			return handler->equals(this, right);
		}
		return data.obj ? data.obj->equals(right) : false;
	}

	Object * Container::toObject() {
		if (handler)  {
			data.obj = handler->toObject(this);
			handler = nullptr;
		}
		return data.obj;
	}

	ObjectArray * Container::toObjectArray() {
		return handler == nullptr ? data.obj->toObjectArray() : nullptr;
	}

	ObjectString * Container::toObjectString() {
		return handler == nullptr && data.obj != nullptr ? data.obj->toObjectString() : nullptr;
	}

	void Container::mark() {
		if (handler == nullptr && data.obj != nullptr)
			data.obj->mark();
	}

	WideString Container::toWideString() {
		if (handler)  {
			return handler->toWideString(this);
		}
		return data.obj->toWideString();
	}

	WideString Container::toWideStringNotation() {
		if (handler)  {
			return handler->toWideStringNotation(this);
		}
		return data.obj->toWideStringNotation();
	}


	extern long long totalObjMem;

	class ObjectList : public MultiList<Object, &Object::prev, &Object::next, &Object::list> {
	public:
		static ObjectList global;
		static ObjectList forMarking;
		void unmark();
		bool mark_2();
		void sweep();
	};

	class SuperObject : public Object {
	public:
		SuperObject();
		static Object *getInstance();
		void flat(Object *fobj) override;
	};

	int32 Object::createIndex(String key) {
		return indexes.createIndex(key);
	}

	int32 Object::searchIndex(String key) {
		return indexes.searchIndex(key);
	}

	String Object::getKey(int32 index) {
		return indexes.getString(index);
	}
}
