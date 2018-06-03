#include "wishlist.hpp"
#include "messages.hpp"





//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Wishlist::EmptyName(const std::string &_s)//пустое имя
{
	if (_s.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);
}

void Wishlist::EmptyWish(const std::string &_s) //пустое желание
{
	if (_s.empty())
		throw std::logic_error(Messages::WishNameEmpty);
}


void Wishlist::SingleWish(const std::string &_s)//желание уже есть
{
	for (auto it : this->heart)
	{
		if (_s == it.first)
			throw std::logic_error(Messages::WishAlreadyExists);
	}
}


void Wishlist::InvalidatedPriority(int _priority)//отрицательный приоритет
{
	if (_priority < 0)
		throw std::logic_error(Messages::NegativePriority);
}


void Wishlist::InvalidatedValue(int _priority)//отрицательное число
{
	if (_priority <= 0)
		throw std::logic_error(Messages::NonPositiveAmount);
}


void Wishlist::InvalidatedWish(std::string const & _s, int _priority)//некоректное желание
{

	EmptyWish(_s);
	InvalidatedPriority(_priority);
	SingleWish(_s);
}




//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Wishlist::Wishlist(const std::string &_s)
{
	EmptyName(_s);
	this->name = _s;
}


Wishlist::Wishlist(const std::string &_s, const std::vector<Wish> &_v)
{
	EmptyName(_s);
	this->name = _s;

	for (auto it : _v)
	{
		addWish(it);
	}
}



Wishlist::Wishlist(const std::string &_s, Wishlist &_v)
	:heart(_v.heart)
{
	EmptyName(_s);
}


Wishlist::Wishlist(Wishlist &&_v)
	:heart(std::move(_v.heart)),
	name(std::move(_v.name))
{

}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::string Wishlist::getOwner()
{
	return this->name;
}


void Wishlist::correctOwner(const std::string &_s)
{
	EmptyName(_s);
	this->name = _s;
}


void Wishlist::addWish(const std::string &_s, int _priority)
{
	InvalidatedWish(_s, _priority);
	this->heart.push_back(make_pair(_s, _priority));
}


void Wishlist::addWish(Wish const &_w)

{
	InvalidatedWish(_w.first, _w.second);
	this->heart.push_back(_w);
}


bool Wishlist::hasWish(const std::string &_s)
{
	EmptyName(_s);
	for (auto it : this->heart)
	{
		if (_s == it.first)
			return true;
	}
	return false;
}


int Wishlist::getWishPriority(const std::string &_s)
{
	EmptyWish(_s);
	for (auto it : this->heart)
	{
		if (_s == it.first)
			return it.second;
	}
	throw std::logic_error(Messages::WishDoesNotExist);
}


int Wishlist::getWishesCount()
{
	return this->heart.size();
}


void Wishlist::updateWishPriority(const std::string &_s, int _priority)
{
	InvalidatedPriority(_priority);
	EmptyWish(_s);
	int counter = 0;
	for (auto it : this->heart)
	{
		if (it.first == _s)
		{
			heart[counter].second = _priority;
			return;
		}
		counter++;
	}
	throw std::logic_error(Messages::WishDoesNotExist);
}


std::vector<std::string> Wishlist::getWishesWithPriority(int _priority)
{
	std::vector<std::string> v;
	InvalidatedPriority(_priority);
	for (auto it : this->heart)
	{
		if (it.second == _priority)
			v.push_back(it.first);
	}
	return v;
}

std::vector<std::string> Wishlist::getMostPrioritizedWishes(int _capacity)
{
	InvalidatedValue(_capacity);
	std::vector <Wish> counterpart(this->heart);
	std::vector<std::string> v;
	while(counterpart.size()!=0 && v.size()<_capacity)
	{
		auto max = counterpart.begin();
		for (auto it = counterpart.begin(); it != counterpart.end(); ++it )
		{
			if (it->second > max->second)
				max = it;
		}

		v.push_back(max->first);
		counterpart.erase(max);
	}	
	return v;
}


std::vector<std::string> Wishlist::getLeastPrioritizedWishes(int _capacity)
{
	InvalidatedValue(_capacity);
	std::vector <Wish> counterpart(this->heart);
	std::vector<std::string> v;
	while (counterpart.size() != 0 && v.size()<_capacity)
	{
		auto min = counterpart.begin();
		for (auto it = counterpart.begin(); it != counterpart.end(); ++it)
		{
			if (it->second < min->second)
				min = it;
		}

		v.push_back(min->first);
		counterpart.erase(min);
	}
	return v;
}


std::set< std::string > Wishlist::getSimilarWishes(Wishlist &_v)
{
	std::set<std::string> generic;
	for (auto iterator : this->heart)
	{
		for (auto it : _v.heart)
		{
			if (it.first == iterator.first)
				generic.insert(iterator.first);
		}
	}
	return generic;
}


void Wishlist::dropWish(const std::string &_s)
{
	EmptyWish(_s);
	for (auto it = heart.begin(); it < heart.end(); it++)
	{
		if (it->first == _s)
		{
			heart.erase(it);
			return;
		}
	}

	throw std::logic_error(Messages::WishDoesNotExist);
}


void Wishlist::dropWishesWithPriorityLessThan(int _priority)
{
	InvalidatedPriority(_priority);
	heart.erase(std::remove_if(heart.begin(), heart.end(), [_priority](Wish const _Wish)
	{
		return _Wish.second < _priority;
	}), heart.end());
}



void Wishlist::clean()
{
	this->heart.clear();
}






Wish & Wishlist::operator [] (unsigned int _k)
{
	if (_k < 1)
		std::out_of_range;
	else
		if (!(this->heart.size() > _k))
			throw std::logic_error("Error:  priority is not valid!");
	return this->heart[_k];

}


void  Wishlist::operator += (Wish &_w)
{
	InvalidatedWish(_w.first, _w.second);
	this->heart.push_back(_w);
}



