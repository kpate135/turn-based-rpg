#include "Entity.hpp"
#include "Character.hpp"
#include "Action.hpp"
#include "Factory.hpp"

#include "gtest/gtest.h"


using namespace std;

#include "Test_Entity_Character.cpp"









int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

