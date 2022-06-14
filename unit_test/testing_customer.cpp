// =========================================================
// File: testing_customer.cpp
// Author: Pedro O. Perez-Murueta, Phd.
// Date: 4/Jan/2022
// Description: This file contains the series of tests that the
//							VoxOperator class must pass.
// To compile: g++ -std=c++11 testing_customer.cpp -o app
// To execute: ./app
// =========================================================
#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "../bill.h"
#include "../operator.h"
#include "../vox.h"
#include "../internet.h"
#include "../customer.h"

TEST_CASE("testing default constructor",
  "Customer(int, std::string, int, Operator*, double)") {
  VoxOperator *vox = new VoxOperator(1, 10.00, 10.00, 10.00, 10, VOX);
  Customer c1(1, "juan", 40, vox, 100.0);
  Customer c2(2, "pedro", 15, vox, 100.0);

	REQUIRE(c1.getId() == 1);
  REQUIRE(c1.getName() == std::string("juan"));
  REQUIRE(c1.getAge() == 40);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0.0);
  REQUIRE(c1.getTotalMessageSent() == 0.0);
  REQUIRE(c1.getTotalInternetUsage() == 0.0);
  REQUIRE(c1.getOperator() != NULL);
  REQUIRE(c1.getOperator()->getId() == 1);
  REQUIRE(c1.getBill() != NULL);
  REQUIRE(c1.getBill()->getLimitAmount() == 100);

  delete vox;
}

TEST_CASE("testing vox talk method", "talk (int, Customer&)") {
  VoxOperator *v1 = new VoxOperator(1, 10.00, 10.00, 10.00, 10, VOX);
  VoxOperator *v2 = new VoxOperator(2, 10.00, 10.00, 10.00, 10, VOX);
  Customer c1(1, "juan", 40, v1, 1000.0);
  Customer c2(2, "pedro", 15, v1, 1000.0);
  Customer c3(2, "luis", 40, v2, 10.0);

  c1.talk(-10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c1.talk(10, c1);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);

  c1.talk(10000, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c1.talk(10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 100);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c1.getTotalSpentTalkingTime() == 10);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c2.talk(10, c1);
	REQUIRE(c2.getBill()->getCurrentDebt() == 90);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 20);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 20);
  REQUIRE(c2.getTotalSpentTalkingTime() == 10);
  REQUIRE(c1.getTotalSpentTalkingTime() == 10);

  c1.talk(10, c3);
	REQUIRE(c1.getBill()->getCurrentDebt() == 200);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 30);
  REQUIRE(c3.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c1.getTotalSpentTalkingTime() == 20);
  REQUIRE(c3.getTotalSpentTalkingTime() == 0);

  delete v1;
  delete v2;
}

TEST_CASE("testing internet talk method", "talk (int, Customer&)") {
  InternetOperator *v1 = new InternetOperator(1, 10.00, 10.00, 10.00, 10, INTERNET);
  InternetOperator *v2 = new InternetOperator(2, 10.00, 10.00, 10.00, 10, INTERNET);
  Customer c1(1, "juan", 40, v1, 1000.0);
  Customer c2(2, "pedro", 15, v1, 1000.0);
  Customer c3(2, "luis", 40, v2, 10.0);

  c1.talk(-10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c1.talk(10, c1);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);

  c1.talk(10000, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 0);
  REQUIRE(c1.getTotalSpentTalkingTime() == 0);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c1.talk(10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 100);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c1.getTotalSpentTalkingTime() == 10);
  REQUIRE(c2.getTotalSpentTalkingTime() == 0);

  c2.talk(1, c1);
	REQUIRE(c2.getBill()->getCurrentDebt() == 9);
  REQUIRE(c2.getOperator()->getTotalSpentTalkingTime() == 11);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 11);
  REQUIRE(c2.getTotalSpentTalkingTime() == 1);
  REQUIRE(c1.getTotalSpentTalkingTime() == 10);

  c1.talk(10, c3);
	REQUIRE(c1.getBill()->getCurrentDebt() == 200);
  REQUIRE(c1.getOperator()->getTotalSpentTalkingTime() == 21);
  REQUIRE(c3.getOperator()->getTotalSpentTalkingTime() == 10);
  REQUIRE(c1.getTotalSpentTalkingTime() == 20);
  REQUIRE(c3.getTotalSpentTalkingTime() == 0);

  delete v1;
  delete v2;
}

