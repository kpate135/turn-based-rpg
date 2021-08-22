#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "Character.hpp"
#include "Equipment.hpp"

class AbstractFactory {

	public:
		AbstractFactory() {};
		~AbstractFactory() {};

		virtual Entity* MakeByArea(std::string area) = 0;
		virtual Entity* MakeByID(int id) = 0;

};


#endif
