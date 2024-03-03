#pragma once
#ifndef _HASH_MAP_
#define _HASH_MAP_

#define HashMap_Macros\
_CAPACITY_\
_PRIME_FOR_HASH_

#define _CAPACITY_ 10
#define _PRIME_FOR_HASH_ 11

#include <iostream>
#include <vector>

template <class... Args>
class HashMap;

template <class DataKey, class DataType>
class HashMap< DataKey, DataType> {
protected:
	class HashNode {
	public:
		HashNode(DataKey key, DataType Value) :Key(key), Value(Value), state(false) {}
		HashNode(DataKey key) :Key(key), Value(), state(false) {}
		HashNode() :Key(), Value(), state(false) {}

		DataKey Key;

		DataType Value;

		bool state;

	public:
		bool operator==(const HashNode& node) const {
			return this->Key == node.Key && this->Value == node.Value;
		}
	};


protected:
	std::vector<HashNode> HashArr;
	int capacity;

public:
	template <typename... Pair2>
	HashMap(Pair2... preSet):HashArr(_CAPACITY_), capacity(_CAPACITY_) { (put(preSet.first, preSet.second), ...); }
	HashMap():HashArr(_CAPACITY_), capacity(_CAPACITY_){}

	void put(const DataKey& key, const DataType& Value) {

		long hash = CalculateHash(key);

		if (HashArr[hash].state == false) {
			HashArr[hash].Key = key;
			HashArr[hash].Value = Value;
			HashArr[hash].state = true;
			return;
		}

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) {
				HashArr[i].Key = key;
				HashArr[i].Value = Value;
				HashArr[i].state = true;
				return;
			}
		}

		extendCapacity();
		put(key, Value);
	}

	DataType getV(const DataKey& key) const {
		long hash = CalculateHash(key);

		if (HashArr[hash].Key == key) {
			return HashArr[hash].Value;
		}

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) { return DataType(); }

			if (HashArr[i].Key == key) { return HashArr[i].Value; }
		}

		return DataType();
	}

	bool inMap(const DataKey& key)const noexcept {
		long hash = CalculateHash(key);

		if (HashArr[hash].Key == key) {
			return true;
		}

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) { return false; }

			if (HashArr[i].Key == key) { return true; }
		}
		return false;
	}

	void clear() {
		for (int i = 0; i < capacity; i++) {
			HashArr[i] = HashNode();
		}
	}

	void size() { return capacity; }

protected:
	long CalculateHash(const DataKey& key) const noexcept {
		long hash = 0;
		long p_pow = 1;

		long size = sizeof(DataType);
		size = size + capacity * size;
		while (--size) {
			hash = ((hash + size * p_pow + 1)) % capacity;
			p_pow = (p_pow * _PRIME_FOR_HASH_) % capacity;
		}
		return hash;
	}

	void extendCapacity() {
		int upto = _CAPACITY_;
		while (upto--) {
			HashArr.push_back(HashNode());
			++capacity;
		}
	}
};


template <class DataType>
class HashMap<DataType> {
protected:
	class HashNode {
	public:
		HashNode(std::string key, DataType Value) :Key(key), Value(Value), state(false) {}
		HashNode(std::string key) :Key(key), Value(), state(false) {}
		HashNode() :Key(""), Value(), state(false) {}

		std::string Key;

		DataType Value;

		bool state;

	public:
		bool operator==(const HashNode& node) const {
			return this->Key == node.Key && this->Value == node.Value;
		}
	};

protected:
	std::vector<HashNode> HashArr;
	int capacity;
public:
	template <typename... Pair>
	HashMap(Pair... preSet):HashArr(_CAPACITY_), capacity(_CAPACITY_) { (put(preSet.key, preSet.Value), ...); }
	HashMap():HashArr(_CAPACITY_), capacity(_CAPACITY_) {}

	void put(const std::string& key, const DataType& Value) {
		if (key == "") { return; }

		long hash = CalculateHash(key);

		if (HashArr[hash].state == false) {
			HashArr[hash].Key = key;
			HashArr[hash].Value = Value;
			HashArr[hash].state = true;
			return;
		}

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) {
				HashArr[i].Key = key;
				HashArr[i].Value = Value;
				HashArr[i].state = true;
				return;
			}
		}

		extendCapacity();
		put(key, Value);
	}

	DataType getV(const std::string& key) const {
		long hash = CalculateHash(key);

		if (HashArr[hash].Key == key) { return HashArr[hash].Value; }

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) { return DataType(); }

			if (HashArr[i].Key == key) { return HashArr[i].Value; }
		}

		return DataType();
	}

	bool inMap(const std::string& key)const noexcept {
		long hash = CalculateHash(key);

		if (HashArr[hash].Key == key) { return true; }

		for (int i = (hash + 1) % capacity; i != hash; i = (i + 1) % capacity) {
			if (HashArr[i].state == false) { return false; }

			if (HashArr[i].Key == key) { return true; }
		}
		return false;
	}

	void clear() {
		for (int i = 0; i < capacity; i++) {
			HashArr[i] = HashNode();
		}
	}

	void extendCapacity() {
		int upto = _CAPACITY_;
		while (upto--) {
			HashArr.push_back(HashNode());
			++capacity;
		}
	}

protected:
	long CalculateHash(const std::string& key) const noexcept {
		long hash = 0;
		long p_pow = 1;
		for (const char& c : key) {
			if (IsLow(c)) {
				hash = (hash + (c - 'a' + 1) * p_pow) % capacity;
				p_pow = (p_pow * _PRIME_FOR_HASH_) % capacity;
			}
			else if (IsUpper(c)) {
				hash = (hash + (c - 'A' + ('a' - 'A') + 1) * p_pow) % capacity;
				p_pow = (p_pow * _PRIME_FOR_HASH_) % capacity;
			}
		}
		return hash;
	}

	bool IsUpper(const char& c) const noexcept {
		return 'A' <= c && c <= 'Z';
	}

	bool IsLow(const char& c) const noexcept {
		return 'a' <= c && c <= 'z';
	}
};

template <class DataType>
class Pair {
public:
	Pair(std::string key, DataType Value) :key(key), Value(Value) {}
	Pair() :key(""), Value() {}
	std::string key;
	DataType Value;
};

#ifndef __SaveMacros__

#undef HashMap_Macros

#endif 


#endif