TEST_CASE("testing message method", "message(int quantity, const Customer &other)") {
  VoxOperator *v1 = new VoxOperator(1, 10.00, 10.00, 10.00, 10, VOX);
  VoxOperator *v2 = new VoxOperator(2, 10.00, 10.00, 10.00, 10, VOX);
  Customer c1(1, "juan", 40, v1, 1000.0);
  Customer c2(2, "pedro", 15, v1, 1000.0);
  Customer c3(3, "luis", 40, v2, 10.0);

  c1.message(-10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 0);
  REQUIRE(c1.getTotalMessageSent() == 0);
  REQUIRE(c2.getTotalMessageSent() == 0);

  c1.message(10, c1);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 0);
  REQUIRE(c1.getTotalMessageSent() == 0);

  c1.message(10000, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 0);
  REQUIRE(c2.getOperator()->getTotalMessageSent() == 0);
  REQUIRE(c1.getTotalMessageSent() == 0);
  REQUIRE(c2.getTotalMessageSent() == 0);

  c1.message(10, c2);
	REQUIRE(c1.getBill()->getCurrentDebt() == 90);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 10);
  REQUIRE(c2.getOperator()->getTotalMessageSent() == 10);
  REQUIRE(c1.getTotalMessageSent() == 10);
  REQUIRE(c2.getTotalMessageSent() == 0);

  c2.message(10, c1);
	REQUIRE(c2.getBill()->getCurrentDebt() == 90);
  REQUIRE(c2.getOperator()->getTotalMessageSent() == 20);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 20);
  REQUIRE(c2.getTotalMessageSent() == 10);
  REQUIRE(c1.getTotalMessageSent() == 10);

  c1.message(10, c3);
	REQUIRE(c1.getBill()->getCurrentDebt() == 190);
  REQUIRE(c1.getOperator()->getTotalMessageSent() == 30);
  REQUIRE(c3.getOperator()->getTotalMessageSent() == 0);
  REQUIRE(c1.getTotalMessageSent() == 20);
  REQUIRE(c3.getTotalMessageSent() == 0);

  delete v1;
  delete v2;
}

TEST_CASE("testing vox connection method", "connection(double amount)") {
  VoxOperator *v1 = new VoxOperator(1, 10.00, 10.00, 10.00, 10, VOX);
  Customer c1(1, "juan", 40, v1, 1000.0);

  c1.connection(-10);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 0);
  REQUIRE(c1.getTotalInternetUsage() == 0);

  c1.connection(1000);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 0);
  REQUIRE(c1.getTotalInternetUsage() == 0);

  c1.connection(10);
	REQUIRE(c1.getBill()->getCurrentDebt() == 100);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 10);
  REQUIRE(c1.getTotalInternetUsage() == 10);

  delete v1;
}

TEST_CASE("testing internet connection method", "connection(double amount)") {
  InternetOperator *v1 = new InternetOperator(1, 10.00, 10.00, 10.00, 10, INTERNET);
  Customer c1(1, "juan", 40, v1, 1000.0);

  c1.connection(-10);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 0);
  REQUIRE(c1.getTotalInternetUsage() == 0);

  c1.connection(1000);
	REQUIRE(c1.getBill()->getCurrentDebt() == 0);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 0);
  REQUIRE(c1.getTotalInternetUsage() == 0);

  c1.connection(10);
	REQUIRE(c1.getBill()->getCurrentDebt() == 90);
  REQUIRE(c1.getOperator()->getTotalInternetUsage() == 10);
  REQUIRE(c1.getTotalInternetUsage() == 10);

  delete v1;
}
