#pragma once
#pragma once



#ifndef _WISHLIST_HPP_
#define _WISHLIST_HPP_

/*****************************************************************************/

#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>
#include <algorithm>
/*****************************************************************************/

typedef
std::pair< std::string, int >
Wish;

/*****************************************************************************/


class Wishlist
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Wishlist(const std::string &_s);

	Wishlist(const std::string &_s, Wishlist &_v);


	//Wishlist(const std::string &_s, std::initializer_list std::vector<Wish> &_v);

	Wishlist(const std::string &_s, const std::vector<Wish> &_v);

	Wishlist(Wishlist &&_v);



	std::string getOwner();

	void correctOwner(const std::string &_s);

	void addWish(const std::string &_s, int _priority);

	void addWish(Wish const &_w);

	bool hasWish(const std::string &_s);

	int getWishPriority(const std::string &_s);

	int getWishesCount();

	void updateWishPriority(const std::string &_s, int _priority);

	std::vector<std::string> getWishesWithPriority(int _priority);

	std::vector<std::string> getMostPrioritizedWishes(int _capacity);

	std::vector<std::string> getLeastPrioritizedWishes(int _capacity);

	std::set< std::string > getSimilarWishes(Wishlist &_v);

	void dropWish(const std::string &_s);

	void dropWishesWithPriorityLessThan(int _priority);

	void clean();



	void InvalidatedWish(std::string const & _wi, int _priority);
	void EmptyName(const std::string &_s);
	void SingleWish(const std::string &_s);	
	void EmptyWish(const std::string &_s);
	void InvalidatedPriority(int _priority);
	void InvalidatedValue(int _priority);



	Wish & operator [] (unsigned int _k);
	//std::string & operator [] (int _k);
	void  operator += (Wish &_w);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string name;
	std::vector<Wish> heart;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

// TODO: inline functions

/*****************************************************************************/


#endif // _WISHLIST_HPP_
